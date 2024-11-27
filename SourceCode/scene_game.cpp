#include "all.h"
#include <sstream>

int game_state;
int game_timer;

float playerX;
float playerY;

int score;
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
	combo = 0;
	comboscore = 1.0f;

	playerX = SCREEN_W /2.0f;
	playerY = SCREEN_H /2.0f;
}
void game_deinit() {
	music::stop(0);
	player_deinit();
	enemy_deinit();
	obstacle_deinit();
	flag_deinit();
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

	text_out(4, "Down:S Right: D Left: A", 0, 0, 1, 1);
	text_out(0, "score", 1100, 0, 2, 2);
	text_out(0, std::to_string(score), 1100, 50, 2, 2);
	text_out(0, "combo", 0, 150, 2, 2);
	text_out(0, std::to_string(combo), 0, 200, 2, 2);
	
	player_render();
	enemy_render();
	obstacle_render();
	flag_render();
	avalanche_render();
	
}
void game_score()
{
	if (combo >= 30)
		comboscore = 2.5f;
	else if (combo >= 20)
		comboscore = 2.0f;
	else if (combo >= 10)
		comboscore = 1.5f;
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

}

void game_over()
{
	if (player.pos.y < 300.0f)
	{
		nextScene = SCENE_RESULT;
		music::play(7, false);
	}
}
