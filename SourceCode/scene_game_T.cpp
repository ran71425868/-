#include "all.h"
#include <sstream>

int tutorial_state;
int tutorial_timer;

float playerX3;
float playerY3;

int score3;
float comboscore3;
int combo3;

extern OBJ2D enemy[ENEMY_MAX];
extern OBJ2D flag[FLAG_MAX];

extern int hp;

Sprite* sprBack3;
Sprite* sprSousa;
Sprite* sprBusuto;
std::ostringstream oss1;                                 // ï∂éöóÒÉXÉgÉäÅ[ÉÄ
POINT point3;

// åªç›ÇÃÉXÉNÉçÅ[Éãó 
float scrollValue1 = 0.0f;

void tutorial_init() {
	tutorial_state = 0;
	tutorial_timer = 0;
	score3 = 0;
	combo3 = 0;
	comboscore3 = 1.0f;

	playerX3 = SCREEN_W / 2.0f;
	playerY3 = SCREEN_H / 2.0f;
}
void tutorial_deinit() {
	music::stop(0);
	player_deinit();
	/*enemy_deinit();
	obstacle_deinit();*/
	avalanche_deinit();
	flag_deinit();

}
void tutorial_update()
{
	switch (tutorial_state)
	{
	case 0:
		sprBack3 = sprite_load(L"./Data/Images/map_04.png");
		sprSousa = sprite_load(L"./Data/Images/sousa.png");
		sprBusuto = sprite_load(L"./Data/Images/busuto.png");

		audio_init();
		player_init();
		enemy_init();
		obstacle_init();
		avalanche_init();
		flag_init();

		tutorial_state++;
		/*fallthrough*/

	case 1:
		GameLib::setBlendMode(Blender::BS_ALPHA);

		music::play(0);
		music::setVolume(0, 0.3f);

		tutorial_state++;
		/*fallthrough*/

	case 2:
		if (TRG(0) & PAD_SELECT) {
			nextScene = SCENE_SENNTAKU;
			break;
		}

		if (hp <= 0)
		{
			nextScene = SCENE_RESULT;
		}

		player_update();
		/*enemy_update();
		obstacle_update();
		avalanche_update();*/
		flag_update();


		game_over();
		judge();
		break;
	}

	scrollValue1 -= 3;

	tutorial_timer++;
}
void tutorial_render() {
	
	




	sprite_render(sprBack3, 0.0f, scrollValue1); // îwåiÇÉJÉÅÉâÇÃà íuÇ…çáÇÌÇπÇƒï`âÊ
	sprite_render(sprBack3, 0.0f, 10000.0f + scrollValue1); // îwåiÇÉJÉÅÉâÇÃà íuÇ…çáÇÌÇπÇƒï`âÊ
	sprite_render(sprSousa, 300, 0, 1.3f, 1.3f);
	sprite_render(sprBusuto, 1000, 0, 1.0f, 1.0f);

	player_render();
	//enemy_render();
	//obstacle_render();
	//avalanche_render();
	flag_render();

}
void tutorial_score()
{
	if (combo3>= 30)
		comboscore3 = 2.5f;
	else if (combo3 >= 20)
		comboscore3 = 2.0f;
	else if (combo3 >= 10)
		comboscore3 = 1.5f;
	else
		comboscore3 = 1.0f;


	for (int i = 0; i < FLAG_MAX; i++) {
		if (enemy[i].moveAlg == -1)
			score3 += 100 * comboscore3;

	}
	combo3++;
}

void tutorial_clear()
{

}

void tutorial_over()
{
	if (player.pos.y < 300.0f)
	{
		nextScene = SCENE_RESULT;
	}
}
