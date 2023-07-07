#include "stdafx.h"
#include "Boss_Turbo_attack.h"
#include "Boss_Turbo.h"
#include "Boss.h"
#include "Player.h"
#include "Customize_UI_ver2.h"
#include "Core_weapons.h"
#include "sound/SoundEngine.h"
#include "Game.h"
#include "Left_arm_weapons.h"
#include "Left_leg_weapons.h"
#include "Right_arm_weapons.h"
#include "Right_leg_weapons.h"
#include "Shoulder_weapons.h"

Boss_Turbo_attack::Boss_Turbo_attack()
{
	m_customizeUI = FindGO<Customize_UI_ver2>("customize_ui_ver2");
	//左腕
	if (m_customizeUI->GetLeftArmWeapon() != nullptr)
	{
		m_leftArm = m_customizeUI->GetLeftArmWeapon();	//カスタマイズUIにあるポインタを渡してやる
	}
	//左足
	if (m_customizeUI->GetLeftLegWeapon() != nullptr)
	{
		m_leftLeg = m_customizeUI->GetLeftLegWeapon();	//カスタマイズUIにあるポインタを渡してやる
	}
	//右腕
	if (m_customizeUI->GetRightArmWeapon() != nullptr)
	{
		m_rightArm = m_customizeUI->GetRightArmWeapon();	//カスタマイズUIにあるポインタを渡してやる
	}
	//右足
	if (m_customizeUI->GetRightLegWeapon() != nullptr)
	{
		m_rightLeg = m_customizeUI->GetRightLegWeapon();	//カスタマイズUIにあるポインタを渡してやる
	}
	//肩
	if (m_customizeUI->GetShoulderWeapon() != nullptr)
	{
		m_shoulder = m_customizeUI->GetShoulderWeapon();	//カスタマイズUIにあるポインタを渡してやる
	}
}

Boss_Turbo_attack::~Boss_Turbo_attack()
{
	m_weapon->m_attackState = false;
}

bool Boss_Turbo_attack::Start()
{
	m_boss = FindGO<Boss>("boss");
	m_player = FindGO<Player>("player");
	m_weapon = FindGO<Boss_Turbo>("boss_turbo");
	m_coreWeapon = FindGO<Core_weapons>("core_weapons");
	//弾モデル。
	//b_a_Bullet.Init("Assets/modelData/V_P_bullet.tkm");
	//m_characterController.Init(1170.0f, 150.0f, m_bulletLocalPosition);
	//音(仮)
	/*g_soundEngine->ResistWaveFileBank(2, "Assets/audio/Taihou_kouho1.wav");

	b_attack_SE = NewGO<SoundSource>(0);
	b_attack_SE->Init(2);
	b_attack_SE->SetVolume(0.2f);
	b_attack_SE->Play(false);*/
	SetUp();

	return true;
}

void Boss_Turbo_attack::DestroyWithImpactEffect()
{
	/*if (Landing_count == 0) {
		m_weaponEffect = NewGO<EffectEmitter>(0);
		m_weaponEffect->Init(enTatumaki_fire);
		m_weaponEffect->SetScale({ 40.0f,40.0f,40.0f });
		m_weaponEffect->SetPosition(firing_position);
		m_weaponEffect->SetRotation(b_a_aiming);
		m_weaponEffect->Play();
		
		
	}*/
	//if (Landing_count == 0) {
	//	//戦艦砲エフェクトの初期化と再生
	//	m_weaponEffect = NewGO<EffectEmitter>(0);
	//	m_weaponEffect->Init(enTatumaki);
	//	m_weaponEffect->SetScale({ 70.0f,70.0f,70.0f });
	//	m_weaponEffect->SetPosition(efePosi);
	//	m_weaponEffect->SetRotation(b_a_aiming);
	//	m_weaponEffect->Play();
	//	efePosi = firing_position;
	//	Damage(true);
	//}
	m_loadingCount++;
	if (m_loadingCount == 55) {
		// 着弾したら死ぬ
		DeleteGO(this);
	}
}

void Boss_Turbo_attack::SetUp()
{
		//b_a_Bullet.Init("Assets/modelData/V_P_bullet.tkm");
		m_aim.Multiply(m_bulletLocalPosition);	//掛け算
		//m_rot = b_a_weapons->b_w_rotation;
		m_firePosition += m_bulletLocalPosition;
		m_firePosition = m_weapon->m_position;
		m_bulletForward = m_weapon->m_forward;
		m_bulletModel.SetScale(30);
		m_bulletModel.SetPosition(m_firePosition);
		//b_a_Bullet.SetRotation(m_rot);
		m_bulletModel.Update();
}

void Boss_Turbo_attack::Update()
{	
	if (m_player->GetGameState() == MAIN_GAME_NUM)
	{
		DestroyWithImpactEffect();
		m_bulletModel.Update();
		Damage(false);
		Move();
		Rotation();
	}
	else if (m_player->GetGameState() == RESULT_NUM)
	{
		DeleteGO(this);	//リザルト画面に行くと消す
	}

	if (m_player->GetGameEndState() == 1)
	{
		DeleteGO(this);	//プレイヤーがポーズ画面からゲームを終了させると消す
	}
}

void Boss_Turbo_attack::Rotation() 
{
		//エネミーからプレイヤーが入ってきたら追いかける。
		//Vector3 toPlayer = b_a_player->GetPlayerPosition() - firing_position;

		//プレイヤーとの距離を計算する。
		//float distToPlayer = toPlayer.Length();
		////プレイヤーに向かって伸びるベクトルを正規化する。
		//Vector3 toPlayerDir = toPlayer;
		//toPlayerDir.Normalize();
		//b_a_Bullet_Fowrad = toPlayerDir;
		/*m_rot.SetRotationY(atan2(b_a_Bullet_Fowrad.x, b_a_Bullet_Fowrad.z));
		b_a_Bullet.SetRotation(m_rot);*/

}

void Boss_Turbo_attack::Move()
{
	//弾を前に飛ばす処理
		m_moveSpeed += m_bulletForward *3.5f;
		//Move_speed.y -= 0.2 + fall_speed;
		//firing_position= b_a_weapons->b_w_position;
		m_firePosition += m_moveSpeed;
	//バレットの更新
		m_bulletModel.SetRotation(m_rot);
		m_bulletModel.SetPosition(m_firePosition);
		m_bulletModel.Update();
}

void Boss_Turbo_attack::Effect()
{
	/*TatumakiEffect = NewGO<EffectEmitter>(0);
	TatumakiEffect->Init(enTatumaki);
	TatumakiEffect->SetScale({ 40.0f,40.0f,40.0f });
	TatumakiEffect->SetPosition(to_core_weapons);
	TatumakiEffect->Play();*/
}

void Boss_Turbo_attack::Damage(bool No_tyakudan) 
{
	//if (No_tyakudan == true) {
	//	//---------------------------------------------------------------------------------------------------
	//	if (b_a_player != nullptr)	//プレイヤーの情報が入っているなら
	//	{
	//		//弾とプレイヤーの距離を測る
	//		Vector3 diffPlayer = efePosi - Vector3{ b_a_player->GetPlayerPosition().x, b_a_player->GetPlayerPosition().y + 50.0f, b_a_player->GetPlayerPosition().z };

	//		//武器によってダメージを変える

	//			//距離を測り一定以下なら体力減少
	//		if (diffPlayer.Length() <= 500.0f) //ダメージが入る範囲
	//		{
	//			b_a_player->m_playerHP -= 200.0f;

	//		}
	//	}



	//	//---------------------------------------------------------------------------------------------------

	//	//---------------------------------------------------------------------------------------------------
	//	if (m_leftArm != nullptr)	//左腕に情報が入っているなら
	//	{
	//		//弾と左腕の距離を測る
	//		Vector3 diffLeftArm = efePosi - Vector3{ m_leftArm->l_a_w_position.x, m_leftArm->l_a_w_position.y, m_leftArm->l_a_w_position.z };

	//		//武器によってダメージを変える

	//			//距離を測り一定以下なら体力減少
	//		if (diffLeftArm.Length() <= 500.0f) //ダメージが入る範囲
	//		{
	//			m_leftArm->L_a_w_HP -= 200.0f;

	//		}
	//	}
	//	//---------------------------------------------------------------------------------------------------

	//	//---------------------------------------------------------------------------------------------------
	//	if (m_leftLeg != nullptr)	//左足に情報が入っているなら
	//	{
	//		//弾と左腕の距離を測る
	//		Vector3 diffLeftLeg = efePosi - Vector3{ m_leftLeg->l_l_w_position.x, m_leftLeg->l_l_w_position.y, m_leftLeg->l_l_w_position.z };

	//		//武器によってダメージを変える

	//			//距離を測り一定以下なら体力減少
	//		if (diffLeftLeg.Length() <= 500.0f) //ダメージが入る範囲
	//		{
	//			m_leftLeg->L_l_w_HP -= 200.0f;

	//		}
	//	}
	//	//---------------------------------------------------------------------------------------------------

	//	//---------------------------------------------------------------------------------------------------
	//	if (m_rightArm != nullptr)	//右手に情報が入っているなら
	//	{
	//		//弾と左腕の距離を測る
	//		Vector3 diffRightArm = efePosi - Vector3{ m_rightArm->r_a_w_position.x, m_rightArm->r_a_w_position.y, m_rightArm->r_a_w_position.z };

	//		//武器によってダメージを変える

	//			//距離を測り一定以下なら体力減少
	//		if (diffRightArm.Length() <= 500.0f) //ダメージが入る範囲
	//		{
	//			m_rightArm->m_rightArmHP -= 200.0f;

	//		}

	//	}
	//	//---------------------------------------------------------------------------------------------------

	//	//---------------------------------------------------------------------------------------------------
	//	if (m_rightLeg != nullptr)	//右足に情報が入っているなら
	//	{
	//		//弾と左腕の距離を測る
	//		Vector3 diffRightLeg = efePosi - Vector3{ m_rightLeg->r_l_w_position.x, m_rightLeg->r_l_w_position.y, m_rightLeg->r_l_w_position.z };

	//		//武器によってダメージを変える

	//			//距離を測り一定以下なら体力減少
	//		if (diffRightLeg.Length() <= 500.0f) //ダメージが入る範囲
	//		{
	//			m_rightLeg->R_l_w_HP -= 200.0f;

	//		}

	//	}
	//	//---------------------------------------------------------------------------------------------------

	//	//---------------------------------------------------------------------------------------------------
	//	if (m_shoulder != nullptr)	//肩に情報が入っているなら
	//	{
	//		//弾と左腕の距離を測る
	//		Vector3 diffShoulder = efePosi - Vector3{ m_shoulder->s_w_position.x, m_shoulder->s_w_position.y, m_shoulder->s_w_position.z };

	//		//武器によってダメージを変える

	//			//距離を測り一定以下なら体力減少
	//		if (diffShoulder.Length() <= 500.0f) //ダメージが入る範囲
	//		{
	//			m_shoulder->S_w_HP -= 200.0f;

	//		}

	//	}
	//	//---------------------------------------------------------------------------------------------------
	//}
	 if (No_tyakudan == false) {


		//---------------------------------------------------------------------------------------------------
		if (m_player != nullptr)	//プレイヤーの情報が入っているなら
		{
			//弾とプレイヤーの距離を測る
			Vector3 diffPlayer = m_firePosition - Vector3{m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y + 50.0f, m_player->GetPlayerPosition().z};

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffPlayer.Length() <= 400.0f) //ダメージが入る範囲
			{
				m_player->ApplyDamage(0.2f);
				DestroyWithImpactEffect();
			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_leftArm != nullptr)	//左腕に情報が入っているなら
		{
			//弾と左腕の距離を測る
			Vector3 diffLeftArm = m_firePosition - m_leftArm->GetPosition();

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffLeftArm.Length() <= 400.0f) //ダメージが入る範囲
			{
				m_leftArm->ApplyDamage(1.0f);
				DestroyWithImpactEffect();
			}
		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_leftLeg != nullptr)	//左足に情報が入っているなら
		{
			//弾と左腕の距離を測る
			Vector3 diffLeftLeg = m_firePosition - m_leftLeg->GetPosition();

			//武器によってダメージを変える

				//距離を測り一定以下なら体e力減少
			if (diffLeftLeg.Length() <= 400.0f) //ダメージが入る範囲
			{
				m_leftLeg->ApplyDamage(1.0f);
				DestroyWithImpactEffect();
			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_rightArm != nullptr)	//右手に情報が入っているなら
		{
			//弾と左腕の距離を測る
			Vector3 diffRightArm = m_firePosition - m_rightArm->GetPosition();

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffRightArm.Length() <= 400.0f) //ダメージが入る範囲
			{
				m_rightArm->ApplyDamage(1.0f);
				DestroyWithImpactEffect();
			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_rightLeg != nullptr)	//右足に情報が入っているなら
		{
			//弾と左腕の距離を測る
			Vector3 diffRightLeg = m_firePosition - m_rightLeg->GetPosition();

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffRightLeg.Length() <= 400.0f) //ダメージが入る範囲
			{
				m_rightLeg->ApplyDamage(1.0f);
				DestroyWithImpactEffect();
			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_shoulder != nullptr)	//肩に情報が入っているなら
		{
			//弾と左腕の距離を測る
			Vector3 diffShoulder = m_firePosition - m_shoulder->GetPosition();

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffShoulder.Length() <= 400.0f) //ダメージが入る範囲
			{
				m_shoulder->ApplyDamage(1.0f);
				DestroyWithImpactEffect();
			}

		}
		//---------------------------------------------------------------------------------------------------
	}
}

void Boss_Turbo_attack::Render(RenderContext& rc)
{
		m_bulletModel.Draw(rc);
}