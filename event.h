#ifndef EVENT_H
#define EVENT_H
#include <limits.h>
#include <vector>
#include <stdint.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

struct event {
#define append(b) \
      if(b == FLAG || b == ESC) {\
        message.push_back(ESC);\
        message.push_back(b ^ MAGIC);\
      } else {\
        message.push_back(b);\
      }

  static const int FLAG = 0x7E;
  static const int ESC = 0x7D;
  static const int MAGIC = 0x20;
  enum EType {
    cardData,
    scoreData,
    getGameChoice,
    getCardChoice,
    sendGameChoice,
    getNVChoice,
    sendHand,
    index,
    null = LONG_MAX
    //this is in order to force EType to be of type int
  };

  EType type;
  size_t len;
  void *data;

  void send(int fd) {
    std::vector<uint8_t> header(8, 0);
    ((uint32_t *)header.data())[0] = htonl(type);
    ((uint32_t *)header.data())[1] = htonl(len);

    std::vector<uint8_t> message;
    message.reserve(8 + len + 2);
    message.push_back(FLAG);

    for(auto &b: header) {
      append(b);
    }

    for(size_t i = 0; i < len; ++i) {
      uint8_t b = ((uint8_t *)data) [i];
      append(b);
    }

    message.push_back(FLAG);

    ::send(fd, message.data(), message.size(), 0);
  }
};

#endif
