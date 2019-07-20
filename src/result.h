#include "ofMain.h"
#define COIN_NUM 5
class result : public ofBaseApp {

private:
    void blur_draw(int blur_value, ofImage image);//blur_valueをもとにimageにブラーをかける
    int update_timing;
    int image_flag;
    int SystemTimeMillis;
    int drawPointValue;
    float scalexy;
    ofTrueTypeFont std_font;
    ofSoundPlayer pointCountSound;
    ofImage coins[6];//コインの画像
public:
    result();   //コンストラクタ

    void draw(ofImage screenImg, bool *bool_OnResult, int before_keyPressed, int pointCnt, int pointCnt_type[]);
    void update();
    ofShader shaderBlurX;
    ofShader shaderBlurY;

    ofFbo fboBlurOnePass;
    ofFbo fboBlurTwoPass;

    ofImage backgroundImg;
    float blur;
};
