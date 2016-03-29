#ifndef GAME_IMPL
#define GAME_IMPL

#include "game.h"

Game::Game() {}

void Game::Start() {
    Game G;

    G.players.push_back(new Bot_Thomas());
    G.players.push_back(new Bot_Thomas());
    G.players.push_back(new Bot_Thomas());

    G.PlayKingOfHearts();
}

void Game::PlayKingOfHearts() {
    std::stack<Card> st;
    for(auto player : players) {
        Card playedCard = player->PlayCard(st);
        st.push(playedCard);
    }
}

Game::~Game() {
    for(auto it : players)
        delete it;
    players.clear();
}

#endif // GAME_IMPL
