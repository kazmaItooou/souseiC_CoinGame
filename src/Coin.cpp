#include "Coin.h"

Coin::Coin(){   //コンストラクタ
    countSound.load("sound/point.mp3");
    Pos_x=0;
    Pos_y=0;
}
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
int Coin::getPoint(){
    return point;
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

ofVec2f Coin::getCoinPos(){
    ofVec2f p;
    p.x=Pos_x;
    p.y=Pos_y;
    return p;
}
ofImage Coin::getImage(){
    return coinImg;
}

//コインを手に入れたとき所定の処理をしてポイントを返す
int Coin::checkGetCoin(int player_x, int player_y){
    if(Pos_x== player_x && Pos_y== player_y){
        setPosRand();
        cout << "coin move" << std::endl;
        countSound.play();
        return point;
    }
    return 0;

}

