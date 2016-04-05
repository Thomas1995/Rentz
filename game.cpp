#ifndef GAME_IMPL
#define GAME_IMPL

#include "game.h"
#include <algorithm>

Game::Game() {}

void Game::Start() {
    Game G;

    // choose players in play
    G.players.push_back(new Bot_Thomas());
    G.players.push_back(new Bot_Lucian());
    G.players.push_back(new Bot_Eugen());
    G.players.push_back(new Bot_Eric());

    // assign the first player
    G.firstPlayer = G.players.begin();

    // start the round
    G.PlayRound();
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
                require(!cardStack.front().isSameSuite(c), player->GetName() + " had chosen a card of a different suite.");
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

void Game::PlayRound() {
    // get all cards in play
    std::vector<Card> allCards = Card::getAllCards(players.size());

    std::random_shuffle(allCards.begin(), allCards.end());

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
        /// TO DO

        std::cout << std::endl;
    }
}

Game::~Game() {
    for(auto it : players)
        delete it;
    players.clear();
}

#endif // GAME_IMPL
