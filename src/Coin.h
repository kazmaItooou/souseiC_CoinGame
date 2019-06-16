#include "ofMain.h"
class Coin : public ofBaseApp {

private:    //非公開
    int BASE_CORD = 40;
    ofSoundPlayer countSound;
    ofImage coinImg;//画像用変数(oF)
public:    //公開
    //メソッド
    Coin(){   //コンストラクタ
        countSound.load("sound/point.wav");
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
