#pragma once

#include "ofMain.h"
#include "startobj.h"
#include "barrierManager.h"
#include "CoinManager.h"
#include "Player.h"
#define COIN_NUM 5
class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        //---------------------------------------------
        //その他
        ofTrueTypeFont std_font;
        startobj startbutton;
        //--------------------------------------------
        //終了
        bool endtimerenable;
        int minute_end;
        int second_end;
        int counddown_end;
        int second_tmp_end;
        ofSoundPlayer countSound_end;
        //---------------------------------------------
        //ゲーム内変数
        int BASE_COORD;//公倍数[1, 2, 4, 5, 8, 10, 16, 20, 32, 40, 80, 160]
        int before_player_x;
        int before_player_y;
        Player PlayerInstance;

        bool bool_keyReleased;
        ofImage playerImg;
        ofImage gndImg;
        ofImage underBoxImg;
        ofImage underBox2Img;

        float coord(int val){//ゲーム座標を返す
            return BASE_COORD*val;
        }

        //ポイントカウント
        int pointCnt;
        char pointCntStr[3];
        int pointCnt_type[COIN_NUM];
        //Coinオブジェクト
        CoinManager CoinMamagerInstance;

        //barrier
        barrierManager bM;
        bool bool_bM;//バリアを発動するか
        bool bool_bM_sound;




};
