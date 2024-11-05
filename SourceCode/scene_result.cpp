#include "all.h"

int result_state;
int result_timer;

Sprite* sprResult;
Sprite* sprClear;

extern int score;

void result_init() {
	result_state = 0;
}

void result_deinit() {

	music::stop(1);
}

void result_update() {
	switch (result_state) {
	case 0:
		////////‰Šúİ’è////////
		sprResult = sprite_load(L"./Data/Images/title_2png.png");
		sprClear = sprite_load(L"./Data/Images/gameclear.png");
		audio_init();
		result_state++;
		/*fallthrough*/

	case 1:
		//////// ƒpƒ‰ƒ[ƒ^‚Ìİ’è ////////
		GameLib::setBlendMode(Blender::BS_ALPHA);
		sound::play(XWB_SYSTEM, XWB_SYSTEM_DONPATU);

		music::play(1);
		music::setVolume(1, 0.5f);
		result_state++;
		/*fallthrough*/

	case 2:
		if (TRG(0) & PAD_START) {
			nextScene = SCENE_TITLE;
			break;
		}
		break;
	}
	result_timer++;
}

void result_render() {
	GameLib::clear(0, 0, 2);
	sprite_render(sprResult, 0, 0);
	sprite_render(sprClear, 0, 0);

	text_out(4, "score", 490, 250, 3, 3);
	text_out(0, std::to_string(score), 570, 320, 3, 3);

	if (result_timer / 32 % 2 == 1) {
		text_out(4, "Push Enter Key", 500, 500, 2, 2, 1, 1, 1);
	}
}