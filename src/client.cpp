#include <netdb.h>
#include "util/card.h"
#include <string>
#include <fcntl.h>
#include <assert.h>
#include <memory>
#include <sstream>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include "util/require.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <vector>
#include "event.h"
#include "bots/bot.h"

#include "bots/Thomas.bot"
#include "bots/Eric.bot"
#include "bots/Bicsi.bot"
#include "bots/Random.bot"

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

  std::unique_ptr<Bot> bot;

  Client() = delete;

  Client(char **argv) {

    srand (time(NULL));

    std::string type = argv[3];

    if(type == "TH")  bot = std::unique_ptr<Bot>(new Bot_Thomas); 
    if(type == "ER")  bot = std::unique_ptr<Bot>(new Bot_Eric); 
    if(type == "BC")  bot = std::unique_ptr<Bot>(new Bot_Bicsi); 
    if(type == "RD")  bot = std::unique_ptr<Bot>(new Bot_Random);

    assert(bot != nullptr);
    

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
        printf("Connected to %s.\n\n", argv[1]);
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
        case event::EType::SEND_CARDS: {
        //the server is sending us what cards were played
        //and are on the table

        //debug("Receiving cards on table...\n");
          std::vector<Card> cards(e.getCards());
          bot->ReceiveCardsOnTable(cards);
          resp.send(sfd);
          break;
      }

      case event::EType::SEND_HAND: {
      //the server is sending us our hand

            debug("Receiving hand: ");
            std::vector<Card> hand(e.getCards());
            for(auto &x: hand)
              debug("%s ", x.to_string().c_str());
            debug("\n");

            bot->ReceiveHand(hand);
            resp.send(sfd);
            break;
        }

        case event::EType::ROUND_END: {
        //the server is sending us the scores so far

            debug("Round ended.\n Scores: ");

            std::vector<int> scores;
            scores.reserve(e.len / 4);

            for(uint32_t i = 0; i < e.len; i += 4)
              scores.push_back(e.getInt(e.data + i));

            for(auto i: scores)
              debug(" %d", i);
            debug("\n\n");

            bot->RoundEnd(scores);
            resp.send(sfd);
            break;
        }

        case event::EType::ASK_GAME: {
        //ask the bot to choose the minigame
            debug("Being asked for minigame...\n");
            uint8_t ans = bot->ChooseMinigame();
            debug("I chose: %s\n", GameName[ans].c_str());
            resp.len = 1;
            resp.data = &ans;
            resp.send(sfd);
            break;
        }

        case event::EType::ROUND_START: {
        //the server is sending us the chosen game type
            debug("Round is starting...\n");
            const uint8_t choice = e.data[0];
            bot->RoundStart(choice);
            resp.send(sfd);
            break;
        }

        case event::EType::ASK_CARD: {
            debug("Being asked for card...\n");
            Card c = bot->PlayCard();
            debug("I chose: %s\n", c.to_string().c_str());
            resp.len = 1;
            uint8_t code = c.encode();
            resp.data = &code;
            resp.send(sfd);
            break;
        }

        case event::EType::ASK_NV: {
            debug("Being asked for NV...\n");
            bool ans = bot->AskIfNV();

            if(ans) debug("Chose NV\n");
            else debug("Did not choose NV\n");
            
            resp.len = 1;
            resp.data = reinterpret_cast<uint8_t *>(&ans);
            resp.send(sfd);
            break;
        }

        case event::EType::GAME_END: {
          debug("The game has ended.\n\n");
          resp.send(sfd);
          goto end;
        }
      }
      e.free();
    }

  end:

    return;
  }

  void handshake(char* name) {

    event e = readEvent();
    assert(e.type = event::EType::ASK_NAME);
    e.free();

    e.len = strlen(name);
    e.data = reinterpret_cast<uint8_t *>(name);

    e.send(sfd);


    e = readEvent();
    assert(e.type == event::EType::SEND_INIT);
    assert(e.len == 4);

    index = ntohl(*(reinterpret_cast<uint32_t *>(e.data)));

    e.free();
    e.len = 0;
    e.data = NULL;
    e.send(sfd);

    printf("Our index is %d\n", index);

    //TODO: add information for number of players
    int players = 3; // Remove this

    //Initialize bot
    bot->Init(index, players);
  }
};

int main(int argc, char ** argv) {

  if(argc != 4) {
    printf("Usage: %s server-address bot-name bot-type\n", argv[0]);
    exit(1);
  }

  Client client(argv);


  return 0;
}
