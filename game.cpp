#ifndef GAME_IMPL
#define GAME_IMPL

#include "game.h"
#include <algorithm>
#include <random>
#include <chrono>

#include "bots/bot_Thomas.cpp"
#include "bots/bot_Lucian.cpp"
#include "bots/bot_Eugen.cpp"
#include "bots/bot_Eric.cpp"

Game::Game() {}

void Game::Start() {
    Game G;

    // choose players in play
    G.players.push_back(new Bot_Thomas());
    G.players.push_back(new Bot_Lucian());
    G.players.push_back(new Bot_Eugen());
    G.players.push_back(new Bot_Eric());

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
                G.modeNV = G.players[i]->PlayNVMode();
            else
                G.modeNV = true;

            // if NV mode not chosen, give cards before game choice
            if(G.modeNV == false)
                G.GiveCards();

            // get the game type
            G.crtGameType = G.players[i]->GetGameType();

            // if NV mode chosen, give cards after game choice
            if(G.modeNV == true)
                G.GiveCards();

            // check if player can play that game
            require(G.crtGameType >= 1 && G.crtGameType <= G.gamesNumber,
              G.players[i]->GetName() + " has chosen a game index out of bounds");
            require(gamesPlayed[i][G.crtGameType] == false,
              G.players[i]->GetName() + " had already chosen that game");

            gamesPlayed[i][G.crtGameType] = true;

            // let the other players know the game type
            for(auto player : G.players)
                player->SetGameType(G.crtGameType);

            // start the round
            G.PlayRound();
        }
}

void Game::PlayerAction(Bot* const player) {
    // send player the cards that were played and get his played card
    Card playedCard = player->PlayCard(cardStack);

    std::cout << player->GetName() << " played " << playedCard << "\n";

    // check if the played card can be played
    if(cardStack.size() > 1) {
        if(!playedCard.isSameSuite(cardStack.front())) {
            auto cards = player->GetHand();
            for(auto c : cards)
                require(!cardStack.front().isSameSuite(c),
                  player->GetName() + " had chosen a card of a different suite.");
        }
    }

    // push the card in play
    cardStack.push_back(playedCard);

    // remove the card from player's hand
    player->RemoveCard(playedCard);
}

void Game::IterateThroughPlayers(std::vector<Bot*>::iterator iterator) {
    for(auto it = iterator; it != players.end(); ++it)
        PlayerAction(*it);
    for(auto it = players.begin(); it != iterator; ++it)
        PlayerAction(*it);
}

void Game::GiveCards() {
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
      players[i]->SetHand(hand);
  }
}

void Game::PlayRound() {
    for(int roundstep = 1; roundstep <= 8; ++roundstep) {
        cardStack.clear();

        // get players to play cards
        IterateThroughPlayers(firstPlayer);

        // announce all players about the cards that were played
        for(int i=0;i<players.size();++i)
            players[i]->GetPlayedCardStack(cardStack);

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
        players[i]->SetScores(score[i], score);
        std::cout << players[i]->GetName() + ": " << score[i] << "\n";
    }
    std::cout << "\n----------\n";

    std::cout << std::endl;
}

void Game::ChangeScore() {

    int crtPlayer = firstPlayer - players.begin();

    int scoreToAdd = 0;

    // king of hearts
    if(crtGameType == KingOfHearts)
        ScoreKingOfHearts(scoreToAdd);

    // queens
    if(crtGameType == Queens)
        ScoreQueens(scoreToAdd);

    // diamonds
    if(crtGameType == Diamonds)
        ScoreDiamonds(scoreToAdd);

    // acool
    if(crtGameType == Acool)
        ScoreAcool(scoreToAdd);

    // whist
    if(crtGameType == Whist)
        ScoreWhist(scoreToAdd);

    // 10 club
    if(crtGameType == TenClub)
        ScoreTenClub(scoreToAdd);

    // totals
    if(crtGameType == Totals)
        ScoreTotals(scoreToAdd);

    score[crtPlayer] += scoreToAdd * (1 + modeNV);
}

void Game::ScoreKingOfHearts(int& scoreToAdd) {
    for(auto c : cardStack)
        if(c.getValue() == 13 && c.getSuite() == 'H')
            scoreToAdd -= 100;
}

void Game::ScoreQueens(int& scoreToAdd) {
    for(auto c : cardStack)
        if(c.getValue() == 12)
            scoreToAdd -= 30;
}

void Game::ScoreDiamonds(int& scoreToAdd) {
    for(auto c : cardStack)
        if(c.getSuite() == 'D')
            scoreToAdd -= 20;
}

void Game::ScoreAcool(int& scoreToAdd) {
    scoreToAdd -= 10;
}

void Game::ScoreWhist(int& scoreToAdd) {
    scoreToAdd += 10;
}

void Game::ScoreTenClub(int& scoreToAdd) {
    for(auto c : cardStack)
        if(c.getValue() == 10 && c.getSuite() == 'C')
            scoreToAdd += 100;
}

void Game::ScoreTotals(int& scoreToAdd) {
    ScoreKingOfHearts(scoreToAdd);
    ScoreQueens(scoreToAdd);
    ScoreDiamonds(scoreToAdd);
    ScoreAcool(scoreToAdd);
}

Game::~Game() {
    for(auto it : players)
        delete it;
    players.clear();
}

#endif // GAME_IMPL
