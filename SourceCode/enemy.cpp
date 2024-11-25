#include "all.h"
#include	<stdlib.h>
#include	<time.h>

int rndX, rndY;
int enemy_state;

extern float angle;
extern int kill;

int enemy_scroll_position_X;
int enemy_scroll_position_Y;

extern float scrollValue;


struct ENEMY_DATA {
    Sprite* spr;
    const wchar_t* filePath;
    VECTOR2          texPos;
    VECTOR2          texSize;
    VECTOR2          pivot;
    float            radius;
}
enemyData[] = {
       {NULL,   L"./Data/Images/rabit_01.png", { 0,0 }, { 70, 70 }, { 35, 35 }, {20}},
       {NULL,   L"./Data/Images/wolf_01.png", { 0,0 }, { 130, 80 }, { 65, 40 }, {10}},
       {NULL,   L"./Data/Images/bear_01.png", { 0,0 }, { 80, 75 }, { 40, 37.5 }, {10}},
};
OBJ2D enemy[ENEMY_MAX];

struct ENEMY_SET {
    int enemyType;
    VECTOR2 pos;
    int moveType;
}
enemySet[] = {
    {0,{  300, 0}, 0},
    {0,{  500, 0}, 0},
    {0,{  100, 0}, 0},
    {1,{  200, 0}, 0},
    {1,{  1000,720 },0},
    {1,{  700, 720}, 0},
    {2,{  800, 720}, 0},
    {2,{  400, 720}, 0},
    {-1,{  -1, -1 }, -1},
};
//--------------------------------------
//  エネミーの初期設定
//--------------------------------------
void enemy_init()
{
    //enemy_stateを0
    enemy_state = 0;

    srand((unsigned)time(NULL));
    for (int i = 0; enemySet[i].enemyType >= 0; i++) {
        rndX = rand() % 1281;
        enemySet[i].pos.x = rndX;
    }

    for (int i = 0; enemySet[i].enemyType >= 0; i++) {
        rndY = rand() % 2;
        if (rndY == 1) {
            rndY = rndY * 720;
        }
        enemySet[i].pos.y = rndY;
    }
}

//--------------------------------------
//  エネミーの終了処理
//--------------------------------------
void enemy_deinit()
{
    //Enemyを破棄
    int dataNum = ARRAYSIZE(enemyData);
    for (int i = 0; i < dataNum; i++) {
        safe_delete(enemyData[i].spr);
    }
}

//--------------------------------------
//  エネミーの更新処理
//--------------------------------------
void enemy_update()
{
    switch (enemy_state)
    {
    case 0:
    {

        //////// 初期設定 ////////

        //エネミーの画像を読み込み
        int dataNum = sizeof(enemyData) / sizeof(ENEMY_DATA);
        for (int i = 0; i < dataNum; i++) {
            enemyData[i].spr = sprite_load(enemyData[i].filePath);
        }
        ++enemy_state;
        /*fallthrough*/
    }

    case 1:
        //////// パラメータの設定 ////////

        for (int i = 0; i < ENEMY_MAX; i++) {
            enemy[i] = {};
            enemy[i].moveAlg = -1;
        }

        ++enemy_state;
        /*fallthrough*/

    case 2:
        //討伐後もう一度呼び出す
        for (int i = 0; enemySet[i].enemyType >= 0; i++) {
            OBJ2D* p = searchSet0(enemy, ENEMY_MAX, enemySet[i].enemyType, enemySet[i].pos);

            enemy[i].type = enemySet[i].moveType;

            if (!p) break;
        }

        for (int i = 0; enemySet[i].enemyType >= 0; i++) {
            rndX = rand() % 1921;
            enemySet[i].pos.x = rndX;
        }

        for (int i = 0; enemySet[i].enemyType >= 0; i++) {
            rndY = rand() % 2;
            if (rndY == 1) {
                rndY = rndY * 720;
            }
            enemySet[i].pos.y = rndY;
        }


        for (int i = 0; i < ENEMY_MAX; i++) {
            if (enemy[i].moveAlg == -1)continue;

            switch (enemy[i].moveAlg) {
            case 0:
                moveEnemy0(&enemy[i]);
                break;
            case 1:
                moveEnemy1(&enemy[i]);
                break;
            case 2:
                moveEnemy2(&enemy[i]);
                break;
            }
            ++enemy[i].timer;
        }

        break;
    }
}

void enemy_render()
{

    for (int i = 0; i < ENEMY_MAX; ++i)
    {
        if (enemy[i].moveAlg == -1)continue;

        // エネミーの描画
        sprite_render(enemy[i].spr, enemy[i].pos.x+ enemy_scroll_position_X, enemy[i].pos.y+enemy_scroll_position_Y, enemy[i].scale.x, enemy[i].scale.y, enemy[i].texPos.x, enemy[i].texPos.y, enemy[i].texSize.x, enemy[i].texSize.y, enemy[i].pivot.x, enemy[i].pivot.y, ToRadian(0), enemy[i].color.x, enemy[i].color.y, enemy[i].color.z, enemy[i].color.w);

    }
}


void moveEnemy0(OBJ2D* obj)
{

    switch (obj->state) {
    case 0:

        obj->scale = { 1.2f, 1.2f };
        obj->color = { 1, 1, 1, 1 };
        obj->spr = enemyData[0].spr;
        obj->texPos = enemyData[0].texPos;
        obj->texSize = enemyData[0].texSize;
        obj->pivot = enemyData[0].pivot;
        obj->radius = enemyData[0].radius;
        

        ++obj->state;
        /*fallthrough*/

    case 1:
        ////////通常時////////

        {
            VECTOR2 pos = player.pos + player.offset;

            float dx = pos.x - obj->pos.x;

            float dy = pos.y - obj->pos.y;

            float dist = sqrtf(dx * dx + dy * dy);

            obj->speed = { dx / dist * 1, dy / dist * 1 };
        }
        obj->pos += obj->speed*4;
        obj->pos -= obj->speed*4*0.85;

        
        break;
    }
}
void moveEnemy1(OBJ2D* obj)
{

    switch (obj->state) {
    case 0:

        obj->scale = { 1.2f, 1.2f };
        obj->color = { 1, 1, 1, 1 };
        obj->spr = enemyData[1].spr;
        obj->texPos = enemyData[1].texPos;
        obj->texSize = enemyData[1].texSize;
        obj->pivot = enemyData[1].pivot;
        obj->radius = enemyData[1].radius;

        ++obj->state;
        /*fallthrough*/

    case 1:
        ////////通常時////////
    {
        VECTOR2 pos = player.pos + player.offset;

        float dx = pos.x - obj->pos.x;

        float dy = pos.y - obj->pos.y;

        float dist = sqrtf(dx * dx + dy * dy);

        obj->speed = { dx / dist * 1, dy / dist * 1 };
    }
    obj->pos += obj->speed * 5;
    obj->pos -= obj->speed*5*0.85;
   
        break;
    }
}
void moveEnemy2(OBJ2D* obj)
{

    switch (obj->state) {
    case 0:

        obj->scale = { 1.3f, 1.3f };
        obj->color = { 1, 1, 1, 1 };
        obj->spr = enemyData[2].spr;
        obj->texPos = enemyData[2].texPos;
        obj->texSize = enemyData[2].texSize;
        obj->pivot = enemyData[2].pivot;
        obj->radius = enemyData[2].radius;

        ++obj->state;
        /*fallthrough*/

    case 1:
        ////////通常時////////
    {
        VECTOR2 pos = player.pos + player.offset;

        float dx = pos.x - obj->pos.x;

        float dy = pos.y - obj->pos.y;

        float dist = sqrtf(dx * dx + dy * dy);

        obj->speed = { dx / dist * 1, dy / dist * 1 };
    }
    obj->pos += obj->speed * 2;
    obj->pos -= obj->speed*2*0.85;
        break;
    }
}