#include "result.h"

result::result(){
    ofTrueTypeFontSettings settings("font/PixelMplus12-Regular.ttf",30);//設定一式を納めるインスタンス
    settings.addRanges(ofAlphabet::Latin);
    settings.addRanges(ofAlphabet::Japanese);//日本語
    std_font.load(settings); // 設定をロード
    update_timing=0;
    image_flag=0;
    drawPointValue=0;
    scalexy=3;
#ifdef TARGET_OPENGLES
    shaderBlurX.load("shadersES2/shaderBlurX");
    shaderBlurY.load("shadersES2/shaderBlurY");
#else
    if(ofIsGLProgrammableRenderer()){
        shaderBlurX.load("shadersGL3/shaderBlurX");
        shaderBlurY.load("shadersGL3/shaderBlurY");
    }else{
        shaderBlurX.load("shadersGL2/shaderBlurX");
        shaderBlurY.load("shadersGL2/shaderBlurY");
    }
#endif
    backgroundImg.load("img/result_background.png");
    fboBlurOnePass.allocate(ofGetWidth(), ofGetHeight());
    fboBlurTwoPass.allocate(ofGetWidth(), ofGetHeight());
}
void result::update(){
    if(image_flag==0){
        update_timing++;
        if(update_timing>=60){
            image_flag=1;
        }
    }
    if(image_flag==1 && update_timing>0){
        update_timing--;
    }
    //cout<<update_timing<<endl;
}
void result::draw(ofImage screenImg,bool *bool_OnResult, int before_keyPressed,int pointCnt){
    if(image_flag==0){
        blur_draw(update_timing,screenImg);
        SystemTimeMillis=ofGetSystemTimeMillis();
    }
    if(image_flag==1){
        pointCnt=999;
        blur_draw(update_timing,backgroundImg);
        if(update_timing==0){
            //スコアとか追加する
            if(SystemTimeMillis+50<=ofGetSystemTimeMillis() && drawPointValue<pointCnt-5){
                drawPointValue+=10;
                SystemTimeMillis+=50;

                if(scalexy==3){
                    scalexy=4;
                }else{
                    scalexy=3;
                }
            }else if(SystemTimeMillis+50<=ofGetSystemTimeMillis()){
                drawPointValue=pointCnt;
            }

            ofPushMatrix();//座標系退避
            ofPushStyle();//表示スタイル退避
            ofScale(scalexy,scalexy);
              char pointCntStr2[3]={};
              sprintf(pointCntStr2,"%3d",drawPointValue);
              std_font.drawString(pointCntStr2, ((ofGetWidth()/2)-10)/scalexy, ((ofGetHeight()/2)+20)/scalexy);
            ofPopMatrix();//座標系退避
            ofPopStyle();//表示スタイル退避

            if(before_keyPressed=='r'){
                *bool_OnResult=false;
            }
        }
    }
}

void result::blur_draw(int blur_value ,ofImage image){
    ofPushMatrix();//座標系退避
    ofPushStyle();//表示スタイル退避

      ofTranslate(0, 0);//座標系変換
      ofSetRectMode(OF_RECTMODE_CORNER);
    blur_value = ofMap(blur_value, 0, 60, 0, 30, true);
    //std::cout << blur_value <<"asdf"<< std::endl;
    //----------------------------------------------------------
    fboBlurOnePass.begin();

    shaderBlurX.begin();
    shaderBlurX.setUniform1f("blurAmnt", blur_value);

    image.draw(0,0);

    shaderBlurX.end();

    fboBlurOnePass.end();

    //----------------------------------------------------------
    fboBlurTwoPass.begin();

    shaderBlurY.begin();
    shaderBlurY.setUniform1f("blurAmnt", blur_value);

    fboBlurOnePass.draw(0, 0);

    shaderBlurY.end();

    fboBlurTwoPass.end();

    //----------------------------------------------------------
    ofSetColor(ofColor::white);
    fboBlurTwoPass.draw(0, 0);
    ofPopStyle();
    ofPopMatrix();

}

