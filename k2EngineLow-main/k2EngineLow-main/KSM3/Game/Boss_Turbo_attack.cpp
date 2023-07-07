#include "stdafx.h"
#include "Boss_Turbo_attack.h"
#include "Boss_Turbo.h"
#include "Boss.h"
#include "Player.h"
#include "sound/SoundEngine.h"
#include "Game.h"
#include "Left_arm_weapons.h"
#include "Left_leg_weapons.h"
#include "Right_arm_weapons.h"
#include "Right_leg_weapons.h"
#include "Shoulder_weapons.h"

Boss_Turbo_attack::Boss_Turbo_attack()
{

}

Boss_Turbo_attack::~Boss_Turbo_attack()
{
	//m_weapon->m_attackState = false;
}

bool Boss_Turbo_attack::Start()
{
	m_boss = FindGO<Boss>("boss");
	m_player = FindGO<Player>("player");
	m_weapon = FindGO<Boss_Turbo>("boss_turbo");
	SetUp();

	return true;
}

void Boss_Turbo_attack::DestroyWithImpactEffect()
{
	m_loadingCount++;
	if (m_loadingCount == 55) {
		// 着弾したら死ぬ
		DeleteGO(this);
	}
}

void Boss_Turbo_attack::SetUp()
{
		m_aim.Multiply(m_bulletLocalPosition);	//掛け算
		m_firePosition += m_bulletLocalPosition;
		m_firePosition = m_weapon->GetPosition();
		m_bulletForward = m_weapon->GetForward();
		m_bulletModel.SetScale(30);
		m_bulletModel.SetPosition(m_firePosition);
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


void Boss_Turbo_attack::Move()
{
	//弾を前に飛ばす処理
	m_moveSpeed += m_bulletForward *3.5f;
	m_firePosition += m_moveSpeed;
	//バレットの更新
	m_bulletModel.SetRotation(m_rot);
	m_bulletModel.SetPosition(m_firePosition);
	m_bulletModel.Update();
}


void Boss_Turbo_attack::Damage(bool No_tyakudan) 
{
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