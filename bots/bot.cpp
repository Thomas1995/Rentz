#include "bot.h"

void Bot::RemoveCard(Card c) {
    auto it = std::find(ALL(hand), c);
    require(it != hand.end(), "Card played by " + name + " not in hand.");
    hand.erase(it);
}
