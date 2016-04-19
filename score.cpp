#include "game.h"

void Game::ChangeScore() {

    int crtPlayer = firstPlayer - players.begin();

    int scoreToAdd = 0;

    if(crtGameType == KingOfHearts)
        ScoreKingOfHearts(scoreToAdd);

    if(crtGameType == Queens)
        ScoreQueens(scoreToAdd);

    if(crtGameType == Diamonds)
        ScoreDiamonds(scoreToAdd);

    if(crtGameType == Acool)
        ScoreAcool(scoreToAdd);

    if(crtGameType == Whist)
        ScoreWhist(scoreToAdd);

    if(crtGameType == TenClub)
        ScoreTenClub(scoreToAdd);

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
