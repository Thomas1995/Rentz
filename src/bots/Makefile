CXX?=g++
CFLAGS?=-std=c++11 -g -Wall
OBJS=bot.o bot_Thomas.o bot_Eric.o bot_Eugen.o bot_Lucian.o
COMMON=../util/card.cpp ../util/require.h ../util/gamelist.h

all: $(OBJS)

bot_Thomas.o: bot_Thomas.h

bot_Eric.o: bot_Eric.h

bot_Eugen.o: bot_Eugen.h

bot_Lucian.o: bot_Lucian.h

%.o: %.cpp %.h $(COMMON)
	$(CXX) $(CFLAGS) -c $<

../util/card.o:
	$(MAKE) -C ../util/

.PHONY: clean
clean:
	rm -f *\.o
