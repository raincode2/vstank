#include "DxLib.h"
#include <math.h>

int Key[256]; // �L�[��������Ă���t���[�������i�[����

// �L�[�̓��͏�Ԃ��X�V����
int gpUpdateKey(){
	char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll( tmpKey ); // �S�ẴL�[�̓��͏�Ԃ𓾂�
	for( int i=0; i<256; i++ ){ 
		if( tmpKey[i] != 0 ){ // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			Key[i]++;     // ���Z
		} else {              // ������Ă��Ȃ����
			Key[i] = 0;   // 0�ɂ���
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

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
						LPSTR lpCmdLine, int nCmdShow )
{


ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

	Handle=LoadGraph("picture/little spice-and-wolf_185720.jpg") ;
	bullet=LoadGraph( "picture/blackball.jpg"); 
	

	 /*  while( 1 ){					esc�L�[�ŏI��
                ProcessMessage();
                if( CheckHitKey(KEY_INPUT_ESCAPE) == 1 ){
                        break;
                }
        }*/
	    while(ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0&& gpUpdateKey()==0 ){//�~�ŏI��
               
				if( CheckHitKey( KEY_INPUT_Z ) == 1 ){//z��������Ă�����ϐ��̒��g��ύX
                        xp = 320;        //�������W�ɃZ�b�g
                        yp = 240;
				flag=1;
                       // angle = GetRand(10000)/10000.f * (PI*2);        //0�`PI*2�̗����𐶐�
                     //   speed = 0.5f + GetRand(10000)/10000.f * 2;      //0.5�`2.5�̗����𐶐�
                }
				if(flag){
				xp += cos( angle )*2 ;      // x���W���X�V
                yp += sin( angle )*2;      // y���W���X�V
				DrawRotaGraph( xp, yp, 1.0, angle,bullet , TRUE );//�e��`��
				}
				if(xp>600||yp>600){
				flag=0;
				}
	     gpCalc();

                gpDraw();
				 DrawFormatString( 0,0,GetColor(255,255,255), "angle=%.2f xp=%.2f\n", angle,xp);
		}
	//WaitKey() ;				// �L�[���͑҂�

	DxLib_End() ;				// �c�w���C�u�����g�p�̏I������
	
	return 0 ;				// �\�t�g�̏I�� 
}