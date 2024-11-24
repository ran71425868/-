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
#define AVALANCHE_TEX_W                 1920.0f
#define AVALANCHE_TEX_H                 1080.0f
#define AVALANCHE_PIVOT_X               960.0f
#define AVALANCHE_PIVOT_Y               540.0f

#define COOL_DOWN_MAX				3	




//------< 変数 >----------------------------------------------------------------

extern OBJ2D avalanche;

//------< 関数 >----------------------------------------------------------------
void avalanche_init();
void avalanche_deinit();
void avalanche_update();
void avalanche_render();

#endif//AVALANCHE_H
