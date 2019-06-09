#pragma once

#include "ofMain.h"
#include "Coin.h"
#include "startobj.h"

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
        //---------------------------------------------
//        //カウントダウン
//        bool next_Countdown;
//        int minute_Countdown;
//        int second_Countdown;
        //--------------------------------------------
        //終了
        bool endtimerenable;
        int minute_end;
        int second_end;
        //---------------------------------------------
        //ゲーム内変数
        int BASE_COORD;//公倍数[1, 2, 4, 5, 8, 10, 16, 20, 32, 40, 80, 160]
        int player_x;
        int player_y;
        bool bool_keyReleased;
        ofImage playerImg;
        ofImage gndImg;
        ofImage underBoxImg;
        ofImage underBox2Img;

        float coord(int val){//ゲーム座標を返す
            return BASE_COORD*val;
        }

        int pointCnt;
        char pointCntStr[3];
        int point_gold;
        int point_silver;
        //---------------------------------------------
        //---------------------------------------------
        //Coinオブジェクト
        ofSoundPlayer pointSound;
        Coin coin_gold,coin_silver;
        std::string coins[1];
//        coins[0]="coin_gold";
//        coins[1]="coin_silver";

        //---------------------------------------------





};
