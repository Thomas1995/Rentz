#include "table.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <vector>

unsigned int Table::TABLE_SIZE = 0;

Table::Table() {
    GAME_END = false;
    GAME_STARTED = false;
}

void Table::Start() {

  std::cout << "\n\nA new game has started!\n\n";

  GAME_STARTED = true;

  for(size_t i = 0; i < players.size(); ++i)
    players[i].sendIndex(i);

  // choose players in play

  Card::lowestCard = 15 - players.size() * 2;

  score.resize(TABLE_SIZE, 0);

  // true if a game was already played but a certain connection, false otherwise
  std::vector<std::vector<bool>> gamesPlayed(players.size(), std::vector<bool>(gamesNumber + 1, false));

  for(size_t i=0;i<players.size();++i)
    for(int j=0;j<gamesNumber+1;++j)
      gamesPlayed[i][j] = false;

  // assign the first connection
  firstPlayer = players.begin();

  for(int gameChoice = 1; gameChoice <= gamesNumber; ++gameChoice) {

    for(size_t i=0;i<players.size();++i) {
      // set the first player
      firstPlayer = players.begin() + i;

      std::cout << "Pre-round:\n";
      std::cout << "First player is " << firstPlayer->getName() << '\n';

      // check if connection wants to play NV mode and enforce it for the last choice
      if(gameChoice < gamesNumber) {
        modeNV = players[i].getNVChoice();
      } else {
        modeNV = true;
      }

      // check if modeNV was chosed
      if(modeNV) {
        std::cout << "NV Mode chosen!\n";
      } else {
        std::cout << "NV Mode not chosen!\n";
      }

      // if NV mode not chosen, give cards before game choice
      if(modeNV == false) {
        GiveHands();
        gameType = players[i].getGameChoice();
      } else {
        gameType = players[i].getGameChoice();
        GiveHands();
      }

      // check if connection can play that game
      require(gameType >= 1 && gameType <= gamesNumber,
          players[i].getName() + " has chosen a game index out of bounds\n");

      std::cout << players[i].getName() << " chose to play: " << GameName[gameType] << '\n';

      require(gamesPlayed[i][gameType] == false,
          players[i].getName() + " had already chosen that game\n");

      gamesPlayed[i][gameType] = true;

      // let the other players know the game type
      for(auto &connection : players)
        connection.sendGameChoice(static_cast<uint8_t>(gameType));

      // start the round
      PlayRound();
    }
  }
  std::cout << "Game is over!\n";
  printScores();

  for(auto &connection: players)
    connection.gameEnd();

  GAME_END = true;
}

void Table::PlayerAction(Connection &connection) {
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
            connection.getName() + " had chosen a card of a different suite.\n");
    }
  }

  // push the card in play
  cardStack.push_back(playedCard);
}

void Table::PlayTurn(std::vector<Connection>::iterator iterator) {
  for(auto it = iterator; it != players.end(); ++it)
    PlayerAction(*it);
  for(auto it = players.begin(); it != iterator; ++it)
    PlayerAction(*it);
  std::cout << std::endl;
}

void Table::GiveHands() {
  // get all cards in play
  std::vector<Card> allCards = Card::getAllCards();

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(allCards.begin(), allCards.end(), std::default_random_engine(seed));

  auto card = allCards.begin();

  // give cards to players
  for(size_t i=0;i<players.size();++i) {
    std::vector<Card> hand;
    for(int j=1;j<=8;++j) {
      hand.push_back(*card);
      ++card;
    }
    players[i].sendHand(hand);
  }
}

void Table::printScores() {
  std::cout << "Scores:\n";
  for(size_t i=0;i<players.size();++i) {
    players[i].sendScores(score);
    std::cout << players[i].getName() + ": " << score[i] << "\n";
  }
}

void Table::PlayRound() {
  std::cout << "\nStarting new round!\n\n";

  // For each of the 8 turns
  for(int roundstep = 1; roundstep <= 8; ++roundstep) {
    cardStack.clear();

    // Play the turn
    PlayTurn(firstPlayer);

    // Trigger EndTurn to all players
    for(size_t i=0;i<players.size();++i) {
      players[i].sendCards(cardStack);
      players[i].turnEnd();
    }

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
      ++firstPlayer;
      if(firstPlayer == players.end())
        firstPlayer = players.begin();
    }

    // change score
    ChangeScore();
  }

  std::cout << "Round over!\n\n";

  // print the final scores
  printScores();
  std::cout << "\n--------------------------\n";

  std::cout << std::endl;
}

void Table::addPlayer(int fd) {
  players.emplace_back(fd, TABLE_SIZE);
  if(players.size() == TABLE_SIZE)
    Start();
}
