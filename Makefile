CC=g++
CFLAGS=-std=c++11 -g

all: server

server: server.o table.o player.o score.o util
	$(CC) $(CFLAGS) score.o server.o player.o util/card.o table.o util/require.o -o server

server.o: server.cpp
	$(CC) $(CFLAGS) -c server.cpp

table.o: table.cpp
	$(CC) $(CFLAGS) -c table.cpp

player.o: player.cpp
	$(CC) $(CFLAGS) -c player.cpp

score.o: score.cpp
	$(CC) $(CFLAGS) -c score.cpp

util: util/card.o util/require.o
	make -C util

clean:
	rm *\.o
	rm server

