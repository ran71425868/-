#ifndef GOAL_H
#define GOAL_H

//******************************************************************************
//
//
//      goal.h
//
//
//******************************************************************************



//プレイヤーの画像定義
#define GOAL_TEX_W                 1280.0f
#define GOAL_TEX_H                 720.0f
#define GOAL_PIVOT_X               640.0f
#define GOAL_PIVOT_Y               360.0f
//------< 変数 >----------------------------------------------------------------

extern OBJ2D goal;

//------< 関数 >----------------------------------------------------------------
void goal_init();
void goal_deinit();
void goal_update();
void goal_render();

void goal_moveY();

#endif//GOAL_H