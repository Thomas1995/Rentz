#ifndef GAME_H
#define GAME_H

#include "util/require.h"
#include "util/card.h"
#include "util/gamelist.h"
#include "connection.h"

#include <vector>

struct Table {
    static unsigned int TABLE_SIZE;
    bool GAME_END;

    std::vector<Connection> players;
    std::vector<Connection>::iterator firstPlayer;
    std::vector<Card> cardStack;
    std::vector<int> score;

    static const int gamesNumber = 7;
    int gameType;
    bool modeNV;

    void PlayTurn(std::vector<Connection>::iterator iterator);
    //Simulates current turn

    void PlayerAction(Connection &player);
    //Requests a player to play a card

    void GiveHands();
    //Gives hands to players

    void PlayRound();
    //Simulates a round

    void ChangeScore();
    //Updates scores

    void printScores();
    //Prints scores to console

    //Score update functions
    void ScoreKingOfHearts(int& scoreToAdd);
    void ScoreQueens(int& scoreToAdd);
    void ScoreDiamonds(int& scoreToAdd);
    void ScoreAcool(int& scoreToAdd);
    void ScoreWhist(int& scoreToAdd);
    void ScoreTenClub(int& scoreToAdd);
    void ScoreTotals(int& scoreToAdd);


    void addPlayer(int fd);
    //Adds a player (as a socket) to the table
    
    Table();

    void Start();
};

#endif // GAME_H
