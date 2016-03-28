#ifndef BOTS
#define BOTS

#include <vector>
#include <algorithm>

#include "../util/card.h"
#include "../util/require.h"
#include "../util/macros.h"

class Bot {
private:
    std::vector<Card> hand;

protected:
    std::string name;

public:
    virtual void SetHand(const std::vector<Card>& cards, const int gameType) = 0;
    virtual Card PlayCard() = 0;

    void RemoveCard(Card c) {
        auto it = std::find(ALL(hand), c);
        require(it != hand.end(), "Card played by " + name + " not in hand.");
        hand.erase(it);
    }

    virtual ~Bot() = 0;
};

#endif // BOTS
