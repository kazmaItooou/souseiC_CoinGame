#pragma onc
#include "ofMain.h"
#include "Coin.h"
#include "barrierManager.h"
#define COIN_NUM 5

class CoinManager{
private:
    ofSoundPlayer countSound;
    barrierManager barrierManagerInstance;
    int coin_type;
public:
    CoinManager();
    vector <Coin *> CoinList;
    ofImage getCoinImage(int i);
    void draw();
    int checkGetCoin(int player_x, int player_y);
    int GetCoinType();
};

