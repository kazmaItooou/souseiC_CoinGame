#include "Coin.h"

void Coin::setPos(float x, float y){
    Pos_x = x;
    Pos_y = y;
}
void Coin::setPosRand(){
    int x = ofRandom(1,15);
    int y = ofRandom(1,11);
    Pos_x = x*BASE_CORD;
    Pos_y = y*BASE_CORD;
}
void Coin::setPoint(int value){
    point=value;
}
void Coin::setImage(string path_on_img){
    coinImg.load(path_on_img);
}

//画像表示
void Coin::draw() {
    ofPushMatrix();//座標系退避
    ofPushStyle();//表示スタイル退避

      ofTranslate(Pos_x, Pos_y);//座標系変換
      ofSetRectMode(OF_RECTMODE_CENTER);
      coinImg.draw(0, 0, 40, 40);

    ofPopStyle();
    ofPopMatrix();

}

