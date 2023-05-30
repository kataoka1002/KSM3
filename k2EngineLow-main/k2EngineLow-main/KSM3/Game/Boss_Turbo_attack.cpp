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

Boss_Turbo_attack::~Boss_Turbo_attack()
{
	b_a_weapons->attack_state = false;
}

bool Boss_Turbo_attack::Start()
{
	b_a_boss = FindGO<Boss>("boss");
	b_a_player = FindGO<Player>("player");
	b_a_weapons = FindGO<Boss_Turbo>("boss_turbo");
	b_a_core_weapons = FindGO<Core_weapons>("core_weapons");
	//弾モデル。
	//b_a_Bullet.Init("Assets/modelData/V_P_bullet.tkm");
	//characterController.Init(1170.0f, 150.0f, m_bulletLocalPosition);
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
	Landing_count++;
	if (Landing_count == 55) {
		// 着弾したら死ぬ
		DeleteGO(this);
	}
}

void Boss_Turbo_attack::SetUp()
{
		b_a_Bullet.Init("Assets/modelData/V_P_bullet.tkm");
		b_a_aiming.Multiply(m_bulletLocalPosition);	//掛け算
		//m_rot = b_a_weapons->b_w_rotation;
		firing_position += m_bulletLocalPosition;
		firing_position = b_a_weapons->b_w_position;
		b_a_Bullet_Fowrad = b_a_weapons->b_w_Fowrad;
		b_a_Bullet.SetScale(30);
		b_a_Bullet.SetPosition(firing_position);
		//b_a_Bullet.SetRotation(m_rot);
		b_a_Bullet.Update();
}

void Boss_Turbo_attack::Update()
{	
	if (b_a_player->game_state == 0)
	{
		DestroyWithImpactEffect();
		b_a_Bullet.Update();
		Damage(false);
		Move();
		Rotation();
	}
	else if (b_a_player->game_state == 2)
	{
		DeleteGO(this);	//リザルト画面に行くと消す
	}

	if (b_a_player->game_end_state == 1)
	{
		DeleteGO(this);	//プレイヤーがポーズ画面からゲームを終了させると消す
	}
}

void Boss_Turbo_attack::Rotation() 
{
		//エネミーからプレイヤーが入ってきたら追いかける。
		//Vector3 toPlayer = b_a_player->player_position - firing_position;

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
		Move_speed += b_a_Bullet_Fowrad *3.5f;
		//Move_speed.y -= 0.2 + fall_speed;
		//firing_position= b_a_weapons->b_w_position;
		firing_position += Move_speed;
	//バレットの更新
		b_a_Bullet.SetRotation(m_rot);
		b_a_Bullet.SetPosition(firing_position);
		b_a_Bullet.Update();
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
	//		Vector3 diffPlayer = efePosi - Vector3{ b_a_player->player_position.x, b_a_player->player_position.y + 50.0f, b_a_player->player_position.z };

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
		if (b_a_player != nullptr)	//プレイヤーの情報が入っているなら
		{
			//弾とプレイヤーの距離を測る
			Vector3 diffPlayer = firing_position - Vector3{b_a_player->player_position.x, b_a_player->player_position.y + 50.0f, b_a_player->player_position.z};

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffPlayer.Length() <= 400.0f) //ダメージが入る範囲
			{
				b_a_player->m_playerHP -= 0.2f;
				DestroyWithImpactEffect();
			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_leftArm != nullptr)	//左腕に情報が入っているなら
		{
			//弾と左腕の距離を測る
			Vector3 diffLeftArm = firing_position - Vector3{ m_leftArm->l_a_w_position.x, m_leftArm->l_a_w_position.y, m_leftArm->l_a_w_position.z };

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffLeftArm.Length() <= 400.0f) //ダメージが入る範囲
			{
				m_leftArm->L_a_w_HP -= 1.0f;
				DestroyWithImpactEffect();
			}
		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_leftLeg != nullptr)	//左足に情報が入っているなら
		{
			//弾と左腕の距離を測る
			Vector3 diffLeftLeg = firing_position - Vector3{ m_leftLeg->l_l_w_position.x, m_leftLeg->l_l_w_position.y, m_leftLeg->l_l_w_position.z };

			//武器によってダメージを変える

				//距離を測り一定以下なら体e力減少
			if (diffLeftLeg.Length() <= 400.0f) //ダメージが入る範囲
			{
				m_leftLeg->L_l_w_HP -= 1.0f;
				DestroyWithImpactEffect();
			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_rightArm != nullptr)	//右手に情報が入っているなら
		{
			//弾と左腕の距離を測る
			Vector3 diffRightArm = firing_position - Vector3{ m_rightArm->r_a_w_position.x, m_rightArm->r_a_w_position.y, m_rightArm->r_a_w_position.z };

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffRightArm.Length() <= 400.0f) //ダメージが入る範囲
			{
				m_rightArm->m_rightArmHP -= 1.0f;
				DestroyWithImpactEffect();
			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_rightLeg != nullptr)	//右足に情報が入っているなら
		{
			//弾と左腕の距離を測る
			Vector3 diffRightLeg = firing_position - Vector3{ m_rightLeg->r_l_w_position.x, m_rightLeg->r_l_w_position.y, m_rightLeg->r_l_w_position.z };

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffRightLeg.Length() <= 400.0f) //ダメージが入る範囲
			{
				m_rightLeg->R_l_w_HP -= 1.0f;
				DestroyWithImpactEffect();
			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_shoulder != nullptr)	//肩に情報が入っているなら
		{
			//弾と左腕の距離を測る
			Vector3 diffShoulder = firing_position - Vector3{ m_shoulder->s_w_position.x, m_shoulder->s_w_position.y, m_shoulder->s_w_position.z };

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffShoulder.Length() <= 400.0f) //ダメージが入る範囲
			{
				m_shoulder->S_w_HP -= 1.0f;
				DestroyWithImpactEffect();
			}

		}
		//---------------------------------------------------------------------------------------------------
	}
}

void Boss_Turbo_attack::Render(RenderContext& rc)
{
		b_a_Bullet.Draw(rc);
}