#ifndef AVALANCHE_H
#define AVALANCHE_H 
//******************************************************************************
//
//
//      avalanche.h
//
//
//******************************************************************************



//プレイヤーの画像定義
#define AVALANCHE_TEX_W                 1280.0f
#define AVALANCHE_TEX_H                 720.0f
#define AVALANCHE_PIVOT_X               640.0f
#define AVALANCHE_PIVOT_Y               360.0f

#define COOL_DOWN_MAX				1	




//------< 変数 >----------------------------------------------------------------

extern OBJ2D avalanche;

//------< 関数 >----------------------------------------------------------------
void avalanche_init();
void avalanche_deinit();
void avalanche_update();
void avalanche_render();

#endif//AVALANCHE_H
