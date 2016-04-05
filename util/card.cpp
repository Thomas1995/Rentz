#ifndef CARD_IMPL
#define CARD_IMPL

#include "card.h"
#include "require.h"

#include <cstring>

Card::Card(int value, char suite) : value(value), suite(toupper(suite)) {
    require(value >= 2 && value <= 14, "Wrong format!");
    require(strchr(Card::suites, suite), "Wrong format!");
}

Card::Card(const Card& c) : value(c.getValue()), suite(c.getSuite()) {}

std::string Card::to_string() const {
    std::string s;

    switch(value) {
        case 10: s += "10"; break;
        case 11: s += "J"; break;
        case 12: s += "Q"; break;
        case 13: s += "K"; break;
        case 14: s += "A"; break;
        default: s += (char)(value + '0'); break;
    }

    s += suite;

    return s;
}

bool Card::operator == (const Card& c) const {
    return value == c.getValue() && suite == c.getSuite();
}

bool Card::isBeatenBy(const Card& c) const {
    if(isSameType(c))
        return value < c.getValue();
    return false;
}

bool Card::isSameType(const Card& c) const {
    if(suite == c.getSuite())
        return true;
    return false;
}

std::ostream& operator << (std::ostream& os, const Card& c) {
    return os << c.to_string();
}

int Card::getValue() const {
    return value;
}

char Card::getSuite() const {
    return suite;
}

std::vector<Card> Card::getAllCards(const int playerNumber) {
      std::vector<Card> allCards;

      for(int i=15-playerNumber*2;i<=14;++i)
          for(char j=0;j<4;++j)
            allCards.push_back(Card(i, Card::suites[j]));

      return allCards;
}

char Card::suites[] = "DHCS";

#endif // CARD_IMPL
