#include "stdafx.h"
#include "Customize_UI_ver2.h"
#include "Enemy_Bullet.h"
#include "Core_weapons.h"
#include "Enemy.h"
#include "Enemy_Near.h"
#include "Enemy_Far.h"
#include "Player.h"
#include "Game.h"
#include "GameCamera.h"
#include "sound/SoundEngine.h"
#include "Left_arm_weapons.h"
#include "Left_leg_weapons.h"
#include "Right_arm_weapons.h"
#include "Right_leg_weapons.h"
#include "Shoulder_weapons.h"

Enemy_Bullet::Enemy_Bullet() 
{
	
}

Enemy_Bullet::~Enemy_Bullet() 
{
	
}
void Enemy_Bullet::DestroyWithImpactEffect()
{
	//親によってエフェクトを変える
	if (m_enemyMama != nullptr)
	{
		if (m_enemyMama->GetWeponKind() == 2)//マシンガンの弾の煙エフェ
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
		if (m_enemyNearMama->GetWeponKind() == 4)//ギガトンキャノンの弾の煙エフェ
		{
			//画面を揺らす
			GameCamera* m_camera = FindGO<GameCamera>("gamecamera");
			m_camera->VibFlag = true;
		}
	}
	else if (m_enemyFarMama != nullptr)
	{
		if (m_enemyFarMama->GetWeponKind() == 6)	//戦艦砲の煙エフェクト
		{
			//戦艦砲エフェクトの初期化と再生
			m_weaponEffect = NewGO<EffectEmitter>(0);
			m_weaponEffect->Init(enTyakudan);
			m_weaponEffect->SetScale({ 5.7f,5.7f,5.7f });
			m_weaponEffect->SetPosition(m_position);
			m_weaponEffect->Play();

			//着弾したら効果音発生
			m_battleShipGunTyakutiSE = NewGO<SoundSource>(0);			//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
			m_battleShipGunTyakutiSE->Init(enButtleShipTyakudan);		//初期化
			m_battleShipGunTyakutiSE->SetVolume(2.0f * m_game->GetSEVol());	//音量調整
			m_battleShipGunTyakutiSE->Play(false);

			//画面を揺らす
			GameCamera* m_camera = FindGO<GameCamera>("gamecamera");
			m_camera->VibFlag = true;
		}
	}
	// 着弾したら死ぬ
	DeleteGO(this);
}
bool Enemy_Bullet::Start()
{
	m_customizeUI = FindGO<Customize_UI_ver2>("customize_ui_ver2");
	m_player = FindGO<Player>("player");
	if (m_player->game_state == 2)
	{
		DeleteGO(this);
	}
	m_coreWeapons = FindGO<Core_weapons>("core_weapons");
	m_game = FindGO<Game>("game");

	FindWeapon();	//プレイヤーの武器を検索する
	Setup();		//武器やエフェクトの設定
		
	return true;
}

void Enemy_Bullet::FindWeapon()
{
	if (m_player->m_playerDead == true)
	{
		return;
	}

	//左腕
	if (m_customizeUI->m_leftArmWeapon != nullptr)
	{
		m_leftArm = m_customizeUI->m_leftArmWeapon;	//カスタマイズUIにあるポインタを渡してやる
	}
	//左足
	if (m_customizeUI->m_leftLegWeapon != nullptr)
	{
		m_leftLeg = m_customizeUI->m_leftLegWeapon;	//カスタマイズUIにあるポインタを渡してやる
	}
	//右腕
	if (m_customizeUI->m_rightArmWeapon != nullptr)
	{
		m_rightArm = m_customizeUI->m_rightArmWeapon;	//カスタマイズUIにあるポインタを渡してやる
	}
	//右足
	if (m_customizeUI->m_rightLegWeapon != nullptr)
	{
		m_rightLeg = m_customizeUI->m_rightLegWeapon;	//カスタマイズUIにあるポインタを渡してやる
	}
	//肩
	if (m_customizeUI->m_shoulderWeapon != nullptr)
	{
		m_shoulder = m_customizeUI->m_shoulderWeapon;	//カスタマイズUIにあるポインタを渡してやる
	}
}

void Enemy_Bullet::Setup() 
{
	//親によって初期情報を変える
	if (m_enemyMama != nullptr)
	{
		switch (m_enemyMama->GetWeponKind())
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
			m_bulletFowrad = m_enemyMama->GetForward();
			//更新
			m_bulletModel.SetRotation(m_enemyMama->GetRot());
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
		switch (m_enemyNearMama->GetWeponKind())
		{
		case 4:	//ギガトンキャノン

			//モデルの初期化
			m_bulletModel.Init("Assets/modelData/V_P_bullet.tkm");
			m_bulletModel.SetScale({ 15.0f ,15.0f,10.0f });
			//エネミーから見て正しい位置に弾を設定
			originRotation.Multiply(m_bulletLocalPosition);	//掛け算
			//最終的な弾の回転を決定
			m_rot = originRotation;
			m_position += m_bulletLocalPosition;				//それに親から見た位置を足して最終的な武器の位置を決定
			//バレットの前方向の設定
			m_bulletFowrad = m_enemyNearMama->GetForward();
			//更新
			m_bulletModel.SetRotation(m_enemyNearMama->GetRot());
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
		switch (m_enemyFarMama->GetWeponKind())
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
			m_bulletFowrad = m_enemyFarMama->GetForward();
			//更新
			m_bulletModel.SetRotation(m_enemyFarMama->GetRot());
			m_bulletModel.SetPosition(m_position);

			//エフェクトの再生
			Effect(6);
			break;

		default:
			break;
		}
	}
}

void Enemy_Bullet::Update() 
{

	if (m_player->game_state == 0)
	{
		//位置が0以下になると消える(全ての弾共通)
		if (m_position.y <= 0.0f)
		{
			DestroyWithImpactEffect();
		}

		//親によって関数を変える
		if (m_enemyMama != nullptr)
		{
			Move();	
			Damage(m_enemyMama->GetWeponKind());
		}
		else if (m_enemyNearMama != nullptr)
		{
			MoveNear();
			Damage(m_enemyNearMama->GetWeponKind());
		}
		else if (m_enemyFarMama != nullptr)
		{
			MoveFar();
			Damage(m_enemyFarMama->GetWeponKind());
		}
	}
	else if (m_player->game_state == 2)
	{
		DeleteGO(this);	//リザルト画面に行くと消す
	}

	if (m_player->game_end_state == 1)
	{
		DeleteGO(this);	//プレイヤーがポーズ画面からゲームを終了させると消す
	}
}

void Enemy_Bullet::Move()
{
	if (m_enemyMama->GetWeponKind() == 1)	//ギガプラズマ
	{

	}
	if (m_enemyMama->GetWeponKind() == 2)	//マシンガン
	{
		//弾を前に飛ばす処理
		m_bulletSpeed += m_bulletFowrad * 2.0f;
		m_position += m_bulletSpeed;

		//弾とエネミー(親)の距離を計算して一定距離以上なら弾を消す
		Vector3 m_toEnemy = m_enemyMama->GetPos() - m_position;
		float m_dirToEnemy = m_toEnemy.Length();
		if (m_dirToEnemy >= 1800.0f)
		{
			DestroyWithImpactEffect();
		}

		//バレットの更新
		m_bulletModel.SetRotation(m_rot);
		m_bulletModel.SetPosition(m_position);
		m_bulletModel.Update();
	}
	if (m_enemyMama->GetWeponKind() == 3)	//ヘルファイヤライフル
	{

	}
}

void Enemy_Bullet::MoveNear()
{
	if (m_enemyNearMama->GetWeponKind() == 4)	//ギガトンキャノン
	{
		//弾を前に飛ばす処理
		m_bulletSpeed += m_bulletFowrad * 2.0f;
		m_position += m_bulletSpeed;

		//弾とエネミー(親)の距離を計算して一定距離以上なら弾を消す
		Vector3 m_toEnemy = m_enemyNearMama->GetPos() - m_position;
		float m_dirToEnemy = m_toEnemy.Length();
		if (m_dirToEnemy >= 100.0f)
		{
			DestroyWithImpactEffect();
		}

		//バレットの更新
		m_bulletModel.SetRotation(m_rot);
		m_bulletModel.SetPosition(m_position);
		m_bulletModel.Update();
	}
}

void Enemy_Bullet::MoveFar()
{
	if (m_enemyFarMama->GetWeponKind() == 5)	//ミサイル
	{

	}
	else if (m_enemyFarMama->GetWeponKind() == 6)	//戦艦砲
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
	//---------------------------------------------------------------------------------------------------
	if (m_player != nullptr)	//プレイヤーの情報が入っているなら
	{
		//弾とプレイヤーの距離を測る
		Vector3 diffPlayer = m_position - Vector3{ m_player->player_position.x, m_player->player_position.y + 50.0f, m_player->player_position.z };

		//武器によってダメージを変える
		if (weaponNum == 2)			//マシンガン
		{
			//距離を測り一定以下なら体力減少
			if (diffPlayer.Length() <= 100.0f) //ダメージが入る範囲
			{
				m_player->m_playerHP -= 0.5f;
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == 4)		//ギガトンキャノン
		{
			//距離を測り一定以下なら体力減少
			if (diffPlayer.Length() <= 100.0f) //ダメージが入る範囲
			{
				m_player->m_playerHP -= 0.5f;
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == 6)	//戦艦砲
		{
			//距離を測り一定以下なら体力減少
			if (diffPlayer.Length() <= 100.0f) //ダメージが入る範囲
			{
				m_player->m_playerHP -= 0.5f;
				DestroyWithImpactEffect();
			}
		}
	}
	//---------------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------------
	if (m_leftArm != nullptr)	//左腕に情報が入っているなら
	{
		//弾と左腕の距離を測る
		Vector3 diffLeftArm = m_position - m_leftArm->GetPosition();
		
		//武器によってダメージを変える
		if (weaponNum == 2)			//マシンガン
		{
			//距離を測り一定以下なら体力減少
			if (diffLeftArm.Length() <= 100.0f) //ダメージが入る範囲
			{
				m_leftArm->ApplyDamage(0.5f);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == 4)		//ギガトンキャノン
		{
			//距離を測り一定以下なら体力減少
			if (diffLeftArm.Length() <= 100.0f) //ダメージが入る範囲
			{
				m_leftArm->ApplyDamage(0.5f);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == 6)	//戦艦砲
		{
			//距離を測り一定以下なら体力減少
			if (diffLeftArm.Length() <= 100.0f) //ダメージが入る範囲
			{
				m_leftArm->ApplyDamage(0.5f);
				DestroyWithImpactEffect();
			}
		}
	}
	//---------------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------------
	if (m_leftLeg != nullptr)	//左足に情報が入っているなら
	{
		//弾と左腕の距離を測る
		Vector3 diffLeftLeg = m_position - m_leftLeg->GetPosition();

		//武器によってダメージを変える
		if (weaponNum == 2)			//マシンガン
		{
			//距離を測り一定以下なら体力減少
			if (diffLeftLeg.Length() <= 100.0f) //ダメージが入る範囲
			{
				m_leftLeg->ApplyDamage(0.5f);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == 4)		//ギガトンキャノン
		{
			//距離を測り一定以下なら体力減少
			if (diffLeftLeg.Length() <= 100.0f) //ダメージが入る範囲
			{
				m_leftLeg->ApplyDamage(0.5f);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == 6)	//戦艦砲
		{
			//距離を測り一定以下なら体力減少
			if (diffLeftLeg.Length() <= 100.0f) //ダメージが入る範囲
			{
				m_leftLeg->ApplyDamage(0.5f);
				DestroyWithImpactEffect();
			}
		}
	}
	//---------------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------------
	if (m_rightArm != nullptr)	//右手に情報が入っているなら
	{
		//弾と左腕の距離を測る
		Vector3 diffRightArm = m_position - m_rightArm->GetPosition();

		//武器によってダメージを変える
		if (weaponNum == 2)			//マシンガン
		{
			//距離を測り一定以下なら体力減少
			if (diffRightArm.Length() <= 100.0f) //ダメージが入る範囲
			{
				m_rightArm->ApplyDamage(0.5f);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == 4)		//ギガトンキャノン
		{
			//距離を測り一定以下なら体力減少
			if (diffRightArm.Length() <= 100.0f) //ダメージが入る範囲
			{
				m_rightArm->ApplyDamage(0.5f);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == 6)	//戦艦砲
		{
			//距離を測り一定以下なら体力減少
			if (diffRightArm.Length() <= 100.0f) //ダメージが入る範囲
			{
				m_rightArm->ApplyDamage(0.5f);
				DestroyWithImpactEffect();
			}
		}
	}
	//---------------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------------
	if (m_rightLeg != nullptr)	//右足に情報が入っているなら
	{
		//弾と左腕の距離を測る
		Vector3 diffRightLeg = m_position - m_rightLeg->GetPosition();

		//武器によってダメージを変える
		if (weaponNum == 2)			//マシンガン
		{
			//距離を測り一定以下なら体力減少
			if (diffRightLeg.Length() <= 100.0f) //ダメージが入る範囲
			{
				m_rightLeg->ApplyDamage(0.5f);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == 4)		//ギガトンキャノン
		{
			//距離を測り一定以下なら体力減少
			if (diffRightLeg.Length() <= 100.0f) //ダメージが入る範囲
			{
				m_rightLeg->ApplyDamage(0.5f);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == 6)	//戦艦砲
		{
			//距離を測り一定以下なら体力減少
			if (diffRightLeg.Length() <= 100.0f) //ダメージが入る範囲
			{
				m_rightLeg->ApplyDamage(0.5f);
				DestroyWithImpactEffect();
			}
		}
	}
	//---------------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------------
	if (m_shoulder != nullptr)	//肩に情報が入っているなら
	{
		//弾と左腕の距離を測る
		Vector3 diffShoulder = m_position - m_shoulder->GetPosition();

		//武器によってダメージを変える
		if (weaponNum == 2)			//マシンガン
		{
			//距離を測り一定以下なら体力減少
			if (diffShoulder.Length() <= 100.0f) //ダメージが入る範囲
			{
				m_shoulder->ApplyDamage(0.5f);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == 4)		//ギガトンキャノン
		{
			//距離を測り一定以下なら体力減少
			if (diffShoulder.Length() <= 100.0f) //ダメージが入る範囲
			{
				m_shoulder->ApplyDamage(0.5f);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == 6)	//戦艦砲
		{
			//距離を測り一定以下なら体力減少
			if (diffShoulder.Length() <= 100.0f) //ダメージが入る範囲
			{
				m_shoulder->ApplyDamage(0.5f);
				DestroyWithImpactEffect();
			}
		}
	}
	//---------------------------------------------------------------------------------------------------
}

void Enemy_Bullet::Render(RenderContext& rc)
{
	if (m_enemyMama != nullptr)
	{
		if (m_enemyMama->GetWeponKind() == 1)	//ギガプラズマ
		{

		}
		else if (m_enemyMama->GetWeponKind() == 2)	//マシンガン
		{
			m_bulletModel.Draw(rc);
		}
		else if (m_enemyMama->GetWeponKind() == 3)	//ヘイルファイヤーライフル
		{

		}
	}
	else if (m_enemyNearMama != nullptr)
	{
		if (m_enemyNearMama->GetWeponKind() == 4)	//ギガトンキャノン
		{
			m_bulletModel.Draw(rc);
		}
	}
	else if (m_enemyFarMama != nullptr)
	{
		if (m_enemyFarMama->GetWeponKind() == 5)	//ミサイル
		{

		}
		else if (m_enemyFarMama->GetWeponKind() == 6)	//戦艦砲
		{
			m_bulletModel.Draw(rc);
		}
	}
}