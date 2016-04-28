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

void sendCards(const std::vector<Card>& cardsOnTable);

void sendScores(const std::vector<int>& allScores);

std::string GetName();
std::vector<Card> GetHand();

int getGameChoice();

void sendGameChoice(int type);

bool getNVChoice();

void sendHand(const std::vector<Card>& cards);

void sendIndex(size_t index);

