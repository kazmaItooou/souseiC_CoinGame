#include "CoinManager.h"

CoinManager::CoinManager(){
    cout << "CoinManager constructor loading"<< endl;

    countSound.load("sound/point.mp3");
    //Coinオブジェクト
    for(int i=0;i<=COIN_NUM;++i){
        Coin *c =new Coin;
        CoinList.push_back(c);
        CoinList[i]->setPosRand();
        CoinList[i]->setPoint(5*(i+1));
    }
    CoinList[0]->setImage("img/coin/copper.png");
    CoinList[1]->setImage("img/coin/silver.png");
    CoinList[2]->setImage("img/coin/gold.png");
    CoinList[3]->setImage("img/coin/red.png");
    CoinList[4]->setImage("img/coin/green.png");
    CoinList[5]->setImage("img/coin/blue.png");

    cout << "CoinManager constructor loaded"<< endl;
}

void CoinManager::draw(){
    for(int i=0;i<=COIN_NUM;++i){
        CoinList[i]->draw();
    }

    for(int i=0;i<=COIN_NUM;++i){
        for(int j=i+1;j<=COIN_NUM;++j){
            if((CoinList[i]->getCoinPos().x==CoinList[j]->getCoinPos().x &&
                    CoinList[i]->getCoinPos().y==CoinList[j]->getCoinPos().y) ||
                    //コインがバリアと重なってるかチェック
                    barrierManagerInstance.isbarrierTouchedtoPlayer(CoinList[i]->getCoinPos().x,CoinList[i]->getCoinPos().y)){

            }
        }
    }
}

int CoinManager::checkGetCoin(int player_x, int player_y){
    for(int i=0;i<=COIN_NUM;++i){
        if(CoinList[i]->getCoinPos().x== player_x &&
                CoinList[i]->getCoinPos().y== player_y){
            CoinList[i]->setPosRand();
            std::cout << "coin move " << i << std::endl;
            countSound.play();
            return CoinList[i]->getPoint();
        }
    }
    return 0;
}
