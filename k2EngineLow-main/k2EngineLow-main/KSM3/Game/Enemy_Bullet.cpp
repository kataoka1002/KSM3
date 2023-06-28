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
	//対象物との当たり判定距離
	const float RANGE_DISTANCE = 100.0f;

	//ダメージ量
	const float ENEMY_MACHINEGUN_DAMAGE = 0.5f;
	const float ENEMY_GIGATONCANNON_DAMAGE = 50.0f;
	const float ENEMY_BATTLESHIPGUN_DAMAGE = 25.0f;

	//スピード
	const float MACHINEGUN_BULLET_SPEED = 2.0f;
	const float GIGATONCANNON_BULLET_SPEED = 2.0f;
	const float BATTLESHIPGUN_BULLET_SPEED = 1.7f;

	//弾のモデルの大きさ
	const Vector3 MACHINEGUN_BULLET_SCALE = { 4.0f,4.0f,4.0f };
	const Vector3 GIGATONCANNON_BULLET_SCALE = { 15.0f,15.0f,10.0f };
	const Vector3 BATTLESHIPGUN_BULLET_SCALE = { 10.0f,10.0f,10.0f };

	//エフェクトの大きさ
	const Vector3 MACHINEGUNE_EFFECT_SCALE = { 10.0f,10.0f,10.0f };
	const Vector3 BATTLESHIPGUN_EFFECT_SCALE = { 5.7f, 5.7f, 5.7f };
}


Enemy_Bullet::Enemy_Bullet() 
{
	
}

Enemy_Bullet::~Enemy_Bullet() 
{
	
}

void Enemy_Bullet::DestroyWithImpactEffect()
{

	//中距離エネミーのとき
	if (m_enemyMama != nullptr)
	{

		//マシンガンのとき
		if (m_enemyMama->GetWeponKind() == MACHINEGUN_NUM)
		{
			
			//マシンガンの弾の煙エフェ
			PlayEffect(enMasinganKemuri, m_position, m_rot, MACHINEGUNE_EFFECT_SCALE);

		}

	}
	//近距離エネミーのとき
	else if (m_enemyNearMama != nullptr)
	{

		//ギガトンキャノンのとき
		if (m_enemyNearMama->GetWeponKind() == GIGATONCANNON_NUM)
		{

			//画面を揺らす
			GameCamera* m_camera = FindGO<GameCamera>("gamecamera");
			m_camera->SetVibFlag(true);

		}

	}
	//遠距離エネミーのとき
	else if (m_enemyFarMama != nullptr)
	{
		
		//戦艦砲のとき
		if (m_enemyFarMama->GetWeponKind() == BATTLESHIPGUN_NUM)	
		{

			//戦艦砲エフェクトの初期化と再生
			PlayEffect(enTyakudan, m_position, m_rot, BATTLESHIPGUN_EFFECT_SCALE);


			//着弾したら効果音発生
			m_battleShipGunTyakutiSE = NewGO<SoundSource>(0);			//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
			m_battleShipGunTyakutiSE->Init(enButtleShipTyakudan);		//初期化
			m_battleShipGunTyakutiSE->SetVolume(2.0f * m_game->GetSEVol());	//音量調整
			m_battleShipGunTyakutiSE->Play(false);


			//画面を揺らす
			GameCamera* m_camera = FindGO<GameCamera>("gamecamera");
			m_camera->SetVibFlag(true);

		}
	}


	//自分自身の削除
	DeleteGO(this);

}

bool Enemy_Bullet::Start()
{

	//プレイヤーを探す
	m_player = FindGO<Player>("player");


	//リザルト中なら
	if (m_player->GetGameState() == RESULT_NUM)
	{

		//自分自身の削除
		DeleteGO(this);

	}


	//カスタマイズUIを探す
	m_customizeUI = FindGO<Customize_UI_ver2>("customize_ui_ver2");


	//コア武器を探す
	m_coreWeapons = FindGO<Core_weapons>("core_weapons");


	//ゲームを探す
	m_game = FindGO<Game>("game");


	//プレイヤーの武器を検索する
	FindWeapon();	
	
	
	//武器やエフェクトの設定
	Setup();		

		
	return true;

}

void Enemy_Bullet::FindWeapon()
{

	//プレイヤーが死んでいたらリターン
	if (m_player->GetPlayerDead() == true)
	{
		return;
	}


	//左腕が存在したら
	if (m_customizeUI->GetLeftArmWeapon() != nullptr)
	{
		
		//カスタマイズUIにあるポインタを渡してやる
		m_leftArm = m_customizeUI->GetLeftArmWeapon();

	}

	//左足が存在したら
	if (m_customizeUI->GetLeftLegWeapon() != nullptr)
	{
		
		//カスタマイズUIにあるポインタを渡してやる
		m_leftLeg = m_customizeUI->GetLeftLegWeapon();

	}

	//右腕が存在したら
	if (m_customizeUI->GetRightArmWeapon() != nullptr)
	{
		
		//カスタマイズUIにあるポインタを渡してやる
		m_rightArm = m_customizeUI->GetRightArmWeapon();

	}

	//右足が存在したら
	if (m_customizeUI->GetRightLegWeapon() != nullptr)
	{
		
		//カスタマイズUIにあるポインタを渡してやる
		m_rightLeg = m_customizeUI->GetRightLegWeapon();

	}

	//肩が存在したら
	if (m_customizeUI->GetShoulderWeapon() != nullptr)
	{
		
		//カスタマイズUIにあるポインタを渡してやる
		m_shoulder = m_customizeUI->GetShoulderWeapon();

	}

}

void Enemy_Bullet::Setup() 
{

	//メモリの確保(make_unique関数内部でnewしている)
	m_bulletModel = std::make_unique<ModelRender>();


	//親が中距離エネミーのとき
	if (m_enemyMama != nullptr)
	{

		switch (m_enemyMama->GetWeponKind())
		{
		case GIGAPLASMA_NUM:	//ギガプラズマ

			break;

		case MACHINEGUN_NUM:	//マシンガン

			//モデルの初期化
			InitBullet("Assets/modelData/V_P_bullet.tkm", MACHINEGUN_BULLET_SCALE, m_enemyMama->GetForward(), m_enemyMama->GetRot());
			

			//エフェクトの再生
			Effect(MACHINEGUN_NUM);
			
			//音はエネミー側で鳴らしている

			break;

		case HELLFIRE_NUM:	//ヘイルファイヤーライフル

			break;

		default:

			break;

		}

	}
	//親が近距離エネミーのとき
	else if (m_enemyNearMama != nullptr)
	{

		switch (m_enemyNearMama->GetWeponKind())
		{
		case GIGATONCANNON_NUM:	//ギガトンキャノン

			//モデルの初期化
			InitBullet("Assets/modelData/V_P_bullet.tkm", GIGATONCANNON_BULLET_SCALE, m_enemyNearMama->GetForward(), m_enemyNearMama->GetRot());
			

			//エフェクトの再生
			Effect(GIGATONCANNON_NUM);

			//爆発音はエネミー側で鳴らしている

			break;

		default:

			break;

		}

	}
	//親距離エネミーのとき
	else if (m_enemyFarMama != nullptr)
	{

		switch (m_enemyFarMama->GetWeponKind())
		{
		case MISSILE_NUM:	//ミサイル

			break;

		case BATTLESHIPGUN_NUM:	//戦艦砲

			//モデルの初期化
			InitBullet("Assets/modelData/V_P_bullet.tkm", BATTLESHIPGUN_BULLET_SCALE, m_enemyFarMama->GetForward(), m_enemyFarMama->GetRot());


			//エフェクトの再生
			Effect(BATTLESHIPGUN_NUM);

			break;

		default:

			break;

		}

	}

}

void Enemy_Bullet::InitBullet(const char* file, Vector3 scale, Vector3 forward, Quaternion rot)
{

	//モデルの初期化
	m_bulletModel->Init(file);


	//大きさ設定
	m_bulletModel->SetScale(scale);


	//エネミーから見て正しい位置に弾を設定
	originRotation.Multiply(m_bulletLocalPosition);	


	//回転量を教える
	m_rot = originRotation;

	
	//それに親から見た位置を足して最終的な武器の位置を決定
	m_position += m_bulletLocalPosition;	


	//バレットの前方向の設定
	m_bulletFowrad = forward;


	//更新
	m_bulletModel->SetRotation(rot);
	m_bulletModel->SetPosition(m_position);

}

void Enemy_Bullet::Update() 
{

	//メインゲーム中
	if (m_player->GetGameState() == MAIN_GAME_NUM)
	{

		//位置Yが0以下になると
		if (m_position.y <= 0.0f)
		{

			//削除しつつエフェクトを再生
			DestroyWithImpactEffect();

		}


		//親によって関数を変える
		if (m_enemyMama != nullptr)
		{

			//移動処理
			Move();	


			//ターゲットを探す
			MamaCheck(m_enemyMama->GetWeponKind());

		}
		else if (m_enemyNearMama != nullptr)
		{

			//移動処理
			MoveNear();


			//ターゲットを探す
			MamaCheck(m_enemyNearMama->GetWeponKind());

		}
		else if (m_enemyFarMama != nullptr)
		{

			//移動処理
			MoveFar();


			//ターゲットを探す
			MamaCheck(m_enemyFarMama->GetWeponKind());

		}

	}	
	//リザルト中
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

void Enemy_Bullet::Move()
{
	
	//ギガプラズマ
	if (m_enemyMama->GetWeponKind() == GIGAPLASMA_NUM)	
	{

	}
	//マシンガン
	else if (m_enemyMama->GetWeponKind() == MACHINEGUN_NUM)	
	{

		//弾を前に飛ばす
		m_bulletSpeed += m_bulletFowrad * MACHINEGUN_BULLET_SPEED;
		m_position += m_bulletSpeed;


		//弾とエネミー(親)の距離を計算
		Vector3 m_toEnemy = m_enemyMama->GetPos() - m_position;
		float m_dirToEnemy = m_toEnemy.Length();


		//一定距離以上なら
		if (m_dirToEnemy >= 1800.0f)
		{

			//弾を消す
			DestroyWithImpactEffect();

		}


		//バレットの更新
		m_bulletModel->SetRotation(m_rot);
		m_bulletModel->SetPosition(m_position);
		m_bulletModel->Update();

	}
	//ヘルファイヤライフル
	else if (m_enemyMama->GetWeponKind() == HELLFIRE_NUM)	
	{

	}

}

void Enemy_Bullet::MoveNear()
{
	
	//ギガトンキャノン
	if (m_enemyNearMama->GetWeponKind() == GIGATONCANNON_NUM)	
	{

		//弾を前に飛ばす
		m_bulletSpeed += m_bulletFowrad * GIGATONCANNON_BULLET_SPEED;
		m_position += m_bulletSpeed;


		//弾とエネミー(親)の距離を計算
		Vector3 m_toEnemy = m_enemyNearMama->GetPos() - m_position;
		float m_dirToEnemy = m_toEnemy.Length();
		
		
		//一定距離以上なら
		if (m_dirToEnemy >= 100.0f)
		{
			
			//弾を消す
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
	
	//ミサイル
	if (m_enemyFarMama->GetWeponKind() == MISSILE_NUM)	
	{

	}
	//戦艦砲
	else if (m_enemyFarMama->GetWeponKind() == BATTLESHIPGUN_NUM)	
	{

		//弾を前に飛ばす
		m_bulletSpeed += m_bulletFowrad * BATTLESHIPGUN_BULLET_SPEED;


		//少しづつ下に落とす
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

void Enemy_Bullet::MamaCheck(int weaponNum)
{
	
	//プレイヤーの情報が入っているなら
	if (m_player != nullptr)	
	{

		//距離を測りつつダメージを与える
		ApplyDamageWithDistanceCheck(m_player, Vector3{ m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y + 50.0f, m_player->GetPlayerPosition().z }, weaponNum);
	
	}

	
	//左腕に情報が入っているなら
	if (m_leftArm != nullptr)	
	{

		//距離を測りつつダメージを与える
		ApplyDamageWithDistanceCheck(m_leftArm, m_leftArm->GetPosition(), weaponNum);
	
	}

	
	//左足に情報が入っているなら
	if (m_leftLeg != nullptr)	
	{

		//距離を測りつつダメージを与える
		ApplyDamageWithDistanceCheck(m_leftLeg, m_leftLeg->GetPosition(), weaponNum);

	}

	
	//右手に情報が入っているなら
	if (m_rightArm != nullptr)	
	{

		//距離を測りつつダメージを与える
		ApplyDamageWithDistanceCheck(m_rightArm, m_rightArm->GetPosition(), weaponNum);

	}

	
	//右足に情報が入っているなら
	if (m_rightLeg != nullptr)	
	{

		//距離を測りつつダメージを与える
		ApplyDamageWithDistanceCheck(m_rightLeg, m_rightLeg->GetPosition(), weaponNum);

	}

	
	//肩に情報が入っているなら
	if (m_shoulder != nullptr)	
	{

		//距離を測りつつダメージを与える
		ApplyDamageWithDistanceCheck(m_shoulder, m_shoulder->GetPosition(), weaponNum);

	}

}

template<typename T>
void Enemy_Bullet::ApplyDamageWithDistanceCheck(T targetName, Vector3 targetPos, int weaponNum)
{

	//対象物までのベクトルを求める
	Vector3 targetToBullet = m_position - targetPos;


	//マシンガン
	if (weaponNum == MACHINEGUN_NUM)			
	{

		//距離が一定以下なら
		if (targetToBullet.Length() <= RANGE_DISTANCE) 
		{

			//ダメージを与える
			targetName->ApplyDamage(ENEMY_MACHINEGUN_DAMAGE);


			//壊れつつエフェクトを再生
			DestroyWithImpactEffect();

		}

	}
	//ギガトンキャノン
	else if (weaponNum == GIGATONCANNON_NUM)		
	{

		//距離が一定以下なら
		if (targetToBullet.Length() <= RANGE_DISTANCE) 
		{
			
			//ダメージを与える
			targetName->ApplyDamage(ENEMY_GIGATONCANNON_DAMAGE);
			
			
			//壊れつつエフェクトを再生
			DestroyWithImpactEffect();

		}

	}
	//戦艦砲
	else if (weaponNum == BATTLESHIPGUN_NUM)	
	{

		//距離が一定以下なら
		if (targetToBullet.Length() <= RANGE_DISTANCE) 
		{
			
			//ダメージを与える
			targetName->ApplyDamage(ENEMY_BATTLESHIPGUN_DAMAGE);
			
			
			//壊れつつエフェクトを再生
			DestroyWithImpactEffect();

		}

	}

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

	//親が中距離
	if (m_enemyMama != nullptr)
	{
		
		//ギガプラズマ
		if (m_enemyMama->GetWeponKind() == GIGAPLASMA_NUM)	
		{

		}
		//マシンガン
		else if (m_enemyMama->GetWeponKind() == MACHINEGUN_NUM)	
		{

			//弾の描画
			m_bulletModel->Draw(rc);

		}
		//ヘイルファイヤーライフル
		else if (m_enemyMama->GetWeponKind() == HELLFIRE_NUM)	
		{

		}

	}
	//親が近距離
	else if (m_enemyNearMama != nullptr)
	{

		//ギガトンキャノン
		if (m_enemyNearMama->GetWeponKind() == GIGATONCANNON_NUM)	
		{
			
			//弾の描画
			m_bulletModel->Draw(rc);

		}

	}
	//親が遠距離
	else if (m_enemyFarMama != nullptr)
	{
		
		//ミサイル
		if (m_enemyFarMama->GetWeponKind() == MISSILE_NUM)	
		{

		}
		//戦艦砲
		else if (m_enemyFarMama->GetWeponKind() == BATTLESHIPGUN_NUM)	
		{
			
			//弾の描画
			m_bulletModel->Draw(rc);

		}

	}

}