#ifndef GAME_IMPL
#define GAME_IMPL

#include "game.h"

Game::Game() {}

void Game::Start() {
    Game G;

    G.players.push_back(new Bot_Thomas());
    G.players.push_back(new Bot_Thomas());
    G.players.push_back(new Bot_Thomas());
}

void Game::PlayKingOfHearts() {
    //for(auto player : players);
}

#endif // GAME_IMPL
