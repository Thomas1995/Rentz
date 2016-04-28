CC=g++
CFLAGS=-std=c++11 -g

all: server

server: server.cpp
	$(CC) $(CFLAGS) server.cpp -o server

clean:
	rm server

