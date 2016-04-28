#include <sys/types.h>
#include <arpa/inet.h>
#include <vector>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "table.h"

const char PORT[] = "31337";
const int BACKLOG = 16;
const int MAX_EVENTS = 1024;

int setupServer() {
//returns server's fd

  struct addrinfo hints, *rez;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  getaddrinfo(NULL, PORT, &hints, &rez);

  int yes = 1;

  int server = -1;

  for(addrinfo *p = rez; p != NULL; p = p->ai_next) {
    server = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

    if(server == -1) {
      perror("Socket() failed: ");
      continue;
    }

    if(setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
      perror("Setsockopt() failed: ");
      exit(1);
    }

    if(bind(server, p->ai_addr, p->ai_addrlen) == -1) {
      perror("Bind() failed: ");
      exit(1);
    }


    if(listen(server, BACKLOG) == -1) {
      perror("Listen() failed: ");
      exit(1);
    }

    break;
  }

  freeaddrinfo(rez);
  return server;
}

void addEvent(const int epfd, const int fd, const int flags) {
  epoll_event e;
  memset(&e, 0, sizeof(e));
  e.events = flags;
  e.data.fd = fd;
  epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &e);
}

int acceptConnection(int server) {
  sockaddr_storage addr;
  socklen_t addrlen = sizeof(addr);
  int client = accept(server, (sockaddr *)&addr, &addrlen);

  char buff[INET6_ADDRSTRLEN];

  if(addr.ss_family == AF_INET) {
  //the client is using IPv4
    sockaddr_in *sin = (sockaddr_in *)&addr;
    inet_ntop(sin->sin_family, (void *)&sin->sin_addr, buff, sizeof(buff));
    printf("Accepted connection from %s: %d", buff, sin->sin_port);
  } else {
  //the client is using IPv6
    sockaddr_in6 *sin = (sockaddr_in6 *)&addr;
    inet_ntop(sin->sin6_family, (void *)&sin->sin6_addr, buff, sizeof(buff));
    printf("Accepted connection from %s: %d", buff, sin->sin6_port);
  }

  if(client == -1) {
    perror("Accept() failed: ");
    exit(1);
  }
  return client;
}

int main() {
  Table table;
  const int server = setupServer();

  if(server == -1) {
    printf("Could not set up server\n");
    exit(1);
  }

  printf("Listening for connections\n");

  const int epfd = epoll_create1(0);
  if(epfd == -1) {
    perror("Epoll_create() failed: ");
    exit(1);
  }
  addEvent(epfd, server, EPOLLIN);

  std::vector<epoll_event> events(MAX_EVENTS);
  while(true) {
    const int n = epoll_wait(epfd, events.data(), MAX_EVENTS, -1);
    for(int i = 0; i < n; ++i) {
      const epoll_event &now = events[i];
      if(now.data.fd == server) {
        int client = acceptConnection(server);
        table.addPlayer(client);
      }
    }
  }
  return 0;
}
