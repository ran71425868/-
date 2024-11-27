#include "all.h"

int avalanche_state;

int avalanche_count;
int avalanche_timer;

int avalanche_flag;

//OBJ2D型の変数avalancheを宣言
OBJ2D avalanche;

Sprite* sprAvalanche1;
Sprite* sprAvalanche2;

//--------------------------------------
//  雪崩の初期設定
//--------------------------------------
void avalanche_init()
{
    //player_stateを0
    avalanche_state = 0;
    avalanche_count = 2;
    avalanche_timer = 0;
    avalanche_flag = 1;
}
//--------------------------------------
//  雪崩の終了処理
//--------------------------------------
void avalanche_deinit()
{
    //sprAvalancheを破棄
    safe_delete(sprAvalanche1);
    safe_delete(sprAvalanche2);
}

//--------------------------------------
//  雪崩の更新処理
//--------------------------------------
void avalanche_update()
{
    switch (avalanche_state)
    {
    case 0:
        //////// 初期設定 ////////

        //プレイヤーの画像を読み込み
        sprAvalanche1 = sprite_load(L"./Data/Images/nadare_a.png");
        sprAvalanche2 = sprite_load(L"./Data/Images/nadare_b.png");
        

        ++avalanche_state;
        /*fallthrough*/

    case 1:
        //////// パラメータの設定 ////////

        //avalancheのパラメータ設定
        avalanche = {};
        avalanche.timer = 0;
        avalanche.pos = { SCREEN_W/2.0f,-50.0f };
        avalanche.scale = { 1.5f,1.5f };
        avalanche.texPos = { 0,0 };
        avalanche.texSize = { AVALANCHE_TEX_W ,AVALANCHE_TEX_H };
        avalanche.pivot = { AVALANCHE_PIVOT_X,AVALANCHE_PIVOT_Y };
        avalanche.color = { 1.0f,1.0f,1.0f,1.0f };
        avalanche.radius = 20.0f;
        avalanche.offset = { 0,0 };



        ++avalanche_state;
        /*fallthrough*/

    case 2:
        //////// 通常時 ////////

        avalanche_timer++;

        break;
    }
}

void avalanche_render()
{
    //雪崩の描画
    /*if (avalanche_flag == 0) {
        sprite_render(sprAvalanche1,
            avalanche.pos.x, avalanche.pos.y,
            avalanche.scale.x, avalanche.scale.y,
            avalanche.texPos.x, avalanche.texPos.y,
            avalanche.texSize.x, avalanche.texSize.y,
            avalanche.pivot.x, avalanche.pivot.y,
            ToRadian(0), avalanche.color.x, avalanche.color.y);
    }
    else if (avalanche_flag == 1) {
        sprite_render(sprAvalanche2,
            avalanche.pos.x, avalanche.pos.y,
            avalanche.scale.x, avalanche.scale.y,
            avalanche.texPos.x, avalanche.texPos.y,
            avalanche.texSize.x, avalanche.texSize.y,
            avalanche.pivot.x, avalanche.pivot.y,
            ToRadian(0), avalanche.color.x, avalanche.color.y);
    }*/

    while (1) {
        if (avalanche_timer % 100 == 0)
        {
            avalanche_count--;
            if (avalanche_count >= 0) {
                avalanche_flag = 1;
            }
            else if (avalanche_count <= 0) {
                avalanche_flag = 0;
                avalanche_count = 1;
            }
        }

        break;
    }
    
}