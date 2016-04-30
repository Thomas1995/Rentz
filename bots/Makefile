CXX?=g++
CFLAGS?=-std=c++11 -g
OBJS=bot_Thomas.o bot.o
COMMON=../util/card.cpp ../util/require.h ../util/gamelist.h

all: $(OBJS)

bot_Thomas.o: bot.h

%.o: %.cpp %.h $(COMMON)
	$(CXX) $(CFLAGS) -c $<

../util/card.o: 
	make -C ../util/

.PHONY: clean
clean:
	rm -f *\.o

