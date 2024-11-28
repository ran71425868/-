#include "all.h"
#include <sstream>

int game_state;
int game_timer;

float playerX;
float playerY;

int score;
int hp_score;
int goalflug;
float comboscore;
int combo;

extern OBJ2D enemy[ENEMY_MAX];
extern OBJ2D flag[FLAG_MAX];

extern int hp;

Sprite* sprBack;

std::ostringstream oss;                                 // ï∂éöóÒÉXÉgÉäÅ[ÉÄ
POINT point; 

// åªç›ÇÃÉXÉNÉçÅ[Éãó 
float scrollValue = 0.0f;

void game_init() {
	game_state = 0;
	game_timer = 0;
	score = 0;
	hp_score = 0;
	combo = 0;
	comboscore = 1.0f;
	goalflug = 0;

	playerX = SCREEN_W /2.0f;
	playerY = SCREEN_H /2.0f;
}
void game_deinit() {
	music::stop(0);
	player_deinit();
	enemy_deinit();
	obstacle_deinit();
	flag_deinit();
	goal_deinit();
	avalanche_deinit();
	
}
void game_update()
{
	switch (game_state)
	{
	case 0:
		sprBack = sprite_load(L"./Data/Images/map_04.png");
		

		audio_init();
		player_init();
		enemy_init();
		obstacle_init();
		flag_init();
		goal_init();
		avalanche_init();

		game_state++;
		/*fallthrough*/

	case 1:
		GameLib::setBlendMode(Blender::BS_ALPHA);

		music::play(0);
		music::setVolume(0, 0.3f);

		game_state++;
		/*fallthrough*/

	case 2:
		if (TRG(0) & PAD_SELECT) {
			nextScene = SCENE_TITLE;
			break;
		}

		if (hp <= 0)
		{
			nextScene = SCENE_RESULT;
		}

		player_update();
		enemy_update();
		obstacle_update();
		flag_update();
		goal_update();
		avalanche_update();


		game_over();
		judge();
		break;
	}

	scrollValue-=3;

	game_timer++;
}
void game_render() {
	
	sprite_render(sprBack, 0.0f, scrollValue); // îwåiÇÉJÉÅÉâÇÃà íuÇ…çáÇÌÇπÇƒï`âÊ
	sprite_render(sprBack, 0.0f, 10000.0f+scrollValue); // îwåiÇÉJÉÅÉâÇÃà íuÇ…çáÇÌÇπÇƒï`âÊ
	sprite_render(sprBack, 0.0f, 20000.0f+scrollValue); // îwåiÇÉJÉÅÉâÇÃà íuÇ…çáÇÌÇπÇƒï`âÊ

	
	player_render();
	enemy_render();
	obstacle_render();
	flag_render();
	goal_render();
	avalanche_render();
	
	text_out(0, "score", 1700, 450, 2, 2);
	text_out(0, std::to_string(score), 1700, 500, 2, 2);
	text_out(0, "combo", 1700, 550, 2, 2);
	text_out(0, std::to_string(combo), 1700, 600, 2, 2);
}
void game_score()
{
	if (combo >= 10)
		comboscore = 2.5f;
	else if (combo >=5)
		comboscore = 2.0f;
	else
		comboscore = 1.0f;


	for (int i = 0; i < FLAG_MAX; i++) {
		if (flag[i].moveAlg == -1)
			score += 100 * comboscore;

	}
	combo++;
}

void game_clear()
{
	goalflug = 1;

	if (goalflug == 1) {
		if (hp == 100) {
			hp_score = 1500;
			score += hp_score;
		}
		else {
			hp_score += hp * 10;
			score += hp_score;
		}

	}
	nextScene = SCENE_RESULT;
}

void game_over()
{
	if (player.pos.y < 300.0f)
	{
		nextScene = SCENE_RESULT_OVER;
		music::play(7, false);
	}
}
