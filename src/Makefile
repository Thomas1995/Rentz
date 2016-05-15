CXX?=g++
CXXFLAGS?=-std=c++11 -g -Wall
OBJS=score.o server.o connection.o table.o common.o
HEADERS=common.h event.h connection.h table.h server.h

all: server client

.PHONY: server
server: $(OBJS) server.h table.h UTIL

.PHONY: client
client: client.o common.o BOTS

event.h server common.o connection.o: util/debug.h

client.o connection.o: common.h event.h

.PHONY: UTIL
UTIL:
	$(MAKE) -C util

.PHONY: BOTS
BOTS:
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
