#ifndef BOT_H
#define BOT_H

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
    virtual Card PlayCard() = 0;

    void SetHand(const std::vector<Card>& cards);
    void RemoveCard(Card c);

    virtual ~Bot() = 0;
};

#endif // BOT_H
