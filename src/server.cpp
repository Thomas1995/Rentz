#include <stdlib.h>
#include "table.h"
#include "server.h"
#include "util/require.h"
#include <chrono>
#include <thread> 

int main(int argc, char ** argv) {

  if(argc != 2) {
    printf("Usage: %s number-of-clients\n", argv[0]);
    exit(1);
  }

  int clientsNumber = atoi(argv[1]);

  require(clientsNumber >= 3 && clientsNumber <= 6,
    "The numbers of clients in a game should be between 3 and 6.\n");

  Table::TABLE_SIZE = clientsNumber;

  Table table;
  Server server;

  while(true) {
    const int n = server.poll();
    //there are n new incoming connections
    for(int i = 0; i < n; ++i) {
      const int client = server.acceptConnection();
      
      if(table.GAME_END) {
          Table newTable;
          table = newTable;
      }

      table.addPlayer(client);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  return 0;
}
