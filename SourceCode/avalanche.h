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
#define AVALANCHE_TEX_W                 1920.0f
#define AVALANCHE_TEX_H                 1080.0f
#define AVALANCHE_PIVOT_X               960.0f
#define AVALANCHE_PIVOT_Y               540.0f

#define COOL_DOWN_MAX				3	




//------< �ϐ� >----------------------------------------------------------------

extern OBJ2D avalanche;

//------< �֐� >----------------------------------------------------------------
void avalanche_init();
void avalanche_deinit();
void avalanche_update();
void avalanche_render();

#endif//AVALANCHE_H
