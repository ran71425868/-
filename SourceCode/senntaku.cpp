#include "all.h"

int senntaku_state;
int senntaku_timer;

Sprite* sprSenntaku;
Sprite* sprHard;
Sprite* sprEasy;
Sprite* sprNormal;
Sprite* sprTutorial;
Sprite* sprT;
Sprite* sprY;
Sprite* sprU;
Sprite* sprI;
Sprite* sprHard1;
Sprite* sprEasy1;
Sprite* sprNormal1;

void senntaku_init() {
	senntaku_state = 0;
	senntaku_timer = 0;
}
void senntaku_deinit() {
	music::stop(2);

}
void senntaku_update() {
	switch (senntaku_state) {
	case 0:
		//////// èâä˙ê›íË ////////

		audio_init();
		sprSenntaku = sprite_load(L"./Data/Images/map_01.png");
		sprHard = sprite_load(L"./Data/Images/Hard.png");
		sprEasy = sprite_load(L"./Data/Images/Easy.png");
		sprNormal = sprite_load(L"./Data/Images/Normal.png");
		sprTutorial = sprite_load(L"./Data/Images/Tutorial.png");
		sprT = sprite_load(L"./Data/Images/T.png");
		sprY = sprite_load(L"./Data/Images/Y.png");
		sprU = sprite_load(L"./Data/Images/U.png");
		sprI = sprite_load(L"./Data/Images/I.png");
		sprHard1 = sprite_load(L"./Data/Images/Hard1.png");
		sprEasy1 = sprite_load(L"./Data/Images/Easy1.png");
		sprNormal1 = sprite_load(L"./Data/Images/Normal1.png");
		senntaku_state++;
		/*fallthrough*/

	case 1:
		//////// ÉpÉâÉÅÅ[É^ÇÃê›íË ////////
		GameLib::setBlendMode(Blender::BS_ALPHA);
		music::play(2);
		music::setVolume(2, 0.5f);
		senntaku_state++;
		/*fallthrough*/

	case 2:
		//////// í èÌéû ////////
		if (TRG(0) & PAD_L2) {
			nextScene4 = SCENE_EASY;
			break;
		}
		else if (TRG(0) & PAD_L3) {
			nextScene3 = SCENE_NORMAL;
			break;
		}
		else if (TRG(0) & PAD_R1) {
			nextScene2 = SCENE_GAME;
			break;
		}
		else if (TRG(0) & PAD_L1) {
			nextScene5 = SCENE_TUTORIAL;
			break;
		}

		else if (TRG(0) & PAD_SELECT) {
			nextScene = SCENE_TITLE;
			break;
		}

		break;
	}



	senntaku_timer++;
}
void senntaku_render() {
	GameLib::clear(0, 0, 0);
	

	sprite_render(sprSenntaku, 0, 0, 1.0f, 1.0f);

	sprite_render(sprTutorial, SCREEN_W / 2.0f-100, 200, 1.0f, 1.0f);

	sprite_render(sprHard,1400,500,1.0f,1.0f);
	sprite_render(sprNormal , SCREEN_W/2.0f-100, 500, 1.0f, 1.0f);
	sprite_render(sprEasy , SCREEN_W / 2.0f - 600, 500, 0.65f, 0.65f);
	
	sprite_render(sprHard1, 1390, 750, 1.0f, 1.0f);
	sprite_render(sprNormal1, SCREEN_W / 2.0f - 110, 750, 1.0f, 1.0f);
	sprite_render(sprEasy1, SCREEN_W / 2.0f - 670, 750, 1.0f, 1.0f);

	if (senntaku_timer / 32 % 2 == 1) {
		sprite_render(sprY, SCREEN_W / 2.0f - 640, 600, 1.0f, 1.0f);
		sprite_render(sprU, SCREEN_W / 2.0f - 100, 600, 1.0f, 1.0f);
		sprite_render(sprI, 1400, 600, 1.0f, 1.0f);
		sprite_render(sprT, SCREEN_W / 2.0f-100, 300, 1.0f, 1.0f);
	}
	/*if (senntaku_timer / 32 % 2 == 1) {
		text_out(4, "Push Enter Key", 350, 450, 2, 2, 1, 1, 1);
	}*/
}