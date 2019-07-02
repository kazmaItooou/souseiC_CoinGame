#include "barrierManager.h"
barrierManager::barrierManager(){
    cout << "barrierManager constructor loading"<< endl;

    //バリア位置
    barrierSetSound.load("sound/setbarrier.mp3");
    barrierTouchSound.load("sound/knocked.mp3");
    for(int ij=0;ij<BARRIER_NUM;ij++){//バリアの位置をセット
        barrier *b = new barrier;
        b->setPos(barrierPos[ij][0]*BASE_CORD,barrierPos[ij][1]*BASE_CORD);
        barrierList.push_back(b);
        cout << "barrierPos seted"<< endl;
        cout << "["<<ij<< "]"<< barrierPos[ij][0] <<","<< barrierPos[ij][1] << endl;
    }
    cout << "barrierManager constructor loaded"<< endl;
}
barrierManager::barrierManager(int Coin){
     cout << "barrierManager constructor for Coin class loaded"<< endl;
}

void barrierManager::draw(){
    //バリアの表示
    for (int i=0; i<barrierList.size(); i++) {
        barrierList.at(i)->draw();
    }
}

void barrierManager::playSetSound(){
    barrierSetSound.play();
}

void barrierManager::playTouchSound(){
    barrierTouchSound.play();
}

bool barrierManager::isbarrierPos(int x,int y){
    for(int i=0;i<BARRIER_NUM;i++){
        if(x==barrierPos[i][0] && y==barrierPos[i][1]){
            return true;
        }
    }
    return false;
}

bool barrierManager::isbarrierTouchedtoPlayer(int Player_x,int Player_y){
    for(int i=0;i<barrierList.size();i++){
        if((barrierList.at(i)->getPos().x)==Player_x && (barrierList.at(i)->getPos().y)==Player_y){
            return true;
        }
    }
    return false;
}
