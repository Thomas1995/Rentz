#include "bot.h"

class Bot_Lucian : public Bot {
public:
    Bot_Lucian() {
        name = "Lucian";
    }

    Card PlayCard(const std::vector<Card>& cardsOnTable) {
        auto hand = GetHand();
        if(cardsOnTable.empty()) return hand[0];

        for(auto c : hand)
            if(cardsOnTable[0].isSameSuite(c))
                return c;

        return hand[0];
    }

    void GetPlayedCardStack(const std::vector<Card>& cardsOnTable) {

    }
};
