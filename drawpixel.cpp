#include "DxLib.h"
#include <math.h>

int Key[256]; // キーが押されているフレーム数を格納する

// キーの入力状態を更新する
int gpUpdateKey(){
	char tmpKey[256]; // 現在のキーの入力状態を格納する
	GetHitKeyStateAll( tmpKey ); // 全てのキーの入力状態を得る
	for( int i=0; i<256; i++ ){ 
		if( tmpKey[i] != 0 ){ // i番のキーコードに対応するキーが押されていたら
			Key[i]++;     // 加算
		} else {              // 押されていなければ
			Key[i] = 0;   // 0にする
		}
	}
	return 0;
}



int x=320, y=240;
float xp=320,yp=240,angle=0;
int Handle;
int bullet;
int flag=0;


void gpCalc(){
	if( Key[ KEY_INPUT_D ] >= 1 ){
		x++;
	}
	if( Key[ KEY_INPUT_S  ] >= 1 ){
		y++;
	}
	if( Key[ KEY_INPUT_A  ] >= 1 ){
		x--;
	}
	if( Key[ KEY_INPUT_W    ] >= 1 ){
		y--;
	}
}

void gpDraw(){
        DrawRotaGraph( x, y, 1.0, 0.0, Handle, TRUE );
		
}

// プログラムは WinMain から始まります
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
						LPSTR lpCmdLine, int nCmdShow )
{


ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //ウィンドウモード変更と初期化と裏画面設定

	Handle=LoadGraph("picture/little spice-and-wolf_185720.jpg") ;
	bullet=LoadGraph( "picture/blackball.jpg"); 
	

	 /*  while( 1 ){					escキーで終了
                ProcessMessage();
                if( CheckHitKey(KEY_INPUT_ESCAPE) == 1 ){
                        break;
                }
        }*/
	    while(ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0&& gpUpdateKey()==0 ){//×で終了
               
				if( CheckHitKey( KEY_INPUT_Z ) == 1 ){//zが押されていたら変数の中身を変更
                        xp = 320;        //初期座標にセット
                        yp = 240;
				flag=1;
                       // angle = GetRand(10000)/10000.f * (PI*2);        //0～PI*2の乱数を生成
                     //   speed = 0.5f + GetRand(10000)/10000.f * 2;      //0.5～2.5の乱数を生成
                }
				if(flag){
				xp += cos( angle )*2 ;      // x座標を更新
                yp += sin( angle )*2;      // y座標を更新
				DrawRotaGraph( xp, yp, 1.0, angle,bullet , TRUE );//弾を描画
				}
				if(xp>600||yp>600){
				flag=0;
				}
	     gpCalc();

                gpDraw();
				 DrawFormatString( 0,0,GetColor(255,255,255), "angle=%.2f xp=%.2f\n", angle,xp);
		}
	//WaitKey() ;				// キー入力待ち

	DxLib_End() ;				// ＤＸライブラリ使用の終了処理
	
	return 0 ;				// ソフトの終了 
}