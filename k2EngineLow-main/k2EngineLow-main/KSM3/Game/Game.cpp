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
#include <time.h>
#include <stdlib.h>

//#include "Fade.h"

#include "Customize_UI_ver2.h"


Game::Game()
{
	//ライトの作成
	lighting = NewGO<Lighting>(1, "lighting");

	//プレイヤーの作成
	player = NewGO<Player>(1, "player");


	
	//エネミーを複数体生成
	for (int i = 0; i < 1; i++)
	{
		Enemy* enemy = NewGO<Enemy>(1, "enemy");
		enemy->m_enemyPosition = { 0.0f,0.0f,3000.0f };
		
		m_enemyObject.push_back(enemy);
	}
	for (int i = 0; i < 1; i++)
	{
		Enemy_Far* enemyFar = NewGO<Enemy_Far>(1, "enemy_far");
		enemyFar->m_enemyPosition = { 0.0f,0.0f,4000.0f };

		m_enemyFarObject.push_back(enemyFar);
	}
	for (int i = 0; i < 1; i++)
	{
		Enemy_Near* enemyNear = NewGO<Enemy_Near>(1, "enemy_near");
		enemyNear->m_enemyPosition = { 0.0f,0.0f,2000.0f };

		m_enemyNearObject.push_back(enemyNear);
	}

	/*for (int i = 0; i < 1; i++)
	{
		Boss_Riser* boss_riser = NewGO<Boss_Riser>(1, "boss_riser");
		boss_riser->b_w_position = boss_riser->b_w_localposition;
	}*/


	//boss = NewGO<Boss>(1, "boss");//15100
	//boss->boss_position = { 0.0f,0.0f,15100.0f };


	//drop_item = NewGO< Drop_item>(1, "drop_item");
	background = NewGO< BackGround>(1, "background");

	gamecamera = NewGO<GameCamera>(1, "gamecamera");
	core_weapons = NewGO<Core_weapons>(2, "core_weapons");
	game_ui = NewGO<Game_UI>(0, "game_ui");

	//カスタム画面の作成
	m_customizeUI = NewGO<Customize_UI_ver2>(1, "customize_ui_ver2");


	//e_h_ui = NewGO<Enemy_HP_UI>(1 , "enemy_hp_ui");
}

Game::~Game()
{
	//プッシュしたボックスを削除していく
	for (auto box : m_boxmoves)
	{
		DeleteGO(box);
	}
	//プッシュしたエネミーを削除していく
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

	
	DeleteGO(boss);
	
	

	DeleteGO(player);

	//プッシュしたアイテムを削除していく
	for (auto dropItem : m_dropItemObject)
	{
		DeleteGO(dropItem);
	}

	DeleteGO(player);
	DeleteGO(m_customizeUI);


	/*if (drop_item->GetState == false) {
		DeleteGO(drop_item);
	}*/
	DeleteGO(background);

	DeleteGO(gamecamera);
	DeleteGO(game_ui);
	DeleteGO(e_h_ui);
}

bool Game::Start()
{
	//エフェクトの設定
	EffectEngine::GetInstance()->ResistEffect(enSunabokori, u"Assets/effect/enemy/sunabokori2.efk");
	EffectEngine::GetInstance()->ResistEffect(enMasinganHibana, u"Assets/effect/enemy/masinganHibana.efk");
	EffectEngine::GetInstance()->ResistEffect(enHidan, u"Assets/effect/enemy/hidan.efk");
	EffectEngine::GetInstance()->ResistEffect(enTyakudan, u"Assets/effect/enemy/bulletTyakudan.efk");
	EffectEngine::GetInstance()->ResistEffect(enEnemyDead, u"Assets/effect/enemy/enemyBakuha.efk");


	//サウンドの設定
	g_soundEngine->ResistWaveFileBank(enRunning, "Assets/audio/enemy/enemyRunning.wav");
	g_soundEngine->ResistWaveFileBank(enDash, "Assets/audio/enemy/enemyDash.wav");
	g_soundEngine->ResistWaveFileBank(enMachineGun, "Assets/audio/enemy/masinganHassya.wav");
	g_soundEngine->ResistWaveFileBank(enGigatonCannon, "Assets/audio/enemy/cannon.wav");
	g_soundEngine->ResistWaveFileBank(enButtleShipGun, "Assets/audio/enemy/buttleShipAttack.wav");
	g_soundEngine->ResistWaveFileBank(enEnemyDeadSE, "Assets/audio/enemy/enemyDead.wav");



	//m_fade = FindGO<Fade>("fade");
	//m_fade->StartFadeIn();
		
	return true;
}

void Game::Update()
{
	//敵を10体以上殺したらボス戦
	if (player->killEnemy >= 10 && boss == nullptr)
	{
		for (int i = 0; i < 1; i++)
		{
			boss = NewGO<Boss>(1, "boss");
			boss->boss_position = { 0.0f,0.0f,15100.0f };
		}
	}
	if (boss != nullptr) {
		if (player->boss_survival == true) {
			boss_time += g_gameTime->GetFrameDeltaTime();
			boss_time_score += g_gameTime->GetFrameDeltaTime();
			if (boss_time_score >= 1.0f) {
				time_score -= 150;
				boss_time_score = 0.0f;
			}
		}
	}

	//wchar_t wcsbuf[256];
	//swprintf_s(wcsbuf, 256, L"%d秒経過!!", int(m_timer));
	//表示するテキストを設定。
	m_fontRender.SetText(L"あいうえお\n");
	//フォントの位置を設定。
	m_fontRender.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender.SetScale(2.0f);
	//フォントの色を設定。
	m_fontRender.SetColor({ 1.0f,0.0f,0.0f,1.0f });
	m_timer += g_gameTime->GetFrameDeltaTime();

	//m_modelRender.PlayAnimation(enAnimClip_Idle);

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

	m_spriteRender.Update();

	//enemy->enemy_game_state = player->game_state;
	//enemy->enemy_position = player->player_position;

	//pause画面からタイトルへの遷移
	/*if (player->game_end_state == 1) {
		title = NewGO<Title>(1, "title");
		DeleteGO(this);
	}*/

	//リザルトへの遷移
	if (g_pad[0]->IsTrigger(enButtonSelect)) {
		result = NewGO<Result>(1, "result");
		DeleteGO(this);
	}
}

void Game::Render(RenderContext& rc)
{
	
}