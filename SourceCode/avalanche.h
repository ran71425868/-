#ifndef AVALANCHE_H
#define AVALANCHE_H 
//******************************************************************************
//
//
//      avalanche.h
//
//
//******************************************************************************



//�v���C���[�̉摜��`
#define AVALANCHE_TEX_W                 1280.0f
#define AVALANCHE_TEX_H                 720.0f
#define AVALANCHE_PIVOT_X               640.0f
#define AVALANCHE_PIVOT_Y               360.0f

#define COOL_DOWN_MAX				1	




//------< �ϐ� >----------------------------------------------------------------

extern OBJ2D avalanche;

//------< �֐� >----------------------------------------------------------------
void avalanche_init();
void avalanche_deinit();
void avalanche_update();
void avalanche_render();

#endif//AVALANCHE_H
