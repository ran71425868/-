#ifndef GOAL_H
#define GOAL_H

//******************************************************************************
//
//
//      goal.h
//
//
//******************************************************************************



//�v���C���[�̉摜��`
#define GOAL_TEX_W                 1280.0f
#define GOAL_TEX_H                 720.0f
#define GOAL_PIVOT_X               640.0f
#define GOAL_PIVOT_Y               360.0f
//------< �ϐ� >----------------------------------------------------------------

extern OBJ2D goal;

//------< �֐� >----------------------------------------------------------------
void goal_init();
void goal_deinit();
void goal_update();
void goal_render();

void goal_moveY();

#endif//GOAL_H