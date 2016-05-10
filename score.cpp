#include "table.h"

void Table::ChangeScore() {

    int crtConnection = firstConnection - connections.begin();

    int scoreToAdd = 0;

    if(gameType == KingOfHearts)
        ScoreKingOfHearts(scoreToAdd);

    if(gameType == Queens)
        ScoreQueens(scoreToAdd);

    if(gameType == Diamonds)
        ScoreDiamonds(scoreToAdd);

    if(gameType == Acool)
        ScoreAcool(scoreToAdd);

    if(gameType == Whist)
        ScoreWhist(scoreToAdd);

    if(gameType == TenClub)
        ScoreTenClub(scoreToAdd);

    if(gameType == Totals)
        ScoreTotals(scoreToAdd);

    score[crtConnection] += scoreToAdd * (1 + modeNV);
}

void Table::ScoreKingOfHearts(int& scoreToAdd) {
    for(auto c : cardStack)
        if(c.getValue() == 13 && c.getSuite() == 'H')
            scoreToAdd -= 100;
}

void Table::ScoreQueens(int& scoreToAdd) {
    for(auto c : cardStack)
        if(c.getValue() == 12)
            scoreToAdd -= 30;
}

void Table::ScoreDiamonds(int& scoreToAdd) {
    for(auto c : cardStack)
        if(c.getSuite() == 'D')
            scoreToAdd -= 20;
}

void Table::ScoreAcool(int& scoreToAdd) {
    scoreToAdd -= 10;
}

void Table::ScoreWhist(int& scoreToAdd) {
    scoreToAdd += 10;
}

void Table::ScoreTenClub(int& scoreToAdd) {
    for(auto c : cardStack)
        if(c.getValue() == 10 && c.getSuite() == 'C')
            scoreToAdd += 100;
}

void Table::ScoreTotals(int& scoreToAdd) {
    ScoreKingOfHearts(scoreToAdd);
    ScoreQueens(scoreToAdd);
    ScoreDiamonds(scoreToAdd);
    ScoreAcool(scoreToAdd);
}
