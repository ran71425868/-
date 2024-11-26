#include "all.h"
#include <sstream>

int normal_state;
int normal_timer;

float playerX2;
float playerY2;

int score2;
float comboscore1;
int combo2;

extern OBJ2D flag[FLAG_MAX];

extern int hp;

Sprite* sprBack2;

std::ostringstream oss2;                                 // ï∂éöóÒÉXÉgÉäÅ[ÉÄ
POINT point2;

// åªç›ÇÃÉXÉNÉçÅ[Éãó 
float scrollValue2 = 0.0f;

void normal_init() {
	normal_state = 0;
	normal_timer = 0;
	score2 = 0;
	combo2 = 0;
	comboscore1 = 1.0f;

	playerX2 = SCREEN_W / 2.0f;
	playerY2 = SCREEN_H / 2.0f;
}
void normal_deinit() {
	music::stop(0);
	player_deinit();
	obstacle_deinit();
	flag_deinit();
	avalanche_deinit();

}
void normal_update()
{
	switch (normal_state)
	{
	case 0:
		sprBack2 = sprite_load(L"./Data/Images/map_04.png");

		audio_init();
		player_init();
		enemy_init();
		obstacle_init();
		flag_init();
		avalanche_init();

		normal_state++;
		/*fallthrough*/

	case 1:
		GameLib::setBlendMode(Blender::BS_ALPHA);

		music::play(0);
		music::setVolume(0, 0.3f);

		normal_state++;
		/*fallthrough*/

	case 2:

		if (hp <= 0)
		{
			nextScene = SCENE_RESULT;
		}

		player_update();
		obstacle_update();
		flag_update();
		avalanche_update();


		game_over();
		judge();
		break;
	}

	scrollValue2 -= 3;

	normal_timer++;
}
void normal_render() {

	sprite_render(sprBack2, 0.0f, scrollValue2); // îwåiÇÉJÉÅÉâÇÃà íuÇ…çáÇÌÇπÇƒï`âÊ
	sprite_render(sprBack2, 0.0f, 10000.0f + scrollValue2); // îwåiÇÉJÉÅÉâÇÃà íuÇ…çáÇÌÇπÇƒï`âÊ

	text_out(4, "Down:S Right: D Left: A", 0, 0, 1, 1);
	text_out(0, "score", 1100, 0, 2, 2);
	text_out(0, std::to_string(score2), 1100, 50, 2, 2);
	text_out(0, "combo", 0, 150, 2, 2);
	text_out(0, std::to_string(combo2), 0, 200, 2, 2);

	player_render();
	obstacle_render();
	flag_render();
	avalanche_render();

}
void normal_score()
{
	if (combo2 >= 30)
		comboscore1 = 2.5f;
	else if (combo2>= 20)
		comboscore1 = 2.0f;
	else if (combo2>= 10)
		comboscore1 = 1.5f;
	else
		comboscore1 = 1.0f;


	for (int i = 0; i < FLAG_MAX; i++) {
		if (flag[i].moveAlg == -1)
			score2 += 100 * comboscore1;

	}
	combo2++;
}

void normal_clear()
{

}

void normal_over()
{
	if (player.pos.y < 300.0f)
	{
		nextScene = SCENE_RESULT;
	}
}
