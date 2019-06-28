#include "barrier.h"

barrier::barrier(){
    barrierImg.load("img/barrier.png");
}

void barrier::setPos(int x, int y){
    barrier_x=x;
    barrier_y=y;
}
ofVec2f barrier::getPos(){
    ofVec2f p;
    p.x=barrier_x;
    p.y=barrier_y;
    return p;
}
void barrier::draw(){
    ofPushMatrix();//座標系退避
    ofPushStyle();//表示スタイル退避

      ofTranslate(barrier_x, barrier_y);//座標系変換
      ofSetRectMode(OF_RECTMODE_CENTER);
      barrierImg.draw(0, 0, 40, 40);

    ofPopStyle();
    ofPopMatrix();
}
