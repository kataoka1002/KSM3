#include "stdafx.h"
#include "Boss_Cannon_attack.h"
#include "Boss_Cannon.h"
#include "Customize_UI_ver2.h"
#include "Boss.h"
#include "Player.h"
#include "Core_weapons.h"
#include "sound/SoundEngine.h"
#include "Game.h"
#include "GameCamera.h"
#include "Left_arm_weapons.h"
#include "Left_leg_weapons.h"
#include "Right_arm_weapons.h"
#include "Right_leg_weapons.h"
#include "Shoulder_weapons.h"

Boss_Cannon_attack::Boss_Cannon_attack()
{
	m_customizeUI = FindGO<Customize_UI_ver2>("customize_ui_ver2");
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

Boss_Cannon_attack::~Boss_Cannon_attack()
{
	b_a_weapons->attack_state = false;
}

bool Boss_Cannon_attack::Start() {
	m_game = FindGO<Game>("game");
	b_a_boss = FindGO<Boss>("boss");
	b_a_player = FindGO<Player>("player");
	b_a_weapons = FindGO<Boss_Cannon>("boss_cannon");
	b_a_core_weapons = FindGO<Core_weapons>("core_weapons");
	

	

	//音(仮)
	g_soundEngine->ResistWaveFileBank(2, "Assets/audio/Taihou_kouho1.wav");

	
	SetUp();

	return true;
}

void Boss_Cannon_attack::DestroyWithImpactEffect() {
	if (Landing_count == 0){
		m_Cannon_LangingSE = NewGO<SoundSource>(0);			//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
		m_Cannon_LangingSE->Init(en_Boss_cannon_Langing_SE);		//初期化
		m_Cannon_LangingSE->SetVolume(2.0f * m_game->GetSEVol());	//音量調整
		m_Cannon_LangingSE->Play(false);

		m_weaponEffect = NewGO<EffectEmitter>(0);
		m_weaponEffect->Init(enBoss_Cannon_Landing);
		m_weaponEffect->SetScale({ 70.0f,70.0f,70.0f });
		m_weaponEffect->SetPosition(firing_position);
		m_weaponEffect->Play();
		efePosi = firing_position;
	}
	if (Landing_count == 126) {
		//戦艦砲エフェクトの初期化と再生
		m_battleShipGunTyakutiSE = NewGO<SoundSource>(0);			//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
		m_battleShipGunTyakutiSE->Init(enButtleShipTyakudan);		//初期化
		m_battleShipGunTyakutiSE->SetVolume(2.0f * m_game->GetSEVol());	//音量調整
		m_battleShipGunTyakutiSE->Play(false);

		m_weaponEffect = NewGO<EffectEmitter>(0);
		m_weaponEffect->Init(enTyakudan);
		m_weaponEffect->SetScale({ 70.0f,70.0f,70.0f });
		m_weaponEffect->SetPosition(efePosi);
		m_weaponEffect->Play();
		Damage(true);
	}
	Landing_count++;
	if (fast == true) {
		//着弾したら効果音発生
		
		
		//画面を揺らす
		GameCamera* m_camera = FindGO<GameCamera>("gamecamera");
		m_camera->SetBigVibFlag(true);
		
		fast = false;
	}
	if (Landing_count == 130) {
		// 着弾したら死ぬ
		DeleteGO(m_weaponEffect);
		m_weaponEffect = nullptr;
		DeleteGO(m_BulletEffect);
		m_BulletEffect = nullptr;
		DeleteGO(this);
	}

}

void Boss_Cannon_attack::SetUp()
{
	
	//弾モデル。
	GameCamera* m_camera = FindGO<GameCamera>("gamecamera");
	m_camera->SetVibFlag(true);
	b_a_Bullet.Init("Assets/modelData/V_P_bullet.tkm");
	b_a_aiming.Multiply(m_bulletLocalPosition);	//掛け算
	m_rot = b_a_aiming;
	firing_position += m_bulletLocalPosition;
	b_a_Bullet.SetScale(30);
	b_a_Bullet.SetPosition(firing_position);
	b_a_Bullet.SetRotation(m_rot);
	b_a_Bullet.Update();

	Effect();
	//b_a_Bullet_Fowrad = b_a_weapons->b_w_Fowrad;
	//firing_position.y += 100.0f;
	//firing_position.x -= 600.0f;
	//b_a_Bullet.SetRotation(b_a_boss->boss_rotation);
	//b_a_Bullet.SetPosition(firing_position);

	
}

void Boss_Cannon_attack::Update()
{
	
		if (Bullet_efe_count % 32 == 0) {
			m_BulletEffect = NewGO<EffectEmitter>(0);
			m_BulletEffect->Init(enBoss_Cannon_Bullet);
			m_BulletEffect->SetScale({ 35.0f,35.0f,35.0f });
			
			m_BulletEffect->Play();
		}
		m_BulletEffect->SetPosition(firing_position);
		Bullet_efe_count++;

	if (b_a_player->GetGameState() == MAIN_GAME_NUM)
	{
		fall_speed += 0.002;

		if (firing_position.y <= 0.0f)
		{
			DestroyWithImpactEffect();
		}
		b_a_Bullet.Update();
		Damage(false);
		Move();
		
	}
	else if (b_a_player->GetGameState() == RESULT_NUM)
	{
		DeleteGO(this);	//リザルト画面に行くと消す
	}

	if (b_a_player->GetGameEndState() == 1)
	{
		DeleteGO(this);	//プレイヤーがポーズ画面からゲームを終了させると消す
	}
	
}

void Boss_Cannon_attack::Effect() {
	//m_weaponEffect = NewGO<EffectEmitter>(0);
	//m_weaponEffect->Init(enMasinganHibana);
	//m_weaponEffect->SetScale({ 10.0f,10.0f,10.0f });
	//m_weaponEffect->SetPosition(firing_position);
	//m_weaponEffect->Play();
}

void Boss_Cannon_attack::Move()
{

	//弾を前に飛ばす処理
	Move_speed += b_a_Bullet_Fowrad * 3.0f;
	Move_speed.y -= 0.2+fall_speed;
	firing_position += Move_speed;

	//バレットの更新
	b_a_Bullet.SetRotation(m_rot);
	b_a_Bullet.SetPosition(firing_position);
	b_a_Bullet.Update();


}

void Boss_Cannon_attack::Damage(bool No_tyakudan)
{
	if (No_tyakudan==true) {
		//---------------------------------------------------------------------------------------------------
		if (b_a_player != nullptr)	//プレイヤーの情報が入っているなら
		{
			//弾とプレイヤーの距離を測る
			Vector3 diffPlayer = efePosi - Vector3{ b_a_player->GetPlayerPosition().x, b_a_player->GetPlayerPosition().y + 50.0f, b_a_player->GetPlayerPosition().z };

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffPlayer.Length() <= 500.0f) //ダメージが入る範囲
			{
				b_a_player->ApplyDamage(200.0f);
				
			}

		}
		 
		 
		
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_leftArm != nullptr)	//左腕に情報が入っているなら
		{
			//弾と左腕の距離を測る
			Vector3 diffLeftArm = efePosi - m_leftArm->GetPosition();

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffLeftArm.Length() <= 500.0f) //ダメージが入る範囲
			{
				m_leftArm->ApplyDamage(200.0f);
			}
		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_leftLeg != nullptr)	//左足に情報が入っているなら
		{
			//弾と左腕の距離を測る
			Vector3 diffLeftLeg = efePosi - m_leftLeg->GetPosition();

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffLeftLeg.Length() <= 500.0f) //ダメージが入る範囲
			{
				m_leftLeg->ApplyDamage(200.0f);
				
			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_rightArm != nullptr)	//右手に情報が入っているなら
		{
			//弾と左腕の距離を測る
			Vector3 diffRightArm = efePosi - m_rightArm->GetPosition();

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffRightArm.Length() <= 500.0f) //ダメージが入る範囲
			{
				m_rightArm->ApplyDamage(200.0f);
				
			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_rightLeg != nullptr)	//右足に情報が入っているなら
		{
			//弾と左腕の距離を測る
			Vector3 diffRightLeg = efePosi - m_rightLeg->GetPosition();

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffRightLeg.Length() <= 500.0f) //ダメージが入る範囲
			{
				m_rightLeg->ApplyDamage(200.0f);
				
			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_shoulder != nullptr)	//肩に情報が入っているなら
		{
			//弾と左腕の距離を測る
			Vector3 diffShoulder = efePosi - m_shoulder->GetPosition();

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffShoulder.Length() <= 500.0f) //ダメージが入る範囲
			{
				m_shoulder->ApplyDamage(200.0f);
				
			}

		}
		//---------------------------------------------------------------------------------------------------
	}
	else if(No_tyakudan==false){

	
	//---------------------------------------------------------------------------------------------------
	if (b_a_player != nullptr)	//プレイヤーの情報が入っているなら
	{
		//弾とプレイヤーの距離を測る
		Vector3 diffPlayer = firing_position - Vector3{ b_a_player->GetPlayerPosition().x, b_a_player->GetPlayerPosition().y + 50.0f, b_a_player->GetPlayerPosition().z };

		//武器によってダメージを変える
		
			//距離を測り一定以下なら体力減少
			if (diffPlayer.Length() <= 200.0f) //ダメージが入る範囲
			{
				b_a_player->ApplyDamage(200.0f);
				DestroyWithImpactEffect();
			}
		
	}
	//---------------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------------
	if (m_leftArm != nullptr)	//左腕に情報が入っているなら
	{
		//弾と左腕の距離を測る
		Vector3 diffLeftArm = firing_position - m_leftArm->GetPosition();

		//武器によってダメージを変える
		
			//距離を測り一定以下なら体力減少
			if (diffLeftArm.Length() <= 200.0f) //ダメージが入る範囲
			{
				m_leftArm->ApplyDamage(200.0f);
				DestroyWithImpactEffect();
			}
		}
	//---------------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------------
	if (m_leftLeg != nullptr)	//左足に情報が入っているなら
	{
		//弾と左腕の距離を測る
		Vector3 diffLeftLeg = firing_position - m_leftLeg->GetPosition();

		//武器によってダメージを変える
		
			//距離を測り一定以下なら体力減少
			if (diffLeftLeg.Length() <= 200.0f) //ダメージが入る範囲
			{
				m_leftLeg->ApplyDamage(200.0f);
				DestroyWithImpactEffect();
			}
		
	}
	//---------------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------------
	if (m_rightArm != nullptr)	//右手に情報が入っているなら
	{
		//弾と左腕の距離を測る
		Vector3 diffRightArm = firing_position - m_rightArm->GetPosition();

		//武器によってダメージを変える
		
			//距離を測り一定以下なら体力減少
			if (diffRightArm.Length() <= 200.0f) //ダメージが入る範囲
			{
				m_rightArm->ApplyDamage(200.0f);
				DestroyWithImpactEffect();
			}
		
	}
	//---------------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------------
	if (m_rightLeg != nullptr)	//右足に情報が入っているなら
	{
		//弾と左腕の距離を測る
		Vector3 diffRightLeg = firing_position - m_rightLeg->GetPosition();

		//武器によってダメージを変える
		
			//距離を測り一定以下なら体力減少
			if (diffRightLeg.Length() <= 200.0f) //ダメージが入る範囲
			{
				m_rightLeg->ApplyDamage(200.0f);
				DestroyWithImpactEffect();
			}
		
	}
	//---------------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------------
	if (m_shoulder != nullptr)	//肩に情報が入っているなら
	{
		//弾と左腕の距離を測る
		Vector3 diffShoulder = firing_position - m_shoulder->GetPosition();

		//武器によってダメージを変える
		
			//距離を測り一定以下なら体力減少
			if (diffShoulder.Length() <= 200.0f) //ダメージが入る範囲
			{
				m_shoulder->ApplyDamage(200.0f);
				DestroyWithImpactEffect();
			}
		
	}
	//---------------------------------------------------------------------------------------------------
}
}


void Boss_Cannon_attack::Render(RenderContext& rc)
{
	b_a_Bullet.Draw(rc);
}