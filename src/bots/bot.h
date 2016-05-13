#ifndef BOT_H
#define BOT_H

#include <vector>
#include <algorithm>

#include "../util/card.h"
#include "../util/require.h"
#include "../util/gamelist.h"

class Bot {
  public:
    std::vector<Card> hand;

    std::string name;
    std::vector<Card> cardsOnTable;

    std::vector<int> scores;

    virtual void receiveCardsOnTable(const std::vector<Card> &cards);

    virtual void receiveHand(const std::vector<Card> &cards);

    virtual void sendScores(const std::vector<int> &scores);

    virtual uint8_t decideGameType() = 0;

    std::vector<Card> getHand();

    virtual void receiveDecidedGameType(const int gameType) = 0;

    virtual Card decideCardToPlay() = 0;

    virtual bool decidePlayNV() = 0;

    virtual ~Bot() = default;
};

#endif // BOT_H
