#include "all.h"
#include <math.h>

extern OBJ2D player;
extern OBJ2D avalanche;
extern OBJ2D obstacle[OBSTACLE_MAX];
extern OBJ2D enemy[ENEMY_MAX];
extern OBJ2D flag[FLAG_MAX];

extern int combo;
extern int hp;
extern int goalflug;

//当たり判定
bool hitCheckCircle(VECTOR2 pos1, float r1, VECTOR2 pos2, float r2) {
    float dx = pos2.x - pos1.x;
    float dy = pos2.y - pos1.y;
    float r = r1 + r2;

    if (dx * dx + dy * dy <= r * r)
        return true;

    return false;
}

bool hitCheck(OBJ2D* obj1, OBJ2D* obj2) {
    return hitCheckCircle(
        obj1->pos + obj1->offset, obj1->radius,
        obj2->pos + obj2->offset, obj2->radius
    );
}

void judge()
{

    //判定
    //プレイヤーとエネミーの判定
    for (int i = 0; i < ENEMY_MAX; i++) {
        if (enemy[i].moveAlg == -1)continue;

        if (hitCheck(&player, &enemy[i])) {
            enemy[i].moveAlg = -1;

            player_hp();
            player.speed.y = -20.0f;
            combo = 0;
            music::play(3, false);
        }
    }

    //プレイヤーと障害物の判定
    for (int i = 0; i < OBSTACLE_MAX; i++) {
        if (obstacle[i].moveAlg == -1)continue;
        if (hitCheck(&player, &obstacle[i])) {
            hp -= 3;
            player.speed.y = -20.0f;
            combo = 0;
            music::play(6, false);
        }

       
    }

    //プレイヤーと旗の判定
    for (int i = 0; i < FLAG_MAX; i++) {
        if (flag[i].moveAlg == -1)continue;
        if (hitCheck(&player, &flag[i])) {
            flag[i].moveAlg = -1;
            music::play(5, false);
            game_score();
        }


    }

    //エネミーと障害物の判定
    for (int i = 0; i < ENEMY_MAX; i++) 
    {
        if (enemy[i].moveAlg == -1)continue;

        for (int j = 0; j < OBSTACLE_MAX; j++) 
        {
            if (hitCheck(&obstacle[j], &enemy[i])) 
            {
                enemy[i].moveAlg = -1;


            }
        }
        
    }

    for (int i = 0; i < FLAG_MAX; i++) {
        if (flag[i].moveAlg == -1)continue;
        for (int j = 7; j < OBSTACLE_MAX; j++) {
            if (hitCheck(&obstacle[j], &flag[i])) {
                
                    flag[i].moveAlg = -1;
               
            }
        }
    }

    for (int i = 0; i < 7; i++) {
        if (obstacle[i].moveAlg == -1)continue;
        for (int j = 7; j < OBSTACLE_MAX; j++) {
            if (hitCheck(&obstacle[j], &obstacle[i])) {

                obstacle[i].moveAlg = -1;

            }
        }
    }



        if (hitCheck(&player, &goal)) {
            goalflug = 1;
            game_clear();
        }
}