#ifndef CARD_IMPL
#define CARD_IMPL

#include "card.h"

Card::Card(int value, char suite) : value(value), suite(suite) {}

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

    s += toupper(suite);

    return s;
}

bool Card::operator == (const Card& c) const {
    return value == c.getValue() && suite == c.getSuite();
}

bool Card::isBeatenBy(const Card& c) const {
    if(suite == c.getSuite())
        return value < c.getValue();

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

#endif // CARD_IMPL
