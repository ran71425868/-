#include "all.h"
#include	<stdlib.h>
#include	<time.h>

int rnd_x;
int flag_state;

struct FLAG_DATA {
    Sprite* spr;
    const wchar_t* filePath;
    VECTOR2          texPos;
    VECTOR2          texSize;
    VECTOR2          pivot;
    float            radius;
}
flagData[] = {
       {NULL,   L"./Data/Images/flag_01.png", { 0,0 }, { 200, 230 }, { 100, 200 }, {30}},
};
OBJ2D flag[FLAG_MAX];

struct FLAG_SET {
    int flagType;
    VECTOR2 pos;
}
flagSet[] = {
    {0,{  300, 1400}},
    {0,{  500, 1500}},
    {0,{  100, 1700}},
    {0,{  200, 1100}},
    {0,{  1000,2000 }},
    {-1,{  -1, -1 }},
};

void flag_init()
{
    //flag_state‚ğ0
    flag_state = 0;

    srand((unsigned)time(NULL));
    for (int i = 0; flagSet[i].flagType >= 0; i++) {
        rnd_x = 300+rand() % 1401;
        flagSet[i].pos.x = rnd_x;
    }

}

void flag_deinit()
{
    //flag‚ğ”jŠü
    int dataNum1 = ARRAYSIZE(flagData);
    for (int i = 0; i < dataNum1; i++) {
        safe_delete(flagData[i].spr);
    }
}

void flag_update()
{
    switch (flag_state)
    {
    case 0:
    {

        //////// ‰Šúİ’è ////////

        //Šø‚Ì‰æ‘œ‚ğ“Ç‚İ‚İ
        int dataNum1 = sizeof(flagData) / sizeof(FLAG_DATA);
        for (int i = 0; i < dataNum1; i++) {
            flagData[i].spr = sprite_load(flagData[i].filePath);
        }

        ++flag_state;
        /*fallthrough*/
    }

    case 1:
        //////// ƒpƒ‰ƒ[ƒ^‚Ìİ’è ////////

        for (int i = 0; i < FLAG_MAX; i++) {
            flag[i] = {};
            flag[i].moveAlg = -1;
        }
        ++flag_state;
        /*fallthrough*/

    case 2:
        //ŠøŠl“¾Œã‚à‚¤ˆê“xŒÄ‚Ño‚·
        for (int i = 0; flagSet[i].flagType >= 0; i++) {
            OBJ2D* p = searchSet0(flag, FLAG_MAX, flagSet[i].flagType, flagSet[i].pos);

            if (!p) break;
        }

        flag_moveY();


        for (int i = 0; flagSet[i].flagType >= 0; i++) {
            rnd_x = 300+rand() % 1401;
            flagSet[i].pos.x = rnd_x;
        }


        for (int i = 0; i < FLAG_MAX; i++) {
            if (flag[i].moveAlg == -1)continue;

            switch (flag[i].moveAlg) {
            case 0:
                Flag0(&flag[i]);
                break;
            }
            ++flag[i].timer;
        }

        break;
    }
}

void flag_render()
{
    for (int i = 0; i < FLAG_MAX; ++i)
    {
        if (flag[i].moveAlg == -1)continue;

        //Šø‚Ì•`‰æ
        sprite_render(flag[i].spr, flag[i].pos.x, flag[i].pos.y, flag[i].scale.x, flag[i].scale.y, flag[i].texPos.x, flag[i].texPos.y, flag[i].texSize.x, flag[i].texSize.y, flag[i].pivot.x, flag[i].pivot.y, ToRadian(0),flag[i].color.x, flag[i].color.y,flag[i].color.z, flag[i].color.w);

        primitive::circle(flag[i].pos + flag[i].offset,
            flag[i].radius, {1, 1}, ToRadian(0), {1, 0, 0, 0.2f});

    }
}

void flag_moveY()
{
    for (int i = 0; i < FLAG_MAX; i++) {
        flag[i].pos.y -= 0.3f;

    }

}

void Flag0(OBJ2D* obj)
{

    switch (obj->state) {
    case 0:

        obj->scale = { 0.5f, 0.5f };
        obj->color = { 1, 1, 1, 1 };
        obj->spr = flagData[0].spr;
        obj->texPos = flagData[0].texPos;
        obj->texSize = flagData[0].texSize;
        obj->pivot = flagData[0].pivot;
        obj->radius = flagData[0].radius;

        ++obj->state;
        /*fallthrough*/

    case 1:
        ////////’Êí////////


        break;
    }
}
