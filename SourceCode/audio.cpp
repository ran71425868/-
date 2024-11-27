#include "all.h"

//--------------------------------------
//  オーディオの初期設定
//--------------------------------------
void audio_init()
{
    // 音楽の読み込み
    music::load(0, L"./Data/Musics/Dark_fantasy.wav");
    music::load(1, L"./Data/Musics/SuperGazer.wav");
    music::load(2, L"./Data/Musics/TVVC3577.wav");
    music::load(3, L"./Data/Musics/4.wav");
    music::load(4, L"./Data/Musics/23.wav");
    music::load(5, L"./Data/Musics/49.wav");
    music::load(6, L"./Data/Musics/6.wav");
    music::load(7, L"./Data/Musics/1234.wav");
   

    sound::load(XWB_SYSTEM, L"./Data/Sounds/system.xwb");    // システム音

}

//--------------------------------------
//  オーディオの終了処理
//--------------------------------------
void audio_deinit()
{
    // 音楽を全て解放
    music::clear();
}
