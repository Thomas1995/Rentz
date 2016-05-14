#include "bot.h"

class Bot_Lucian : public Bot {
public:
    Bot_Lucian();

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

    ~Bot_Lucian() = default;
};
