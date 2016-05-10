#include "table.h"
#include "server.h"

int main() {
  Table table;
  Server server;

  while(true) {
    const int n = server.poll();
    //there are n new incoming connections
    for(int i = 0; i < n; ++i) {
      const int client = server.acceptConnection();
      table.addConnection(client);
    }
  }
  return 0;
}
