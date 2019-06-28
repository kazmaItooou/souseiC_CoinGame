#pragma once
#include "ofMain.h"
#include "barrier.h"


class barrierManager {
private:
public:
    ofSoundPlayer barrierSetSound;
    ofSoundPlayer barrierKnockedSound;
    int BASE_CORD = 40;
    barrierManager();
    vector <barrier *> barrierList;
    void draw();
    void playSetSound();
    bool isbarrierTouchedtoPlayer(int Player_x,int Player_y);
    };
