CC=g++
CFLAGS=-std=c++11 -g
OBJS=bot_Thomas.o bot.o
COMMON=../util/card.cpp ../util/require.h ../util/gamelist.h

all: $(OBJS)

bot_Thomas.o: bot_Thomas.cpp $(COMMON)
	$(CC) $(CFLAGS) -c bot_Thomas.cpp

bot.o: bot.cpp $(COMMON)
	$(CC) $(CFLAGS) -c bot.cpp

../util/card.o: 
	make -C ../util/

.PHONY: clean
clean:
	rm -f *\.o

