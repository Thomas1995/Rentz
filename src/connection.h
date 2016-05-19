#ifndef connection_H
#define connection_H

#include "util/card.h"
#include "util/require.h"
#include "util/gamelist.h"
#include <vector>
#include <algorithm>
#include "event.h"
#include "common.h"

/* Connection is the server's interface
 * to the clients connected to it
 * the way it currently works is
 * server calls one of the following functions
 * the function sends an event thru the network
 * gets the response
 * interprets the resposne
 * and returns the coresponding information
 */
struct Connection : public Common {

    std::string name;

    std::vector<Card> hand;

    void sendCards(const std::vector<Card>& cardsOnTable);
    // Sends cards on table to client
    
    void sendScores(const std::vector<int>& allScores);
    // Sends scores to client

    Card getCardChoice();
    // Receives card choice of client

    uint8_t getGameChoice();
    // Receives minigame choice of client

    void sendGameChoice(uint8_t type);
    // Sends chosen minigame to client

    bool getNVChoice();
    // Receives NV choice of client

    void sendHand(const std::vector<Card>& cards);
    // Sends a client the hand

    std::string handshake(uint8_t playerCount);
    // Sets up client-server connection

    void gameEnd();
    // Sends a client game end flag, along with updated scores

    void turnEnd();
    // Sends a client turn end flag

    Connection() = delete;
    explicit Connection(int sfd, uint8_t table_size);

    void sendIndex(size_t index);
    // Sends a client its index in the table

    std::string getName();
    std::vector<Card> getHand();
};

#endif //connection_H
