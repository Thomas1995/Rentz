#ifndef GAME_H
#define GAME_H

#include "util/require.h"
#include "util/card.h"
#include "util/gamelist.h"
#include "player.h"

#include <vector>

struct Table {
    static const int TABLE_SIZE = 4;

    std::vector<Player> players;
    std::vector<Player>::iterator firstPlayer;
    std::vector<Card> cardStack;
    std::vector<int> score;

    static const int gamesNumber = 7;
    int gameType;
    bool modeNV;

    void IterateThroughPlayers(std::vector<Player>::iterator iterator);
    void PlayerAction(Player const player);
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

    void addPlayer(int fd);

    Table();

    static void Start();

    ~Table();
};

#endif // GAME_H
