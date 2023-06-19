#include "stdafx.h"
#include "Battle_ship_attack.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy_Far.h"
#include "Enemy_Near.h"
#include "Game.h"
#include "Boss.h"
#include "Boss_Riser.h"
#include "Boss_Drill.h"

Battle_ship_attack::Battle_ship_attack() 
{
	
	//ステータスの初期化---------------------------------

	//弾のダメージ
	m_bulletDamage = 50.0f;

	//落下スピード
	m_fallSpeed = 0.0f;

	//前方向のスピード
	m_moveSpeed = 30.0f;

	//スピード減少量
	m_decreaseSpeed = 0.05f;

	//落下スピード増加量
	m_addFallSpeed = 0.1f;

	//---------------------------------------------------

}

Battle_ship_attack::~Battle_ship_attack()
{

}

void Battle_ship_attack::DestroyWithImpactEffect()
{

	//着弾エフェクトの再生
	PlayEffect(enTyakudan, { m_position.x,m_position.y + 50.0f,m_position.z }, m_rot, { 5.7f,5.7f,5.7f });


	//SE発生
	m_battleShipGunTyakudanSE = NewGO<SoundSource>(0);					//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
	m_battleShipGunTyakudanSE->Init(enButtleShipTyakudan);				//初期化
	m_battleShipGunTyakudanSE->SetVolume(2.0f * m_game->GetSEVol());	//音量調整
	m_battleShipGunTyakudanSE->Play(false);


	//自分自身の削除
	DeleteGO(this);	

}

void Battle_ship_attack::SetUp() 
{

	//発射音の再生
	m_battleShipGunSE = NewGO<SoundSource>(0);					//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
	m_battleShipGunSE->Init(enButtleShipGun);					//初期化
	m_battleShipGunSE->SetVolume(1.0f * m_game->GetSEVol());	//音量調整
	m_battleShipGunSE->Play(false);


	//弾の初期化
	BulletSetUp(5.0f);

}

void Battle_ship_attack::Update()
{

	//メインゲーム中
	if (m_player->GetGameState() == 0)
	{
	
		//ダメージ処理
		DamageEvent(m_bulletDamage);


		//煙の発生
		SmokeEfect();


		//移動処理
		Move(2000.0f);

	}
	//リザルト画面に行くと
	else if (m_player->GetGameState() == 2)
	{

		//自分自身の削除
		DeleteGO(this);	

	}


	//プレイヤーがポーズ画面からゲームを終了させると
	if (m_player->GetGameEndState() == 1)
	{

		//自分自身の削除
		DeleteGO(this);	

	}

}

void Battle_ship_attack::SmokeEfect()
{

	//カウントアップ
	m_smokeCount++;


	//カウントが一定以上になったら
	if (m_smokeCount >= 2)
	{

		//エフェクトの初期化と再生
		PlayEffect(enSenkanhouKemuri, { m_position.x,m_position.y + 50.0f,m_position.z }, m_rot, { 5.0f,5.0f,5.0f });


		//カウントリセット
		m_smokeCount = 0;

	}

}

void Battle_ship_attack::Render(RenderContext& rc) 
{

	//弾モデルの描画
	m_bulletModel->Draw(rc);

}