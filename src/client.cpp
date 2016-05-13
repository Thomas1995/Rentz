#include <netdb.h>
#include "util/card.h"
#include <string>
#include <fcntl.h>
#include <assert.h>
#include <sstream>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include "util/require.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <vector>
#include "event.h"
#include "bots/bot.h"
#include "bots/bot_Thomas.h"
#include "common.h"

const char PORT[] = "31337";

/* Client is what connects to the server.
 * It receives certain events from the server and interprets them.
 * Based on the event that it receives,
 * it calls coresponding methods of the 
 * bot member variable
 */

struct Client : public Common {

  int index;

  Bot* bot;

  Client() = delete;

  Client(char **argv) {

    bot = new Bot_Thomas;

    addrinfo hints, *rez;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo(argv[1], PORT, &hints, &rez);

    for(addrinfo *p = rez; p != NULL; p = p->ai_next) {
      sfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

      if(sfd == -1)
        continue;

      if(connect(sfd, p->ai_addr, p->ai_addrlen) != -1) {
        printf("Connected to %s\n", argv[1]);
        break;
      }

      close(sfd);
    }

    fcntl(sfd, F_SETFL, O_NONBLOCK);

    freeaddrinfo(rez);

    handshake(argv[2]);

    while(1) {
      event e = readEvent();
      event resp;
      resp.type = e.type;

      switch(e.type) {
        case event::EType::sendCards: {
        //the server is sending us what cards were played
        //and are on the table
        //TODO:
        //implement parsing these cards
        //and implement a coresponding method in #Bot
        
            std::vector<Card> cards(e.getCards());
            //bot->receiveCardsOnTable(cards);
          
            break;
        }

        case event::EType::sendHand: {
        //the server is sending us our hand
        //TODO:
        //implement a coresponding method in #Bot
            
            std::vector<Card> hand(e.getCards());
            //bot->receiveHand(hand);
            break;
        }

        case event::EType::sendScores: {
        //the server is sending us the scores so far
        //TODO:
        //implement a coresponding method in #Bot
            
            std::vector<int> scores;
            scores.reserve(e.len / 4);

            for(uint32_t i = 0; i < e.len; i += 4) 
              scores.push_back(e.getInt(e.data + i));

            //bot->sendScores(scores);
            break;
        }

        case event::EType::getGameChoice: {
            uint8_t ans = bot->GetGameType();
            resp.len = 1;
            resp.data = &ans;
            resp.send(sfd);
            break;
        }

        case event::EType::sendGameChoice: {
        //the server is sending us the chosen game type
        //TODO:
        //implement a coresponding method in #Bot
            const uint8_t choice = e.data[0];

            //bot->sendGameChoice(choice);
            break;
        }

        case event::EType::getCardChoice: {
            Card c = bot->PlayCard();
            resp.len = 1;
            uint8_t code = c.encode();
            resp.data = &code;
            resp.send(sfd);
            break;
        }

        case event::EType::getNVChoice: {
            bool ans = bot->PlayNVMode();
            resp.len = 1;
            resp.data = reinterpret_cast<uint8_t *>(&ans);
            resp.send(sfd);
            break;
        }
      }
      e.free();
    }
  }

  void handshake(char* name) {

    event e = readEvent();
    assert(e.type = event::EType::requestName);
    e.free();

    e.len = strlen(name);
    e.data = reinterpret_cast<uint8_t *>(name);

    e.send(sfd);


    e = readEvent();
    assert(e.type == event::EType::sendIndex);
    assert(e.len == 4);

    index = *(reinterpret_cast<uint32_t *>(e.data));

    e.free();
    e.len = 0;
    e.data = NULL;
    e.send(sfd);

    printf("our index is %d\n", index);
  }

  ~Client() {
    delete bot;
  }
};

int main(int argc, char ** argv) {

  if(argc != 3) {
    printf("Usage: %s server-address bot-name\n", argv[0]);
    exit(1);
  }

  Client client(argv);


  return 0;
}
