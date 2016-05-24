#include <netdb.h>
#include <unordered_map>
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
#include <chrono>
#include <thread>
#include "event.h"
#include "bots/bot.h"

#include "bots/Thomas.bot"
#include "bots/Eric.bot"
#include "bots/Bicsi.bot"
#include "bots/Eugen.bot"
#include "bots/Random.bot"

#include "common.h"

const char PORT[] = "31337";

/* Client is what connects to the server.
 * It receives certain events from the server and interprets them.
 * Based on the event that it receives,
 * it calls coresponding methods of the
 * bot member variable
 */

template<typename T, typename O>
bool in(const T& t, const O& o) {
  return std::find(o.begin(), o.end(), t) != o.end();
}

struct Client : public Common {

  int index;

  std::unique_ptr<Bot> bot;

  Client() = delete;

  static const std::vector<std::string> names;

  std::string random_name() const {
    size_t i = rand() % names.size();
    return names[i];
  }

  Client(const std::unordered_map<std::string, std::string> &opts) {

    srand (time(NULL));

    const std::string name = opts.count("name") ? opts.at("name") : random_name();

    if(name == "TH")  bot = std::unique_ptr<Bot>(new Bot_Thomas);
    if(name == "ER")  bot = std::unique_ptr<Bot>(new Bot_Eric);
    if(name == "BC")  bot = std::unique_ptr<Bot>(new Bot_Bicsi);
    if(name == "EU")  bot = std::unique_ptr<Bot>(new Bot_Eugen);
    if(name == "RD")  bot = std::unique_ptr<Bot>(new Bot_Random);

    require(bot != nullptr, "Name not available. Choose from: TH | ER | BC | EU | RD\n");

    addrinfo hints, *rez;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    const std::string address = opts.count("address") ? opts.at("address") : "127.0.0.1";

    getaddrinfo(address.c_str(), PORT, &hints, &rez);

    for(addrinfo *p = rez; p != NULL; p = p->ai_next) {
      sfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

      if(sfd == -1)
        continue;

      if(connect(sfd, p->ai_addr, p->ai_addrlen) != -1) {
        printf("Connected to %s\n", address.c_str());
        break;
      }

      close(sfd);
    }

    fcntl(sfd, F_SETFL, O_NONBLOCK);

    freeaddrinfo(rez);

    handshake(const_cast<char *>(name.c_str()));

    while(true) {
      event e = readEvent();
      event resp;
      resp.type = e.type;
      resp.len = 0;
      resp.data = NULL;

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

        case event::EType::TURN_END: {
        //the server is telling us that turn has ended

          debug("Turn has ended.\n");
          bot->TurnEnd();
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
        //the server is asking us for a minigame to choose

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
        //the server is asking us for a card to play

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
        //the server is asking us if we want NV
          
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
        //the server is telling us that game has ended

          debug("The game has ended.\n\n");
          resp.send(sfd);
          goto end;
        }
      }
      e.free();

      std::this_thread::sleep_for(std::chrono::milliseconds(5));
    } // end while

  end:

    return;
  }

  void handshake(char *name) {

    event e = readEvent();
    assert(e.type = event::EType::HANDSHAKE);
    uint8_t playerCount = e.data[0];
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

    //Initialize bot
    bot->Init(index, playerCount);
  }
};

const std::vector<std::string> Client::names = {"TH", "ER", "BC", "RD"};

bool
addOptions(std::vector<std::string> &args,
    std::unordered_map<std::string, std::string> &opts,
    const std::string &opt_name,
    const std::vector<std::string> &aliases) {

  std::string s = args.back();

  if(!in(s, aliases))
    return false;

  args.pop_back();

  if(args.empty())
    return false;

  opts[opt_name] = args.back();

  args.pop_back();
  return true;
}

std::unordered_map<std::string, std::string>
parseArgs(int argc, char ** argv) {

  std::vector<std::string> args(argv + 1, argv + argc);

  std::reverse(args.begin(), args.end());

  std::unordered_map<std::string, std::string> options;

  while(!args.empty()) {

    if(addOptions(args, options, "address", {"--address", "-a"}))
      continue;

    if(addOptions(args, options, "name", {"--name", "-n"}))
      continue;

    if(addOptions(args, options, "help", {"--help", "-h"}))
      goto args_error;

    goto args_error;
  }

  return options;

args_error:
  printf("Usage: %s [OPTIONS]\n", argv[0]);
  printf("Optional arguments:\n");
  printf("%-20s ADDRESS\n", "-a, --address");
  printf("%-20s NAME\n", "-n, --name");
  printf("%-20s display this help message\n", "-h, --help");
  exit(1);

}

int main(int argc, char ** argv) {

  const auto &args = parseArgs(argc, argv);

  Client client(args);
  return 0;
}
