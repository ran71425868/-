#ifndef PLAYER_H
#define PLAYER_H

//******************************************************************************
//
//
//      player.h
//
//
//******************************************************************************



//�v���C���[�̉摜��`
#define PLAYER_TEX_W                 96.0f
#define PLAYER_TEX_H                 96.0f
#define PLAYER_PIVOT_X               48.0f
#define PLAYER_PIVOT_Y               48.0f




#define GRAVITY                     1.0f

//�v���C���[�̉������̒萔
#define PLAYER_ACCEL_X      0.3f
#define PLAYER_ACCEL_Y      0.3f
#define PLAYER_DECEL_X      0.4f
#define PLAYER_DECEL_Y      0.4f
#define PLAYER_SPEED_X_MAX      6.0f
#define PLAYER_SPEED_Y_MAX      6.0f

//�ǂ̔���
#define WALL_LEFT          SCREEN_W - PLAYER_TEX_W * 0.5f
#define WALL_RIGHT          PLAYER_TEX_W * 0.5f
#define WALL_DOWN          SCREEN_H - PLAYER_TEX_H * 0.5f
#define WALL_UP             PLAYER_TEX_H * 0.5f


//�n�ʂ̍���
#define GROUND_Y                    600.0f

//------< �ϐ� >----------------------------------------------------------------

extern OBJ2D player;

//------< �֐� >----------------------------------------------------------------
void player_init();
void player_deinit();
void player_update();
void player_render();

void player_moveX();
void player_moveY();
void player_radian();

#endif//PLAYER_H