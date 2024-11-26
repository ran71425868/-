#include "all.h"
#include <sstream>

int easy_state;
int easy_timer;

float playerX1;
float playerY1;

int score1;
float comboscore2;
int combo1;

extern OBJ2D flag[FLAG_MAX];

extern int hp;

Sprite* sprBack1;

std::ostringstream oss3;                                 // 文字列ストリーム
POINT point1;

// 現在のスクロール量
float scrollValue3 = 0.0f;

void easy_init() {
	easy_state = 0;
	easy_timer = 0;
	score1 = 0;
	combo1 = 0;
	comboscore2 = 1.0f;

	playerX1 = SCREEN_W / 2.0f;
	playerY1 = SCREEN_H / 2.0f;
}
void easy_deinit() {
	music::stop(0);
	player_deinit();
	flag_deinit();
	avalanche_deinit();

}
void easy_update()
{
	switch (easy_state)
	{
	case 0:
		sprBack1 = sprite_load(L"./Data/Images/map_04.png");

		audio_init();
		player_init();
		flag_init();
		avalanche_init();

		easy_state++;
		/*fallthrough*/

	case 1:
		GameLib::setBlendMode(Blender::BS_ALPHA);

		music::play(0);
		music::setVolume(0, 0.3f);

		easy_state++;
		/*fallthrough*/

	case 2:
		if (hp <= 0)
		{
			nextScene = SCENE_RESULT;
		}

		player_update();
		flag_update();
		avalanche_update();


		game_over();
		judge();
		break;
	}

	scrollValue3 -= 3;

	easy_timer++;
}
void easy_render() {

	sprite_render(sprBack1, 0.0f, scrollValue3); // 背景をカメラの位置に合わせて描画
	sprite_render(sprBack1, 0.0f, 10000.0f + scrollValue3); // 背景をカメラの位置に合わせて描画

	text_out(4, "Down:S Right: D Left: A", 0, 0, 1, 1);
	text_out(0, "score", 1100, 0, 2, 2);
	text_out(0, std::to_string(score1), 1100, 50, 2, 2);
	text_out(0, "combo", 0, 150, 2, 2);
	text_out(0, std::to_string(combo1), 0, 200, 2, 2);

	player_render();
	flag_render();
	avalanche_render();

}
void easy_score()
{
	if (combo1 >= 30)
		comboscore2 = 2.5f;
	else if (combo1 >= 20)
		comboscore2 = 2.0f;
	else if (combo1 >= 10)
		comboscore2 = 1.5f;
	else
		comboscore2 = 1.0f;


	for (int i = 0; i < FLAG_MAX; i++) {
		if (flag[i].moveAlg == -1)
			score1 += 100 * comboscore2;

	}
	combo1++;
}

void easy_clear()
{

}

void easy_over()
{
	if (player.pos.y < 300.0f)
	{
		nextScene = SCENE_RESULT;
	}
}
