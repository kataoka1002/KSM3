#include "stdafx.h"
#include "Enemy_Bullet.h"
#include "Core_weapons.h"
#include "Enemy.h"
#include "Enemy_Near.h"
#include "Enemy_Far.h"
#include "Player.h"
#include "Game.h"
#include "sound/SoundEngine.h"

Enemy_Bullet::Enemy_Bullet() 
{
	
}

Enemy_Bullet::~Enemy_Bullet() 
{
	//親によってエフェクトを変える
	if (m_enemyMama != nullptr)
	{
		if (m_enemyMama->m_setWeapon == 2)//マシンガンの弾の煙エフェ
		{
			m_tyakudanEffect = NewGO<EffectEmitter>(0);
			m_tyakudanEffect->Init(enMasinganKemuri);
			m_tyakudanEffect->SetScale({ 10.0f,10.0f,10.0f });
			m_tyakudanEffect->SetPosition({ m_position.x,m_position.y,m_position.z });
			m_tyakudanEffect->Play();
		}
	}
	else if (m_enemyNearMama != nullptr)
	{
		
	}
	else if (m_enemyFarMama != nullptr)
	{
		//エフェクトの初期化と再生
		m_weaponEffect = NewGO<EffectEmitter>(0);
		m_weaponEffect->Init(enTyakudan);
		m_weaponEffect->SetScale({ 5.7f,5.7f,5.7f });
		m_weaponEffect->SetPosition(m_position);
		m_weaponEffect->Play();

		//着弾したら効果音発生
		m_battleShipGunTyakutiSE = NewGO<SoundSource>(0);			//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
		m_battleShipGunTyakutiSE->Init(enButtleShipTyakudan);		//初期化
		m_battleShipGunTyakutiSE->SetVolume(2.0f * m_game->SEvol);	//音量調整
		m_battleShipGunTyakutiSE->Play(false);
	}
}

bool Enemy_Bullet::Start()
{
	m_player = FindGO<Player>("player");
	m_coreWeapons = FindGO<Core_weapons>("core_weapons");
	m_game = FindGO<Game>("game");

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
			originRotation.Multiply(m_bulletLocalPosition);	//掛け算

			//最終的な弾の回転を決定
			m_rot = originRotation;
			m_position += m_bulletLocalPosition;				//それに親から見た位置を足して最終的な武器の位置を決定
			//バレットの前方向の設定
			m_bulletFowrad = m_enemyMama->m_enemyForward;
			//更新
			m_bulletModel.SetRotation(m_enemyMama->m_enemyRotation);
			m_bulletModel.SetPosition(m_position);

			//音はエネミー側で鳴らしている

			//エフェクトの再生
			Effect(2);
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

			//モデルの初期化
			m_bulletModel.Init("Assets/modelData/V_P_bullet.tkm");
			m_bulletModel.SetScale({ 15.0f ,15.0f,10.0f});
			//エネミーから見て正しい位置に弾を設定
			originRotation.Multiply(m_bulletLocalPosition);	//掛け算
			//最終的な弾の回転を決定
			m_rot = originRotation;
			m_position += m_bulletLocalPosition;				//それに親から見た位置を足して最終的な武器の位置を決定
			//バレットの前方向の設定
			m_bulletFowrad = m_enemyNearMama->m_enemyForward;
			//更新
			m_bulletModel.SetRotation(m_enemyNearMama->m_enemyRotation);
			m_bulletModel.SetPosition(m_position);

			//爆発音はエネミー側で鳴らしている

			//エフェクトの再生
			Effect(4);

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
			break;

		case 6:	//戦艦砲

			//モデルの初期化
			m_bulletModel.Init("Assets/modelData/V_P_bullet.tkm");
			m_bulletModel.SetScale(10.0f);
			//エネミーから見て正しい位置に弾を設定
			originRotation.Multiply(m_bulletLocalPosition);	//掛け算
			//最終的な弾の回転を決定
			m_rot = originRotation;
			m_position += m_bulletLocalPosition;				//それに親から見た位置を足して最終的な武器の位置を決定
			//バレットの前方向の設定
			m_bulletFowrad = m_enemyFarMama->m_enemyForward;
			//更新
			m_bulletModel.SetRotation(m_enemyFarMama->m_enemyRotation);
			m_bulletModel.SetPosition(m_position);

			//エフェクトの再生
			Effect(6);
			break;

		default:
			break;
		}
	}
		

	return true;
}

void Enemy_Bullet::Setup() 
{

}

void Enemy_Bullet::Update() 
{
	if (m_player->game_state == 0)
	{
		//位置が0以下になると消える(全ての弾共通)
		if (m_position.y <= 0.0f)
		{
			DeleteGO(this);
		}

		//親によって関数を変える
		if (m_enemyMama != nullptr)
		{
			Move();	
			Damage(m_enemyMama->m_setWeapon);
		}
		else if (m_enemyNearMama != nullptr)
		{
			MoveNear();
			Damage(m_enemyNearMama->m_setWeapon);
		}
		else if (m_enemyFarMama != nullptr)
		{
			MoveFar();
			Damage(m_enemyFarMama->m_setWeapon);
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
		//弾を前に飛ばす処理
		m_bulletSpeed += m_bulletFowrad * 2.0f;
		m_position += m_bulletSpeed;

		//弾とエネミー(親)の距離を計算して一定距離以上なら弾を消す
		Vector3 m_toEnemy = m_enemyNearMama->m_enemyPosition - m_position;
		float m_dirToEnemy = m_toEnemy.Length();
		if (m_dirToEnemy >= 100.0f)
		{
			DeleteGO(this);
		}

		//バレットの更新
		m_bulletModel.SetRotation(m_rot);
		m_bulletModel.SetPosition(m_position);
		m_bulletModel.Update();
	}
}

void Enemy_Bullet::MoveFar()
{
	if (m_enemyFarMama->m_setWeapon == 5)	//ミサイル
	{

	}
	else if (m_enemyFarMama->m_setWeapon == 6)	//戦艦砲
	{
		//弾を前に飛ばす処理
		m_bulletSpeed += m_bulletFowrad * 1.7f;
		m_bulletSpeed.y -= 0.1f;
		m_position += m_bulletSpeed;

		//バレットの更新
		m_bulletModel.SetRotation(m_rot);
		m_bulletModel.SetPosition(m_position);
		m_bulletModel.Update();
	}
}

void Enemy_Bullet::Effect(int num)
{
	if (num == 1)
	{
	}
	else if (num == 2)
	{
		//エフェクトの初期化と再生
		m_weaponEffect = NewGO<EffectEmitter>(0);
		m_weaponEffect->Init(enMasinganHibana);
		m_weaponEffect->SetScale({ 0.7f,0.7f,0.7f });
		m_weaponEffect->SetPosition(m_position);
		m_weaponEffect->Play();
	}
	else if (num == 3)
	{

	}
	else if (num == 4)
	{
		//エフェクトの初期化と再生
		m_weaponEffect = NewGO<EffectEmitter>(0);
		m_weaponEffect->Init(enHidan);
		m_weaponEffect->SetScale({ 1.5f,1.5f,1.5f });
		m_weaponEffect->SetPosition(m_position);
		m_weaponEffect->Play();
	}
	else if (num == 5)
	{

	}
	else if (num == 6)
	{
		//エフェクトの初期化と再生
		m_weaponEffect = NewGO<EffectEmitter>(0);
		m_weaponEffect->Init(enMasinganHibana);
		m_weaponEffect->SetScale({ 0.7f,0.7f,0.7f });
		m_weaponEffect->SetPosition(m_position);
		m_weaponEffect->Play();
	}
}

void Enemy_Bullet::Damage(int weaponNum)
{
	//武器によってダメージを変える
	if (weaponNum == 2)			//マシンガン
	{
		//弾とプレイヤーの距離を測り一定以下なら体力減少
		Vector3 diff = m_position - Vector3{ m_player->player_position.x, m_player->player_position.y + 50.0f, m_player->player_position.z };
		if (diff.Length() <= 100.0f) //ダメージが入る範囲
		{
			m_player->m_playerHP -= 0.5f;
			DeleteGO(this);	//弾は消える
		}
	}
	else if(weaponNum == 4)		//ギガトンキャノン
	{
		//弾とプレイヤーの距離を測り一定以下なら体力減少
		Vector3 diff = m_position - Vector3{ m_player->player_position.x, m_player->player_position.y + 50.0f, m_player->player_position.z };
		if (diff.Length() <= 100.0f) //ダメージが入る範囲
		{
			m_player->m_playerHP -= 0.5f;
			DeleteGO(this);	//弾は消える
		}
	}
	else if (weaponNum == 6)	//戦艦砲
	{
		//弾とプレイヤーの距離を測り一定以下なら体力減少
		Vector3 diff = m_position - Vector3{ m_player->player_position.x, m_player->player_position.y + 50.0f, m_player->player_position.z };
		if (diff.Length() <= 100.0f) //ダメージが入る範囲
		{
			m_player->m_playerHP -= 0.5f;
			DeleteGO(this);	//弾は消える
		}
	}
}

void Enemy_Bullet::EffectDelete(int num)
{
	
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
			m_bulletModel.Draw(rc);
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