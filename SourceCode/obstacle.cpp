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
       {NULL,   L"./Data/Images/stone_01.png", { 0,0 }, { 200, 200 }, { 100, 100 }, {25}},
       {NULL,   L"./Data/Images/tree_01.png", { 0,0 }, { 100, 200 }, { 50, 100 }, {20}},
       {NULL,   L"./Data/Images/dirt.png", { 0,0 }, { 64, 64 }, { 32, 32 }, {30}},
};
OBJ2D obstacle[OBSTACLE_MAX];

struct OBSTACLE_SET {
    int obstacleType;
    VECTOR2 pos;
    int obstaclesort;
}
obstacleSet[] = {
    {0,{  300, 1080},0},
    {0,{  500, 1300},0},
    {0,{  100, 1800},0},
    {0,{  200, 1200},0},
    {1,{  1000,1400 },0},
    {1,{  700, 1100},0},
    {1,{  800, 1600},0},
    {2,{  300, 350},1},
    {2,{  400, 350},1},
    {2,{  500, 350},1},
    {2,{  600, 350},1},
    {2,{  700, 350},1},
    {2,{  800, 350},1},
    {2,{  900,350 },1},
    {2,{  1000, 350},1},
    {2,{  1100, 350},1},
    {2,{  1200, 350},1},
    {2,{  1300, 350},1},
    {2,{  1400, 350},1},
    {2,{  1500, 350},1},
    {2,{  1600, 350},1},
    {2,{  1700, 350},1},
    {-1,{  -1, -1 },-1},
};

void obstacle_init()
{
    //obstacle_stateÇ0
    obstacle_state = 0;

    srand((unsigned)time(NULL));
    for (int i = 0; obstacleSet[i].obstacleType >= 0; i++) {
        if (obstacleSet[i].obstaclesort == 0) {
            rndx = 300 + rand() % 1401;
            obstacleSet[i].pos.x = rndx;

        }
    }

}

void obstacle_deinit()
{
    //ObstacleÇîjä¸
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

        //////// èâä˙ê›íË ////////

        //è·äQï®ÇÃâÊëúÇì«Ç›çûÇ›
        int dataNum1 = sizeof(obstacleData) / sizeof(OBSTACLE_DATA);
        for (int i = 0; i < dataNum1; i++) {
            obstacleData[i].spr = sprite_load(obstacleData[i].filePath);
        }
        ++obstacle_state;
        /*fallthrough*/
    }

    case 1:
        //////// ÉpÉâÉÅÅ[É^ÇÃê›íË ////////

        for (int i = 0; i < OBSTACLE_MAX; i++) {
            obstacle[i] = {};
            obstacle[i].moveAlg = -1;
        }

        ++obstacle_state;
        /*fallthrough*/

    case 2:
        //ì¢î∞å„Ç‡Ç§àÍìxåƒÇ—èoÇ∑
        for (int i = 0; obstacleSet[i].obstacleType >= 0; i++) {
            OBJ2D* p = searchSet0(obstacle, OBSTACLE_MAX, obstacleSet[i].obstacleType, obstacleSet[i].pos);

            if (!p) break;
        }

        obstacle_moveY();

        for (int i = 0; obstacleSet[i].obstacleType >= 0; i++) {
            rndx = 300+rand() % 1401;
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
            case 2:
                Obstacle2(&obstacle[i]);
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

        //è·äQï®ÇÃï`âÊ
        sprite_render(obstacle[i].spr, obstacle[i].pos.x, obstacle[i].pos.y, obstacle[i].scale.x, obstacle[i].scale.y, obstacle[i].texPos.x, obstacle[i].texPos.y, obstacle[i].texSize.x, obstacle[i].texSize.y,obstacle[i].pivot.x, obstacle[i].pivot.y, ToRadian(0), obstacle[i].color.x, obstacle[i].color.y,obstacle[i].color.z, obstacle[i].color.w);

        primitive::circle(obstacle[i].pos + obstacle[i].offset,
            obstacle[i].radius, { 1, 1 }, ToRadian(0), { 1, 0, 0, 0.2f });
    }
}

void obstacle_moveY()
{
    for (int i = 0; i < 7; i++)
    {
        obstacle[i].pos.y -= 0.3f;
    }

}

void Obstacle0(OBJ2D* obj)
{

    switch (obj->state) {
    case 0:

        obj->scale = { 0.7f, 0.7f };
        obj->color = { 1, 1, 1, 1 };
        obj->spr = obstacleData[0].spr;
        obj->texPos = obstacleData[0].texPos;
        obj->texSize = obstacleData[0].texSize;
        obj->pivot = obstacleData[0].pivot;
        obj->radius = obstacleData[0].radius;

        ++obj->state;
        /*fallthrough*/

    case 1:
        ////////í èÌéû////////
        break;
    }
}

void Obstacle1(OBJ2D* obj)
{

    switch (obj->state) {
    case 0:

        obj->scale = { 0.6f, 0.6f };
        obj->color = { 1, 1, 1, 1 };
        obj->spr = obstacleData[1].spr;
        obj->texPos = obstacleData[1].texPos;
        obj->texSize = obstacleData[1].texSize;
        obj->pivot = obstacleData[1].pivot;
        obj->radius = obstacleData[1].radius;

        ++obj->state;
        /*fallthrough*/

    case 1:
        ////////í èÌéû////////
        break;
    }
}

void Obstacle2(OBJ2D* obj)
{
    switch (obj->state) {
    case 0:

        obj->scale = { 1.0f, 1.0f };
        obj->color = { 1, 1, 1, 1 };
        obj->spr = obstacleData[2].spr;
        obj->texPos = obstacleData[2].texPos;
        obj->texSize = obstacleData[2].texSize;
        obj->pivot = obstacleData[2].pivot;
        obj->radius = obstacleData[2].radius;

        ++obj->state;
        /*fallthrough*/

    case 1:
        ////////í èÌéû////////
        break;
    }
}
