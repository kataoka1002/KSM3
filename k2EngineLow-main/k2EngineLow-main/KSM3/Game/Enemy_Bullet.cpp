#include "stdafx.h"
#include "Enemy_Bullet.h"
#include "Core_weapons.h"
#include "Enemy.h"
#include "Enemy_Near.h"
#include "Enemy_Far.h"
#include "Player.h"
#include "sound/SoundEngine.h"

Enemy_Bullet::Enemy_Bullet() 
{
	//効果音の作成
	m_soundSource = NewGO<SoundSource>(0);
}

Enemy_Bullet::~Enemy_Bullet() 
{
	DeleteGO(masinganEffect);
	DeleteGO(m_soundSource);
}

bool Enemy_Bullet::Start()
{
	m_player = FindGO<Player>("player");
	m_coreWeapons = FindGO<Core_weapons>("core_weapons");


	//親によって初期情報を変える
	if (m_enemyMama != nullptr)
	{
		switch (m_enemyMama->m_setWeapon)
		{
		case 1:	//ギガプラズマ
			break;

		case 2:	//マシンガン

			//モデルの初期化
			m_bulletModel.Init("Assets/modelData/V_P_bullet.tkm");
			m_bulletModel.SetScale(4.0f);
			//エネミーから見て正しい位置に弾を設定
			originRotation.Multiply(m_macineGunLocalPosition);	//掛け算
			//最終的な弾の回転を決定
			m_rot = originRotation;
			m_position += m_macineGunLocalPosition;				//それに親から見た位置を足して最終的な武器の位置を決定
			//バレットの前方向の設定
			m_bulletFowrad = m_enemyMama->m_enemyForward;
			m_bulletModel.SetRotation(m_enemyMama->m_enemyRotation);
			m_bulletModel.SetPosition(m_position);

			//効果音の設定
			g_soundEngine->ResistWaveFileBank(2, "Assets/audio/enemy/masinganHassya.wav");
			m_soundSource->Init(m_enemyMama->m_setWeapon);	//初期化
			m_soundSource->SetVolume(0.2f);					//音量調整
			break;

		case 3:	//ヘイルファイヤーライフル
			break;

		default:
			break;
		}

		
	}
	else if (m_enemyNearMama != nullptr)
	{
		switch (m_enemyNearMama->m_setWeapon)
		{
		case 4:	//ギガトンキャノン
		
			//効果音の初期化
			m_soundSource->Init(m_enemyNearMama->m_setWeapon);

			break;

		default:
			break;
		}

	}
	else if (m_enemyFarMama != nullptr)
	{
		switch (m_enemyFarMama->m_setWeapon)
		{
		case 5:	//ミサイル

			//効果音の初期化
			m_soundSource->Init(m_enemyFarMama->m_setWeapon);
			break;

		case 6:	//戦艦砲

			//効果音の初期化
			m_soundSource->Init(m_enemyFarMama->m_setWeapon);

			break;

		default:
			break;
		}
	}
		

	//セットアップ
	Setup();


	return true;
}

void Enemy_Bullet::Setup() 
{
	//エフェクトの初期化と再生
	masinganEffect = NewGO<EffectEmitter>(0);
	masinganEffect->Init(enMasinganHibana);
	masinganEffect->SetScale({ 0.7f,0.7f,0.7f });
	masinganEffect->SetPosition(m_position);
	masinganEffect->Play();
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

		//親によって関数を変える
		if (m_enemyMama != nullptr)
		{
			Move();	
		}
		else if (m_enemyNearMama != nullptr)
		{
			MoveNear();
		}
		else if (m_enemyFarMama != nullptr)
		{
			MoveFar();
		}
	}
}

void Enemy_Bullet::Move()
{
	if (m_enemyMama->m_setWeapon == 1)	//ギガプラズマ
	{

	}
	if (m_enemyMama->m_setWeapon == 2)	//マシンガン
	{
		//弾を前に飛ばす処理
		m_bulletSpeed += m_bulletFowrad * 2.0f;
		m_position += m_bulletSpeed;

		//弾とエネミー(親)の距離を計算して一定距離以上なら弾を消す
		Vector3 m_toEnemy = m_enemyMama->m_enemyPosition - m_position;
		float m_dirToEnemy = m_toEnemy.Length();
		if (m_dirToEnemy >= 1800.0f)
		{
			DeleteGO(this);
		}

		//バレットの更新
		m_bulletModel.SetRotation(m_rot);
		m_bulletModel.SetPosition(m_position);
		m_bulletModel.Update();
	}
	if (m_enemyMama->m_setWeapon == 3)	//ヘルファイヤライフル
	{

	}
}

void Enemy_Bullet::MoveNear()
{
	if (m_enemyNearMama->m_setWeapon == 4)	//ギガトンキャノン
	{

	}

}

void Enemy_Bullet::MoveFar()
{
	if (m_enemyFarMama->m_setWeapon == 5)	//ミサイル
	{

	}
	else if (m_enemyFarMama->m_setWeapon == 6)	//戦艦砲
	{

	}

}

void Enemy_Bullet::Render(RenderContext& rc)
{
	if (m_enemyMama != nullptr)
	{
		if (m_enemyMama->m_setWeapon == 1)	//ギガプラズマ
		{

		}
		else if (m_enemyMama->m_setWeapon == 2)	//マシンガン
		{
			m_bulletModel.Draw(rc);
		}
		else if (m_enemyMama->m_setWeapon == 3)	//ヘイルファイヤーライフル
		{

		}
	}
	else if (m_enemyNearMama != nullptr)
	{
		if (m_enemyNearMama->m_setWeapon == 4)	//ギガトンキャノン
		{

		}
	}
	else if (m_enemyFarMama != nullptr)
	{
		if (m_enemyFarMama->m_setWeapon == 5)	//ミサイル
		{

		}
		else if (m_enemyFarMama->m_setWeapon == 6)	//戦艦砲
		{
			m_bulletModel.Draw(rc);
		}
	}
}