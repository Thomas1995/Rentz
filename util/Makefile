CXX?=g++
CFLAGS?=-std=c++11 -g -Wall
OBJS=card.o require.o

all: $(OBJS)

%.o: %.cpp %.h
	$(CXX) $(CFLAGS) -c $<

.PHONY: clean
clean:
		rm -f *\.o
