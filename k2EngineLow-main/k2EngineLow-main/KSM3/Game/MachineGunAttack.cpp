#include "stdafx.h"
#include "MachineGunAttack.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy_Far.h"
#include "Enemy_Near.h"
#include "Game.h"
#include "Boss.h"
#include "Boss_Drill.h"

MachineGunAttack::MachineGunAttack()
{

	//ステータスの初期化---------------------------------

	//弾のダメージ
	m_bulletDamage = 5.0f;

	//落下スピード
	m_fallSpeed = 0.0f;

	//前方向のスピード
	m_moveSpeed = 100.0f;

	//---------------------------------------------------

}

MachineGunAttack::~MachineGunAttack()
{
	
}

void MachineGunAttack::SetUp()
{

	//弾の初期化
	BulletSetUp(2.0f);

}

void MachineGunAttack::DestroyWithImpactEffect()
{

	//着弾エフェクトの再生
	PlayEffect(enMasinganKemuri, m_position, m_rot, { 10.0f,10.0f,10.0f });


	//自分自身の削除
	DeleteGO(this);

}

void MachineGunAttack::Update()
{

	//メインゲーム中
	if (m_player->game_state == 0)
	{

		//移動処理
		Move(1800.0f);


		//ダメージ処理
		DamageEvent(m_bulletDamage);

	}
	//リザルト中
	else if (m_player->game_state == 2)
	{

		//自分自身の削除
		DeleteGO(this);	

	}


	//プレイヤーがポーズ画面からゲームを終了させると消す
	if (m_player->game_end_state == 1)
	{

		//自分自身の削除
		DeleteGO(this);	

	}

}

void MachineGunAttack::Render(RenderContext& rc)
{

	//弾モデルの表示
	m_bulletModel.Draw(rc);

}