#include <netdb.h>
#include <string>
#include <fcntl.h>
#include <assert.h>
#include <sstream>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include "util/require.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <vector>
#include "event.h"
#include "common.h"

const char PORT[] = "31337";

struct Client : public Common {

  int index;

  Client() = delete;

  Client(char **argv) {

    addrinfo hints, *rez;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo(argv[1], PORT, &hints, &rez);

    for(addrinfo *p = rez; p != NULL; p = p->ai_next) {
      sfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

      if(sfd == -1)
        continue;

      if(connect(sfd, p->ai_addr, p->ai_addrlen) != -1) {
        printf("Connected to %s\n", argv[1]);
        break;
      }

      close(sfd);
    }

    fcntl(sfd, F_SETFL, O_NONBLOCK);

    freeaddrinfo(rez);

    handshake(argv[2]);

    while(1) {

    }
  }

  void handshake(char* name) {

    event e = readEvent();
    assert(e.type = event::EType::requestName);
    e.free();

    e.len = strlen(name);
    e.data = reinterpret_cast<uint8_t *>(name);

    e.send(sfd);
  }
};

int main(int argc, char ** argv) {

  if(argc != 3) {
    printf("Usage: %s server-address bot-name\n", argv[0]);
    exit(1);
  }

  Client client(argv);


  return 0;
}

