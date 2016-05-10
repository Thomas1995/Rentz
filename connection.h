#ifndef connection_H
#define connection_H
#include "util/card.h"
#include "util/require.h"
#include "util/gamelist.h"
#include <vector>
#include <algorithm>
#include "event.h"
#include "common.h"

struct Connection : public Common {

    std::string name;

    std::vector<Card> hand;

    void sendCards(const std::vector<Card>& cardsOnTable);

    void sendScores(const std::vector<int>& allScores);

    Card getCardChoice();

    uint8_t getGameChoice();

    void sendGameChoice(uint8_t type);

    bool getNVChoice();

    void sendHand(const std::vector<Card>& cards);

    std::string requestName();

    Connection() = delete;
    explicit Connection(int sfd);

    void sendIndex(size_t index);

    std::string getName();
    std::vector<Card> getHand();

};

#endif
