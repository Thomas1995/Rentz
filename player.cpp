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

  assert(resp.type == event::getCardChoice);
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

  return card;
}

void Player::sendCards(const std::vector<Card>& cardsOnTable) {

}

void Player::sendScores(const std::vector<int>& allScores) {

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

}

