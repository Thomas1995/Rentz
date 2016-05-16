#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>
#include <algorithm>
#include <assert.h>

struct Card {

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

  static const char suites[];

  std::string to_string() const;

  int suiteIndex() const;

  uint8_t encode() const;

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
