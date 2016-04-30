#include "bot_Thomas.h"

Bot_Thomas::Bot_Thomas() : gamesOrderNV{Totals, Queens, Diamonds,
  Whist, Acool, KingOfHearts, TenClub} {
    name = "Thomas";
  }

Card Bot_Thomas::PlayCard() {
  /// TO DO BETTER

  auto hand = GetHand();
  if(cardsOnTable.empty()) return hand[0];

  for(auto c : hand)
    if(cardsOnTable[0].isSameSuite(c))
      return c;

  return hand[0];
}

void Bot_Thomas::GetPlayedCardStack() {
  /// TO DO
}

int Bot_Thomas::GetGameType() {
  if(NVModeChosen) {
    // chose a game based on gamesOrderNV
    for(int i=0;i<7;++i)
      if(!gamesPlayed[gamesOrderNV[i]]) {
        gamesPlayed[gamesOrderNV[i]] = true;
        return gamesOrderNV[i];
      }
  }
  else {
    auto hand = GetHand();

    /// TO DO BETTER

    /// DETELE THIS
    for(int i=0;i<7;++i)
      if(!gamesPlayed[gamesOrderNV[i]]) {
        gamesPlayed[gamesOrderNV[i]] = true;
        return gamesOrderNV[i];
      }
  }
}

void Bot_Thomas::SetGameType(const int gameType) {
  crtGameType = gameType;
}

bool Bot_Thomas::PlayNVMode() {
  // play NV mode if not first or second player
  if(myLadderPosition > 2) {
    NVModeChosen = true;
    return true;
  }

  NVModeChosen = false;
  return false;
}

void Bot_Thomas::SetScores(const int yourScore, const std::vector<int>& allScores) {
  // count scores bigger than mine
  int biggerScores = 0;
  for(auto it : allScores) {
    if(it > yourScore)
      ++biggerScores;
  }
  // update my ladder position
  myLadderPosition = biggerScores + 1;
}

