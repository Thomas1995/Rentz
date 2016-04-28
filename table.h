#ifndef GAME_H
#define GAME_H

#include "util/require.h"
#include "util/card.h"
#include "util/gamelist.h"
#include "bots/bot.h"

#include <vector>

class Table {
    std::vector<Bot*> players;
    std::vector<Bot*>::iterator firstPlayer;
    std::vector<Card> cardStack;
    std::vector<int> score;

    const int gamesNumber = 7;
    int crtTableType;
    bool modeNV;

    void IterateThroughPlayers(std::vector<Bot*>::iterator iterator);
    void PlayerAction(Bot* const player);
    void GiveCards();
    void PlayRound();
    void ChangeScore();

    void ScoreKingOfHearts(int& scoreToAdd);
    void ScoreQueens(int& scoreToAdd);
    void ScoreDiamonds(int& scoreToAdd);
    void ScoreAcool(int& scoreToAdd);
    void ScoreWhist(int& scoreToAdd);
    void ScoreTenClub(int& scoreToAdd);
    void ScoreTotals(int& scoreToAdd);

    Table();

public:
    static void Start();

    ~Table();
};

#endif // GAME_H
