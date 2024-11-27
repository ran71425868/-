#include "all.h"

int result_over_state;
int result_over_timer;

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
		////////‰Šúİ’è////////

		audio_init();
		result_over_state++;
		/*fallthrough*/

	case 1:
		//////// ƒpƒ‰ƒ[ƒ^‚Ìİ’è ////////
		GameLib::setBlendMode(Blender::BS_ALPHA);
		sound::play(XWB_SYSTEM, XWB_SYSTEM_DONPATU);

		music::play(8);
		music::setVolume(8, 0.5f);
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
	
	text_out(4, "score", 490, 250, 3, 3);
	text_out(0, std::to_string(score), 570, 320, 3, 3);

	if (result_over_timer / 32 % 2 == 1) {
		text_out(4, "Push Enter Key", 500, 500, 2, 2, 1, 1, 1);
	}
}
