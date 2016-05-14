#include <stdlib.h>
#include "table.h"
#include "server.h"
#include "util/require.h"

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
      table.addPlayer(client);
    }
  }
  return 0;
}
