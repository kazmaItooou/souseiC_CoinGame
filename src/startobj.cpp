#include "startobj.h"
startobj::startobj(){
    buttonImg.load("img/start.png");
    isEnable=true;
}
bool startobj::btn_y(float OverY,float UnderY,float MouseY){
    if(OverY<=MouseY && UnderY>=MouseY){
        return true;
    }
    return false;
}
//X軸
bool startobj::btn_x(float LeftX, float RightX,float MouseX){
    if(LeftX <=MouseX && RightX >= MouseX){
        return true;
    }
    return false;
}
void startobj::Draw(){
    ofPushMatrix();//座標系退避
    ofPushStyle();//表示スタイル退避

      ofTranslate(40*8, 40*6);//座標系変換
      ofSetRectMode(OF_RECTMODE_CENTER);
      buttonImg.draw(0, 0, 200, 120);

    ofPopStyle();
    ofPopMatrix(); 
}

void startobj::mousePressed(int x, int y, int button,int *pointCnt,int *pointCnt_type){
    int BtnU_y=40*6+120/2;//オプションボタンの下のy座標
    int BtnO_y=40*6-120/2;//オプションボタンの上のy座標

    int BtnL_x=40*8-200/2;//オプションボタンの左のx座標
    int BtnR_x=40*8+200/2;//オプションボタンの右のx座標
    if(isEnable){
        if(btn_y(BtnO_y,BtnU_y, y) &&
                btn_x(BtnL_x, BtnR_x,x) && button==0){
            isEnable=false;
            *pointCnt=0;
            for(int i=0;i<=COIN_NUM;i++){
                pointCnt_type[i]=0;
            }
            std::cout << "isEnable" << std::endl;
        }
    }
}
