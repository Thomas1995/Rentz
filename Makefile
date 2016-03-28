build:
	g++ -std=c++11 main.cpp game.cpp util/card.cpp util/require.cpp bots/bot.cpp bots/bot_Thomas.cpp -o exe
run:
	./exe
clean:
	rm -f *.o exe
