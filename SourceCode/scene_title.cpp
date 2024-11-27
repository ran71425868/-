#include "all.h"

int title_state;
int title_timer;

int title_flag;
int title_second;

Sprite* sprTitle1;
Sprite* sprTitle2;
Sprite* sprTitle_name;

void title_init() {
	title_state = 0;
	title_timer = 0;
	title_flag = 0;
	title_second = 2;
}
void title_deinit() {
	music::stop(2);

}
void title_update() {
	switch (title_state) {
	case 0:
		//////// ‰ŠúÝ’è ////////

		audio_init();
		sprTitle1 = sprite_load(L"./Data/Images/title_a.png");
		sprTitle2 = sprite_load(L"./Data/Images/title_b.png");
		sprTitle_name = sprite_load(L"./Data/Images/title_name.png");
		title_state++;
		/*fallthrough*/

	case 1:
		//////// ƒpƒ‰ƒ[ƒ^‚ÌÝ’è ////////
		GameLib::setBlendMode(Blender::BS_ALPHA);
		music::play(2);
		music::setVolume(2, 0.5f);
		title_state++;
		/*fallthrough*/

	case 2:
		//////// ’ÊíŽž ////////
		if (TRG(0) & PAD_START) {
			nextScene = SCENE_SENNTAKU;
			break;
		}

		break;
	}



	title_timer++;
}
void title_render() {
	GameLib::clear(0, 0, 0);

	if (title_flag == 0) {
		sprite_render(sprTitle1, 0, 0, 1.0f, 1.0f);
	}
	else if (title_flag == 1) {
		sprite_render(sprTitle2, 0, 0, 1.0f, 1.0f);

	}

	while (1) {
		if (title_timer % 100 == 0)
		{
			title_second--;
			if (title_second >= 0) {
				title_flag = 1;
			}
			else if (title_second <= 0) {
				title_flag = 0;
				title_second = 1;
			}
		}
		
		break;
	}

	sprite_render(sprTitle_name, 200, 200, 3.0f, 3.0f);
	
	if (title_timer / 32 % 2 == 1) {
		text_out(4, "Push Enter Key", 960, 720, 2, 2, 1, 1, 1);
	}
	
}