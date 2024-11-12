#include "all.h"
#include	<stdlib.h>
#include	<time.h>

int rndX, rndY;
int obstacle_state;

extern float angle;

struct ENEMY_DATA {
    Sprite* spr;
    const wchar_t* filePath;
    VECTOR2          texPos;
    VECTOR2          texSize;
    VECTOR2          pivot;
    float            radius;
}
enemyData[] = {
       {NULL,   L"./Data/Images/dirtr.png", { 0,0 }, { 64, 64 }, { 32, 32 }, {20}},
       /*{NULL,   L"./Data/Images/Green_monster.png", { 0,0 }, { 160, 160 }, { 80, 80 }, {20}},
       {NULL,   L"./Data/Images/Red_monster.png", { 0,0 }, { 160, 160 }, { 80, 80 }, {20}},*/
};
OBJ2D enemy[OBSTACLE_MAX];

struct ENEMY_SET {
    int obstacleType;
    VECTOR2 pos;
}
enemySet[] = {
    {0,{  300, 0}},
    {0,{  500, 0}},
    {0,{  100, 0}},
    {1,{  200, 0}},
    {1,{  1000,720 }},
    {1,{  700, 720}},
    {2,{  800, 720}},
    {2,{  400, 720}},
    {-1,{  -1, -1 }},
};

void obstacle_init()
{
    //enemy_state‚ð0
    obstacle_state = 0;

    srand((unsigned)time(NULL));
    for (int i = 0; enemySet[i].obstacleType >= 0; i++) {
        rndX = rand() % 1281;
        enemySet[i].pos.x = rndX;
    }

}

void obstacle_deinit()
{
}

void obstacle_update()
{
}

void obstacle_render()
{
}
