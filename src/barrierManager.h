#pragma once
#include "ofMain.h"
#include "barrier.h"


class barrierManager {
private:
    ofSoundPlayer barrierSetSound;
    ofSoundPlayer barrierTouchSound;
    int BASE_CORD = 40;
public:
    barrierManager();
    vector <barrier *> barrierList;
    void draw();
    void playSetSound();
    void playTouchSound();
    bool isbarrierTouchedtoPlayer(int Player_x,int Player_y);//プレイヤー等がバリアと重なっているか真偽を返す
    };
