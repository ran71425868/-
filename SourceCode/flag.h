#ifndef FLAG_H
#define FLAG_H

//******************************************************************************
//
//
//      obstacle.h
//
//
//******************************************************************************

#define FLAG_MAX   (8)


//�v���C���[�̉摜��`
#define FLAG_TEX_W                 64.0f
#define FLAG_TEX_H                 64.0f
#define FLAG_PIVOT_X               32.0f
#define FLAG_PIVOT_Y               64.0f

//------< ��� >----------------------------------------------------------------


//------< �֐� >----------------------------------------------------------------
void flag_init();
void flag_deinit();
void flag_update();
void flag_render();

void Flag0(OBJ2D* obj);


#endif