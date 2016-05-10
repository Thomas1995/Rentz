#ifndef GAME_H
#define GAME_H

#include "util/require.h"
#include "util/card.h"
#include "util/gamelist.h"
#include "connection.h"

#include <vector>

struct Table {
    static const int TABLE_SIZE = 1;

    std::vector<Connection> players;
    std::vector<Connection>::iterator firstPlayer;
    std::vector<Card> cardStack;
    std::vector<int> score;

    static const int gamesNumber = 7;
    int gameType;
    bool modeNV;

    void IterateThroughPlayers(std::vector<Connection>::iterator iterator);
    void PlayerAction(Connection &player);
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

    void Start();

    ~Table();
};

#endif // GAME_H
