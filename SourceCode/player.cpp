#include "all.h"

int player_state;
int hp;
float angle = 0.0f;
int scroll_position_X;
int scroll_position_Y;

float boost = 0.0f;

//OBJ2D�^�̕ϐ�player��錾
OBJ2D player;

Sprite* sprPlayer;

//--------------------------------------
//  �v���C���[�̏����ݒ�
//--------------------------------------
void player_init()
{
    //player_state��0
    player_state = 0;
    hp = 100;
}
//--------------------------------------
//  �v���C���[�̏I������
//--------------------------------------
void player_deinit()
{
    //sprPlayer��j��
    safe_delete(sprPlayer);
}

//--------------------------------------
//  �v���C���[�̍X�V����
//--------------------------------------
void player_update()
{
    switch (player_state)
    {
    case 0:
        //////// �����ݒ� ////////

        //�v���C���[�̉摜��ǂݍ���
        sprPlayer = sprite_load(L"./Data/Images/player_01.png");

        ++player_state;
        /*fallthrough*/

    case 1:
        //////// �p�����[�^�̐ݒ� ////////

        //player�̃p�����[�^�ݒ�
        player = {};
        player.timer = 0;
        player.pos = { SCREEN_W * 0.5f,SCREEN_H * 0.5f + 100 };
        player.scale = { 1.0f,1.0f };
        player.texPos = { 0,0 };
        player.texSize = { PLAYER_TEX_W ,PLAYER_TEX_H };
        player.pivot = { PLAYER_PIVOT_X,PLAYER_PIVOT_Y };
        player.color = { 1.0f,1.0f,1.0f,1.0f };
        player.radius = 20.0f;
        player.offset = { 0,0 };



        ++player_state;
        /*fallthrough*/

    case 2:
        //////// �ʏ펞 ////////

        //player_moveX�EY���Ă�
        player_moveY();
        player_moveX();
        player_radian();

        // �ʒu�ɑ��x�𑫂�
        player.pos += player.speed;

        // �v���C���[�̏㉺���E�̃G���A�`�F�b�N
        if (player.pos.x < 0 + WALL_RIGHT) {
            player.pos.x = 0 + WALL_RIGHT;
        }
        if (player.pos.x > WALL_LEFT) {
            player.pos.x = WALL_LEFT;
        }

        /*if (player.pos.y < 0 + WALL_UP) {
            player.pos.y = 0 + WALL_UP;
        }
        if (player.pos.y > WALL_DOWN) {
            player.pos.y = WALL_DOWN;
        }*/

        break;
    }
}

void player_render()
{
    //�v���C���[�̕`��
    sprite_render(sprPlayer, player.pos.x + scroll_position_X, player.pos.y + scroll_position_Y, player.scale.x, player.scale.y, player.texPos.x, player.texPos.y, player.texSize.x, player.texSize.y, player.pivot.x, player.pivot.y,
        ToRadian(angle), player.color.x, player.color.y);
    primitive::rect(player.pos.x-100, player.pos.y-150, 200 * hp / 100, 15, 0, 0, ToRadian(0), 0, 1, 0);
}

void player_moveY()
{
    if (STATE(0) & PAD_DOWN && !(STATE(0) & PAD_UP)) {
        player.speed.y += PLAYER_ACCEL_Y;
        player.scale.y = 1.0f;
        

    }
    else if (STATE(0) & PAD_UP && !(STATE(0) & PAD_DOWN)) {
        player.speed.y -= PLAYER_ACCEL_Y;
        player.scale.y = 1.0f;
        
    }
    else {
        if (player.speed.y > 0) {
            player.speed.y -= PLAYER_DECEL_Y;
            if (player.speed.y < 0)
                player.speed.y = 0.0f;

        }

        if (player.speed.y < 0) {
            player.speed.y += PLAYER_DECEL_Y;
            if (player.speed.y > 0)
                player.speed.y = 0.0f;

        }
    }
    if (player.speed.y >= PLAYER_SPEED_Y_MAX)
        player.speed.y = PLAYER_SPEED_Y_MAX+boost;

    if (player.speed.y <= -PLAYER_SPEED_Y_MAX)
        player.speed.y = -PLAYER_SPEED_Y_MAX-boost;
    if (STATE(0) & PAD_DOWN && !(STATE(0) & PAD_UP)) {
        player.speed.y += PLAYER_ACCEL_Y;
        player.scale.y = 1.0f;


    }
}


void player_moveX()
{

    //�C�ӂ̑���ɂ��ړ�
    if (TRG(0) & PAD_TRG1)
    {
        boost = 5.0f;


    }
    boost = 0.0;
    if (STATE(0) & PAD_LEFT && !(STATE(0) & PAD_RIGHT)) {
        player.speed.x -= PLAYER_ACCEL_X;
        player.scale.x = 1.0f;
        
    }
    else if (STATE(0) & PAD_RIGHT && !(STATE(0) & PAD_LEFT)) {
        player.speed.x += PLAYER_ACCEL_X;
        player.scale.x = 1.0f;
       
    }
    else {
        if (player.speed.x > 0) {
            player.speed.x -= PLAYER_DECEL_X;
            if (player.speed.x < 0) {
                player.speed.x = 0.0f;
            }
        }

        if (player.speed.x < 0) {
            player.speed.x += PLAYER_DECEL_X;
            if (player.speed.x > 0) {
                player.speed.x = 0.0f;
            }
        }

    }
    if (player.speed.x >= PLAYER_SPEED_X_MAX)
        player.speed.x = PLAYER_SPEED_X_MAX+boost;

    if (player.speed.x <= -PLAYER_SPEED_X_MAX)
        player.speed.x = -PLAYER_SPEED_X_MAX-boost;
}
void player_radian() {
    if (STATE(0) & PAD_TRG2 && !(STATE(0) & PAD_TRG3)) {
        angle += 3;
    }
    else if (STATE(0) & PAD_TRG3 && !(STATE(0) & PAD_TRG2)) {
        angle -= 3;
    }

}