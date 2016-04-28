#include "table.h"
#include <algorithm>
#include <random>
#include <chrono>

Table::Table() {}

void Table::Start() {
    Table G;

    for(size_t i = 0; i < G.players.size(); ++i)
      G.players[i].sendIndex(i);
    
    // choose players in play
    
    Card::lowestCard = 15 - G.players.size() * 2;

    G.score.resize(4, 0);

    // true if a game was already played but a certain player, false otherwise
    bool gamesPlayed[G.players.size()][G.gamesNumber+1];

    for(int i=0;i<G.players.size();++i)
        for(int j=0;j<G.gamesNumber+1;++j)
            gamesPlayed[i][j] = false;

    // assign the first player
    G.firstPlayer = G.players.begin();

    for(int gameChoice = 1; gameChoice <= G.gamesNumber; ++gameChoice)
        for(int i=0;i<G.players.size();++i) {

            // check if player wants to play NV mode and enforce it for the last choice
            if(gameChoice < G.gamesNumber)
                G.modeNV = G.players[i].getNVChoice();
            else
                G.modeNV = true;

            // if NV mode not chosen, give cards before game choice
            if(G.modeNV == false)
                G.GiveCards();

            // get the game type
            G.gameType = G.players[i].getGameChoice();

            // if NV mode chosen, give cards after game choice
            if(G.modeNV == true)
                G.GiveCards();

            // check if player can play that game
            require(G.gameType >= 1 && G.gameType <= G.gamesNumber,
              G.players[i].getName() + " has chosen a game index out of bounds");
            require(gamesPlayed[i][G.gameType] == false,
              G.players[i].getName() + " had already chosen that game");

            gamesPlayed[i][G.gameType] = true;

            // let the other players know the game type
            for(auto player : G.players)
              player.sendGameChoice(G.gameType);

            // start the round
            G.PlayRound();
        }
}

void Table::PlayerAction(Player player) {
    // send player the cards that were played and get his played card
    player.sendCards(cardStack);

    Card playedCard = player.getCardChoice();

    std::cout << player.getName() << " played " << playedCard << "\n";

    // check if the played card can be played
    if(cardStack.size() > 1) {
        if(!playedCard.isSameSuite(cardStack.front())) {
            auto cards = player.getHand();
            for(auto c : cards)
                require(!cardStack.front().isSameSuite(c),
                  player.getName() + " had chosen a card of a different suite.");
        }
    }

    // push the card in play
    cardStack.push_back(playedCard);

    // remove the card from player's hand
}

void Table::IterateThroughPlayers(std::vector<Player>::iterator iterator) {
    for(auto it = iterator; it != players.end(); ++it)
        PlayerAction(*it);
    for(auto it = players.begin(); it != iterator; ++it)
        PlayerAction(*it);
}

void Table::GiveCards() {
  // get all cards in play
  std::vector<Card> allCards = Card::getAllCards();

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(allCards.begin(), allCards.end(), std::default_random_engine(seed));

  auto card = allCards.begin();

  // give cards to players
  for(int i=0;i<players.size();++i) {
      std::vector<Card> hand;
      for(int j=1;j<=8;++j) {
          hand.push_back(*card);
          ++card;
      }
      players[i].sendHand(hand);
  }
}

void Table::PlayRound() {
    for(int roundstep = 1; roundstep <= 8; ++roundstep) {
        cardStack.clear();

        // get players to play cards
        IterateThroughPlayers(firstPlayer);

        // announce all players about the cards that were played
        for(int i=0;i<players.size();++i)
            players[i].sendCards(cardStack);

        // check for winner
        int winnerIndex = 0;
        Card winnerCard = cardStack[winnerIndex];

        for(int i=1;i<cardStack.size();++i) {
            if(winnerCard.isBeatenBy(cardStack[i])) {
                winnerCard = cardStack[i];
                winnerIndex = i;
            }
        }

        // change the first player to go
        while(winnerIndex--) {
            ++firstPlayer;
            if(firstPlayer == players.end())
                firstPlayer = players.begin();
        }

        // change score
        ChangeScore();

        std::cout << std::endl;
    }

    // let players know the scores
    std::cout << "Scores:\n";
    for(int i=0;i<players.size();++i) {
        players[i].sendScores(score);
        std::cout << players[i].getName() + ": " << score[i] << "\n";
    }
    std::cout << "\n----------\n";

    std::cout << std::endl;
}

Table::~Table() {
    players.clear();
}

void Table::addPlayer(int fd) {
  players.emplace_back(Player(fd));
  if(players.size() == TABLE_SIZE)
    Start();
}
