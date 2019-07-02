#include "ofMain.h"
#define BARRIER_NUM 32

class Coin : public ofBaseApp {

private:    //非公開
    int BASE_CORD = 40;
    ofSoundPlayer countSound;
    ofImage coinImg;//画像用変数(oF)
    bool bool_touchingBarrier;
    //barrierManager bM(1);
    //barrierManager *bM;
    int barrierPos[BARRIER_NUM][2]={{4,2},{5,2},{4,3},//1
                       {11,2},{12,2},{12,3},//2
                       {7,3},{7,4},{8,3},{9,3},{9,4},//3
                       {3,5},{3,6},{3,7},{4,5},{4,7},//4
                       {13,5},{13,6},{13,7},{12,5},{12,7},//5
                       {7,8},{7,9},{8,9},{9,9},{9,8},//6
                       {4,9},{5,10},{4,10},//7
                       {11,10},{12,9},{12,10}};//8
public:    //公開
    //メソッド
    Coin(){   //コンストラクタ
        countSound.load("sound/point.mp3");
        Pos_x=0;
        Pos_y=0;
    }
    //プロパティ
    float Pos_x; //位置x
    float Pos_y; //位置y
    int point;
    //アクセサ
    void setPos(float x, float y);
    void setPosRand();
    void setPoint(int value);
    void setImage(string path_on_img);
    void draw();
    int checkGetCoin(int player_x, int player_y);
};
