#include "stdafx.h"
#include "Game.h"
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
#include "Enemy_HP_UI.h"
#include "SoundManage.h"
#include <time.h>
#include <stdlib.h>
#include "PlayerUI.h"
#include "Wave.h"
#include "Customize_UI_ver2.h"
#include "Customize_area.h"
#include "SkyCube.h"
#include "GuideLight.h"
#include "Combo.h"
#include "OPVoice.h"


Game::Game()
{

	//ライトの作成
	m_lighting = NewGO<Lighting>(1, "lighting");


	//ステージの作成
	m_backGround = NewGO< BackGround>(1, "background");


	//カスタマイズエリアの生成
	m_customizeArea = NewGO<Customize_area>(1, "customize_area");


	//ゲームカメラの作成
	m_gameCamera = NewGO<GameCamera>(1, "gamecamera");

	
	//スカイキューブの作成
	m_skyCube = NewGO<SkyCube>(0, "skycube");
	m_skyCube->SetLuminance(1.0f);
	m_skyCube->SetScale(4000.0f);
	m_skyCube->SetPosition({ 0.0f,40.0f,0.0f });
	m_skyCube->SetType((EnSkyCubeType)enSkyCubeType_DayToon_2);


	//オープニングボイスの生成
	OPVoice* m_voice = NewGO<OPVoice>(1, "opvoice");

}

Game::~Game()
{

	//エネミーを削除
	DeleteEnemy();


	//プッシュしたアイテムを削除していく
	for (auto dropItem : m_dropItemObject)
	{
		DeleteGO(dropItem);

	}


	//削除
	DeleteGO(m_soundManage);
	DeleteGO(m_customizeUI);
	DeleteGO(m_backGround);
	DeleteGO(m_skyCube);
	DeleteGO(m_wave);
	DeleteGO(m_coreWeapon);
	DeleteGO(m_playerUI);
	DeleteGO(m_combo);
	DeleteGO(m_customizeArea);

	//ボスが存在するなら
	if (m_boss != nullptr) 
	{
		DeleteGO(m_boss);
	}

}

bool Game::Start()
{

	//プレイヤーの作成
	m_player = NewGO<Player>(2, "player");
	
	
	//プレイヤーにカラーの情報を渡す
	m_player->SetPlayerColorData(m_playerColorDate);


	//コア武器の作成
	m_coreWeapon = NewGO<Core_weapons>(1, "core_weapons");


	//エフェクトの初期化
	InitEffect();


	//サウンドの初期化
	InitSound();


	//効果音の大きさをセーブする
	m_saveSEvol = m_SEvol;
		

	return true;

}

void Game::InitEffect()
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
	EffectEngine::GetInstance()->ResistEffect(enEnemyHassei, u"Assets/effect/enemy/newGO.efk");
	EffectEngine::GetInstance()->ResistEffect(enBoss_Cannon_Charge, u"Assets/effect/enemy/Boss_cannon.efk");
	EffectEngine::GetInstance()->ResistEffect(enBoss_Cannon_Landing, u"Assets/effect/enemy/Boss_cannon_Landing.efk");
	EffectEngine::GetInstance()->ResistEffect(enBoss_Magic_Circle, u"Assets/effect/enemy/Boss_Magic_Circle.efk");
	EffectEngine::GetInstance()->ResistEffect(enBoss_Cannon_Bullet, u"Assets/effect/enemy/Boss_Cannon_Bullet.efk");
	EffectEngine::GetInstance()->ResistEffect(enGuide, u"Assets/effect/enemy/guide.efk");
	EffectEngine::GetInstance()->ResistEffect(enBoss_Dozar_Charge, u"Assets/effect/enemy/Boss_dozar_Charge.efk");
	EffectEngine::GetInstance()->ResistEffect(enBoss_Dozar_efe, u"Assets/effect/enemy/Boss_dozar.efk");
	EffectEngine::GetInstance()->ResistEffect(enBoss_Dozar_Landing, u"Assets/effect/enemy/Boss_Dozar_Landing2.efk");
	EffectEngine::GetInstance()->ResistEffect(enBoss_Explosion, u"Assets/effect/enemy/Boss_NotCore_Explosion.efk");
	EffectEngine::GetInstance()->ResistEffect(enBoss_Explosion_Another, u"Assets/effect/enemy/Boss_NotCore_Explosion_attack.efk");
	EffectEngine::GetInstance()->ResistEffect(enBoss_Death, u"Assets/effect/enemy/Boss_Explosion.efk");
	EffectEngine::GetInstance()->ResistEffect(enBoss_Death2, u"Assets/effect/enemy/Boss_Explosion2.efk");
	EffectEngine::GetInstance()->ResistEffect(enBoss_Drill, u"Assets/effect/enemy/Boss_Drill_efe.efk");
	EffectEngine::GetInstance()->ResistEffect(enBoss_Drill_Landing, u"Assets/effect/enemy/Boss_Drill_Landing.efk");
	EffectEngine::GetInstance()->ResistEffect(enBoss_Shovel_shock, u"Assets/effect/enemy/Boss_shovel_shock.efk");
	EffectEngine::GetInstance()->ResistEffect(enTatumaki_charge, u"Assets/effect/enemy/Tatumaki_charge.efk");
	EffectEngine::GetInstance()->ResistEffect(enTatumaki_fire, u"Assets/effect/enemy/Tatumaki_fire2.efk");
	EffectEngine::GetInstance()->ResistEffect(enImpact, u"Assets/effect/enemy/impact.efk");
	EffectEngine::GetInstance()->ResistEffect(enSword, u"Assets/effect/enemy/swordEfe.efk");
	EffectEngine::GetInstance()->ResistEffect(enFeatherBall, u"Assets/effect/enemy/featherBall.efk");
	EffectEngine::GetInstance()->ResistEffect(en_Boss_attack, u"Assets/effect/enemy/Boss_attack.efk");
	EffectEngine::GetInstance()->ResistEffect(en_Boss_attack_Explosion, u"Assets/effect/enemy/Boss_attack_Explosion.efk");

}


void Game::InitSound()
{

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
	g_soundEngine->ResistWaveFileBank(enResultBGM, "Assets/audio/BGM/result.wav");
	g_soundEngine->ResistWaveFileBank(enVoice, "Assets/audio/OP/OPvoice.wav");
	g_soundEngine->ResistWaveFileBank(enPutun, "Assets/audio/OP/putun.wav");
	g_soundEngine->ResistWaveFileBank(enTatumaki, "Assets/audio/enemy/Tatumaki2.wav");
	g_soundEngine->ResistWaveFileBank(enBisi, "Assets/audio/enemy/bisi2.wav");
	g_soundEngine->ResistWaveFileBank(enBoss_Shovel_roar, "Assets/audio/Shovel_roar.wav");
	g_soundEngine->ResistWaveFileBank(en_Boss_Drill, "Assets/audio/Drill.wav");
	g_soundEngine->ResistWaveFileBank(enBoss_Cannon_Charge_SE, "Assets/audio/Cannon_Charge.wav");
	g_soundEngine->ResistWaveFileBank(en_Boss_Drill_sonic, "Assets/audio/Drill_sonic.wav");
	g_soundEngine->ResistWaveFileBank(en_Boss_Dozar_Charge_SE, "Assets/audio/Dozar_Charge.wav");
	g_soundEngine->ResistWaveFileBank(en_Boss_Shovel_shock, "Assets/audio/Shovel_shock.wav");
	g_soundEngine->ResistWaveFileBank(en_Boss_cannon_Langing_SE, "Assets/audio/Cannon_Langing.wav");
	g_soundEngine->ResistWaveFileBank(en_Boss_Dozar_Langing_SE, "Assets/audio/Dozar_Langing.wav");
	g_soundEngine->ResistWaveFileBank(en_PushButton, "Assets/audio/pushButton.wav");
}


void Game::Update()
{

	//最初のシーン中
	if (m_player->GetGameState() == 4)
	{

		//タイトルからメインゲームへの遷移時の処理
		TitleToGame();

	}


	//最初のシーンじゃなかったら
	if (m_player->GetGameState() != 4)
	{

		//メインゲーム中の処理
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
	m_wave = NewGO<Wave>(3, "wave");


	//コンボ管理のクラス
	m_combo = NewGO<Combo>(2, "combo");

}

void Game::MakePlayerUI()
{

	//プレイヤーUIの作成
	m_playerUI = NewGO<PlayerUI>(2, "playerui");

}

void Game::MakeEnemy()
{

	//エネミーを複数体生成
	for (int i = 0; i < 4; i++)
	{
		Enemy* enemy = NewGO<Enemy>(1, "enemy");
		enemy->SetPosition(RandomPosition());

		m_enemyObject.push_back(enemy);

		m_numEnemy++;	//エネミーの存在数をプラス
	}


	//遠距離エネミーを複数体生成
	for (int i = 0; i < 4; i++)
	{
		Enemy_Far* enemyFar = NewGO<Enemy_Far>(1, "enemy_far");
		enemyFar->SetPosition(RandomPosition());

		m_enemyFarObject.push_back(enemyFar);

		m_numEnemy++;	//エネミーの存在数をプラス
	}


	//近距離エネミーを複数体生成
	for (int i = 0; i < 2; i++)
	{
		Enemy_Near* enemyNear = NewGO<Enemy_Near>(1, "enemy_near");
		enemyNear->SetPosition(RandomPosition());

		m_enemyNearObject.push_back(enemyNear);

		m_numEnemy++;	//エネミーの存在数をプラス
	}

}

void Game::DeleteEnemy()
{

	//プッシュしたエネミーの削除

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
	if (m_player->GetPlayerPosition().z >= 9550.0f && m_boss == nullptr && m_wave->GetGoBoss() == true)
	{

		//一定のカウントまでいったら
		if (m_wave->GetLoadCount() == 2)
		{

			//ボス戦中に変更
			m_player->SetBossState(1);

		}


		//ローディング画面が表示されたらボスを作り出す
		if (m_wave->GetLoadCount() == 10)
		{

			//スカイキューブを作り直す
			DeleteGO(m_skyCube);
			m_skyCube = NewGO<SkyCube>(0, "skycube");
			m_skyCube->SetLuminance(1.0f);
			m_skyCube->SetScale(4000.0f);
			m_skyCube->SetPosition({ 0.0f,40.0f,0.0f });
			m_skyCube->SetType((EnSkyCubeType)enSkyCubeType_Wild_Night);


			//ボスを発生させる
			m_boss = NewGO<Boss>(1, "boss");
			m_boss->SetPosition({ -19800.0f,0.0f,7800.0f });


			//ウェーブクラスのボスポインタに教えてやる
			m_wave->SetBoss(m_boss);


			//プレイヤーの場所をボスの場所へ移動させる
			m_player->SetPosition({-19246.0f,0.0f,-130.0f});
			//player->m_playerModel.SetPosition(player->GetPlayerPosition());
			m_player->SetCharacterControllerPosition(m_player->GetPlayerPosition());


			//ばねカメラを瞬間移動させる
			//gamecamera->GetSpringCamera().Refresh();
			m_gameCamera->SpringCameraRefresh();


			//プレイヤーの更新
			//player->m_playerModel.Update(true);


			//今いる雑魚敵を全部消す
			DeleteEnemy();

		}
	}


	//プレイヤーが死んだら
	if (m_player->GetGameEndState() == 1)
	{

		//タイトルを作成
		m_title = NewGO<Title>(1, "title");


		//自分自身の削除
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