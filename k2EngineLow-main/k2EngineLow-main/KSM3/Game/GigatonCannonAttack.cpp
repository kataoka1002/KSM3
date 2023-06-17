#include "stdafx.h"
#include "GigatonCannonAttack.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy_Far.h"
#include "Enemy_Near.h"
#include "Game.h"
#include "Boss.h"
#include "Boss_Drill.h"

GigatonCannonAttack::GigatonCannonAttack()
{

	//ステータスの初期化---------------------------------

	//弾のダメージ
	m_bulletDamage = 100.0f;

	//落下スピード
	m_fallSpeed = 0.0f;

	//前方向のスピード
	m_moveSpeed = 100.0f;

	//---------------------------------------------------

}

GigatonCannonAttack::~GigatonCannonAttack()
{

}

void GigatonCannonAttack::SetUp()
{

	//弾の初期化
	BulletSetUp(10.0f);

}

void GigatonCannonAttack::DestroyWithImpactEffect()
{

	//着弾エフェクトの再生
	PlayEffect(enGigatonAttack, { m_position.x,m_position.y + 50.0f,m_position.z }, m_rot, { 5.0f,5.0f,5.0f });


	//爆発音の再生
	m_cannonSE = NewGO<SoundSource>(0);
	m_cannonSE->Init(enGigatonCannon);					//初期化
	m_cannonSE->SetVolume(2.0f * m_game->GetSEVol());	//音量調整
	m_cannonSE->Play(false);


	//自分自身の削除
	DeleteGO(this);

}

void GigatonCannonAttack::Update()
{

	//メインゲーム中
	if (m_player->GetGameState() == 0)
	{

		//移動処理
		Move(150.0f);


		//ダメージ処理
		DamageEvent(m_bulletDamage);

	}
	//リザルト中
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

void GigatonCannonAttack::Render(RenderContext& rc)
{

	//ギガトンキャノンの弾は見せない
	//m_bulletModel.Draw(rc);

}