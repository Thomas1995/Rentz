#ifndef PLAYER_H
#define PLAYER_H
#include "util/card.h"
#include "util/require.h"
#include "util/gamelist.h"
#include <vector>
#include <algorithm>


struct Player {

    std::string name;
    int fd;

    std::vector<Card> hand;

    Card getCardChoice();
    void sendCards(const std::vector<Card>& cardsOnTable);

    void sendScores(const std::vector<int>& allScores);

    std::string getName();
    std::vector<Card> getHand();

    int getGameChoice();

    void sendGameChoice(int type);

    bool getNVChoice();

    void sendHand(const std::vector<Card>& cards);

    Player() = delete;
    explicit Player(int fd);

    void sendIndex(size_t index);

};

#endif
