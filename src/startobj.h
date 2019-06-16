#include "ofMain.h"
class startobj : public ofBaseApp {

private:    //非公開
    //void setPos(float x, float y);
    bool btn_y(float OverY,float UnderY,float MouseY);
    bool btn_x(float LeftX, float RightX,float MouseX);
    ofImage buttonImg;
    ofTimer gameTimer;
public:    //公開
    startobj();   //コンストラクタ

    bool isEnable;//ボタンが押されているか
    void Draw();
    void mousePressed(int x, int y, int button);
};
