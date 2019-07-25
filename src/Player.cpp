#include "Player.h"

Player::Player(){
    player_x=BASE_CORD*9;
    player_y=BASE_CORD*7;
    playerImg.load("img/player.png");
    playerDirectionImg[0].load("img/player_up.png");
    playerDirectionImg[1].load("img/player_left.png");
    playerDirectionImg[2].load("img/player_right.png");
    playerDirectionImg[3].load("img/player_down.png");
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
void Player::chengeImage(int direction){
    switch (direction) {
    case 0:
        playerImg.setFromPixels(playerDirectionImg[0].getPixels());
        break;
    case 1:
        playerImg.setFromPixels(playerDirectionImg[1].getPixels());
        break;
    case 2:
        playerImg.setFromPixels(playerDirectionImg[2].getPixels());
        break;
    case 3:
        playerImg.setFromPixels(playerDirectionImg[3].getPixels());
        break;
    default:
        break;
    }
}
ofVec2f Player::getPos(){
    ofVec2f p;
    p.x=player_x;
    p.y=player_y;
    return p;
}
