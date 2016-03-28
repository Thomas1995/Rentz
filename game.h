#ifndef GAME_H
#define GAME_H

#include "util/require.h"
#include "bots/bot.h"

#include <vector>

class Game {

    std::vector<Bot*> players;

public:
    Game();

    void PlayKingOfHearts();
};

#endif // GAME_H
