CC=g++
CFLAGS=-std=c++11 -g
OBJS=card.o require.o

all: $(OBJS)

%.o: %.cpp %.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
		rm -f *\.o
