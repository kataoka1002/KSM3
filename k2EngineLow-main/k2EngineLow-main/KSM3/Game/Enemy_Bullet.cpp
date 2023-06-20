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


namespace
{
	const float RANGE_DISTANCE = 100.0f;

	const float ENEMY_MACHINEGUN_DAMAGE = 0.5f;
	const float ENEMY_GIGATONCANNON_DAMAGE = 50.0f;
	const float ENEMY_BATTLESHIPGUN_DAMAGE = 25.0f;
}


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
		if (m_enemyMama->GetWeponKind() == MACHINEGUN_NUM)//マシンガンの弾の煙エフェ
		{
			PlayEffect(enMasinganKemuri, m_position, m_rot, { 10.0f,10.0f,10.0f });
		}
	}
	else if (m_enemyNearMama != nullptr)
	{
		if (m_enemyNearMama->GetWeponKind() == GIGATONCANNON_NUM)//ギガトンキャノンの弾の煙エフェ
		{
			//画面を揺らす
			GameCamera* m_camera = FindGO<GameCamera>("gamecamera");
			m_camera->VibFlag = true;
		}
	}
	else if (m_enemyFarMama != nullptr)
	{
		if (m_enemyFarMama->GetWeponKind() == BATTLESHIPGUN_NUM)	//戦艦砲の煙エフェクト
		{
			//戦艦砲エフェクトの初期化と再生
			PlayEffect(enTyakudan, m_position, m_rot, { 5.7f,5.7f,5.7f });

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
	if (m_player->GetGameState() == 2)
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
	if (m_player->GetPlayerDead() == true)
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

	//メモリの確保(make_unique関数内部でnewしている)
	m_bulletModel = std::make_unique<ModelRender>();


	//親によって初期情報を変える
	if (m_enemyMama != nullptr)
	{
		switch (m_enemyMama->GetWeponKind())
		{
		case GIGAPLASMA_NUM:	//ギガプラズマ
			break;

		case MACHINEGUN_NUM:	//マシンガン

			//モデルの初期化
			m_bulletModel->Init("Assets/modelData/V_P_bullet.tkm");
			m_bulletModel->SetScale(4.0f);
			//エネミーから見て正しい位置に弾を設定
			originRotation.Multiply(m_bulletLocalPosition);	//掛け算

			//最終的な弾の回転を決定
			m_rot = originRotation;
			m_position += m_bulletLocalPosition;				//それに親から見た位置を足して最終的な武器の位置を決定
			//バレットの前方向の設定
			m_bulletFowrad = m_enemyMama->GetForward();
			//更新
			m_bulletModel->SetRotation(m_enemyMama->GetRot());
			m_bulletModel->SetPosition(m_position);

			//音はエネミー側で鳴らしている

			//エフェクトの再生
			Effect(MACHINEGUN_NUM);
			break;

		case HELLFIRE_NUM:	//ヘイルファイヤーライフル
			break;

		default:
			break;
		}
	}
	else if (m_enemyNearMama != nullptr)
	{
		switch (m_enemyNearMama->GetWeponKind())
		{
		case GIGATONCANNON_NUM:	//ギガトンキャノン

			//モデルの初期化
			m_bulletModel->Init("Assets/modelData/V_P_bullet.tkm");
			m_bulletModel->SetScale({ 15.0f ,15.0f,10.0f });
			//エネミーから見て正しい位置に弾を設定
			originRotation.Multiply(m_bulletLocalPosition);	//掛け算
			//最終的な弾の回転を決定
			m_rot = originRotation;
			m_position += m_bulletLocalPosition;				//それに親から見た位置を足して最終的な武器の位置を決定
			//バレットの前方向の設定
			m_bulletFowrad = m_enemyNearMama->GetForward();
			//更新
			m_bulletModel->SetRotation(m_enemyNearMama->GetRot());
			m_bulletModel->SetPosition(m_position);

			//爆発音はエネミー側で鳴らしている

			//エフェクトの再生
			Effect(GIGATONCANNON_NUM);



			break;

		default:
			break;
		}
	}
	else if (m_enemyFarMama != nullptr)
	{
		switch (m_enemyFarMama->GetWeponKind())
		{
		case MISSILE_NUM:	//ミサイル

			//効果音の初期化
			break;

		case BATTLESHIPGUN_NUM:	//戦艦砲

			//モデルの初期化
			m_bulletModel->Init("Assets/modelData/V_P_bullet.tkm");
			m_bulletModel->SetScale(10.0f);
			//エネミーから見て正しい位置に弾を設定
			originRotation.Multiply(m_bulletLocalPosition);	//掛け算
			//最終的な弾の回転を決定
			m_rot = originRotation;
			m_position += m_bulletLocalPosition;				//それに親から見た位置を足して最終的な武器の位置を決定
			//バレットの前方向の設定
			m_bulletFowrad = m_enemyFarMama->GetForward();
			//更新
			m_bulletModel->SetRotation(m_enemyFarMama->GetRot());
			m_bulletModel->SetPosition(m_position);

			//エフェクトの再生
			Effect(BATTLESHIPGUN_NUM);
			break;

		default:
			break;
		}
	}
}

void Enemy_Bullet::Update() 
{

	if (m_player->GetGameState() == 0)
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
	else if (m_player->GetGameState() == 2)
	{
		DeleteGO(this);	//リザルト画面に行くと消す
	}

	if (m_player->GetGameEndState() == 1)
	{
		DeleteGO(this);	//プレイヤーがポーズ画面からゲームを終了させると消す
	}
}

void Enemy_Bullet::Move()
{
	if (m_enemyMama->GetWeponKind() == GIGAPLASMA_NUM)	//ギガプラズマ
	{

	}
	if (m_enemyMama->GetWeponKind() == MACHINEGUN_NUM)	//マシンガン
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
		m_bulletModel->SetRotation(m_rot);
		m_bulletModel->SetPosition(m_position);
		m_bulletModel->Update();
	}
	if (m_enemyMama->GetWeponKind() == HELLFIRE_NUM)	//ヘルファイヤライフル
	{

	}
}

void Enemy_Bullet::MoveNear()
{
	if (m_enemyNearMama->GetWeponKind() == GIGATONCANNON_NUM)	//ギガトンキャノン
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
		m_bulletModel->SetRotation(m_rot);
		m_bulletModel->SetPosition(m_position);
		m_bulletModel->Update();
	}
}

void Enemy_Bullet::MoveFar()
{
	if (m_enemyFarMama->GetWeponKind() == MISSILE_NUM)	//ミサイル
	{

	}
	else if (m_enemyFarMama->GetWeponKind() == BATTLESHIPGUN_NUM)	//戦艦砲
	{
		//弾を前に飛ばす処理
		m_bulletSpeed += m_bulletFowrad * 1.7f;
		m_bulletSpeed.y -= 0.1f;
		m_position += m_bulletSpeed;

		//バレットの更新
		m_bulletModel->SetRotation(m_rot);
		m_bulletModel->SetPosition(m_position);
		m_bulletModel->Update();
	}
}

void Enemy_Bullet::Effect(int num)
{
	if (num == GIGAPLASMA_NUM)
	{
	}
	else if (num == MACHINEGUN_NUM)
	{
		//エフェクトの初期化と再生
		PlayEffect(enMasinganHibana, m_position, m_rot, { 0.7f,0.7f,0.7f });
	}
	else if (num == HELLFIRE_NUM)
	{

	}
	else if (num == GIGATONCANNON_NUM)
	{
		//エフェクトの初期化と再生
		PlayEffect(enHidan, m_position, m_rot, { 1.5f,1.5f,1.5f });
	}
	else if (num == MISSILE_NUM)
	{

	}
	else if (num == BATTLESHIPGUN_NUM)
	{
		//エフェクトの初期化と再生
		PlayEffect(enMasinganHibana, m_position, m_rot, { 0.7f,0.7f,0.7f });
	}
}

void Enemy_Bullet::Damage(int weaponNum)
{
	//---------------------------------------------------------------------------------------------------
	if (m_player != nullptr)	//プレイヤーの情報が入っているなら
	{
		//弾とプレイヤーの距離を測る
		Vector3 diffPlayer = m_position - Vector3{ m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y + 50.0f, m_player->GetPlayerPosition().z };

		//武器によってダメージを変える
		if (weaponNum == MACHINEGUN_NUM)			//マシンガン
		{
			//距離を測り一定以下なら体力減少
			if (diffPlayer.Length() <= RANGE_DISTANCE) //ダメージが入る範囲
			{
				m_player->ApplyDamage(ENEMY_MACHINEGUN_DAMAGE);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == GIGATONCANNON_NUM)		//ギガトンキャノン
		{
			//距離を測り一定以下なら体力減少
			if (diffPlayer.Length() <= RANGE_DISTANCE) //ダメージが入る範囲
			{
				m_player->ApplyDamage(ENEMY_GIGATONCANNON_DAMAGE);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == BATTLESHIPGUN_NUM)	//戦艦砲
		{
			//距離を測り一定以下なら体力減少
			if (diffPlayer.Length() <= RANGE_DISTANCE) //ダメージが入る範囲
			{
				m_player->ApplyDamage(ENEMY_BATTLESHIPGUN_DAMAGE);
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
		if (weaponNum == MACHINEGUN_NUM)			//マシンガン
		{
			//距離を測り一定以下なら体力減少
			if (diffLeftArm.Length() <= RANGE_DISTANCE) //ダメージが入る範囲
			{
				m_leftArm->ApplyDamage(ENEMY_MACHINEGUN_DAMAGE);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == GIGATONCANNON_NUM)		//ギガトンキャノン
		{
			//距離を測り一定以下なら体力減少
			if (diffLeftArm.Length() <= RANGE_DISTANCE) //ダメージが入る範囲
			{
				m_leftArm->ApplyDamage(ENEMY_GIGATONCANNON_DAMAGE);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == BATTLESHIPGUN_NUM)	//戦艦砲
		{
			//距離を測り一定以下なら体力減少
			if (diffLeftArm.Length() <= RANGE_DISTANCE) //ダメージが入る範囲
			{
				m_leftArm->ApplyDamage(ENEMY_BATTLESHIPGUN_DAMAGE);
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
		if (weaponNum == MACHINEGUN_NUM)			//マシンガン
		{
			//距離を測り一定以下なら体力減少
			if (diffLeftLeg.Length() <= RANGE_DISTANCE) //ダメージが入る範囲
			{
				m_leftLeg->ApplyDamage(ENEMY_MACHINEGUN_DAMAGE);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == GIGATONCANNON_NUM)		//ギガトンキャノン
		{
			//距離を測り一定以下なら体力減少
			if (diffLeftLeg.Length() <= RANGE_DISTANCE) //ダメージが入る範囲
			{
				m_leftLeg->ApplyDamage(ENEMY_GIGATONCANNON_DAMAGE);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == BATTLESHIPGUN_NUM)	//戦艦砲
		{
			//距離を測り一定以下なら体力減少
			if (diffLeftLeg.Length() <= RANGE_DISTANCE) //ダメージが入る範囲
			{
				m_leftLeg->ApplyDamage(ENEMY_BATTLESHIPGUN_DAMAGE);
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
		if (weaponNum == MACHINEGUN_NUM)			//マシンガン
		{
			//距離を測り一定以下なら体力減少
			if (diffRightArm.Length() <= RANGE_DISTANCE) //ダメージが入る範囲
			{
				m_rightArm->ApplyDamage(ENEMY_MACHINEGUN_DAMAGE);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == GIGATONCANNON_NUM)		//ギガトンキャノン
		{
			//距離を測り一定以下なら体力減少
			if (diffRightArm.Length() <= RANGE_DISTANCE) //ダメージが入る範囲
			{
				m_rightArm->ApplyDamage(ENEMY_GIGATONCANNON_DAMAGE);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == BATTLESHIPGUN_NUM)	//戦艦砲
		{
			//距離を測り一定以下なら体力減少
			if (diffRightArm.Length() <= RANGE_DISTANCE) //ダメージが入る範囲
			{
				m_rightArm->ApplyDamage(ENEMY_BATTLESHIPGUN_DAMAGE);
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
		if (weaponNum == MACHINEGUN_NUM)			//マシンガン
		{
			//距離を測り一定以下なら体力減少
			if (diffRightLeg.Length() <= RANGE_DISTANCE) //ダメージが入る範囲
			{
				m_rightLeg->ApplyDamage(ENEMY_MACHINEGUN_DAMAGE);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == GIGATONCANNON_NUM)		//ギガトンキャノン
		{
			//距離を測り一定以下なら体力減少
			if (diffRightLeg.Length() <= RANGE_DISTANCE) //ダメージが入る範囲
			{
				m_rightLeg->ApplyDamage(ENEMY_GIGATONCANNON_DAMAGE);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == BATTLESHIPGUN_NUM)	//戦艦砲
		{
			//距離を測り一定以下なら体力減少
			if (diffRightLeg.Length() <= RANGE_DISTANCE) //ダメージが入る範囲
			{
				m_rightLeg->ApplyDamage(ENEMY_BATTLESHIPGUN_DAMAGE);
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
		if (weaponNum == MACHINEGUN_NUM)			//マシンガン
		{
			//距離を測り一定以下なら体力減少
			if (diffShoulder.Length() <= RANGE_DISTANCE) //ダメージが入る範囲
			{
				m_shoulder->ApplyDamage(ENEMY_MACHINEGUN_DAMAGE);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == GIGATONCANNON_NUM)		//ギガトンキャノン
		{
			//距離を測り一定以下なら体力減少
			if (diffShoulder.Length() <= RANGE_DISTANCE) //ダメージが入る範囲
			{
				m_shoulder->ApplyDamage(ENEMY_GIGATONCANNON_DAMAGE);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == BATTLESHIPGUN_NUM)	//戦艦砲
		{
			//距離を測り一定以下なら体力減少
			if (diffShoulder.Length() <= RANGE_DISTANCE) //ダメージが入る範囲
			{
				m_shoulder->ApplyDamage(ENEMY_BATTLESHIPGUN_DAMAGE);
				DestroyWithImpactEffect();
			}
		}
	}
	//---------------------------------------------------------------------------------------------------
}

void Enemy_Bullet::PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale)
{

	//エフェクトの再生
	EffectEmitter* m_effect = NewGO<EffectEmitter>(0);
	m_effect->Init(name);
	m_effect->SetPosition(pos);
	m_effect->SetRotation(rot);
	m_effect->SetScale(scale);
	m_effect->Play();

}

void Enemy_Bullet::Render(RenderContext& rc)
{
	if (m_enemyMama != nullptr)
	{
		if (m_enemyMama->GetWeponKind() == GIGAPLASMA_NUM)	//ギガプラズマ
		{

		}
		else if (m_enemyMama->GetWeponKind() == MACHINEGUN_NUM)	//マシンガン
		{
			m_bulletModel->Draw(rc);
		}
		else if (m_enemyMama->GetWeponKind() == HELLFIRE_NUM)	//ヘイルファイヤーライフル
		{

		}
	}
	else if (m_enemyNearMama != nullptr)
	{
		if (m_enemyNearMama->GetWeponKind() == GIGATONCANNON_NUM)	//ギガトンキャノン
		{
			m_bulletModel->Draw(rc);
		}
	}
	else if (m_enemyFarMama != nullptr)
	{
		if (m_enemyFarMama->GetWeponKind() == MISSILE_NUM)	//ミサイル
		{

		}
		else if (m_enemyFarMama->GetWeponKind() == BATTLESHIPGUN_NUM)	//戦艦砲
		{
			m_bulletModel->Draw(rc);
		}
	}
}