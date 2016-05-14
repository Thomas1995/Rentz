#include "bot.h"

class Bot_Eric : public Bot {
public:
    Bot_Eric();

    std::vector<Card> getPlayedCardStack();

    bool gamesPlayed[8];
    bool NVModeChosen;
    int myLadderPosition = 1;
    int gamesOrderNV[7];
    int crtGameType;

    uint8_t decideGameType();

    void receiveDecidedGameType(const int gameType);

    Card decideCardToPlay();

    bool decidePlayNV(); 

    ~Bot_Eric() = default;
};
