#include "bot.h"
#include "../util/gamelist.h"
#include "../util/card.h"
#include <iostream>

void Bot::Init(int index, int players) {
	debug("Getting initialized\n");

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
    debug("\n\n------------------\n");
    debug("Info for bot #%d(%s):\n", index, name.c_str());

    debug("Current scores: ");
    for(auto x : scores) debug("%d ", x);
    debug("\n");

    debug("Available minigames: ");
    for(auto x : games) debug("%d ", x);
    debug("\n");

    debug("Current hand: ");
    for(auto x : hand) debug("%s ", x.to_string().c_str());
    debug("\n");

    debug("Cards on table: ");
    for(auto x : cardsOnTable) debug("%s ", x.to_string().c_str());
    debug("\n------------------\n\n");
}

void Bot::ReceiveCardsOnTable(std::vector<Card> cardsOnTable) {
	// Server gives you the cards on the table
	this->cardsOnTable = cardsOnTable;
}

Minigame Bot::ChooseMinigame() {
	// Choose a minigame

	debug("I have %d games available\n", games.size());
	Minigame game = onChooseMinigame();
	auto it = find(games.begin(), games.end(), game);
	
	assert(it != games.end());
	
	games.erase(it); //TODO: Check if game in games
	debug("I now have %d games available\n", games.size());

	return game;
}

bool Bot::AskIfNV() {
	return onAskIfNV();
}

void Bot::RoundStart(int gameIndex) {
	// Update current game and call virtual method
	currentGame = gameIndex;
	
	//TODO: Remove this line
	dumpInfo();

	onRoundStart();
}


void Bot::RoundEnd(std::vector<int> scores) {
	// Round ended; empty your hand, update scores

	hand.clear();
	cardsOnTable.clear();
	this->scores = scores;
	
	onRoundEnd();
}

Card Bot::PlayCard() {
	// Play a card and erase it from your hand

	//TODO: Remove this line
	dumpInfo();

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