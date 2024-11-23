#include "all.h"

int avalanche_state;

int avalanche_count;
int avalanche_timer;

//OBJ2D型の変数avalancheを宣言
OBJ2D avalanche;

Sprite* sprAvalanche;

//--------------------------------------
//  雪崩の初期設定
//--------------------------------------
void avalanche_init()
{
    //player_stateを0
    avalanche_state = 0;
    avalanche_count = 2;
    avalanche_timer = 0;
}
//--------------------------------------
//  雪崩の終了処理
//--------------------------------------
void avalanche_deinit()
{
    //sprPlayerを破棄
    safe_delete(sprAvalanche);
}

//--------------------------------------
//  プレイヤーの更新処理
//--------------------------------------
void avalanche_update()
{
    switch (avalanche_state)
    {
    case 0:
        //////// 初期設定 ////////

        //プレイヤーの画像を読み込み
        sprAvalanche = sprite_load(L"./Data/Images/nadare_01.png");

        ++avalanche_state;
        /*fallthrough*/

    case 1:
        //////// パラメータの設定 ////////

        //playerのパラメータ設定
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
        //////// 通常時 ////////


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
    //プレイヤーの描画
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