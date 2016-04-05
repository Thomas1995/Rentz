build:
	g++ -std=c++11 main.cpp game.cpp util/card.cpp util/require.cpp bots/bot.cpp bots/bot_Thomas.cpp bots/bot_Lucian.cpp bots/bot_Eugen.cpp bots/bot_Eric.cpp -o exe
run:
	./exe
clean:
	rm -f *.o exe
