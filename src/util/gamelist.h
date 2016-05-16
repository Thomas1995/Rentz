#ifndef GAMELIST
#define GAMELIST

#include <vector>
#include <string>

enum Minigame {
  KingOfHearts = 1,
  Queens = 2,
  Diamonds = 3,
  Acool = 4,
  Whist = 5,
  TenClub = 6,
  Totals = 7
};
const int MinigameCount = 7;

const std::vector<std::string> GameName = {
	"null",
	"King of Hearts",
	"Queens",
	"Diamonds",
	"Acool",
	"Whist",
	"Ten of clubs",
	"Totals"
};

#endif // GAMELIST
