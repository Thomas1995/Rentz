#include "bot_Eric.h"
#include "../util/debug.h"

Bot_Eric::Bot_Eric() : gamesOrderNV{Totals, Queens, Diamonds,
  Whist, Acool, KingOfHearts, TenClub} {
    setName("Eric");
  }

Card Bot_Eric::onPlayCard() {
  /// TO DO BETTER

  auto hand = getHand();
  auto card = hand.back();
  auto cardsOnTable = getCardsOnTable();

  if(cardsOnTable.empty())
    goto decided;

  for(const auto &c : hand)
    if(cardsOnTable[0].isSameSuite(c)) {
      card = c;
      goto decided;
    }

decided:
  return card;
}

Minigame Bot_Eric::onChooseMinigame() {
  auto games = getAvailableGames();

  if(NVModeChosen) {
    // chose a game based on gamesOrderNV
    for(auto game : gamesOrderNV)
      if(find(games.begin(), games.end(), game) != games.end()) {
        return game;
      }
  }
  else {
    auto hand = getHand();

    /// TODO BETTER
    return games.back();
  }

  assert(false);
  return Minigame::Totals;
}

bool Bot_Eric::onAskIfNV() {
  // play NV mode if not first or second player
  if(myLadderPosition > 2) {
    NVModeChosen = true;
    return true;
  }

  NVModeChosen = false;
  return false;
}
