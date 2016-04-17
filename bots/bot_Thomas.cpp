#include "bot.h"

class Bot_Thomas : public Bot {
public:
    Bot_Thomas() : gamesOrderNV{Totals, Queens, Diamonds,
                    Whist, Acool, KingOfHearts, TenClub} {
        name = "Thomas";
    }

    Card PlayCard(const std::vector<Card>& cardsOnTable) {
        /// TO DO BETTER

        auto hand = GetHand();
        if(cardsOnTable.empty()) return hand[0];

        for(auto c : hand)
            if(cardsOnTable[0].isSameSuite(c))
                return c;

        return hand[0];
    }

    void GetPlayedCardStack(const std::vector<Card>& cardsOnTable) {
        /// TO DO
    }

    int GetGameType() {
        if(NVModeChosen) {
            // chose a game based on gamesOrderNV
            for(int i=0;i<7;++i)
              if(!gamesPlayed[gamesOrderNV[i]]) {
                gamesPlayed[gamesOrderNV[i]] = true;
                return gamesOrderNV[i];
              }
        }
        else {
            auto hand = GetHand();

            /// TO DO BETTER

            /// DETELE THIS
            for(int i=0;i<7;++i)
              if(!gamesPlayed[gamesOrderNV[i]]) {
                gamesPlayed[gamesOrderNV[i]] = true;
                return gamesOrderNV[i];
              }
        }
    }

    void SetGameType(const int gameType) {
        /// TO DO
    }

    bool PlayNVMode() {
        // play NV mode if not first or second player
        if(myLadderPosition > 2) {
            NVModeChosen = true;
            return true;
        }

        NVModeChosen = false;
        return false;
    }

    void SetScores(const int yourScore, const std::vector<int>& allScores) {
        // count scores bigger than mine
        int biggerScores = 0;
        for(auto it : allScores) {
            if(it > yourScore)
                ++biggerScores;
        }
        // update my ladder position
        myLadderPosition = biggerScores + 1;
    }

private:
    bool gamesPlayed[8];
    bool NVModeChosen;
    int myLadderPosition = 1;
    int gamesOrderNV[7];
};
