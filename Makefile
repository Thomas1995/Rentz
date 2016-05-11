CXX?=g++
CFLAGS?=-std=c++11 -g -Wall
OBJS=score.o server.o connection.o util/card.o table.o util/require.o common.o
BOTS=bots/bot_Thomas.o bots/bot.o
UTIL=util/card.o util/require.o
HEADERS=common.h event.h connection.h table.h server.h

all: server client

server: $(OBJS) server.h table.h
	$(CXX) $(CFLAGS) $(OBJS) -o server

client: client.o common.o $(BOTS)
	$(CXX) $(CFLAGS) $(BOTS) $(UTIL) common.o client.o -o client

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $<

%.cpp: %.h

event.h server common.o connection.o: util/debug.h

client.o connection.o: common.h event.h

util/card.o: util/card.cpp util/card.h
	make -C util

util/require.o: util/require.h util/require.cpp
	make -C util

bots/%.o: bots/%.cpp bots/%.h
	make -C bots

bots/bot_Thomas.o: bots/bot.h

.PHONY: clean
clean:
	rm -f *\.o
	rm -f server
	make -C util clean
	make -C bots clean

