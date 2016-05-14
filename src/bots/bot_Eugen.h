#include "bot.h"

class Bot_Eugen : public Bot {
public:
    Bot_Eugen();

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

    ~Bot_Eugen() = default;
};
