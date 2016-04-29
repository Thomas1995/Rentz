#ifndef PLAYER_H
#define PLAYER_H
#include "util/card.h"
#include "util/require.h"
#include "util/gamelist.h"
#include <vector>
#include <algorithm>
#include "event.h"

struct Player {

    static const size_t MAX_BUFF = 1024 * 8;

    std::string name;
    int fd;

    uint8_t buff[MAX_BUFF];
    int at;

    std::vector<int> flags;

    std::vector<Card> hand;

    int inc(int &at);

    void sendCards(const std::vector<Card>& cardsOnTable);

    std::vector<uint8_t> readFrame();

    event readEvent();

    void sendScores(const std::vector<int>& allScores);

    Card getCardChoice();

    int getGameChoice();

    void sendGameChoice(int type);

    bool getNVChoice();

    void sendHand(const std::vector<Card>& cards);

    Player() = delete;
    explicit Player(int fd);

    void sendIndex(size_t index);

    std::string getName();
    std::vector<Card> getHand();

};

#endif
