#include "stdafx.h"
#include "Game.h"
#include "BoxMove.h"
#include "Player.h"
#include "Title.h"
#include "Result.h"
#include "Lighting.h"
#include "Enemy_Near.h"
#include "Enemy.h"
#include "Enemy_Far.h"
#include "Left_arm_weapons.h"
#include "Drop_item.h"
#include "BackGround.h"
#include "Core_weapons.h"
#include "GameCamera.h"
#include "Boss.h"
#include "Boss_Riser.h"
#include "Game_UI.h"
#include "Enemy_HP_UI.h"
#include "SoundManage.h"
#include <time.h>
#include <stdlib.h>
#include "PlayerUI.h"
//#include "Fade.h"
#include "Wave.h"
#include "Customize_UI_ver2.h"
#include "SkyCube.h"


Game::Game()
{
	//ライトの作成
	lighting = NewGO<Lighting>(1, "lighting");

	//プレイヤーとコア武器とUIの作成
	player = NewGO<Player>(1, "player");
	core_weapons = NewGO<Core_weapons>(1, "core_weapons");
	m_playerUI = NewGO<PlayerUI>(1,"playerui");

	//ステージの作成
	background = NewGO< BackGround>(1, "background");

	//ゲームカメラの作成
	gamecamera = NewGO<GameCamera>(1, "gamecamera");
	
	//スカイキューブの作成
	m_skyCube = NewGO<SkyCube>(0, "skycube");
	m_skyCube->SetLuminance(1.0f);
	m_skyCube->SetScale(4000.0f);
	m_skyCube->SetPosition({ 0.0f,40.0f,0.0f });
	m_skyCube->SetType((EnSkyCubeType)enSkyCubeType_DayToon_2);
}

Game::~Game()
{
	DeleteGO(core_weapons);
	DeleteGO(m_playerUI);
	//プッシュしたエネミーを削除していく
	DeleteEnemy();
	//プッシュしたアイテムを削除していく
	for (auto dropItem : m_dropItemObject)
	{
		DeleteGO(dropItem);
	}
	DeleteGO(m_soundManage);
	DeleteGO(m_customizeUI);
	DeleteGO(background);
	DeleteGO(game_ui);
	DeleteGO(m_skyCube);
	DeleteGO(m_wave);
}

bool Game::Start()
{
	//エフェクトの設定
	EffectEngine::GetInstance()->ResistEffect(enSunabokori, u"Assets/effect/enemy/sunabokori2.efk");
	EffectEngine::GetInstance()->ResistEffect(enMasinganHibana, u"Assets/effect/enemy/masinganHibana.efk");
	EffectEngine::GetInstance()->ResistEffect(enHidan, u"Assets/effect/enemy/hidan.efk");
	EffectEngine::GetInstance()->ResistEffect(enTyakudan, u"Assets/effect/enemy/bulletTyakudan.efk");
	EffectEngine::GetInstance()->ResistEffect(enEnemyDead, u"Assets/effect/enemy/enemyBakuha.efk");
	EffectEngine::GetInstance()->ResistEffect(enSenkanhouKemuri, u"Assets/effect/enemy/senkahouKemuri.efk");
	EffectEngine::GetInstance()->ResistEffect(enMasinganKemuri, u"Assets/effect/enemy/masinganKemuri.efk");
	EffectEngine::GetInstance()->ResistEffect(enGigatonAttack, u"Assets/effect/enemy/gigatonAttack.efk");


	//サウンドの設定
	g_soundEngine->ResistWaveFileBank(enRunning, "Assets/audio/enemy/enemyRunning.wav");
	g_soundEngine->ResistWaveFileBank(enDash, "Assets/audio/enemy/enemyDash.wav");
	g_soundEngine->ResistWaveFileBank(enMachineGun, "Assets/audio/enemy/masinganHassya.wav");
	g_soundEngine->ResistWaveFileBank(enGigatonCannon, "Assets/audio/enemy/cannon.wav");
	g_soundEngine->ResistWaveFileBank(enButtleShipGun, "Assets/audio/enemy/buttleShipAttack.wav");
	g_soundEngine->ResistWaveFileBank(enEnemyDeadSE, "Assets/audio/enemy/enemyDead.wav");
	g_soundEngine->ResistWaveFileBank(enButtleShipTyakudan, "Assets/audio/enemy/buttleShipTyakudan.wav");
	g_soundEngine->ResistWaveFileBank(enPlayerRun, "Assets/audio/player/playerRun.wav");
	g_soundEngine->ResistWaveFileBank(enGameBGM, "Assets/audio/BGM/game_bgm.wav");
	g_soundEngine->ResistWaveFileBank(enBossBGM, "Assets/audio/BGM/last_boss_bgm.wav");
	g_soundEngine->ResistWaveFileBank(enCustomizeBGM, "Assets/audio/BGM/Customize_bgm.wav");
	g_soundEngine->ResistWaveFileBank(enKetteiSE, "Assets/audio/ketteion.wav");
	g_soundEngine->ResistWaveFileBank(enCancelSE, "Assets/audio/cancelon.wav");
	g_soundEngine->ResistWaveFileBank(enSentakuIdouSE, "Assets/audio/sentakuidouon.wav");
	g_soundEngine->ResistWaveFileBank(enSoutyakuSE, "Assets/audio/soutyakuon.wav");
	g_soundEngine->ResistWaveFileBank(enByuSE, "Assets/audio/byu.wav");
	g_soundEngine->ResistWaveFileBank(enPlayerDead, "Assets/audio/player/playerDead.wav");

	//m_fade = FindGO<Fade>("fade");
	//m_fade->StartFadeIn();

	//効果音の大きさをセーブする
	SaveSEvol = SEvol;
		
	return true;
}

void Game::Update()
{
	if (g_pad[0]->IsTrigger(enButtonY))
	{
		g_renderingEngine->SetGrayScale(true);
	}

	//最初のシーン中
	if (player->game_state == 4)
	{
		TitleToGame();
	}

	//最初のシーンじゃなかったら
	if (player->game_state != 4)
	{
		GameNow();
	}
}

void Game::SetUp()
{
	//BGMの作成
	m_soundManage = NewGO<SoundManage>(1, "soundmanage");

	//エネミーの生成
	MakeEnemy();

	//カスタム画面の作成
	m_customizeUI = NewGO<Customize_UI_ver2>(1, "customize_ui_ver2");

	//ウェーブ管理のクラス作成
	m_wave = NewGO<Wave>(1, "wave");
}

void Game::MakeEnemy()
{
	//エネミーを複数体生成
	for (int i = 0; i < 4; i++)
	{
		Enemy* enemy = NewGO<Enemy>(1, "enemy");
		enemy->m_enemyPosition = RandomPosition();

		m_enemyObject.push_back(enemy);
	}
	for (int i = 0; i < 4; i++)
	{
		Enemy_Far* enemyFar = NewGO<Enemy_Far>(1, "enemy_far");
		enemyFar->m_enemyPosition = RandomPosition();

		m_enemyFarObject.push_back(enemyFar);
	}
	for (int i = 0; i < 2; i++)
	{
		Enemy_Near* enemyNear = NewGO<Enemy_Near>(1, "enemy_near");
		enemyNear->m_enemyPosition = RandomPosition();

		m_enemyNearObject.push_back(enemyNear);
	}
}

void Game::DeleteEnemy()
{
	for (auto enemy : m_enemyObject)
	{
		DeleteGO(enemy);
	}
	for (auto enemyFar : m_enemyFarObject)
	{
		DeleteGO(enemyFar);
	}
	for (auto enemyNear : m_enemyNearObject)
	{
		DeleteGO(enemyNear);
	}
}

void Game::TitleToGame()
{

}

void Game::GameNow()
{
	//敵の全滅コマンド
	if (g_pad[0]->IsTrigger(enButtonX))
	{
		
	}

	//3ウェーブ突破したらボス戦
	if (player->player_position.z >= 9550.0f  && boss == nullptr && m_wave->m_goBoss == true)
	{
		//スカイキューブを作り直す
		DeleteGO(m_skyCube);
		m_skyCube = NewGO<SkyCube>(0, "skycube");
		m_skyCube->SetLuminance(1.0f);
		m_skyCube->SetScale(4000.0f);
		m_skyCube->SetPosition({ 0.0f,40.0f,0.0f });
		m_skyCube->SetType((EnSkyCubeType)enSkyCubeType_Wild_Night);

		player->bossState = 1;

		//ボスを発生させる
		boss = NewGO<Boss>(1, "boss");
		boss->boss_position = { -19800.0f,0.0f,7800.0f };	
		//プレイヤーの場所をボスの場所へ移動させる
		player->player_position = { -19246.0f,0.0f,-130.0f };
		player->player_modelRender.SetPosition(player->player_position);
		player->characterController.SetPosition(player->player_position);
		gamecamera->m_springCamera.Refresh();
		player->player_modelRender.Update(true);

		//今いる雑魚敵を全部消す
		DeleteEnemy();
	}

	if (boss != nullptr)
	{
		if (player->boss_survival == true)
		{
			
		}
	}

	//if (m_gameState == enGameState_GameClear_Idle)
//	{
		//if (m_isWaitFadeout)
	{
		//if (!m_fade->IsFade())
		{
			if (player->game_end_state == 1)
			{
				title = NewGO<Title>(1, "title");
				DeleteGO(this);
			}
		}
	}
	//		else
	//		{
	//			if (g_pad[0]->IsTrigger(enButtonA))
	//			{
	//				m_isWaitFadeout = true;
	//				m_fade->StartFadeOut();
	//			}
	//		}
	//		return;
	//	}

	//m_spriteRender.Update();

	//リザルトへの遷移
	if (g_pad[0]->IsTrigger(enButtonSelect)) {
		result = NewGO<Result>(1, "result");
		DeleteGO(this);
	}
}

Vector3 Game::RandomPosition()
{
	Vector3 m_pos;

	//ランダムにポジションを当てはめる
	m_pos.x = rand() % 4800 - 2400;
	m_pos.y = 0.0f;
	m_pos.z = rand() % 9000;

	return m_pos;
}

void Game::Render(RenderContext& rc)
{
	
}