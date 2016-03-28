#ifndef CARD_H
#define CARD_H

#include <string>

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

std::string to_string() const;

public:
    Card(int value, char suite);
    Card(const Card& c);

    bool operator == (const Card& c) const;

    bool isBeatenBy(const Card& c) const;

    int getValue() const;
    char getSuite() const;

    friend std::ostream& operator << (std::ostream& os, const Card& c);
};

#endif // CARD_H
