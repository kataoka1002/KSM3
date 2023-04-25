#include "stdafx.h"
#include "Enemy_BulletFar.h"
#include "Core_weapons.h"
#include "Enemy_Far.h"
#include "Player.h"
#include "sound/SoundEngine.h"

Enemy_BulletFar::Enemy_BulletFar()
{
	//バレットの初期化
	m_bulletModel.Init("Assets/modelData/V_P_bullet.tkm");
}

Enemy_BulletFar::~Enemy_BulletFar()
{
	
}

bool Enemy_BulletFar::Start()
{
	m_enemy = FindGO<Enemy_Far>("enemy_far");
	m_player = FindGO<Player>("player");
	m_coreWeapons = FindGO<Core_weapons>("core_weapons");

	//武器の種類によって効果音を変える
	switch (m_enemy->m_setWeapon)
	{
	case 1:	//ミサイル
		g_soundEngine->ResistWaveFileBank(2, "Assets/audio/Taihou_kouho1.wav");
		break;
	case 2:	//戦艦砲
		g_soundEngine->ResistWaveFileBank(2, "Assets/audio/Taihou_kouho1.wav");
		break;
	default:
		break;
	}

	m_soundSource = NewGO<SoundSource>(0);	//効果音の作成
	m_soundSource->Init(2);				//初期化
	m_soundSource->SetVolume(0.2f);		//音量調整
	m_soundSource->Play(false);			//再生

	//セットアップ
	Setup();

	return true;
}

void Enemy_BulletFar::Setup()
{
	m_bulletFowrad = m_enemy->m_enemyForward;		//バレットの前方向の設定
	m_position.y += 10.0f;							//打ち出す位置を少し上げる
	m_bulletModel.SetRotation(m_enemy->m_enemyRotation);
	m_bulletModel.SetPosition(m_position);
}

void Enemy_BulletFar::Update()
{
	if (m_player->game_state == 0)
	{
		//位置が0以下になると消える
		if (m_position.y <= 0.0f)
		{
			DeleteGO(this);
		}

		Move();	//移動処理
		m_bulletModel.Update();	//バレットの更新
	}
}

void Enemy_BulletFar::Move()
{
	//弾を前に飛ばす処理
	m_position += m_bulletFowrad * m_bulletSpeed;
	if (m_position.y <= m_coreWeapons->cw_position.y && fast_count == true)
	{
		m_position.y += 1.0f;
	}
	else
	{
		fast_count = false;
		m_fallSpeed += 0.1f;
	}
	m_position.y -= m_fallSpeed;
	m_bulletSpeed -= 0.05f;	//だんだん遅くする

	m_bulletModel.SetPosition(m_position);
}

void Enemy_BulletFar::Render(RenderContext& rc)
{
	m_bulletModel.Draw(rc);
}