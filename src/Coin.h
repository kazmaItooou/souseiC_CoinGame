#include "ofMain.h"
class Coin : public ofBaseApp {

private:    //非公開
    int BASE_CORD = 40;
public:    //公開
    //メソッド
    coin();   //コンストラクタ

    //プロパティ
    float Pos_x; //位置x
    float Pos_y; //位置y
    ofImage coinImg;//画像用変数(oF)

    //アクセサ
    void setPos(float x, float y);
    void setPosRand();
    void setImage(string path_on_img);
    void draw();
};
