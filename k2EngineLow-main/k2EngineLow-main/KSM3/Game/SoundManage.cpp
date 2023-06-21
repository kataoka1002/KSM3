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
	//�T��
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");

	//BGN�̏����ݒ�
	SetUp();
	
	return true;
}

void SoundManage::Update()
{
	//�|�[�Y��ʂ܂��̓v���C���[������ł���Ƃ�
	if (m_player->GetGameState() == PAUSE_NUM || m_player->GetPlayerDead() == true)
	{

		//�Q�[��BGM�X�g�b�v
		m_gameBGM->Stop();

		//�{�XBGM�X�g�b�v
		m_bossBGM->Stop();

		return;
	}

	
	if (m_player->GetBossState() == 1 && m_bossBGM->IsPlaying() != true)
	{

		//�{�X���BGM�Đ�
		m_bossBGM->Play(true);
		
		//�Q�[��BGM�͎~�߂�
		m_gameBGM->Stop();	

		return;
	}


	//�{�X�킶��Ȃ��Ȃ�
	if (m_gameBGM->IsPlaying() != true && m_player->GetBossState() != 1) 
	{

		//�Q�[�����܂��̓|�[�Y��ʂ̎�
		if (m_player->GetGameState() == MAIN_GAME_NUM || m_player->GetGameState() == PAUSE_NUM)
		{
			
			//�Q�[������BGM�Đ�
			m_gameBGM->Play(true);
			
			//�J�X�^��BGM�͎~�߂�
			m_customizeBGM->Stop();	

		}
	}

	//�J�X�^�}�C�Y��ʒ�
	if (m_player->GetGameState() == CUSTOMIZE_NUM && m_customizeBGM->IsPlaying() != true)
	{
		
		//�J�X�^�}�C�Y��ʂ�BGM�Đ�
		m_customizeBGM->Play(true);
		
		//�Q�[��BGM�͎~�߂�
		m_gameBGM->Stop();	

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