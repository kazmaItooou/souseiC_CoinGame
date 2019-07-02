#pragma onc
#include "ofMain.h"
#include "Coin.h"
#include "barrierManager.h"
#define COIN_NUM 5

class CoinManager{
private:
    ofSoundPlayer countSound;
    barrierManager barrierManagerInstance;
public:
    CoinManager();
    vector <Coin *> CoinList;
    void draw();
    int checkGetCoin(int player_x, int player_y);
};

