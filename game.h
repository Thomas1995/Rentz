#ifndef GAME_H
#define GAME_H

#include "util/require.h"
#include "util/card.h"
#include "bots/bot.h"

#include "bots/bot_Thomas.cpp"

#include <vector>
#include <stack>

class Game {
    std::vector<Bot*> players;
    std::vector<Bot*>::iterator firstPlayer;
    std::stack<Card> cardStack;

    Game();

    void IterateThroughPlayers(std::vector<Bot*>::iterator iterator);
    void PlayerAction(Bot* const player);

public:
    static void Start();

    void PlayRound();

    ~Game();
};

#endif // GAME_H
