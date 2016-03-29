#ifndef GAME_H
#define GAME_H

#include "util/require.h"
#include "bots/bot.h"

#include "bots/bot_Thomas.cpp"

#include <vector>

class Game {
    std::vector<Bot*> players;

    Game();

public:
    static void Start();

    void PlayKingOfHearts();
};

#endif // GAME_H
