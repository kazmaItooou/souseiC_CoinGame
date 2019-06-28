#include "barrierManager.h"

barrierManager::barrierManager(){
    //バリア位置
    int barrierPos[32][2]={{4,2},{5,2},{4,3},//1
                       {11,2},{12,2},{12,3},//2
                       {7,3},{7,4},{8,3},{9,3},{9,4},//3
                       {3,5},{3,6},{3,7},{4,5},{4,7},//4
                       {13,5},{13,6},{13,7},{12,5},{12,7},//5
                       {7,8},{7,9},{8,9},{9,9},{9,8},//6
                       {4,2},{5,2},{4,3},//7
                       {11,2},{12,2},{12,3}};//8

    for(int i=0;i<=31;i++){//バリアの位置をセット
        barrier *b = new barrier;
        b->setPos(barrierPos[i][1]*BASE_CORD,barrierPos[i][2]*BASE_CORD);
        barrierList.push_back(b);
    }
}

void barrierManager::draw(){
    //バリアの表示
    for (int i=0; i<barrierList.size(); i++) {
        barrierList.at(i)->draw();
    }
}

bool barrierManager::isbarrierTouchedtoPlayer(int Player_x,int Player_y){
    for(int i=0;i<0;i++){
        if((barrierList.at(i)->getPos().x)==Player_x && (barrierList.at(i)->getPos().y)==Player_y){
            return true;
        }
    }
    return false;
}
