#include "Coin.h"

void Coin::setPos(float x, float y){
    Pos_x = x;
    Pos_y = y;
}
void Coin::setPosRand(){
    int x = ofRandom(1,15);
    int y = ofRandom(1,11);

    int barrierPos[32][2]={{4,2},{5,2},{4,3},//1
                       {11,2},{12,2},{12,3},//2
                       {7,3},{7,4},{8,3},{9,3},{9,4},//3
                       {3,5},{3,6},{3,7},{4,5},{4,7},//4
                       {13,5},{13,6},{13,7},{12,5},{12,7},//5
                       {7,8},{7,9},{8,9},{9,9},{9,8},//6
                       {4,9},{5,10},{4,10},//7
                       {11,10},{12,9},{12,10}};
    for(int i=0;i<=32;i++){
        if(x==barrierPos[i][1] && y==barrierPos[i][2]){
            cout << "coin == barrier" << endl;
            setPosRand();
        }
    }
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
//コインを手に入れたとき所定の処理をしてポイントを返す
int Coin::checkGetCoin(int player_x, int player_y){
    if(Pos_x== player_x && Pos_y== player_y){
        setPosRand();
//        for(int i=0;i<sizeof(*coin[]) / sizeof(int);++i){
//            if((coin[i]-> Pos_x)==Pos_x &&(coin[i]-> Pos_y)==Pos_y){
//                checkGetCoin(player_x,player_y,coin[]);
//            }
//        }
        std::cout << "coin move" << std::endl;
        countSound.play();
        return point;
    }
    return 0;

}

