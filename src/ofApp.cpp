#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //---------------------------------------------
    //その他
    ofBackground(0, 0, 0);//背景は黒
    ofSetRectMode(OF_RECTMODE_CENTER);
    startbutton.setup();
    countSound_end.load("sound/endcount.wav");
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
    //---------------------------------------------
    //Coinオブジェクト
    coin_gold.setImage("img/coin/gold.png");
    coin_gold.setPosRand();
    coin_gold.setPoint(20);
    coin_silver.setImage("img/coin/silver.png");
    coin_silver.setPosRand();
    coin_silver.setPoint(10);
    coin_copper.setImage("img/coin/copper.png");
    coin_copper.setPosRand();
    coin_copper.setPoint(10);
    coin_green.setImage("img/coin/green.png");
    coin_green.setPosRand();
    coin_green.setPoint(10);
    coin_blue.setImage("img/coin/blue.png");
    coin_blue.setPosRand();
    coin_blue.setPoint(10);
    coin_red.setImage("img/coin/red.png");
    coin_red.setPosRand();
    coin_red.setPoint(10);
    //---------------------------------------------
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
        //-------------------------------------
        if(minute_end+1==ofGetMinutes() && second_end==ofGetSeconds()){
            startbutton.isEnable=true;
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
    pointCnt+=coin_gold.checkGetCoin(player_x_cache,player_y_cache);
    pointCnt+=coin_silver.checkGetCoin(player_x_cache,player_y_cache);
    pointCnt+=coin_copper.checkGetCoin(player_x_cache,player_y_cache);
    pointCnt+=coin_green.checkGetCoin(player_x_cache,player_y_cache);
    pointCnt+=coin_blue.checkGetCoin(player_x_cache,player_y_cache);
    pointCnt+=coin_red.checkGetCoin(player_x_cache,player_y_cache);
    //----------------------------------------------
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
    //---------------------------------------------
    //カウントダウン
    //---------------------------------------------
    //終了

    //---------------------------------------------
    //Coinオブジェクト
    coin_gold.draw();
    coin_silver.draw();
    coin_copper.draw();
    coin_green.draw();
    coin_blue.draw();
    coin_red.draw();
    //---------------------------------------------
    playerImg.draw(player_x, player_y);//プレイヤー
    if(startbutton.isEnable){startbutton.Draw();}//スタートボタン
    //---------------------------------------------
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
    //---------------------------------------------


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(!bool_keyReleased) return;
    if(bool_keyReleased)bool_keyReleased= false;
    if(key==1)ofSetWindowShape(640,480);

    if (key == 'w') {
        player_y -=BASE_COORD;
        //if (player_y<=coord(0)){player_y= coord(1);}
    }

    if (key == 's') {
        player_y +=BASE_COORD;
        //if (player_y>=coord(12)){player_y= coord(11);}
    }

    if (key == 'a') {
        player_x -=BASE_COORD;
        //if (player_x<=coord(0)){player_x= coord(1);}
    }
    if (key == 'd') {
        player_x +=BASE_COORD;
        //if (player_x>=coord(16)){player_x= coord(15);}
    }


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    bool_keyReleased = true;

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

