#include "all.h"

extern OBJ2D player;
extern OBJ2D avalanche;
extern OBJ2D obstacle[OBSTACLE_MAX];
extern OBJ2D enemy[ENEMY_MAX];

extern int combo;
extern int hp;
//“–‚½‚è”»’è
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

    //”»’è
    for (int i = 0; i < ENEMY_MAX; i++) {
        if (enemy[i].moveAlg == -1)continue;

        if (hitCheck(&player, &enemy[i])) {
            enemy[i].moveAlg = -1;

            player_hp();
            combo = 0;

        }
    }

    for (int i = 0; i < OBSTACLE_MAX; i++) {
        if (obstacle[i].moveAlg == -1)continue;
        if (hitCheck(&player, &obstacle[i])) {
            hp -= 5;

        }

       
    }

    if (hitCheck(&player, &avalanche)) {

        nextScene = SCENE_RESULT;

    }

}