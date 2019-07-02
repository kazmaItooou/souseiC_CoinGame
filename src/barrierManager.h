#pragma once
#include "ofMain.h"
#include "barrier.h"
#define BARRIER_NUM 32

class barrierManager {
private:
    ofSoundPlayer barrierSetSound;
    ofSoundPlayer barrierTouchSound;
    int BASE_CORD = 40;
    int barrierPos[BARRIER_NUM][2]={{4,2},{5,2},{4,3},//1
                       {11,2},{12,2},{12,3},//2
                       {7,3},{7,4},{8,3},{9,3},{9,4},//3
                       {3,5},{3,6},{3,7},{4,5},{4,7},//4
                       {13,5},{13,6},{13,7},{12,5},{12,7},//5
                       {7,8},{7,9},{8,9},{9,9},{9,8},//6
                       {4,9},{5,10},{4,10},//7
                       {11,10},{12,9},{12,10}};//8
public:
    barrierManager();
    barrierManager(int Coin);
    vector <barrier *> barrierList;
    void draw();
    void playSetSound();
    void playTouchSound();
    bool isbarrierPos(int x,int y);
    bool isbarrierTouchedtoPlayer(int Player_x,int Player_y);//プレイヤー等がバリアと重なっているか真偽を返す
    };
