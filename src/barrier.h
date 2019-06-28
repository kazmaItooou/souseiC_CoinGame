#include "ofMain.h"
class barrier : public ofBaseApp{
private:
    int BASE_CORD = 40;
    ofImage barrierImg;
    int barrier_x;
    int barrier_y;
public:
    barrier();

    void setPos(int x, int y);
    void draw();

    ofVec2f getPos();
};
