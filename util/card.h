#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>
#include <algorithm>
#include <assert.h>

class Card {

int value;
/*
    2-10
    J: 11
    Q: 12
    K: 13
    A: 14
*/

char suite;
/*
    Hearts: 'H'
    Clubs: 'C'
    Diamonds: 'D'
    Spades: 'S'
*/

static char suites[];

std::string to_string() const;

public:

  int suiteIndex() {
    for(int i = 0; i < 4; ++i) {
      if(suites[i] == suite)
        return i;
    }
    assert(false);
  }

  uint8_t encode() {
    uint8_t ret = value;
    //the last 4 bits represent the value
    ret |= suiteIndex() << 4;
    //the next 2 bits represent the suite
    return ret;
  }

    Card(uint8_t code);
    Card(int value, char suite);
    Card(const Card& c);

    bool operator == (const Card& c) const;

    bool isBeatenBy(const Card& c) const;
    bool isSameSuite(const Card& c) const;

    int getValue() const;
    char getSuite() const;

    static std::vector<Card> getAllCards();

    friend std::ostream& operator << (std::ostream& os, const Card& c);

    static int lowestCard;
};

#endif // CARD_H
