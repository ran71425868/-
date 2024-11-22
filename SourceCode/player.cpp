#include "all.h"

int player_state;
int hp;

int scroll_position_X;
int scroll_position_Y;

float player_boost;
int boost_timer;
int boost_timer_max;

int cooldown;
int cooldown_timer;

extern float scrollValue;
extern OBJ2D enemy[ENEMY_MAX];

//OBJ2D型の変数playerを宣言
OBJ2D player;

Sprite* sprPlayer;

//--------------------------------------
//  プレイヤーの初期設定
//--------------------------------------
void player_init()
{
    //player_stateを0
    player_state = 0;
    hp = 100;
    player_boost = 0.0f;
    boost_timer = 0;
    boost_timer_max = 100;
    cooldown = 3;
    cooldown_timer=0;
}
//--------------------------------------
//  プレイヤーの終了処理
//--------------------------------------
void player_deinit()
{
    //sprPlayerを破棄
    safe_delete(sprPlayer);
}

//--------------------------------------
//  プレイヤーの更新処理
//--------------------------------------
void player_update()
{
    switch (player_state)
    {
    case 0:
        //////// 初期設定 ////////

        //プレイヤーの画像を読み込み
        sprPlayer = sprite_load(L"./Data/Images/player_02.png");

        ++player_state;
        /*fallthrough*/

    case 1:
        //////// パラメータの設定 ////////

        //playerのパラメータ設定
        player = {};
        player.timer = 0;
        player.pos = { SCREEN_W * 0.5f,SCREEN_H * 0.5f };
        player.scale = { 0.5f,0.5f };
        player.texPos = { 0,0 };
        player.texSize = { PLAYER_TEX_W ,PLAYER_TEX_H };
        player.pivot = { PLAYER_PIVOT_X,PLAYER_PIVOT_Y };
        player.color = { 1.0f,1.0f,1.0f,1.0f };
        player.radius = 20.0f;
        player.offset = { 0,0 };



        ++player_state;
        /*fallthrough*/

    case 2:
        //////// 通常時 ////////

        //player_moveX・Yを呼ぶ
        player_moveY();
        player_moveX();

        // 位置に速度を足す
        player.pos += player.speed;

        // プレイヤーの上下左右のエリアチェック
        if (player.pos.x < 0 + WALL_RIGHT) {
            player.pos.x = 0 + WALL_RIGHT;
        }
        if (player.pos.x > WALL_LEFT) {
            player.pos.x = WALL_LEFT;
        }

        if (boost_timer>=boost_timer_max)
        {
           if(cooldown_timer%100==0){

                if (cooldown > 0)
                {
                    cooldown--;
                }

            }
           else if (cooldown <= 0) {

               boost_timer = 0;
               cooldown = 3;

           }
        }
        
        cooldown_timer++;
        
        break;
    }
}

void player_render()
{
    //プレイヤーの描画
    sprite_render(sprPlayer, player.pos.x + scroll_position_X, player.pos.y + scroll_position_Y, player.scale.x, player.scale.y, player.texPos.x, player.texPos.y, player.texSize.x, player.texSize.y, player.pivot.x, player.pivot.y,
        ToRadian(0), player.color.x, player.color.y);
    primitive::rect(player.pos.x-100, player.pos.y-150, 200 * hp / 100, 15, 0, 0, ToRadian(0), 0, 1, 0);
    
    text_out(0, "boost", 0, 500, 2, 2);
    text_out(0, std::to_string(boost_timer), 0, 550, 2, 2);
    text_out(0, "cooldown", 0, 600, 2, 2);
    text_out(0, std::to_string(cooldown), 0, 650, 2, 2);

}

void player_moveY()
{
    
    if (STATE(0) & PAD_DOWN && !(STATE(0) & PAD_UP)) 
    {
        player.speed.y += PLAYER_ACCEL_Y;
        player.scale.y = 0.5f;
        if (player.pos.y > SCREEN_H / 3.0f)
        {
            scrollValue -= player.speed.y;
            player.pos -= player.speed*0.85;
        }

    }
    else if (STATE(0) & PAD_UP && !(STATE(0) & PAD_DOWN)) 
    {
        player.speed.y -= PLAYER_ACCEL_Y;
        player.scale.y = 0.5f;
        if (player.pos.y < SCREEN_H / 1.5f) {
            //scrollValue -= player.speed.y;
            //player.pos -= player.speed/2;
        }
        
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
    if (player.speed.y >= PLAYER_SPEED_Y_MAX) {
        player.speed.y = PLAYER_SPEED_Y_MAX+player_boost; 
        if (boost_timer < boost_timer_max && STATE(0) & PAD_TRG1 && STATE(0) & PAD_DOWN && !(STATE(0) & PAD_UP) && cooldown == 3) {
            boost_timer++;
            player_boost = 5.0f;
            player.speed.y = PLAYER_SPEED_Y_MAX + player_boost;
        }

    }
    player_boost = 0.0f;

    if (player.speed.y <= -PLAYER_SPEED_Y_MAX) {
        player.speed.y = -PLAYER_SPEED_Y_MAX-player_boost;
        if (boost_timer < boost_timer_max && STATE(0) & PAD_TRG1 && STATE(0) & PAD_UP && !(STATE(0) & PAD_DOWN) && cooldown == 3) {
            boost_timer++;
            player_boost = 5.0f;
            player.speed.y = -PLAYER_SPEED_Y_MAX - player_boost;
        }

    }
    

    
}



void player_moveX()
{

    //任意の操作による移動
    if (STATE(0) & PAD_LEFT && !(STATE(0) & PAD_RIGHT)) {
        player.speed.x -= PLAYER_ACCEL_X;
        player.scale.x = 0.5f;
        
    }
    else if (STATE(0) & PAD_RIGHT && !(STATE(0) & PAD_LEFT)) {
        player.speed.x += PLAYER_ACCEL_X;
        player.scale.x = 0.5f;
       
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
    if (player.speed.x >= PLAYER_SPEED_X_MAX) {
        player.speed.x = PLAYER_SPEED_X_MAX;
        
        if (boost_timer < boost_timer_max && STATE(0) & PAD_TRG1&&STATE(0) & PAD_RIGHT && !(STATE(0) & PAD_LEFT)&&cooldown==3) {

            boost_timer++;
            player_boost = 5.0f;
            player.speed.x = PLAYER_SPEED_X_MAX + player_boost;
        }
        player_boost = 0.0f;
           
    }
            

    if (player.speed.x <= -PLAYER_SPEED_X_MAX) {
        player.speed.x = -PLAYER_SPEED_X_MAX;

        if (boost_timer < boost_timer_max&&STATE(0) & PAD_TRG1&& STATE(0) & PAD_LEFT && !(STATE(0) & PAD_RIGHT)&&cooldown==3) {
            boost_timer++;
            player_boost = 5.0f;
            player.speed.x = -PLAYER_SPEED_X_MAX - player_boost;
        }
        player_boost = 0.0f;
    }
}

void player_hp()
{
  /*  for (int i = 0; i < 3; i++) {
        if (enemy[i].moveAlg == -1) {
            hp -= 5;
        }
    }
    
    for (int i = 3; i < 6; i++) {
        if (enemy[i].moveAlg == -1) {
            hp -= 10;
        }
    }

    for (int i = 6; i < 8; i++) {
        if (enemy[i].moveAlg == -1) {
            hp -= 30;
        }
    }*/
}