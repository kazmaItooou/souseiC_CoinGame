#include "ofMain.h"
#define BASE_CORD 40
class Player: public ofBaseApp{
private:
    ofImage playerImg;
    ofImage playerDirectionImg[4];
    int player_x;
    int player_y;

public:
    Player();
    void setPos(int x,int y);
    void setPos_x(int x);
    void setPos_y(int y);
    void draw();
    void chengeImage(int direction);
    ofVec2f getPos();
};

