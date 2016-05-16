#include "connection.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include "event.h"
#include <fcntl.h>
#include "util/debug.h"

#define readAndAssert(resp) event resp = readEvent();\
                      assert(resp.type == req.type);

Connection::Connection(int sfd):
  Common(sfd) {
    name = requestName();
    debug("Connection on sfd = %d is named %s\n", sfd, name.c_str());
  }

Card Connection::getCardChoice() {
  event req;
  req.type = event::ASK_CARD;
  req.len = 0;
  req.data = NULL;
  req.send(sfd);

  readAndAssert(resp);

  assert(resp.len == 1);

  Card card(resp.data[0]);

  debug("Received card %s from client\n", card.to_string().c_str());

  bool in = 0;

  for(const auto &i: hand) {
      if(i == card)
          in = 1;
  }

  if(!in) {
      debug("The client has sent an incorrect card");
      exit(1);
  }

  hand.erase(find(hand.begin(), hand.end(), card));

  resp.free();
  return card;
}

std::vector<uint8_t> encodeCards(const std::vector<Card>& cards) {
  std::vector<uint8_t> ret;

  for(const auto &c: cards)
    ret.push_back(c.encode());

  return ret;
}

std::string Connection::requestName() {
  event req;
  req.type = event::EType::ASK_NAME;
  req.len = 0;
  req.data = NULL;
  req.send(sfd);

  readAndAssert(resp);

  std::string name;

  for(size_t i = 0; i < resp.len; ++i) {
    name += resp.data[i];
  }

  resp.free();
  return name;
}

void Connection::sendCards(const std::vector<Card>& cardsOnTable) {

  auto cards = encodeCards(cardsOnTable);

  event req;
  req.type = event::EType::SEND_CARDS;
  req.len = cards.size();
  req.data = cards.data();
  req.send(sfd);

  readAndAssert(resp);

  resp.free();
}

void Connection::sendScores(const std::vector<int>& allScores) {

  std::vector<uint8_t> data;

  data.reserve(allScores.size() * 4);

  for(const auto &i: allScores) {
    const int x = htonl(i);
    const uint8_t*const ptr = reinterpret_cast<const uint8_t *const>(&x);
    for(int i = 0; i < 4; ++i)
      data.push_back(ptr[i]);
  }

  event req;
  req.type = event::EType::ROUND_END;
  req.len = data.size();
  req.data = data.data();
  req.send(sfd);

  readAndAssert(resp);

  resp.free();
}

void Connection::gameEnd() {
  event req;
  req.type = event::EType::GAME_END;
  req.len = 0;
  req.data = 0;
  req.send(sfd);

  readAndAssert(resp);
  resp.free();
}

std::string Connection::getName() {
  return name;
}

std::vector<Card> Connection::getHand() {
  return hand;
}

uint8_t Connection::getGameChoice() {
  event req;
  req.type = event::EType::ASK_GAME;
  req.len = 0;
  req.data = NULL;
  req.send(sfd);

  readAndAssert(resp);
  assert(resp.len == 1);

  uint8_t choice = resp.data[0];
  resp.free();
  return choice;
}

void Connection::sendGameChoice(uint8_t type) {
  event req;
  req.type = event::EType::ROUND_START;
  req.len = 1;
  req.data = &type;
  req.send(sfd);

  readAndAssert(resp);

  resp.free();
}

bool Connection::getNVChoice() {
  event req;
  req.type = event::EType::ASK_NV;
  req.len = 0;
  req.data = NULL;
  req.send(sfd);

  readAndAssert(resp);
  assert(resp.len == 1);
  bool NV = resp.data[0];

  resp.free();
  return NV;
}

void Connection::sendHand(const std::vector<Card>& hand) {
  auto cards = encodeCards(hand);
  event req;
  req.type = event::EType::SEND_HAND;
  req.len = cards.size();
  req.data = cards.data();
  req.send(sfd);

  this->hand = hand;

  readAndAssert(resp);

  resp.free();
}

void Connection::sendIndex(size_t index) {

  index = htonl(index);

  event req;
  req.type = event::EType::SEND_INIT;
  req.len = 4;
  req.data = reinterpret_cast<uint8_t *>(&index);
  req.send(sfd);


  readAndAssert(resp);

  resp.free();
}

