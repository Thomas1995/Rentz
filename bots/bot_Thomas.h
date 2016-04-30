#include "bot.h"

class Bot_Thomas : public Bot {
public:
    Bot_Thomas();

    Card PlayCard();

    void GetPlayedCardStack();

    int GetGameType();

    void SetGameType(const int gameType);

    bool PlayNVMode();

    void SetScores(const int yourScore, const std::vector<int>& allScores);

private:
    bool gamesPlayed[8];
    bool NVModeChosen;
    int myLadderPosition = 1;
    int gamesOrderNV[7];
    int crtGameType;
};
