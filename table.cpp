#include "table.h"
#include <algorithm>
#include <random>
#include <chrono>

Table::Table() {}

void Table::Start() {

  debug("The game has started!\n");

  for(size_t i = 0; i < connections.size(); ++i)
    connections[i].sendIndex(i);

  // choose connections in play

  Card::lowestCard = 15 - connections.size() * 2;

  score.resize(4, 0);

  // true if a game was already played but a certain connection, false otherwise
  bool gamesPlayed[connections.size()][gamesNumber+1];

  for(size_t i=0;i<connections.size();++i)
    for(int j=0;j<gamesNumber+1;++j)
      gamesPlayed[i][j] = false;

  // assign the first connection
  firstConnection = connections.begin();

  for(int gameChoice = 1; gameChoice <= gamesNumber; ++gameChoice)
    for(size_t i=0;i<connections.size();++i) {

      // check if connection wants to play NV mode and enforce it for the last choice
      if(gameChoice < gamesNumber)
        modeNV = connections[i].getNVChoice();
      else
        modeNV = true;

      // if NV mode not chosen, give cards before game choice
      if(modeNV == false)
        GiveCards();

      // get the game type
      gameType = connections[i].getGameChoice();

      // if NV mode chosen, give cards after game choice
      if(modeNV == true)
        GiveCards();

      // check if connection can play that game
      require(gameType >= 1 && gameType <= gamesNumber,
          connections[i].getName() + " has chosen a game index out of bounds");
      require(gamesPlayed[i][gameType] == false,
          connections[i].getName() + " had already chosen that game");

      gamesPlayed[i][gameType] = true;

      // let the other connections know the game type
      for(auto connection : connections)
        connection.sendGameChoice(static_cast<uint8_t>(gameType));

      // start the round
      PlayRound();
    }
}

void Table::ConnectionAction(Connection connection) {
  // send connection the cards that were played and get his played card
  connection.sendCards(cardStack);

  Card playedCard = connection.getCardChoice();

  std::cout << connection.getName() << " played " << playedCard << "\n";

  // check if the played card can be played
  if(cardStack.size() > 1) {
    if(!playedCard.isSameSuite(cardStack.front())) {
      auto cards = connection.getHand();
      for(auto c : cards)
        require(!cardStack.front().isSameSuite(c),
            connection.getName() + " had chosen a card of a different suite.");
    }
  }

  // push the card in play
  cardStack.push_back(playedCard);
}

void Table::IterateThroughConnections(std::vector<Connection>::iterator iterator) {
  for(auto it = iterator; it != connections.end(); ++it)
    ConnectionAction(*it);
  for(auto it = connections.begin(); it != iterator; ++it)
    ConnectionAction(*it);
}

void Table::GiveCards() {
  // get all cards in play
  std::vector<Card> allCards = Card::getAllCards();

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(allCards.begin(), allCards.end(), std::default_random_engine(seed));

  auto card = allCards.begin();

  // give cards to connections
  for(size_t i=0;i<connections.size();++i) {
    std::vector<Card> hand;
    for(int j=1;j<=8;++j) {
      hand.push_back(*card);
      ++card;
    }
    connections[i].sendHand(hand);
  }
}

void Table::PlayRound() {
  for(int roundstep = 1; roundstep <= 8; ++roundstep) {
    cardStack.clear();

    // get connections to play cards
    IterateThroughConnections(firstConnection);

    // announce all connections about the cards that were played
    for(size_t i=0;i<connections.size();++i)
      connections[i].sendCards(cardStack);

    // check for winner
    int winnerIndex = 0;
    Card winnerCard = cardStack[winnerIndex];

    for(size_t i=1;i<cardStack.size();++i) {
      if(winnerCard.isBeatenBy(cardStack[i])) {
        winnerCard = cardStack[i];
        winnerIndex = i;
      }
    }

    // change the first connection to go
    while(winnerIndex--) {
      ++firstConnection;
      if(firstConnection == connections.end())
        firstConnection = connections.begin();
    }

    // change score
    ChangeScore();

    std::cout << std::endl;
  }

  // let connections know the scores
  std::cout << "Scores:\n";
  for(size_t i=0;i<connections.size();++i) {
    connections[i].sendScores(score);
    std::cout << connections[i].getName() + ": " << score[i] << "\n";
  }
  std::cout << "\n----------\n";

  std::cout << std::endl;
}

Table::~Table() {
  connections.clear();
}

void Table::addConnection(int fd) {
  connections.emplace_back(Connection(fd));
  if(connections.size() == TABLE_SIZE)
    Start();
}
