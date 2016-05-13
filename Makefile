CXX?=g++
CFLAGS?=-std=c++11 -g -Wall
OBJS=src/score.o src/server.o src/connection.o src/util/card.o src/table.o src/util/require.o src/common.o
CLIENT_OBJS=src/common.o src/client.o
BOTS=src/bots/bot_Thomas.o src/bots/bot.o
UTIL=src/util/card.o src/util/require.o

all: bin

.PHONY: src
src: FORCE
	make -C src

FORCE:

bin: server client

server: src
	$(CXX) $(CFLAGS) $(OBJS) -o server

client:  src
	$(CXX) $(CFLAGS) $(BOTS) $(UTIL) $(CLIENT_OBJS) -o client

.PHONY: clean
clean:
	make -C src clean
	$(RM) bin/server
	$(RM) bin/client

