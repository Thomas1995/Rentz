#ifndef BOT_H
#define BOT_H

#include <vector>
#include <algorithm>

#include "../util/card.h"
#include "../util/require.h"
#include "../util/gamelist.h"

class Bot {
private:
    int playersCount; // How many players are at the table
    int index; // Your player index in the game (0-based)
    std::string name = "Default"; // Your player name in the game
    Minigame currentGame; // The current game played

    std::vector<int> scores; // All players' scores

    std::vector<Card> hand; // Your hand at the moment of game
    std::vector<Minigame> games; // Your available games
    std::vector<Card> cardsOnTable; // The current card stack in the turn

public:
    void Init(int index, int players);
    //Initializes you with an index and number of players;
    //also sets your scores to 0

    void ReceiveHand(std::vector<Card> hand);
    // Server gives you your hand for the round
    // Update the current hand

    void ReceiveCardsOnTable(std::vector<Card> cardsOnTable);
    // Server gives you the cards on the table
    // Update them

    Minigame ChooseMinigame();
    // Server asks player for a minigame

    bool AskIfNV();
    // Server asks player if playing NV

    void RoundStart(int gameIndex);
    // Server sends the game index to all players
    // Round starts; currently only calls onRoundStart

    void RoundEnd(std::vector<int> scores);
    // Round ended; empty your hand, update scores

    Card PlayCard();
    // Play a card and erase it from your hand

    void TurnEnd();
    // Turn ends; calls onTurnEnd

    void dumpInfo();
    // Returns all information and returns a string for debug

    virtual ~Bot() = default;

protected:
    //Getters
    //------ 

    std::string getName();
    int getIndex();
    int getPlayersCount();
    Minigame getCurrentGame();
    std::vector<int> getScores();
    std::vector<Card> getHand();
    std::vector<Card> getCardsOnTable();
    std::vector<Minigame> getAvailableGames();

    void setName(const std::string name);

    //-----

    virtual bool onAskIfNV() = 0;
    // You are first; server is asking you if you want to play NV
    // Return true if playing NV, else false

    virtual Minigame onChooseMinigame() = 0;
    // You are first; if you have chosen NV mode, your hand is empty;
    // else you can see your hand

    virtual void onRoundStart();
    // You have all received your hands. You can update information about the game

    virtual void onTurnEnd();
    // Turn has ended; cardsOnTable contains the cards played at current turn
    // You may update information about current cards

    virtual Card onPlayCard() = 0;
    // It's your turn; cardsOnTable contains the cards played at current turn
    // You have to play a certain card (return value)

    virtual void onRoundEnd();
    // Round has ended; all scores are updated
    // You may update information about current state
};

#endif // BOT_H
