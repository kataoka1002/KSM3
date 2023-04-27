#include "stdafx.h"
#include "Enemy_Bullet.h"
#include "Core_weapons.h"
#include "Enemy.h"
#include "Player.h"
#include "sound/SoundEngine.h"

Enemy_Bullet::Enemy_Bullet() 
{
	//バレットの初期化
	m_bulletModel.Init("Assets/modelData/V_P_bullet.tkm");
	m_bulletModel.SetScale(15.0f);
}

Enemy_Bullet::~Enemy_Bullet() 
{
	
}

bool Enemy_Bullet::Start()
{
	m_player = FindGO<Player>("player");
	m_coreWeapons = FindGO<Core_weapons>("core_weapons");


	//武器の種類によって初期情報を変える
	switch (m_enemyMama->m_setWeapon)
	{
	case 1:	//ギガプラズマ
		g_soundEngine->ResistWaveFileBank(2, "Assets/audio/Taihou_kouho1.wav");
		break;
	case 2:	//マシンガン
		//効果音の設定
		g_soundEngine->ResistWaveFileBank(2, "Assets/audio/Taihou_kouho1.wav");
		//エネミーから見て正しい位置に弾を設定
		originRotation.Multiply(m_macineGunLocalPosition);	//何かしらの計算
		//最終的な弾の回転を決定
		m_rot = originRotation;
		m_position += m_macineGunLocalPosition;				//それに親から見た位置を足して最終的な武器の位置を決定
		break;
	case 3:	//ヘイルファイヤーライフル
		g_soundEngine->ResistWaveFileBank(2, "Assets/audio/Taihou_kouho1.wav");
		break;
	default:
		break;
	}

	m_soundSource = NewGO<SoundSource>(0);	//効果音の作成
	m_soundSource->Init(2);					//初期化
	m_soundSource->SetVolume(0.2f);			//音量調整
	m_soundSource->Play(false);				//再生

	//セットアップ
	Setup();

	return true;
}

void Enemy_Bullet::Setup() 
{
	m_bulletFowrad = m_enemyMama->m_enemyForward;				//バレットの前方向の設定
	m_bulletModel.SetRotation(m_enemyMama->m_enemyRotation);
	m_bulletModel.SetPosition(m_position);
}

void Enemy_Bullet::Update() 
{
	if (m_player->game_state == 0)
	{
		//位置が0以下になると消える
		if (m_position.y <= 0.0f)
		{
			DeleteGO(this);
		}

		Move();	//移動処理

		//バレットの更新
		m_bulletModel.SetRotation(m_rot);
		m_bulletModel.SetPosition(m_position);
		m_bulletModel.Update();
	}
}

void Enemy_Bullet::Move()
{
	//弾を前に飛ばす処理
	m_bulletSpeed += m_bulletFowrad * 2.0f;
	m_position += m_bulletSpeed;

	m_position.y -= 2.0f;
}

void Enemy_Bullet::Render(RenderContext& rc) 
{
	m_bulletModel.Draw(rc);
}