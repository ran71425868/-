#include "all.h"

int result_over_state;
int result_over_timer;

Sprite* sprGame_over;

extern int score;

void result_over_init()
{
	result_over_state = 0;
}

void result_over_deinit()
{
	music::stop(1);
}

void result_over_update()
{
	switch (result_over_state) {
	case 0:
		////////初期設定////////
		sprGame_over = sprite_load(L"./Data/Images/GameOver.png");

		audio_init();
		result_over_state++;
		/*fallthrough*/

	case 1:
		//////// パラメータの設定 ////////
		GameLib::setBlendMode(Blender::BS_ALPHA);

		music::play(10);
		music::setVolume(10, 0.5f);
		result_over_state++;
		/*fallthrough*/

	case 2:
		if (TRG(0) & PAD_START) {
			nextScene = SCENE_TITLE;
			break;
		}
		break;
	}
	result_over_timer++;
}

void result_over_render()
{
	GameLib::clear(0, 0, 0);
	sprite_render(sprGame_over, 680, 50);
	
	text_out(4, "Score", 750, 200, 4, 4);
	text_out(0, std::to_string(score), 900, 300, 3, 3);

	if (result_over_timer / 32 % 2 == 1) {
		text_out(4, "Push Enter Key", 700, 500, 2, 2, 1, 1, 1);
	}
}
