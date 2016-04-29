#include "player.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include "event.h"
#include <fcntl.h>
#include "util/require.h"

Player::Player(int fd):
  fd(fd),
  at(0) {
    fcntl(fd, F_SETFL, O_NONBLOCK);
    //make the fd non blocking
    name.resize(100, 0);
    read(fd, (char *)name.data(), name.length());
    name.shrink_to_fit();
    memset(buff, 0, sizeof(buff));
  }

int Player::inc(int &at) {
    at++;
    if(at == MAX_BUFF)
        at = 0;
    return at;
}

std::vector<uint8_t> Player::readFrame() {
  int n;

  const int prev = at;

  while((n = read(fd, buff + at, MAX_BUFF - at)) > 0) {
      at += n;
      if(at >= MAX_BUFF)
          at -= MAX_BUFF;
  }

  for(int i = prev; i != at; inc(i)) {
      if(buff[i] == FLAG) {
          flags.push_back(i);
      }
  }

  if(flags.size() < 2) {
      debug("The client has closed the connection\n");
      exit(1);
      //TODO
      //add disconnect handling
  }

  assert(flags.size() == 2);

  inc(flags[1]);
  //flags[1] refers to the
  //past the flag byte

  std::vector<uint8_t> frame;
  const int cnt = flags[1] > flags[0] ? flags[1] - flags[0] : MAX_BUFF - flags[0] + flags[1];
  frame.reserve(cnt);

  for(int i = flags[0]; i != flags[1]; inc(i)) {
      frame.push_back(buff[i]);
      buff[i] = 0;
  }

  flags.clear();

  frame.shrink_to_fit();
  return frame;
}

Card Player::getCardChoice() {
  event req;
  req.type = event::getCardChoice;
  req.len = 0;
  req.data = NULL;
  req.send(fd);

  event resp;
  resp.init(readFrame().data());

  assert(resp.type == req.type);
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

void Player::sendCards(const std::vector<Card>& cardsOnTable) {
  std::vector<uint8_t> cards;

  for(const auto &c: cardsOnTable)
    cards.push_back(c.encode());

  event req;
  req.type = event::EType::sendCards;
  req.len = cards.size();
  req.data = cards.data();
  req.send(fd);

  event resp;

  resp.init(readFrame().data());

  assert(resp.type == req.type);

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
  req.send(fd);


  event resp;
  resp.init(readFrame().data());

  assert(resp.type == req.type);

  resp.free();
}

std::string Player::getName() {
  return name;
}

std::vector<Card> Player::getHand() {
  return hand;
}

int Player::getGameChoice() {

}

void Player::sendGameChoice(int type) {

}

bool Player::getNVChoice() {

}

void Player::sendHand(const std::vector<Card>& cards) {

}

void Player::sendIndex(size_t index) {

  index = htonl(index);

  event req;
  req.type = event::EType::sendIndex;
  req.len = 4;
  req.data = reinterpret_cast<uint8_t *>(&index);
  req.send(fd);


  event resp;
  resp.init(readFrame().data());
  assert(resp.type == req.type);

  resp.free();
}

