#include "stdafx.h"
#include "SoundManage.h"
#include "Game.h"
#include "Player.h"

SoundManage::SoundManage()
{
	
}

SoundManage::~SoundManage()
{
	DeleteGO(m_gameBGM);
	DeleteGO(m_customizeBGM);
	DeleteGO(m_bossBGM);
}

bool SoundManage::Start()
{
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");

	//BGN�̏����ݒ�
	SetUp();
	
	return true;
}

void SoundManage::Update()
{
	//�Q�[������BGM�Đ�
	if (m_player->game_state == 0 && m_gameBGM->IsPlaying()!=true)
	{
		m_gameBGM->Play(true);
	}
}

void SoundManage::SetUp()
{
	//�쐬
	m_gameBGM = NewGO<SoundSource>(0);
	m_customizeBGM = NewGO<SoundSource>(0);
	m_bossBGM = NewGO<SoundSource>(0);

	//������
	m_gameBGM->Init(enGameBGM);
	m_gameBGM->SetVolume(0.5f * m_game->BGMvol);	//���ʒ���
	m_customizeBGM->Init(enCustomizeBGM);
	m_customizeBGM->SetVolume(0.5f * m_game->BGMvol);	//���ʒ���
	m_bossBGM->Init(enBossBGM);
	m_bossBGM->SetVolume(0.5f * m_game->BGMvol);	//���ʒ���
}