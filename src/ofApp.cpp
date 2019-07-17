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
    gndImg.load("img/gnd.png");
    underBoxImg.load("img/underBox.png");
    underBox2Img.load("img/underBox2.png");

    //ポイント
    pointCnt=0;
    for(int i=0;i<=COIN_NUM;i++){
        pointCnt_type[i]=0;
    }
    //---------------------------------------------
    //バリア
    bool_bM=false;
    bool_bM_sound=true;
    //result
    bool_OnResult=false;
}

//--------------------------------------------------------------
void ofApp::update(){
    //result
    if(bool_OnResult){
        resultInstance.update();
    }

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
            screenImg.grabScreen(0,0,ofGetWidth(),ofGetHeight());
            bool_OnResult=true;
            startbutton.isEnable=true;
            bool_bM_sound=true;
            return;
        }
    }
    cout<<"counddown_end: " <<counddown_end <<endl;

    //プレイヤーをステージ外に出さないようにする
    if (PlayerInstance.getPos().x<=coord(0)){PlayerInstance.setPos_x(coord(1));}
    if (PlayerInstance.getPos().x>=coord(16)){PlayerInstance.setPos_x(coord(15));}

    if (PlayerInstance.getPos().y<=coord(0)){PlayerInstance.setPos_y(coord(1));}
    if (PlayerInstance.getPos().y>=coord(12)){PlayerInstance.setPos_y(coord(11));}

    //----------------------------------------------
    //コインの位置
    //yクラッシュするのでx ,yのcacheを作ることで改善
    int player_y_cache=PlayerInstance.getPos().y;
    int player_x_cache=PlayerInstance.getPos().x;

    int point_cache=CoinMamagerInstance.checkGetCoin(player_x_cache,player_y_cache);
    pointCnt+=point_cache;

    if(point_cache>0){
        int Coin_type=CoinMamagerInstance.GetCoinType();
        pointCnt_type[Coin_type]++;
    }


    //barrierとの接触
    if(bM.isbarrierTouchedtoPlayer(player_x_cache ,player_y_cache) && bool_bM){
        PlayerInstance.setPos_y(before_player_y);
        PlayerInstance.setPos_x(before_player_x);
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

    //コインマネージャでコインを描画
    CoinMamagerInstance.draw();

    //プレイヤー
    PlayerInstance.draw();
    //スタートボタン
    if(startbutton.isEnable){startbutton.Draw();}

    //下のbox
    ofPushMatrix();
        underBoxImg.draw(ofGetWidth()/2+60, ofGetHeight()-60,ofGetWidth()-120,120);
    ofPopMatrix();
    ofPushMatrix();
        underBox2Img.draw(coord(2)-20, ofGetHeight()-60,120,120);
    ofPopMatrix();

    //ポイント表示
    ofSetColor(0,0,0,255);
    std_font.drawString("POINT", 12, ofGetHeight()-70);
    sprintf(pointCntStr,"%3d",pointCnt);
    std_font.drawString(pointCntStr, 30, ofGetHeight()-30);
    ofSetColor(255,255,255,255);

    ofSetColor(0,0,0,255);

    int pointCountPos=150;
    for(int i=0;i<=COIN_NUM;i++){
        ofPushMatrix();//座標系退避
        ofPushStyle();//表示スタイル退避
          ofSetColor(255,255,255);
          ofTranslate(pointCountPos+40, ofGetHeight()-80);//座標系変換
          //coinImage[i]->draw(0,0,40,40);
          CoinMamagerInstance.getCoinImage(i).draw(0,0,40,40);

        ofPopStyle();
        ofPopMatrix();
        memset( pointCntStr, 0, sizeof( pointCntStr ) );
        sprintf(pointCntStr,"%3d",pointCnt_type[i]);
        std_font.drawString(pointCntStr, pointCountPos, ofGetHeight()-30);
        pointCountPos+=80;
    }
    ofSetColor(255,255,255,255);

    if(bool_OnResult){
        resultInstance.draw(screenImg,&bool_OnResult,before_keyPressed);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    before_keyPressed=key;
    if(!bool_keyReleased) return;//連続移動できないようにする
    if(bool_keyReleased)bool_keyReleased= false;
    if(key==1)ofSetWindowShape(640,480);
    //バリア用のプレイヤー位置保存
    before_player_y=PlayerInstance.getPos().y;
    before_player_x=PlayerInstance.getPos().x;

    if (key == 'w') {
        PlayerInstance.setPos_y(before_player_y-BASE_COORD);
    }

    if (key == 's') {
        PlayerInstance.setPos_y(before_player_y+BASE_COORD);
    }

    if (key == 'a') {
        PlayerInstance.setPos_x(before_player_x-BASE_COORD);
    }
    if (key == 'd') {
        PlayerInstance.setPos_x(before_player_x+BASE_COORD);
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
    startbutton.mousePressed(x,y,button,&pointCnt,&pointCnt_type[0]);
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

