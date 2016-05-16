#include "bot.h"

class Bot_Eric : public Bot {
public:
    Bot_Eric();

    bool NVModeChosen;
    int myLadderPosition = 1;
    std::vector<Minigame> gamesOrderNV;

    Minigame onChooseMinigame();

    Card onPlayCard();

    bool onAskIfNV();
};
