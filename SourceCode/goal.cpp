#include "all.h"

int goal_state;

//OBJ2D�^�̕ϐ�goal��錾
OBJ2D goal;

Sprite* sprGoal;

void goal_init()
{
	//goal_state��0
	goal_state = 0;
}

void goal_deinit()
{
	//sprGoal��j��
	safe_delete(sprGoal);
}

void goal_update()
{
    switch (goal_state)
    {
    case 0:
        //////// �����ݒ� ////////

        //�v���C���[�̉摜��ǂݍ���
        sprGoal = sprite_load(L"./Data/Images/goal.png");

        ++goal_state;
        /*fallthrough*/

    case 1:
        //////// �p�����[�^�̐ݒ� ////////
       

        //player�̃p�����[�^�ݒ�
        goal = {};
        goal.timer = 0;
        goal.pos = { SCREEN_W * 0.5f,20000+SCREEN_H * 0.5f };
        goal.scale = { 1.5f,1.5f };
        goal.texPos = { 0,0 };
        goal.texSize = { GOAL_TEX_W ,GOAL_TEX_H };
        goal.pivot = { GOAL_PIVOT_X,GOAL_PIVOT_Y };
        goal.color = { 1.0f,1.0f,1.0f,1.0f };
        goal.radius = 400.0f;
        goal.offset = { 0,0 };



        ++goal_state;
        /*fallthrough*/

    case 2:
        //////// �ʏ펞 ////////
        goal_moveY();

        break;
    }

}

void goal_render()
{
    //goal�̕`��
    sprite_render(sprGoal, 
        goal.pos.x, goal.pos.y, 
        goal.scale.x, goal.scale.y, 
        goal.texPos.x, goal.texPos.y, 
        goal.texSize.x, goal.texSize.y, 
        goal.pivot.x, goal.pivot.y,
        ToRadian(0), goal.color.x, goal.color.y);

}

void goal_moveY()
{
    goal.pos.y -= 5;
}
