#include "all.h"

int avalanche_state;

int avalanche_count;
int avalanche_timer;

//OBJ2D�^�̕ϐ�avalanche��錾
OBJ2D avalanche;

Sprite* sprAvalanche;

//--------------------------------------
//  ����̏����ݒ�
//--------------------------------------
void avalanche_init()
{
    //player_state��0
    avalanche_state = 0;
    avalanche_count = 2;
    avalanche_timer = 0;
}
//--------------------------------------
//  ����̏I������
//--------------------------------------
void avalanche_deinit()
{
    //sprPlayer��j��
    safe_delete(sprAvalanche);
}

//--------------------------------------
//  �v���C���[�̍X�V����
//--------------------------------------
void avalanche_update()
{
    switch (avalanche_state)
    {
    case 0:
        //////// �����ݒ� ////////

        //�v���C���[�̉摜��ǂݍ���
        sprAvalanche = sprite_load(L"./Data/Images/nadare_01.png");

        ++avalanche_state;
        /*fallthrough*/

    case 1:
        //////// �p�����[�^�̐ݒ� ////////

        //player�̃p�����[�^�ݒ�
        avalanche = {};
        avalanche.timer = 0;
        avalanche.pos = { SCREEN_W/2.0f,250.0f };
        avalanche.scale = { 1.0f,1.0f };
        avalanche.texPos = { 0,0 };
        avalanche.texSize = { AVALANCHE_TEX_W ,AVALANCHE_TEX_H };
        avalanche.pivot = { AVALANCHE_PIVOT_X,AVALANCHE_PIVOT_Y };
        avalanche.color = { 1.0f,1.0f,1.0f,1.0f };
        avalanche.radius = 80.0f;
        avalanche.offset = { 0,0 };



        ++avalanche_state;
        /*fallthrough*/

    case 2:
        //////// �ʏ펞 ////////


            if (avalanche_timer % 100 == 0) {

                if (avalanche_count >= 0)
                {
                    avalanche_count--;
                }

            }
            else if (avalanche_count <= 0) {

                avalanche_count = 2;

            }

        avalanche_timer++;

        break;
    }
}

void avalanche_render()
{
    //�v���C���[�̕`��
    sprite_render(sprAvalanche,
        avalanche.pos.x, avalanche.pos.y, 
        avalanche.scale.x, avalanche.scale.y, 
        avalanche.texPos.x, avalanche.texPos.y, 
        avalanche.texSize.x, avalanche.texSize.y, 
        avalanche.pivot.x, avalanche.pivot.y,
        ToRadian(0), avalanche.color.x, avalanche.color.y);
   
    /*text_out(0, "cooldown", 0, 600, 2, 2);
    text_out(0, std::to_string(cooldown), 0, 650, 2, 2);*/

}