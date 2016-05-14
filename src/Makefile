CXX?=g++
CFLAGS?=-std=c++11 -g -Wall
OBJS=score.o server.o connection.o util/card.o table.o util/require.o common.o
BOTS=bots/bot_Thomas.o bots/bot.o bots/bot_Eric.o
UTIL=util/card.o util/require.o
HEADERS=common.h event.h connection.h table.h server.h

all: server client

.PHONY: server
server: $(OBJS) server.h table.h

.PHONY: client
client: client.o common.o $(BOTS)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $<

%.cpp: %.h

event.h server common.o connection.o: util/debug.h

client.o connection.o: common.h event.h

util/card.o: util/card.cpp util/card.h
	make -C util

util/require.o: util/require.h util/require.cpp
	make -C util

$(BOTS): 
	make -C bots

bots/%.o: bots/%.cpp bots/%.h
	make -C bots

bots/bot_Thomas.o: bots/bot.h

bots/bot_Eric.o: bots/bot.h

.PHONY: clean
clean:
	rm -f *\.o
	rm -f server
	make -C util clean
	make -C bots clean

