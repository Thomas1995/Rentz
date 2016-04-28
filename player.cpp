#include "player.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

Player::Player(int fd):
  fd(fd) {
    name.resize(100, 0);
    read(fd, (char *)name.data(), name.length());
    name.shrink_to_fit();
  }


Card Player::getCardChoice() {

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

