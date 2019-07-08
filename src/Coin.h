#include "ofMain.h"
#define BARRIER_NUM 32

class Coin : public ofBaseApp {

private:    //非公開
    int BASE_CORD = 40;
    ofSoundPlayer countSound;
    ofImage coinImg;//画像用変数(oF)
    bool bool_touchingBarrier;
    //プロパティ
    float Pos_x; //位置x
    float Pos_y; //位置y
    int point;
public:    //公開
    //メソッド
    Coin();
    //アクセサ
    void setPos(float x, float y);
    void setPosRand();
    void setPoint(int value);
    int getPoint();
    ofImage getImage();
    void setImage(string path_on_img);
    void draw();
    ofVec2f getCoinPos();
    int checkGetCoin(int player_x, int player_y);
};
