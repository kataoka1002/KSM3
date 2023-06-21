#include "stdafx.h"
#include "Core_weapons.h"
#include "Core_weapons_attack.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy_Far.h"
#include "Enemy_Near.h"
#include "Game.h"
#include "Boss.h"
#include "Boss_Drill.h"

Core_weapons_attack::Core_weapons_attack() 
{
	
	//ステータスの初期化---------------------------------

	//弾のダメージ
	m_bulletDamage = 5.0f;

	//落下スピード
	m_fallSpeed = 0.1f;

	//前方向のスピード
	m_moveSpeed = 200.0f;

	//スピード減少量
	m_decreaseSpeed = 0.05f;

	//落下スピード増加量
	m_addFallSpeed = 0.1f;

	//---------------------------------------------------

}

Core_weapons_attack::~Core_weapons_attack()
{

}

void Core_weapons_attack::SetUp() 
{

	//コア武器を探す
	m_coreWeapon = FindGO<Core_weapons>("core_weapons");


	//元の回転量を求める
	m_originRotation = m_coreWeapon->cw_Rotation;


	//発生する場所を求める
	m_position = m_coreWeapon->cw_position;


	//付けているコア武器によって変える
	switch (m_coreWeapon->set_weapons)
	{

	case 1:

		break;

	case 2:

		//ローカルポジションの設定
		m_bulletLocalPosition = { 0.0f,12.0f,0.0f };

		break;

	default:
		break;

	}


	//弾の初期化
	BulletSetUp(2.0f);

}


void Core_weapons_attack::DestroyWithImpactEffect()
{

	//着弾エフェクトの再生
	PlayEffect(enMasinganKemuri, m_position, m_rot, { 10.0f,10.0f,10.0f });


	//自分自身の削除
	DeleteGO(this);

}

void Core_weapons_attack::Update() 
{

	//メインゲーム中
	if (m_player->GetGameState() == MAIN_GAME_NUM)
	{

		//ダメージ処理
		DamageEvent(m_bulletDamage);


		//移動処理
		Move(2000.0f);

	}
	//リザルト画面に行くと
	else if (m_player->GetGameState() == RESULT_NUM)
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

void Core_weapons_attack::Render(RenderContext& rc) 
{

	//弾モデルの初期化
	m_bulletModel->Draw(rc);

}

