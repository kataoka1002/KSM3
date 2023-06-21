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
	//探す
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");

	//BGNの初期設定
	SetUp();
	
	return true;
}

void SoundManage::Update()
{
	//ポーズ画面またはプレイヤーが死んでいるとき
	if (m_player->GetGameState() == PAUSE_NUM || m_player->GetPlayerDead() == true)
	{

		//ゲームBGMストップ
		m_gameBGM->Stop();

		//ボスBGMストップ
		m_bossBGM->Stop();

		return;
	}

	
	if (m_player->GetBossState() == 1 && m_bossBGM->IsPlaying() != true)
	{

		//ボス戦のBGM再生
		m_bossBGM->Play(true);
		
		//ゲームBGMは止める
		m_gameBGM->Stop();	

		return;
	}


	//ボス戦じゃないなら
	if (m_gameBGM->IsPlaying() != true && m_player->GetBossState() != 1) 
	{

		//ゲーム中またはポーズ画面の時
		if (m_player->GetGameState() == MAIN_GAME_NUM || m_player->GetGameState() == PAUSE_NUM)
		{
			
			//ゲーム中のBGM再生
			m_gameBGM->Play(true);
			
			//カスタムBGMは止める
			m_customizeBGM->Stop();	

		}
	}

	//カスタマイズ画面中
	if (m_player->GetGameState() == CUSTOMIZE_NUM && m_customizeBGM->IsPlaying() != true)
	{
		
		//カスタマイズ画面のBGM再生
		m_customizeBGM->Play(true);
		
		//ゲームBGMは止める
		m_gameBGM->Stop();	

	}
}

void SoundManage::SetUp()
{
	//作成
	m_gameBGM = NewGO<SoundSource>(0);
	m_customizeBGM = NewGO<SoundSource>(0);
	m_bossBGM = NewGO<SoundSource>(0);

	//初期化
	m_gameBGM->Init(enGameBGM);
	m_gameBGM->SetVolume(0.5f * m_game->GetBGMVol());		//音量調整
	m_customizeBGM->Init(enCustomizeBGM);
	m_customizeBGM->SetVolume(0.5f * m_game->GetBGMVol());	//音量調整
	m_bossBGM->Init(enBossBGM);
	m_bossBGM->SetVolume(1.0f * m_game->GetBGMVol());		//音量調整
}