#include "bot.h"

void Bot::receiveCardsOnTable(const std::vector<Card> &cards) {
  cardsOnTable = cards;
}

void Bot::receiveHand(const std::vector<Card> &cards) {
  hand = cards;
}


void Bot::sendScores(const std::vector<int> &scores) {
  this->scores = scores;
}

std::vector<Card> Bot::getHand() {
  return hand;
}
