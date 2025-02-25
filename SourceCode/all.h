//インクルードガード
#ifndef ALL_H
#define ALL_H

//必要なファイルのインクルード
#include "../GameLib/game_lib.h"

#include "common.h"
#include "audio.h"

#include "obj2d.h"
#include "player.h"
#include "enemy.h"
#include "goal.h"
#include "avalanche.h"
#include "obstacle.h"
#include "flag.h"
#include "judge.h"

#include "scene_game.h"
#include "scene_game_E.h"
#include "scene_game_N.h"

#include "scene_game_T.h"
#include "scene_title.h"
#include "scene_result.h"
#include "scene_result_over.h"
#include "senntaku.h"


using namespace GameLib;// using ディレクティブ
using namespace input;

//インクルードガード終了
#endif//ALL_H