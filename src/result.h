#include "ofMain.h"
#define COIN_NUM 5
class result : public ofBaseApp {

private:
    void blur_draw(int blur_value, ofImage image);
    int update_timing;
    int image_flag;
    int SystemTimeMillis;
    int drawPointValue;
    int scalexy;
    ofTrueTypeFont std_font;
public:
    result();   //コンストラクタ
    void draw(ofImage screenImg, bool *bool_OnResult, int before_keyPressed, int pointCnt);
    void update();
    ofShader shaderBlurX;
    ofShader shaderBlurY;

    ofFbo fboBlurOnePass;
    ofFbo fboBlurTwoPass;

    ofImage backgroundImg;
    float blur;
};
