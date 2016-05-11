#ifndef COMMON_H
#define COMMON_H
#include <vector>
#include <stdint.h>
#include "event.h"
#include <vector>
#include "event.h"
#include <sys/socket.h>
#include <stdlib.h>
#include "util/debug.h"
#include <unistd.h>

/* Common is a common interface
 * that both Connection (the server's view of the world)
 * and Client (the clients which connect to the server
 *             from the other side of the wire)
 */

struct Common {
  static const int MAX_BUFF = 1024 * 8;
  std::vector<int> flags;
  char buff[MAX_BUFF];
  int at;
  int sfd;

  int inc(int &x);

  std::vector<uint8_t> readFrame();

  event readEvent();

  Common();

  Common(int sfd);
};

#endif
