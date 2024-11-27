#include "all.h"

int avalanche_state;

int avalanche_count;
int avalanche_timer;

//OBJ2D�^�̕ϐ�avalanche��錾
OBJ2D avalanche;

Sprite* sprAvalanche1;
Sprite* sprAvalanche2;

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
    //sprAvalanche��j��
    safe_delete(sprAvalanche1);
    safe_delete(sprAvalanche2);
}

//--------------------------------------
//  ����̍X�V����
//--------------------------------------
void avalanche_update()
{
    switch (avalanche_state)
    {
    case 0:
        //////// �����ݒ� ////////

        //�v���C���[�̉摜��ǂݍ���
        sprAvalanche1 = sprite_load(L"./Data/Images/nadare_a.png");
        sprAvalanche2 = sprite_load(L"./Data/Images/nadare_b.png");
        

        ++avalanche_state;
        /*fallthrough*/

    case 1:
        //////// �p�����[�^�̐ݒ� ////////

        //avalanche�̃p�����[�^�ݒ�
        avalanche = {};
        avalanche.timer = 0;
        avalanche.pos = { SCREEN_W/2.0f,-0.0f };
        avalanche.scale = { 2.0f,1.1f };
        avalanche.texPos = { 0,0 };
        avalanche.texSize = { AVALANCHE_TEX_W ,AVALANCHE_TEX_H };
        avalanche.pivot = { AVALANCHE_PIVOT_X,AVALANCHE_PIVOT_Y };
        avalanche.color = { 1.0f,1.0f,1.0f,1.0f };
        avalanche.radius = 500.0f;
        avalanche.offset = { 0,0 };



        ++avalanche_state;
        /*fallthrough*/

    case 2:
        //////// �ʏ펞 ////////

        


            

        avalanche_timer++;

        break;
    }
}

void avalanche_render()
{
    sprite_render(sprAvalanche1,
        avalanche.pos.x, avalanche.pos.y,
        avalanche.scale.x, avalanche.scale.y,
        avalanche.texPos.x, avalanche.texPos.y,
        avalanche.texSize.x, avalanche.texSize.y,
        avalanche.pivot.x, avalanche.pivot.y,
        ToRadian(0), avalanche.color.x, avalanche.color.y);

    //while (1)
    //{
    //    
    //    if (avalanche_timer % 100 == 0) {

    //        if (avalanche_count >= 0)
    //        {
    //            //����̕`��
    //            sprite_render(sprAvalanche2,
    //                avalanche.pos.x, avalanche.pos.y,
    //                avalanche.scale.x, avalanche.scale.y,
    //                avalanche.texPos.x, avalanche.texPos.y,
    //                avalanche.texSize.x, avalanche.texSize.y,
    //                avalanche.pivot.x, avalanche.pivot.y,
    //                ToRadian(0), avalanche.color.x, avalanche.color.y);

    //            avalanche_count--;
    //        }

    //    }
    //    else if (avalanche_count <= 0) {

    //       

    //        sprite_render(sprAvalanche1,
    //            avalanche.pos.x, avalanche.pos.y,
    //            avalanche.scale.x, avalanche.scale.y,
    //            avalanche.texPos.x, avalanche.texPos.y,
    //            avalanche.texSize.x, avalanche.texSize.y,
    //            avalanche.pivot.x, avalanche.pivot.y,
    //            ToRadian(0), avalanche.color.x, avalanche.color.y);
    //        avalanche_count = 2;

    //    }

    //    break;
    //}
    
    text_out(0, "cooldown", 0, 800, 2, 2);
    text_out(0, std::to_string(avalanche_count), 0, 850, 2, 2);
    
}