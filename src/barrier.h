#include "ofMain.h"
class barrier : public ofBaseApp{
private:
    ofImage barrierImg;
    ofSoundPlayer barrierSetSound;
    ofSoundPlayer barrierKnockedSound;
public:
    barrier();

    int barrier_x;
    int barrier_y;

    void setPos(int x, int y);
    void draw();
};
