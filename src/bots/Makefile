CXX?=g++
CFLAGS?=-std=c++11 -g -Wall
OBJS=bot_Thomas.o bot_Eric.o bot.o
COMMON=../util/card.cpp ../util/require.h ../util/gamelist.h

all: $(OBJS)

bot_Thomas.o: bot.h

bot_Eric.o: bot_Eric.h

%.o: %.cpp %.h $(COMMON)
	$(CXX) $(CFLAGS) -c $<

../util/card.o: 
	make -C ../util/

.PHONY: clean
clean:
	rm -f *\.o

