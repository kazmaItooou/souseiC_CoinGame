#include "result.h"

result::result(){
    ofTrueTypeFontSettings settings("font/PixelMplus12-Regular.ttf",60);//設定一式を納めるインスタンス
    settings.addRanges(ofAlphabet::Latin);
    settings.addRanges(ofAlphabet::Japanese);//日本語
    std_font.load(settings); // 設定をロード
    update_timing=0;
    image_flag=0;
    drawPointValue=0;
    scalexy=3;
    pointCountSound.load("sound/pointcount.mp3");
    pointCountSound.setSpeed(2);
    coins[0].load("img/coin/copper.png");
    coins[1].load("img/coin/silver.png");
    coins[2].load("img/coin/gold.png");
    coins[3].load("img/coin/red.png");
    coins[4].load("img/coin/green.png");
    coins[5].load("img/coin/blue.png");
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
}
void result::draw(ofImage screenImg,bool *bool_OnResult, int before_keyPressed,int pointCnt,int pointCnt_type[]){
    //CoinMamagerInstance.CoinList[i]
    if(image_flag==0){
        blur_draw(update_timing,screenImg);
        SystemTimeMillis=ofGetSystemTimeMillis();

    }
    if(image_flag==1){
        //デバッグ用
        //pointCnt=999;
        blur_draw(update_timing,backgroundImg);
        if(update_timing==0){
            //スコアとか追加する
            if(SystemTimeMillis+70<=ofGetSystemTimeMillis() && drawPointValue<pointCnt-5){
                drawPointValue+=5;
                SystemTimeMillis+=70;

                if(scalexy==1){
                    scalexy=1.2;
                }else{
                    scalexy=1;
                }
                pointCountSound.play();
            }else if(SystemTimeMillis+70<=ofGetSystemTimeMillis()){
                drawPointValue=pointCnt;
                scalexy=1.2;
            }
            //スコアの数字
            ofPushMatrix();
            ofPushStyle();
            ofScale(scalexy,scalexy);
            ofSetColor(0,0,0);
              char pointCntStr2[3]={};
              sprintf(pointCntStr2,"%3d",drawPointValue);
              std_font.drawString(pointCntStr2, ((ofGetWidth()/2)-10)/scalexy, ((ofGetHeight()/2)+20)/scalexy);
            ofPopMatrix();
            ofPopStyle();

            //スコアを表示
            //RESTART
            ofPushMatrix();
            ofPushStyle();
            ofScale(1,1);
              ofSetColor(0,0,0);
              std_font.drawString("SCORE: ", ((ofGetWidth()/2)-260), ((ofGetHeight()/2)+20));
              std_font.drawString("RESTART: R", ((ofGetWidth()/2-260)), ((ofGetHeight()/2)+220));

              //coin score
              int pointCountPos=-10;
              char pointCntStr[3];
              for(int i=0;i<=COIN_NUM;i++){
                  ofPushMatrix();
                  ofPushStyle();
                    ofSetColor(255,255,255);
                    ofTranslate(pointCountPos, 30);
                    coins[i].draw(80,0,50,50);
                  ofPopStyle();
                  ofPopMatrix();

                  ofPushStyle();
                    ofSetColor(0,0,0);
                    memset( pointCntStr, 0, sizeof( pointCntStr ));
                    sprintf(pointCntStr,"%3d",pointCnt_type[i]);
                    std_font.drawString(pointCntStr, pointCountPos, 110);
                    pointCountPos+=100;
                  ofPopStyle();
              }

            ofPopMatrix();
            ofPopStyle();
            //'r'を押すとリザル度画面が終了する
            if(before_keyPressed=='r'){
                *bool_OnResult=false;
            }
        }
    }
}

void result::blur_draw(int blur_value ,ofImage image){
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(0, 0);
    ofSetRectMode(OF_RECTMODE_CORNER);

    //09_gaussianBlurFilterを利用してブラーを作った
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

