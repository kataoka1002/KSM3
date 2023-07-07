//ドリルのパーツ。

#include "stdafx.h"
#include "Boss_Drill.h"
#include "Player.h"
#include "Boss.h"
#include "Boss_Drill_attack.h"
#include "Drop_item.h"
#include "Boss_Shovel.h"
#include "Game.h"
#include "Left_arm_weapons.h"
#include "Left_leg_weapons.h"
#include "Right_arm_weapons.h"
#include "Right_leg_weapons.h"
#include "Shoulder_weapons.h"

Boss_Drill::Boss_Drill()
{
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");

	m_animationClip[enAnimationClip_Idle].Load("Assets/animData/Boss_Drill_idol.tka");
	m_animationClip[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClip[enAnimationClip_attack].Load("Assets/animData/Boss_Drill_attack.tka");
	m_animationClip[enAnimationClip_attack].SetLoopFlag(true);
}

Boss_Drill::~Boss_Drill()
{
	if (m_drillAttack != nullptr) {
		DeleteGO(m_drillAttack);
	}
	DeleteGO(m_drillAttack);
	/*if (defeatState == true)
	{
		drop_item->drop_kinds = set_weapons;
	}*/
}

void Boss_Drill::Setup()
{
	m_setWeapon = 1;
	m_boss = FindGO<Boss>("boss");
	if (m_setWeapon == 1)
	{
		m_drillModel.Init("Assets/modelData/Boss_Drill.tkm", true, false, m_animationClip, enAnimationClip_Num, enModelUpAxisZ);
		m_drillModel.Update();
	}

	
}

void Boss_Drill::Update()
{
	if (m_fastFlag == 0)
	{
		Setup();
	}
	m_fastFlag++;
	if (m_player->GetGameState() == MAIN_GAME_NUM && m_fastFlag != 0)
	{
		Move();

		if (m_fastFlag >= 20 && m_fastFlag < 140) {
			m_drillModel.PlayAnimation(enAnimationClip_attack, 0.5f);
		}
		else {
			m_drillModel.PlayAnimation(enAnimationClip_Idle, 0.5f);
		}
		if (m_fastFlag == 20)
		{
			m_drillAttack = NewGO<Boss_Drill_attack>(1, "boss_Drill_attack");
			m_attackState = true;
			m_drillAttack->SetPosition(m_position);
			m_drillAttack->SetRotation(m_boss->GetRotation());
			m_drillAttack->SetForward(m_boss->GetForward());
		}
		//攻撃終了時リセット
		if (m_fastFlag >=21) {
			if (m_drillAttack == nullptr) {
				m_fastFlag = 1;
			}
		}

	}
	if (m_player->GetGameEndState() == 1)
	{
		DeleteGO(this);
	}
	m_drillModel.Update();

	m_drillModel.SetScale(m_scale);
	m_drillModel.Update();
	if (m_HP<=0.0f)
	{
		
		//自分が死ぬと同時にショベルも消す
		if (m_deathCount == 0){
			m_explosionAnother = NewGO<EffectEmitter>(0);
			m_explosionAnother->Init(enBoss_Explosion_Another);
			m_explosionAnother->SetScale({ 25.0f,25.0f,25.0f });
			
			//efeLP += b_w_position;
			m_explosionAnother->SetPosition(m_effectLocalPos + m_position);
			m_explosionAnother->SetRotation(m_rotation);
			m_explosionAnother->Play();
		}
		if (m_deathCount == 140) {
			Damage();
		}
		if (m_deathCount>=320&&m_deathCount<340) {
			m_scale -= 1.0f;
			m_drillModel.SetScale(m_scale);
		}
		if (m_deathCount == 320) {
			m_explosionEffect = NewGO<EffectEmitter>(0);
			m_explosionEffect->Init(enBoss_Explosion);
			m_explosionEffect->SetScale({ 70.0f,70.0f,70.0f });
			
			//efeLP += b_w_position;
			m_explosionEffect->SetPosition(m_effectLocalPos + m_position);
			m_explosionEffect->SetRotation(m_rotation);
			m_explosionEffect->Play();
		}
		if (m_deathCount == 340) {
			DeleteGO(m_boss->GetShovel());
			DeleteGO(this);
		}
		

		m_deathCount++;
	}
}

void Boss_Drill::Move()
{
	//ここは丸パクリでOK
	Quaternion originRotation = m_boss->GetRotation();
	m_position = m_boss->GetPosition();
	Vector3 lp = m_localPosition;
	originRotation.Multiply(lp);
	m_position += lp;
	m_rotation = originRotation;
	m_drillModel.SetPosition(m_position);
	m_drillModel.SetRotation(m_rotation);
}

void Boss_Drill::Damage()
{
	m_effectPosition = m_position;
		//---------------------------------------------------------------------------------------------------
		if (m_player != nullptr)	//プレイヤーの情報が入っているなら
		{
			//弾とプレイヤーの距離を測る
			Vector3 diffPlayer = m_effectPosition - Vector3{ m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y + 50.0f, m_player->GetPlayerPosition().z };

			//武器によってダメージを変える
			float a = diffPlayer.Length();
				//距離を測り一定以下なら体力減少
			if (diffPlayer.Length() <= 2000.0f) //ダメージが入る範囲
			{
				m_player->ApplyDamage(200.0f);

			}

		}



		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_leftArm != nullptr)	//左腕に情報が入っているなら
		{
			//弾と左腕の距離を測る
			Vector3 diffLeftArm = m_effectPosition - m_leftArm->GetPosition();

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffLeftArm.Length() <= 2000.0f) //ダメージが入る範囲
			{
				m_leftArm->ApplyDamage(200.0f);

			}
		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_leftLeg != nullptr)	//左足に情報が入っているなら
		{
			//弾と左腕の距離を測る
			Vector3 diffLeftLeg = m_effectPosition - m_leftLeg->GetPosition();

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffLeftLeg.Length() <= 2000.0f) //ダメージが入る範囲
			{
				m_leftLeg->ApplyDamage(200.0f);

			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_rightArm != nullptr)	//右手に情報が入っているなら
		{
			//弾と左腕の距離を測る
			Vector3 diffRightArm = m_effectPosition - m_rightArm->GetPosition();

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffRightArm.Length() <= 2000.0f) //ダメージが入る範囲
			{
				m_rightArm->ApplyDamage(200.0f);

			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_rightLeg != nullptr)	//右足に情報が入っているなら
		{
			//弾と左腕の距離を測る
			Vector3 diffRightLeg = m_effectPosition - m_rightLeg->GetPosition();

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffRightLeg.Length() <= 2000.0f) //ダメージが入る範囲
			{
				m_rightLeg->ApplyDamage(200.0f);

			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_shoulder != nullptr)	//肩に情報が入っているなら
		{
			//弾と左腕の距離を測る
			Vector3 diffShoulder = m_effectPosition - m_shoulder->GetPosition();

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffShoulder.Length() <= 2000.0f) //ダメージが入る範囲
			{
				m_shoulder->ApplyDamage(200.0f);

			}

		}
		//---------------------------------------------------------------------------------------------------
	
	
}

void Boss_Drill::Render(RenderContext& rc)
{
	m_drillModel.Draw(rc);
}