build:
	g++ -std=c++11 main.cpp util/card.cpp -o exe
run:
	./exe Nume1 Nume2 Nume3 Nume4
clean:
	rm -f *.o exe
