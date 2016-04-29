CC=g++
CFLAGS=-std=c++11 -g
OBJS=score.o server.o player.o util/card.o table.o util/require.o common.o

all: server client

server: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o server

client: client.o
	$(CC) $(CFLAGS) common.o client.o -o client

client.o: client.cpp
	$(CC) $(CFLAGS) -c client.cpp

common.o: common.cpp
	$(CC) $(CFLAGS) -c common.cpp

server.o: server.cpp
	$(CC) $(CFLAGS) -c server.cpp

table.o: table.cpp
	$(CC) $(CFLAGS) -c table.cpp

player.o: player.cpp
	$(CC) $(CFLAGS) -c player.cpp

score.o: score.cpp
	$(CC) $(CFLAGS) -c score.cpp

util/card.o:
	make -C util

util/require.o:
	make -C util



.PHONY: clean
clean:
	rm -f *\.o
	rm -f server
	make -C util clean

