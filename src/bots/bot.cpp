#include "bot.h"
#include "../util/gamelist.h"
#include "../util/card.h"
#include <iostream>

void Bot::Init(int index, int players) {

	this->index = index;
	this->playersCount = players;
	scores.resize(players, 0);
	
	if(games.empty())
	for(int i = 1; i <= MinigameCount; ++i)
		games.push_back(static_cast<Minigame>(i));
}

void Bot::ReceiveHand(std::vector<Card> hand) {
	// Server gives you your hand for the round
	// Update the current hand

	this->hand = hand;
}

void Bot::dumpInfo() {
    std::cerr << "Info for bot #" << index << " (" << name << "):" << std::endl;

    std::cerr << "Current scores: ";
    for(auto x : scores) std::cerr << x << " ";
    std::cerr << std::endl;

    std::cerr << "Avaliable minigames: ";
    for(auto x : games) std::cerr << x << " ";
    std::cerr << std::endl;

    std::cerr << "Current hand: ";
    for(auto x : hand) std::cerr << x << " ";
    std::cerr << std::endl;

    std::cerr << "Cards on table: ";
    for(auto x : cardsOnTable) std::cerr << x << " ";
    std::cerr << std::endl;
}

void Bot::ReceiveCardsOnTable(std::vector<Card> cardsOnTable) {
	// Server gives you the cards on the table
	std::vector<Minigame> games;
	for(int i = 1; i <= MinigameCount; ++i)
        games.push_back((Minigame) i);

    this->games = games;
	this->cardsOnTable = cardsOnTable;
}

Minigame Bot::ChooseMinigame() {
	// Choose a minigame

	Minigame game = onChooseMinigame();
	auto it = find(games.begin(), games.end(), game);
	
	assert(it != games.end());
	
	games.erase(it); //TODO: Check if game in games
	return game;
}

bool Bot::AskIfNV() {
	return onAskIfNV();
}

void Bot::RoundStart(int gameIndex) {
	// Update current game and call virtual method
	currentGame = gameIndex;
	onRoundStart();
}


void Bot::RoundEnd(std::vector<int> scores) {
	// Round ended; empty your hand, update scores

	hand.clear();
	this->scores = scores;
	onRoundEnd();
}

Card Bot::PlayCard() {
	// Play a card and erase it from your hand

    Card use = onPlayCard();
    hand.erase(find(hand.begin(), hand.end(), use)); //TODO: Check if card in hand
    return use;
}

void Bot::setName(const std::string name) {
	this->name = name;
}

int Bot::getIndex() {
	return index;
}
int Bot::getPlayersCount() {
	return playersCount;
}
std::string Bot::getName() {
    return name;
}
std::vector<int> Bot::getScores() {
	return scores;
}
std::vector<Card> Bot::getHand() {
	return hand;
}
std::vector<Card> Bot::getCardsOnTable() {
	return cardsOnTable;
}
std::vector<Minigame> Bot::getAvailableGames() {
    return games;
}
int Bot::getCurrentGame() {
	return currentGame;
}

void Bot::onRoundStart() {}
void Bot::onTurnEnd() {}
void Bot::onRoundEnd() {}