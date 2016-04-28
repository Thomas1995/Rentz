#ifndef EVENT_H
#define EVENT_H

struct event {
  enum EType {
    cardData,
    scoreData,
    getGameChoice,
    getCardChoice,
    sendGameChoice,
    getNVChoice,
    sendHand,
    index
  };

  EType type;
  void *data;
};

#endif
