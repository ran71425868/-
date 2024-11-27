#include "all.h"

int title_state;
int title_timer;

Sprite* sprTitle;
Sprite* sprTitle_name;
Sprite* sprEnter;

void title_init() {
	title_state = 0;
	title_timer = 0;
}
void title_deinit() {
	music::stop(2);

}
void title_update() {
	switch (title_state) {
	case 0:
		//////// ‰Šúİ’è ////////

		audio_init();
		sprTitle = sprite_load(L"./Data/Images/title_a.png");
		sprEnter = sprite_load(L"./Data/Images/Push.png");
		sprTitle_name= sprite_load(L"./Data/Images/title_name.png");
		title_state++;
		/*fallthrough*/

	case 1:
		//////// ƒpƒ‰ƒ[ƒ^‚Ìİ’è ////////
		GameLib::setBlendMode(Blender::BS_ALPHA);
		music::play(2);
		music::setVolume(2, 0.5f);
		title_state++;
		/*fallthrough*/

	case 2:
		//////// ’Êí ////////
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
	sprite_render(sprTitle, 0,0,1.0f,1.0f);
	sprite_render(sprTitle_name, 100,700,1.5f,1.5f);

	/*GameLib::text_out(3, "repel it", 225, 80, 5, 5, 1, 1, 0);
	GameLib::text_out(3, "the aliens", 404, 180, 5, 5, 1, 1, 0);*/

	if (title_timer / 32 % 2 == 1) 
	{
		sprite_render(sprEnter, 350, 850, 2, 2);
	}
}