#ifndef GAME_H
#define GAME_H

#include "util/require.h"
#include "util/card.h"
#include "bots/bot.h"

#include "bots/bot_Thomas.cpp"
#include "bots/bot_Lucian.cpp"
#include "bots/bot_Eugen.cpp"
#include "bots/bot_Eric.cpp"

#include <vector>

class Game {
    std::vector<Bot*> players;
    std::vector<Bot*>::iterator firstPlayer;
    std::vector<Card> cardStack;
    std::vector<int> score;

    int crtGameType;
    bool modeNV;

    void IterateThroughPlayers(std::vector<Bot*>::iterator iterator);
    void PlayerAction(Bot* const player);
    void PlayRound();
    void ChangeScore();

    void ScoreKingOfHearts(int& scoreToAdd);
    void ScoreQueens(int& scoreToAdd);
    void ScoreDiamonds(int& scoreToAdd);
    void ScoreAcool(int& scoreToAdd);
    void ScoreWhist(int& scoreToAdd);
    void ScoreTenClub(int& scoreToAdd);
    void ScoreTotals(int& scoreToAdd);

    Game();

public:
    static void Start();

    ~Game();
};

#endif // GAME_H
