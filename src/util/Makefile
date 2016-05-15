CXX?=g++
CXXFLAGS?=-std=c++11 -g -Wall
OBJS=card.o require.o

all: $(OBJS)

%.o: %.cpp %.h

.PHONY: clean
clean:
		rm -f *\.o
