CC=g++
CFLAGS=-std=c++11 -g

all: card.o require.o

card.o: card.cpp
		$(CC) $(CFLAGS) -c card.cpp

require.o: require.cpp
		$(CC) $(CFLAGS) -c require.cpp

clean:
		rm *\.o
