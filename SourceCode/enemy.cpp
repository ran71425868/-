#include "all.h"
#include	<stdlib.h>
#include	<time.h>

int rndX, rndY;
int enemy_state;
float speed[8] = { 1,1.25,1.5,2,2.5,3,5,7 };

extern float angle;
extern int kill;


struct ENEMY_DATA {
    Sprite* spr;
    const wchar_t* filePath;
    VECTOR2          texPos;
    VECTOR2          texSize;
    VECTOR2          pivot;
    float            radius;
}
enemyData[] = {
       {NULL,   L"./Data/Images/monster.png", { 0,0 }, { 160, 160 }, { 80, 80 }, {20}},
       {NULL,   L"./Data/Images/Green_monster.png", { 0,0 }, { 160, 160 }, { 80, 80 }, {20}},
       {NULL,   L"./Data/Images/Red_monster.png", { 0,0 }, { 160, 160 }, { 80, 80 }, {20}},
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

      /*  enemy_moveX();
        enemy_moveY();*/


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
        sprite_render(enemy[i].spr, enemy[i].pos.x, enemy[i].pos.y, enemy[i].scale.x, enemy[i].scale.y, enemy[i].texPos.x, enemy[i].texPos.y, enemy[i].texSize.x, enemy[i].texSize.y, enemy[i].pivot.x, enemy[i].pivot.y, ToRadian(0), enemy[i].color.x, enemy[i].color.y, enemy[i].color.z, enemy[i].color.w);

    }
}
void enemy_moveX() {


    for (int i = 0; i < ENEMY_MAX; i++) {

        if (enemy[i].type == 0)
        {
           /* if (player.pos.x - enemy[i].pos.x < 30) {
                enemy[i].pos.x = player.pos.x;
            }*/
            if (enemy[i].pos.x > SCREEN_W / 2) {
                if (kill > 100)
                    enemy[i].pos.x -= speed[7];
                else if (kill > 80)
                    enemy[i].pos.x -= speed[6];
                else if (kill > 60)
                    enemy[i].pos.x -= speed[5];
                else if (kill > 40)
                    enemy[i].pos.x -= speed[4];
                else if (kill > 30)
                    enemy[i].pos.x -= speed[3];
                else if (kill > 20)
                    enemy[i].pos.x -= speed[2];
                else if (kill > 10)
                    enemy[i].pos.x -= speed[1];
                else
                    enemy[i].pos.x -= speed[0];

            }
            else if (enemy[i].pos.x <= SCREEN_W / 2) {
                if (kill > 100)
                    enemy[i].pos.x += speed[7];
                else if (kill > 80)
                    enemy[i].pos.x += speed[6];
                else if (kill > 60)
                    enemy[i].pos.x += speed[5];
                else if (kill > 40)
                    enemy[i].pos.x += speed[4];
                else if (kill > 30)
                    enemy[i].pos.x += speed[3];
                else if (kill > 20)
                    enemy[i].pos.x += speed[2];
                else if (kill > 10)
                    enemy[i].pos.x += speed[1];
                else
                    enemy[i].pos.x += speed[0];
            }


        }

    }
}
void enemy_moveY() {
    for (int i = 0; i < ENEMY_MAX; i++) {

        if (enemy[i].type == 0)
        {
           /* if (player.pos.y - enemy[i].pos.y < 30) {
                enemy[i].pos.y = player.pos.y;
            }*/
            if (enemy[i].pos.y < SCREEN_H / 2) {
                if (kill > 100)
                    enemy[i].pos.y += speed[7];
                else if (kill > 80)
                    enemy[i].pos.y += speed[6];
                else if (kill > 60)
                    enemy[i].pos.y += speed[5];
                else if (kill > 40)
                    enemy[i].pos.y += speed[4];
                else if (kill > 30)
                    enemy[i].pos.y += speed[3];
                else if (kill > 20)
                    enemy[i].pos.y += speed[2];
                else if (kill > 10)
                    enemy[i].pos.y += speed[1];
                else
                    enemy[i].pos.y += speed[0];
            }
            else if (enemy[i].pos.y >= SCREEN_H / 2) {
                if (kill > 100)
                    enemy[i].pos.y -= speed[7];
                else if (kill > 80)
                    enemy[i].pos.y -= speed[6];
                else if (kill > 60)
                    enemy[i].pos.y -= speed[5];
                else if (kill > 40)
                    enemy[i].pos.y -= speed[4];
                else if (kill > 30)
                    enemy[i].pos.y -= speed[3];
                else if (kill > 20)
                    enemy[i].pos.y -= speed[2];
                else if (kill > 10)
                    enemy[i].pos.y -= speed[1];
                else
                    enemy[i].pos.y -= speed[0];
            }
        }

    }
}

void moveEnemy0(OBJ2D* obj)
{

    switch (obj->state) {
    case 0:

        obj->scale = { 1.0f, 1.0f };
        obj->color = { 1, 1, 1, 1 };
        obj->spr = enemyData[0].spr;
        obj->texPos = enemyData[0].texPos;
        obj->texSize = enemyData[0].texSize;
        obj->pivot = enemyData[0].pivot;
        obj->radius = enemyData[0].radius;
        obj->speed = enemy[3].speed;

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
        obj->pos += obj->speed;

        break;
    }
}
void moveEnemy1(OBJ2D* obj)
{

    switch (obj->state) {
    case 0:

        obj->scale = { 1.0f, 1.0f };
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
        break;
    }
}
void moveEnemy2(OBJ2D* obj)
{

    switch (obj->state) {
    case 0:

        obj->scale = { 1.0f, 1.0f };
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
        break;
    }
}