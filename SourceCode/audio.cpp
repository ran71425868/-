#include "all.h"

//--------------------------------------
//  �I�[�f�B�I�̏����ݒ�
//--------------------------------------
void audio_init()
{
    // ���y�̓ǂݍ���
    music::load(0, L"./Data/Musics/Dark_fantasy.wav");
    music::load(1, L"./Data/Musics/SuperGazer.wav");
    music::load(2, L"./Data/Musics/TVVC3577.wav");
    music::load(3, L"./Data/Musics/4.wav");
    music::load(4, L"./Data/Musics/23.wav");
    music::load(5, L"./Data/Musics/49.wav");
    music::load(6, L"./Data/Musics/6.wav");
    music::load(7, L"./Data/Musics/1234.wav");
   

    sound::load(XWB_SYSTEM, L"./Data/Sounds/system.xwb");    // �V�X�e����

}

//--------------------------------------
//  �I�[�f�B�I�̏I������
//--------------------------------------
void audio_deinit()
{
    // ���y��S�ĉ��
    music::clear();
}
