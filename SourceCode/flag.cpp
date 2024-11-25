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
       {NULL,   L"./Data/Images/flag_01.png", { 0,0 }, { 200, 230 }, { 100, 200 }, {20}},
};
OBJ2D flag[FLAG_MAX];

struct FLAG_SET {
    int flagType;
    VECTOR2 pos;
}
flagSet[] = {
    {0,{  300, 540}},
    {0,{  500, 540}},
    {0,{  100, 540}},
    {0,{  200, 540}},
    {0,{  1000,540 }},
    {0,{  700, 540}},
    {0,{  800, 540}},
    {0,{  400, 540}},
    {-1,{  -1, -1 }},
};

void flag_init()
{
    //flag_state��0
    flag_state = 0;

    srand((unsigned)time(NULL));
    for (int i = 0; flagSet[i].flagType >= 0; i++) {
        rnd_x = rand() % 1921;
        flagSet[i].pos.x = rnd_x;
    }

}

void flag_deinit()
{
    //flag��j��
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

        //////// �����ݒ� ////////

        //���̉摜��ǂݍ���
        int dataNum1 = sizeof(flagData) / sizeof(FLAG_DATA);
        for (int i = 0; i < dataNum1; i++) {
            flagData[i].spr = sprite_load(flagData[i].filePath);
        }

        ++flag_state;
        /*fallthrough*/
    }

    case 1:
        //////// �p�����[�^�̐ݒ� ////////

        for (int i = 0; i < FLAG_MAX; i++) {
            flag[i] = {};
            flag[i].moveAlg = -1;
        }
        ++flag_state;
        /*fallthrough*/

    case 2:
        //���l���������x�Ăяo��
        for (int i = 0; flagSet[i].flagType >= 0; i++) {
            OBJ2D* p = searchSet0(flag, FLAG_MAX, flagSet[i].flagType, flagSet[i].pos);

            if (!p) break;
        }

        for (int i = 0; flagSet[i].flagType >= 0; i++) {
            rnd_x = rand() % 1281;
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

        //���̕`��
        sprite_render(flag[i].spr, flag[i].pos.x, flag[i].pos.y, flag[i].scale.x, flag[i].scale.y, flag[i].texPos.x, flag[i].texPos.y, flag[i].texSize.x, flag[i].texSize.y, flag[i].pivot.x, flag[i].pivot.y, ToRadian(0),flag[i].color.x, flag[i].color.y,flag[i].color.z, flag[i].color.w);

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
        ////////�ʏ펞////////


        break;
    }
}
