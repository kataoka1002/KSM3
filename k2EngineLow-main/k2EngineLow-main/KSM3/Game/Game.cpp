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
#include "Game_UI.h"
#include "Enemy_HP_UI.h"
#include "Fade.h"




bool Game::Start()
{
	//エフェクトの設定
	EffectEngine::GetInstance()->ResistEffect(enSunabokori, u"Assets/effect/enemy/sunabokori2.efk");
	EffectEngine::GetInstance()->ResistEffect(enMasinganHibana, u"Assets/effect/enemy/masinganHibana.efk");
	EffectEngine::GetInstance()->ResistEffect(enHidan, u"Assets/effect/enemy/hidan.efk");

	//サウンドの設定
	g_soundEngine->ResistWaveFileBank(enRunning, "Assets/audio/enemy/enemyRunning.wav");
	g_soundEngine->ResistWaveFileBank(enMachineGun, "Assets/audio/enemy/masinganHassya.wav");
	g_soundEngine->ResistWaveFileBank(enGigatonCannon, "Assets/audio/enemy/cannon.wav");
	g_soundEngine->ResistWaveFileBank(enButtleShipGun, "Assets/audio/enemy/buttleShipAttack.wav");



	//m_spriteRender.Init("Assets/modelData/utc_nomal.DDS", 100.0f, 100.0f);
	//m_spriteRender.SetPosition({ -600.0f,300.0f,0.0f });

	
	//m_modelRender.Init("Assets/modelData/test_player.tkm");

	//m_modelRender.SetPosition(0.0f, 0.0f, 0.0f);

	/*m_levelRender.Init("Assets/level/sample.tkl",
		[&](LevelObjectData2& objData)
		{
			//名前がBox_Moveだったら。
			if (objData.EqualObjectName(L"Box_Move") == true) {

				auto box = NewGO<BoxMove>(0);
				//配置座標、スケール、回転を取得する。
				box->m_position = objData.position;
				box->m_scale = objData.scale;
				box->m_rotation = objData.rotation;
				//後で削除するために、ボックスをプッシュしておく。
				m_boxmoves.push_back(box);

				//trueにすると、レベルの方でモデルが読み込まれない。
				return true;
			}
		});
		*/

	m_fade = FindGO<Fade>("fade");
	m_fade->StartFadeIn();
		
	//m_modelRender.SetRotation(rot);
	//m_modelRender.SetScale(1.0f);
	//m_modelRender.Update();


	return true;
}

Game::Game()
{
	lighting = NewGO<Lighting>(1, "lighting");
	player = NewGO<Player>(2, "player");

	
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



	boss = NewGO<Boss>(1, "boss");//15100
	boss->boss_position = { 0.0f,0.0f,5100.0f };
	

	drop_item = NewGO< Drop_item>(1, "drop_item");
	background = NewGO< BackGround>(1, "background");

	gamecamera = NewGO<GameCamera>(1, "gamecamera");
	core_weapons = NewGO<Core_weapons>(2, "core_weapons");
	game_ui = NewGO<Game_UI>(0, "game_ui");
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

	DeleteGO(player);
	DeleteGO(boss);

	if (drop_item->GetState == false) {
		DeleteGO(drop_item);
	}
	DeleteGO(background);

	DeleteGO(gamecamera);
	DeleteGO(game_ui);
	DeleteGO(e_h_ui);
}

void Game::Update()
{

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
		if (m_isWaitFadeout)
		{
			if (!m_fade->IsFade())
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

	//m_modelRender.Update();
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
	//m_modelRender.Draw(rc);
	//m_spriteRender.Draw(rc);

	//m_fontRender.Draw(rc);
}