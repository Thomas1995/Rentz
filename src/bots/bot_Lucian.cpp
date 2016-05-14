#include "bot_Lucian.h"
#include "../util/debug.h"

Bot_Lucian::Bot_Lucian() : gamesOrderNV{Totals, Queens, Diamonds,
  Whist, Acool, KingOfHearts, TenClub} {
    name = "Lucian";
  }

Card Bot_Lucian::decideCardToPlay() {
  int x = rand() % hand.size();
  std::swap(hand[x], hand.back());

  auto card = std::move(hand.back());
  hand.pop_back();
  return card;
}

std::vector<Card> Bot_Lucian::getPlayedCardStack() {
  return cardsOnTable;
}

uint8_t Bot_Lucian::decideGameType() {
  if(NVModeChosen) {
    // chose a game based on gamesOrderNV
    for(int i=0;i<7;++i)
      if(!gamesPlayed[gamesOrderNV[i]]) {
        gamesPlayed[gamesOrderNV[i]] = true;
        return gamesOrderNV[i];
      }
  }
  else {
    auto hand = getHand();

    /// TO DO BETTER

    /// DETELE THIS
    for(int i=0;i<7;++i)
      if(!gamesPlayed[gamesOrderNV[i]]) {
        gamesPlayed[gamesOrderNV[i]] = true;
        return gamesOrderNV[i];
      }
  }

  return -1;
}

void Bot_Lucian::receiveDecidedGameType(const int gameType) {
  crtGameType = gameType;
}

bool Bot_Lucian::decidePlayNV() {
  return false;
}
