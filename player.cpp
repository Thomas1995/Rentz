#include "player.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include "event.h"
#include <fcntl.h>
#include "util/debug.h"

#define readAndAssert(resp) event resp = readEvent();\
                      assert(resp.type == req.type);

Player::Player(int sfd):
  Common(sfd) {
    name = requestName();
    debug("Player on sfd = %d is named %s\n", sfd, name.c_str());
  }

Card Player::getCardChoice() {
  event req;
  req.type = event::getCardChoice;
  req.len = 0;
  req.data = NULL;
  req.send(sfd);

  readAndAssert(resp);

  assert(resp.len == 1);

  Card card(resp.data[0]);

  bool in = 0;

  for(const auto &i: hand) {
      if(i == card)
          in = 1;
  }

  if(!in) {
      debug("The client has sent an incorrect card");
      exit(1);
  }

  resp.free();
  return card;
}

std::vector<uint8_t> encodeCards(const std::vector<Card>& cards) {
  std::vector<uint8_t> ret;

  for(const auto &c: cards)
    ret.push_back(c.encode());

  return ret;
}

std::string Player::requestName() {
  event req;
  req.type = event::EType::requestName;
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

void Player::sendCards(const std::vector<Card>& cardsOnTable) {

  auto cards = encodeCards(cardsOnTable);

  event req;
  req.type = event::EType::sendCards;
  req.len = cards.size();
  req.data = cards.data();
  req.send(sfd);

  readAndAssert(resp);

  resp.free();
}

void Player::sendScores(const std::vector<int>& allScores) {

  std::vector<uint8_t> data;

  data.reserve(allScores.size() * 4);

  for(const auto &i: allScores) {
    const int x = htonl(i);
    const uint8_t*const ptr = reinterpret_cast<const uint8_t *const>(&x);
    for(int i = 0; i < 4; ++i)
      data.push_back(ptr[i]);
  }

  event req;
  req.type = event::EType::sendScores;
  req.len = data.size();
  req.data = data.data();
  req.send(sfd);

  readAndAssert(resp);

  resp.free();
}

std::string Player::getName() {
  return name;
}

std::vector<Card> Player::getHand() {
  return hand;
}

uint8_t Player::getGameChoice() {
  event req;
  req.type = event::EType::getGameChoice;
  req.len = 0;
  req.data = NULL;
  req.send(sfd);

  readAndAssert(resp);
  assert(resp.len == 1);

  uint8_t choice = resp.data[0];
  resp.free();
  return choice;
}

void Player::sendGameChoice(uint8_t type) {
  event req;
  req.type = event::EType::sendGameChoice;
  req.len = 1;
  req.data = &type;
  req.send(sfd);

  readAndAssert(resp);

  resp.free();
}

bool Player::getNVChoice() {
  event req;
  req.type = event::EType::getNVChoice;
  req.len = 0;
  req.data = NULL;
  req.send(sfd);

  readAndAssert(resp);
  assert(resp.len == 1);
  bool NV = resp.data[0];

  resp.free();
  return NV;
}

void Player::sendHand(const std::vector<Card>& hand) {
  auto cards = encodeCards(hand);
  event req;
  req.type = event::EType::sendHand;
  req.len = cards.size();
  req.data = cards.data();
  req.send(sfd);

  readAndAssert(resp);

  resp.free();
}

void Player::sendIndex(size_t index) {

  index = htonl(index);

  event req;
  req.type = event::EType::sendIndex;
  req.len = 4;
  req.data = reinterpret_cast<uint8_t *>(&index);
  req.send(sfd);


  readAndAssert(resp);

  resp.free();
}

