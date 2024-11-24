#ifndef OBSTACLE_H
#define OBSTACLE_H

//******************************************************************************
//
//
//      obstacle.h
//
//
//******************************************************************************

#define OBSTACLE_MAX   (8)


//プレイヤーの画像定義
#define OBSTACLE_TEX_W                 64.0f
#define OBSTACLE_TEX_H                 64.0f
#define OBSTACLE_PIVOT_X               32.0f
#define OBSTACLE_PIVOT_Y               64.0f

//------< 状態 >----------------------------------------------------------------


//------< 関数 >----------------------------------------------------------------
void obstacle_init();
void obstacle_deinit();
void obstacle_update();
void obstacle_render();

void Obstacle0(OBJ2D* obj);
void Obstacle1(OBJ2D* obj);

#endif