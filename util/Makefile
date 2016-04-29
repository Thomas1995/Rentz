CC=g++
CFLAGS=-std=c++11 -g

all: card.o require.o

card.o: card.cpp card.h
		$(CC) $(CFLAGS) -c card.cpp

require.o: require.cpp require.h
		$(CC) $(CFLAGS) -c require.cpp

clean:
		rm -f *\.o
