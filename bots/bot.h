#ifndef BOT_H
#define BOT_H

#include <vector>
#include <algorithm>

#include "../util/card.h"
#include "../util/require.h"

class Bot {
private:
    std::vector<Card> hand;

protected:
    std::string name;

public:
    virtual Card PlayCard(const std::vector<Card>& cardsOnTable) = 0;
    virtual void GetPlayedCardStack(const std::vector<Card>& cardsOnTable) = 0;
    virtual int GetGameType() = 0;
    virtual void SetGameType(const int gameType) = 0;
    virtual bool PlayNVMode() = 0;
    virtual void SetScores(const int yourScore, const std::vector<int>& allScores) = 0;

    std::string GetName();

    std::vector<Card> GetHand();
    void SetHand(const std::vector<Card>& cards);
    void RemoveCard(Card c);
};

#endif // BOT_H
