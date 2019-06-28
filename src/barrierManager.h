#pragma once
#include "ofMain.h"
#include "barrier.h"


class barrierManager {
private:
    ofSoundPlayer barrierSetSound;
    ofSoundPlayer barrierKnockedSound;
public:
    int BASE_CORD = 40;
    barrierManager();
    //モンスタ管理用動的配列
    vector <barrier *> barrierList; //全モンスターを統括するポインタ配列
    //モンスタの表示
    void draw();

    bool isbarrierTouchedtoPlayer(int Player_x,int Player_y);
    };
