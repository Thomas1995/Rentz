#ifndef GAME_IMPL
#define GAME_IMPL

#include "game.h"

Game::Game() {}

void Game::Start() {
    Game G;

    G.players.push_back(new Bot_Thomas());
    G.players.push_back(new Bot_Thomas());
    G.players.push_back(new Bot_Thomas());

    G.firstPlayer = G.players.begin();

    G.PlayRound();
}

void Game::PlayerAction(Bot* const player) {
    Card playedCard = player->PlayCard(cardStack);
    cardStack.push(playedCard);
    player->RemoveCard(playedCard);
}

void Game::IterateThroughPlayers(std::vector<Bot*>::iterator iterator) {
    while(!cardStack.empty())
      cardStack.pop();

    for(auto it = iterator; it != players.end(); ++it)
        PlayerAction(*it);
    for(auto it = players.begin(); it != iterator; ++it)
        PlayerAction(*it);
}

void Game::PlayRound() {
    IterateThroughPlayers(firstPlayer);
}

Game::~Game() {
    for(auto it : players)
        delete it;
    players.clear();
}

#endif // GAME_IMPL
