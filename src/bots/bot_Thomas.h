#ifndef BOT_THOMAS_H
#define BOT_THOMAS_H

#include "bot.h"

class Bot_Thomas : public Bot {
private:
	std::vector<Minigame> gamesOrderNV;
	int myLadderPosition;
	bool NVModeChosen;

public:
	Bot_Thomas() : gamesOrderNV{Totals, Queens, Diamonds,
	  Whist, Acool, KingOfHearts, TenClub} {
	    setName("Thomas");
	  }

	Card onPlayCard() {
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

	Minigame onChooseMinigame() {
	  auto games = getAvailableGames();

	  if(NVModeChosen) {
	    // chose a game based on gamesOrderNV
	    for(auto game : gamesOrderNV)
	      if(find(games.begin(), games.end(), game) != games.end()) {
	        return game;
	      }
	  }
	  else {
	    return games[rand() % games.size()];
	  }

	  assert(false);
	  return Minigame::Totals;
	}

	bool onAskIfNV() {
	  // play NV mode if not first or second player
	  if(myLadderPosition > 2) {
	    NVModeChosen = true;
	    return true;
	  }

	  NVModeChosen = false;
	  return false;
	}
};

#endif //BOT_THOMAS_H

