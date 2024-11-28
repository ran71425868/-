#include "all.h"
#include <sstream>

int normal_state;
int normal_timer;

float playerX2;
float playerY2;

extern int score;
extern float comboscore;
extern int combo;


extern OBJ2D flag[FLAG_MAX];

extern int hp;

Sprite* sprBack2;
Sprite* sprGoal2;

std::ostringstream oss2;                                 // ï∂éöóÒÉXÉgÉäÅ[ÉÄ
POINT point2;

// åªç›ÇÃÉXÉNÉçÅ[Éãó 
float scrollValue2 = 0.0f;

void normal_init() {
	normal_state = 0;
	normal_timer = 0;

	playerX2 = SCREEN_W / 2.0f;
	playerY2 = SCREEN_H / 2.0f;
}
void normal_deinit() {
	music::stop(0);
	player_deinit();
	obstacle_deinit();
	flag_deinit();
	goal_deinit();
	avalanche_deinit();

}
void normal_update()
{
	switch (normal_state)
	{
	case 0:
		sprBack2 = sprite_load(L"./Data/Images/map_04.png");
		sprGoal2 = sprite_load(L"./Data/Images/goal.png");

		audio_init();
		player_init();
		//enemy_init();
		obstacle_init();
		flag_init();
		goal_init();
		avalanche_init();

		normal_state++;
		/*fallthrough*/

	case 1:
		GameLib::setBlendMode(Blender::BS_ALPHA);

		music::play(0);
		music::setVolume(0, 0.3f);

		score = 0;

		normal_state++;
		/*fallthrough*/

	case 2:

		if (hp <= 0)
		{
			nextScene = SCENE_RESULT_OVER;
		}

		player_update();
		obstacle_update();
		flag_update();
		goal_update();
		avalanche_update();


		game_over();
		judge();
		
		break;
	}

	scrollValue2 -= 5;
	if (scrollValue2 < -9000)
	{
		scrollValue2 = 0;
	}
	normal_timer++;
}
void normal_render() {

	sprite_render(sprBack2, 0.0f, scrollValue2); // îwåiÇÉJÉÅÉâÇÃà íuÇ…çáÇÌÇπÇƒï`âÊ
	sprite_render(sprBack2, 0.0f, 10000.0f + scrollValue2); // îwåiÇÉJÉÅÉâÇÃà íuÇ…çáÇÌÇπÇƒï`âÊ
	sprite_render(sprBack2, 0.0f, 20000.0f + scrollValue2); // îwåiÇÉJÉÅÉâÇÃà íuÇ…çáÇÌÇπÇƒï`âÊ
	sprite_render(sprGoal2, 0.0f, 20000.0 + scrollValue2); // îwåiÇÉJÉÅÉâÇÃà íuÇ…çáÇÌÇπÇƒï`âÊ


	
	text_out(0, "score", 1700, 450, 2, 2);
	text_out(0, std::to_string(score), 1700, 500, 2, 2);
	text_out(0, "combo", 1700, 550, 2, 2);
	text_out(0, std::to_string(combo), 1700, 600, 2, 2);

	player_render();
	obstacle_render();
	flag_render();
	goal_render();
	avalanche_render();

}