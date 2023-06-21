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
	if (m_player->GetGameState() == PAUSE_NUM || m_player->GetPlayerDead() == true)
	{
		m_gameBGM->Stop();
		m_bossBGM->Stop();
		return;
	}

	//�{�X���BGM�Đ�
	if (m_player->GetBossState() == 1 && m_bossBGM->IsPlaying() != true)
	{
		m_bossBGM->Play(true);
		m_gameBGM->Stop();	//�Q�[��BGM�͎~�߂�

		return;
	}

	//�Q�[������BGM�Đ�
	if (m_gameBGM->IsPlaying() != true && m_player->GetBossState() != 1) //�{�X�킶��Ȃ��Ȃ�
	{
		if (m_player->GetGameState() == MAIN_GAME_NUM || m_player->GetGameState() == PAUSE_NUM)
		{
			m_gameBGM->Play(true);
			m_customizeBGM->Stop();	//�J�X�^��BGM�͎~�߂�
		}
	}

	//�J�X�^�}�C�Y��ʂ�BGM�Đ�
	if (m_player->GetGameState() == CUSTOMIZE_NUM && m_customizeBGM->IsPlaying() != true)
	{
		m_customizeBGM->Play(true);
		m_gameBGM->Stop();	//�Q�[��BGM�͎~�߂�
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
	m_gameBGM->SetVolume(0.5f * m_game->GetBGMVol());		//���ʒ���
	m_customizeBGM->Init(enCustomizeBGM);
	m_customizeBGM->SetVolume(0.5f * m_game->GetBGMVol());	//���ʒ���
	m_bossBGM->Init(enBossBGM);
	m_bossBGM->SetVolume(1.0f * m_game->GetBGMVol());		//���ʒ���
}