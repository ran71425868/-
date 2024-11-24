#include "all.h"
#include	<stdlib.h>
#include	<time.h>

int rndx;
int obstacle_state;

extern float angle;

struct OBSTACLE_DATA {
    Sprite* spr;
    const wchar_t* filePath;
    VECTOR2          texPos;
    VECTOR2          texSize;
    VECTOR2          pivot;
    float            radius;
}
obstacleData[] = {
       {NULL,   L"./Data/Images/stone_01.png", { 0,0 }, { 200, 200 }, { 100, 100 }, {20}},
       {NULL,   L"./Data/Images/tree_01.png", { 0,0 }, { 100, 200 }, { 50, 100 }, {20}},
       //{NULL,   L"./Data/Images/Red_monster.png", { 0,0 }, { 160, 160 }, { 80, 80 }, {20}},
};
OBJ2D obstacle[OBSTACLE_MAX];

struct OBSTACLE_SET {
    int obstacleType;
    VECTOR2 pos;
}
obstacleSet[] = {
    {0,{  300, 720}},
    {0,{  500, 720}},
    {0,{  100, 720}},
    {0,{  200, 720}},
    {1,{  1000,720 }},
    {1,{  700, 720}},
    {1,{  800, 720}},
    {1,{  400, 720}},
    {-1,{  -1, -1 }},
};

void obstacle_init()
{
    //obstacle_state‚ğ0
    obstacle_state = 0;

    srand((unsigned)time(NULL));
    for (int i = 0; obstacleSet[i].obstacleType >= 0; i++) {
        rndx = rand() % 1921;
        obstacleSet[i].pos.x = rndx;
    }

}

void obstacle_deinit()
{
    //Obstacle‚ğ”jŠü
    int dataNum1 = ARRAYSIZE(obstacleData);
    for (int i = 0; i < dataNum1; i++) {
        safe_delete(obstacleData[i].spr);
    }
}

void obstacle_update()
{
    switch (obstacle_state)
    {
    case 0:
    {

        //////// ‰Šúİ’è ////////

        //áŠQ•¨‚Ì‰æ‘œ‚ğ“Ç‚İ‚İ
        int dataNum1 = sizeof(obstacleData) / sizeof(OBSTACLE_DATA);
        for (int i = 0; i < dataNum1; i++) {
            obstacleData[i].spr = sprite_load(obstacleData[i].filePath);
        }
        ++obstacle_state;
        /*fallthrough*/
    }

    case 1:
        //////// ƒpƒ‰ƒ[ƒ^‚Ìİ’è ////////

        for (int i = 0; i < OBSTACLE_MAX; i++) {
            obstacle[i] = {};
            obstacle[i].moveAlg = -1;
        }
        ++obstacle_state;
        /*fallthrough*/

    case 2:
        //“¢”°Œã‚à‚¤ˆê“xŒÄ‚Ño‚·
        for (int i = 0; obstacleSet[i].obstacleType >= 0; i++) {
            OBJ2D* p = searchSet0(obstacle, OBSTACLE_MAX, obstacleSet[i].obstacleType, obstacleSet[i].pos);

            if (!p) break;
        }

        for (int i = 0; obstacleSet[i].obstacleType >= 0; i++) {
            rndx = rand() % 1281;
            obstacleSet[i].pos.x = rndx;
        }


        for (int i = 0; i < OBSTACLE_MAX; i++) {
            if (obstacle[i].moveAlg == -1)continue;

            switch (obstacle[i].moveAlg) {
            case 0:
                Obstacle0(&obstacle[i]);
                break;
            case 1:
                Obstacle1(&obstacle[i]);
                break;
            }
            ++obstacle[i].timer;
        }

        break;
    }
}

void obstacle_render()
{
    for (int i = 0; i < OBSTACLE_MAX; ++i)
    {
        if (obstacle[i].moveAlg == -1)continue;

        //áŠQ•¨‚Ì•`‰æ
        sprite_render(obstacle[i].spr, obstacle[i].pos.x, obstacle[i].pos.y, obstacle[i].scale.x, obstacle[i].scale.y, obstacle[i].texPos.x, obstacle[i].texPos.y, obstacle[i].texSize.x, obstacle[i].texSize.y,obstacle[i].pivot.x, obstacle[i].pivot.y, ToRadian(0), obstacle[i].color.x, obstacle[i].color.y,obstacle[i].color.z, obstacle[i].color.w);

    }
}

void Obstacle0(OBJ2D* obj)
{

    switch (obj->state) {
    case 0:

        obj->scale = { 1.0f, 1.0f };
        obj->color = { 1, 1, 1, 1 };
        obj->spr = obstacleData[0].spr;
        obj->texPos = obstacleData[0].texPos;
        obj->texSize = obstacleData[0].texSize;
        obj->pivot = obstacleData[0].pivot;
        obj->radius = obstacleData[0].radius;

        ++obj->state;
        /*fallthrough*/

    case 1:
        ////////’Êí////////
        break;
    }
}

void Obstacle1(OBJ2D* obj)
{

    switch (obj->state) {
    case 0:

        obj->scale = { 1.0f, 1.0f };
        obj->color = { 1, 1, 1, 1 };
        obj->spr = obstacleData[1].spr;
        obj->texPos = obstacleData[1].texPos;
        obj->texSize = obstacleData[1].texSize;
        obj->pivot = obstacleData[1].pivot;
        obj->radius = obstacleData[1].radius;

        ++obj->state;
        /*fallthrough*/

    case 1:
        ////////’Êí////////
        break;
    }
}