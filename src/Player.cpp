#include "Player.h"

Player::Player(){
    player_x=BASE_CORD*9;
    player_y=BASE_CORD*7;
    playerImg.load("img/player.png");
}

void Player::setPos(int x,int y){
    player_x=BASE_CORD*x;
    player_y=BASE_CORD*y;
}

void Player::setPos_x(int x){
    player_x=x;
}

void Player::setPos_y(int y){
    player_y=y;
}
void Player::draw(){
    ofPushMatrix();//座標系退避
    ofPushStyle();//表示スタイル退避

      ofTranslate(player_x, player_y);//座標系変換
      ofSetRectMode(OF_RECTMODE_CENTER);
      playerImg.draw(0, 0, 40, 40);

    ofPopStyle();
    ofPopMatrix();
}
ofVec2f Player::getPos(){
    ofVec2f p;
    p.x=player_x;
    p.y=player_y;
    return p;
}
