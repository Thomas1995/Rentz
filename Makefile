CC=g++
CFLAGS=-std=c++11 -g
OBJS=score.o server.o player.o util/card.o table.o util/require.o common.o
BOTS=bots/bot_Thomas.o bots/bot.o util/card.o util/require.o
HEADERS=common.h event.h player.h table.h

all: server client

server: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o server

client: client.o common.o $(BOTS)
	$(CC) $(CFLAGS) $(BOTS) common.o client.o -o client

client.o: client.cpp 
	$(CC) $(CFLAGS) -c client.cpp

common.o: common.cpp
	$(CC) $(CFLAGS) -c common.cpp

server.o: server.cpp
	$(CC) $(CFLAGS) -c server.cpp

table.o: table.cpp table.h
	$(CC) $(CFLAGS) -c table.cpp

player.o: player.cpp player.h 
	$(CC) $(CFLAGS) -c player.cpp

score.o: score.cpp
	$(CC) $(CFLAGS) -c score.cpp

event.h server common.o player.o: util/debug.h

client.o player.o: common.h event.h

util/card.o: util/card.cpp util/card.h
	make -C util

util/require.o: util/require.h util/require.cpp
	make -C util

bots/bot_Thomas.o: bots/bot_Thomas.cpp bots/bot_Thomas.cpp bots/bot.h bots/bot.cpp
	make -C bots

bots/bot.o: bots/bot.cpp bots/bot.h
	make -C bots

.PHONY: clean
clean:
	rm -f *\.o
	rm -f server
	make -C util clean
	make -C bots clean

