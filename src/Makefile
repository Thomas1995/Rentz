CXX?=g++
CFLAGS?=-std=c++11 -g -Wall
OBJS=score.o server.o connection.o util/card.o table.o util/require.o common.o
BOTS=src/bots/bot.o src/bots/bot_Thomas.o src/bots/bot_Eric.o src/bots/bot_Eugen.o src/bots/bot_Lucian.o
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
	$(MAKE) -C util

util/require.o: util/require.h util/require.cpp
	$(MAKE) -C util

$(BOTS):
	$(MAKE) -C bots

bots/%.o: bots/%.cpp bots/%.h
	$(MAKE) -C bots

bots/bot_Thomas.o: bots/bot.h

bots/bot_Eric.o: bots/bot.h

bots/bot_Eugen.o: bots/bot.h

bots/bot_Lucian.o: bots/bot.h

.PHONY: clean
clean:
	rm -f *\.o
	rm -f server
	$(MAKE) -C util clean
	$(MAKE) -C bots clean
