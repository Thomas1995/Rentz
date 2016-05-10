#ifndef GAME_H
#define GAME_H

#include "util/require.h"
#include "util/card.h"
#include "util/gamelist.h"
#include "connection.h"

#include <vector>

struct Table {
    static const int TABLE_SIZE = 1;

    std::vector<Connection> connections;
    std::vector<Connection>::iterator firstConnection;
    std::vector<Card> cardStack;
    std::vector<int> score;

    static const int gamesNumber = 7;
    int gameType;
    bool modeNV;

    void IterateThroughConnections(std::vector<Connection>::iterator iterator);
    void ConnectionAction(Connection const connection);
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

    void addConnection(int fd);

    Table();

    void Start();

    ~Table();
};

#endif // GAME_H
