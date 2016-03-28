build:
	g++ -std=c++11 main.cpp game.cpp util/card.cpp -o exe
run:
	./exe
clean:
	rm -f *.o exe
