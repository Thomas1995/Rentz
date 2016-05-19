#include "card.h"
#include "require.h"
#include "../table.h"

#include <cstring>
#include <string>

Card::Card(int value, char suite) : value(value), suite(toupper(suite)) {
    require(value >= 2 && value <= 14, "Wrong format: " + std::to_string(value));
    require(strchr(Card::suites, suite), "Wrong format: " + std::to_string(suite));
}

Card::Card(uint8_t code):
  value(code & 0b1111),
  suite(suites[code >> 4]) {

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
  return to_string() == c.to_string();
}

bool Card::isBeatenBy(const Card& c) const {
    if(isSameSuite(c))
        return value < c.getValue();
    return false;
}

bool Card::isSameSuite(const Card& c) const {
    if(suite == c.getSuite())
        return true;
    return false;
}

std::ostream& operator << (std::ostream& os, const Card& c) {
    return os << c.to_string();
}

int Card::suiteIndex() const {
  for(int i = 0; i < 4; ++i) {
    if(suites[i] == suite)
      return i;
  }
  assert(false);
}

uint8_t Card::encode() const {
  uint8_t ret = value;
  //the last 4 bits represent the value
  ret |= suiteIndex() << 4;
  //the next 2 bits represent the suite
  return ret;
}

int Card::getValue() const {
    return value;
}

char Card::getSuite() const {
    return suite;
}

std::vector<Card> Card::getAllCards() {
      std::vector<Card> allCards;

      for(int i=lowestCard;i<=14;++i)
          for(char j=0;j<4;++j)
            allCards.push_back(Card(i, Card::suites[(int)j]));

      return allCards;
}

const char Card::suites[] = "DHCS";
int Card::lowestCard = 1;
