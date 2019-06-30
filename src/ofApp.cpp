#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
    //---------------------------------------------
    //その他
    ofBackground(0, 0, 0);//背景は黒
    ofSetRectMode(OF_RECTMODE_CENTER);
    countSound_end.load("sound/endcount.mp3");
    //---------------------------------------------
    //フォント
    ofTrueTypeFontSettings settings("font/PixelMplus12-Regular.ttf",30);//設定一式を納めるインスタンス
    settings.addRanges(ofAlphabet::Latin);
    settings.addRanges(ofAlphabet::Japanese);//日本語
    std_font.load(settings); // 設定をロード
    if (std_font.isLoaded()){
        cout << "Title Font loaded" << endl;
    } else {
        cout << "Title Font file is not found" << endl;
    }
    //---------------------------------------------
    //ゲーム内変数
    BASE_COORD = 40;//xとyの公倍数[1, 2, 4, 5, 8, 10, 16, 20, 32, 40, 80, 160]
    playerImg.load("img/player.png");
    gndImg.load("img/gnd.png");
    underBoxImg.load("img/underBox.png");
    underBox2Img.load("img/underBox2.png");
    player_x=coord(9);
    player_y=coord(7);
    //ポイント
    pointCnt=0;
    //---------------------------------------------
    //Coinオブジェクト
    for(int i=0;i<=COIN_NUM;++i){
        coinList_p[i]=new Coin;
        coinList_p[i]->setPosRand();
        coinList_p[i]->setPoint(5*(i+1));
    }
    coinList_p[0]->setImage("img/coin/copper.png");
    coinList_p[1]->setImage("img/coin/silver.png");
    coinList_p[2]->setImage("img/coin/gold.png");
    coinList_p[3]->setImage("img/coin/red.png");
    coinList_p[4]->setImage("img/coin/green.png");
    coinList_p[5]->setImage("img/coin/blue.png");
    //---------------------------------------------
    //バリア
    bool_bM=false;
    bool_bM_sound=true;
}

//--------------------------------------------------------------
void ofApp::update(){
    //スタートボタンがONのときは常にminute_end、second_endに現在の時間を入れる。
    //そしてタイマーをOFFにし続ける。
    if(!startbutton.isEnable){
        //ボタンが押されたときにタイマーをONにする
        endtimerenable=true;
    }else{
        minute_end=ofGetMinutes();
        second_end=ofGetSeconds();
        second_tmp_end=ofGetSeconds();
        counddown_end=60;
        endtimerenable=false;
        return;
    }
    //タイマーがONになっているとき、先程の処理でわかった時刻+1分になったときに再びタイマーをつける。
    if(endtimerenable){
        //----------------------------------
        //音を鳴らす
        if(second_tmp_end!=ofGetSeconds()){
            second_tmp_end=ofGetSeconds();
            counddown_end--;
            if(counddown_end<=5){
                countSound_end.play();
            }
        }
        if(minute_end+1==ofGetMinutes() && second_end==ofGetSeconds()){
            startbutton.isEnable=true;
            pointCnt=0;
            bool_bM_sound=true;
            return;
        }
    }

    if (player_x<=coord(0)){player_x= coord(1);}
    if (player_x>=coord(16)){player_x= coord(15);}

    if (player_y<=coord(0)){player_y= coord(1);}
    if (player_y>=coord(12)){player_y= coord(11);}

    //----------------------------------------------
    //コインの位置
    //yクラッシュするのでx ,yのcacheを作ることで改善
    int player_y_cache=player_y;
    int player_x_cache=player_x;
    for(int i=0;i<=COIN_NUM;++i){
        int point_cache=coinList_p[i]->checkGetCoin(player_x_cache,player_y_cache);
        pointCnt+=point_cache;

        if(point_cache>0){//こいんがかさならなくする
            for(int j=0;j<=COIN_NUM;++j){

                if((coinList_p[i]->Pos_x==coinList_p[j]->Pos_x &&
                   coinList_p[i]->Pos_y==coinList_p[j]->Pos_y) ||
                        (bM.isbarrierTouchedtoPlayer(coinList_p[i]->Pos_x ,coinList_p[i]->Pos_y))){

                    if(coinList_p[i]!=coinList_p[j]){
                        coinList_p[i]->setPosRand();
                        cout << "coin touched other coin" <<endl;
                    }
                }
            }
        }


    }
    //barrierとの接触
    if(bM.isbarrierTouchedtoPlayer(player_x_cache ,player_y_cache) && bool_bM){
        player_y=before_player_y;
        player_x=before_player_x;
        bM.playTouchSound();
    }

    //　pointCnt>=200　でバリアをONにする
    if(pointCnt>=200){
        bool_bM=true;
        //バリアの発動のときに音を出す
        if(bool_bM_sound){
            bM.playSetSound();
            bool_bM_sound=false;
        }
    }else bool_bM=false;

    if(pointCnt>=999){pointCnt=999;}//999ポイントがカンスト
}

//--------------------------------------------------------------
void ofApp::draw(){
    //---------------------------------------------
    //地面　ひとマス40dpiなのでそれを基準に敷く
    for(int COORD_X =0;BASE_COORD*COORD_X<=640;++COORD_X){
        for(int COORD_Y=0;BASE_COORD*COORD_Y<=480;++COORD_Y){
            gndImg.draw(coord(COORD_X),coord(COORD_Y));

            //マスをわかりやすくする処理
            if((COORD_X%2 && COORD_Y%2)){ofSetColor(51,51,51);}//偶数マス（黒）
            if (!(COORD_X%2) && !(COORD_Y%2)){ofSetColor(51,51,51);}//奇数マス
            if ((!(COORD_X%2) && (COORD_Y%2)) || ((COORD_X%2) && !(COORD_Y%2))){ofSetColor(51,51,51);}//白
            ofSetRectMode(OF_RECTMODE_CENTER);
            ofNoFill();
            ofDrawRectangle(coord(COORD_X),coord(COORD_Y), BASE_COORD, BASE_COORD);
            ofSetColor(255,255,255);
        }
    }
    //barrierオブジェクト
    if(bool_bM){bM.draw();}

    //Coinオブジェクト
    for(int i=0;i<=COIN_NUM;++i){
        coinList_p[i]->draw();
    }

    //プレイヤー
    playerImg.draw(player_x, player_y);

    //スタートボタン
    if(startbutton.isEnable){startbutton.Draw();}

    //下のbox
    ofPushMatrix();
        underBoxImg.draw(ofGetWidth()/2+60, ofGetHeight()-60,ofGetWidth()-120,120);
    ofPopMatrix();
    ofPushMatrix();
        underBox2Img.draw(coord(2)-20, ofGetHeight()-60,120,120);
    ofPopMatrix();

    ofSetColor(0,0,0,255);
    std_font.drawString("POINT", 12, ofGetHeight()-70);
    sprintf(pointCntStr,"%3d",pointCnt);
    std_font.drawString(pointCntStr, 30, ofGetHeight()-30);
    ofSetColor(255,255,255,255);


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(!bool_keyReleased) return;//連続移動できないようにする
    if(bool_keyReleased)bool_keyReleased= false;
    if(key==1)ofSetWindowShape(640,480);
    //バリア用のプレイヤー位置保存
    before_player_y=player_y;
    before_player_x=player_x;

    if (key == 'w') {
        before_player_y=player_y;
        player_y -=BASE_COORD;
    }

    if (key == 's') {
        before_player_y=player_y;
        player_y +=BASE_COORD;
    }

    if (key == 'a') {
        before_player_x=player_x;
        player_x -=BASE_COORD;
    }
    if (key == 'd') {
        before_player_x=player_x;
        player_x +=BASE_COORD;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    bool_keyReleased = true;//連続移動できないようにする

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    startbutton.mousePressed(x,y,button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    ofSetWindowShape(640,600);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
}

