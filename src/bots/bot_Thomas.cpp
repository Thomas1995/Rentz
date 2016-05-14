#include "bot_Thomas.h"
#include "../util/debug.h"

Bot_Thomas::Bot_Thomas() : gamesOrderNV{Totals, Queens, Diamonds,
  Whist, Acool, KingOfHearts, TenClub} {
    name = "Thomas";
  }

Card Bot_Thomas::decideCardToPlay() {
  /// TO DO BETTER

  auto card = hand.back();

  if(cardsOnTable.empty())
    goto decided;

  for(const auto &c : hand)
    if(cardsOnTable[0].isSameSuite(c)) {
      card = c;
      goto decided;
    }

decided:
  hand.erase(find(hand.begin(), hand.end(), card));
  return card;
}

std::vector<Card> Bot_Thomas::getPlayedCardStack() {
  return cardsOnTable;
}

uint8_t Bot_Thomas::decideGameType() {
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

void Bot_Thomas::receiveDecidedGameType(const int gameType) {
  crtGameType = gameType;
}

bool Bot_Thomas::decidePlayNV() {
  // play NV mode if not first or second player
  if(myLadderPosition > 2) {
    NVModeChosen = true;
    return true;
  }

  NVModeChosen = false;
  return false;
}
