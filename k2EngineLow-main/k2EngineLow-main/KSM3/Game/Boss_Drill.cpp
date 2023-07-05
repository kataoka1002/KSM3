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
	b_a_player = FindGO<Player>("player");

	m_animationClip[enAnimationClip_Idle].Load("Assets/animData/Boss_Drill_idol.tka");
	m_animationClip[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClip[enAnimationClip_attack].Load("Assets/animData/Boss_Drill_attack.tka");
	m_animationClip[enAnimationClip_attack].SetLoopFlag(true);
}

Boss_Drill::~Boss_Drill()
{
	if (b_boss_weapons != nullptr) {
		DeleteGO(b_boss_weapons);
	}
	DeleteGO(b_boss_weapons);
	/*if (defeatState == true)
	{
		drop_item->drop_kinds = set_weapons;
	}*/
}

void Boss_Drill::Setup()
{
	set_weapons = 1;
	m_boss = FindGO<Boss>("boss");
	if (set_weapons == 1)
	{
		boss_Drill_Render.Init("Assets/modelData/Boss_Drill.tkm", true, false, m_animationClip, enAnimationClip_Num, enModelUpAxisZ);
		boss_Drill_Render.Update();
	}

	
}

void Boss_Drill::Update()
{
	if (fast == 0)
	{
		Setup();
	}
	fast++;
	if (b_a_player->GetGameState() == MAIN_GAME_NUM && fast != 0)
	{
		Move();

		if (fast >= 20 && fast < 140) {
			boss_Drill_Render.PlayAnimation(enAnimationClip_attack, 0.5f);
		}
		else {
			boss_Drill_Render.PlayAnimation(enAnimationClip_Idle, 0.5f);
		}
		if (fast == 20)
		{
			b_boss_weapons = NewGO<Boss_Drill_attack>(1, "boss_Drill_attack");
			m_attackState = true;
			b_boss_weapons->firing_position = m_position;
			b_boss_weapons->b_a_aiming = m_boss->GetRotation();
			b_boss_weapons->b_a_Bullet_Fowrad = m_boss->GetForward();
		}
		//攻撃終了時リセット
		if (fast >=21) {
			if (b_boss_weapons == nullptr) {
				fast = 1;
			}
		}

		



		

		//if (attack_ok == true)
		//{
		//	firing_cound++;//攻撃のタイミングの計算。
		//	if (firing_cound % 108 == 0)
		//	{
		//		b_boss_weapons = NewGO<Boss_Drill_attack>(1, "boss_Drill_attack");
		//		attack_state = true;
		//		b_boss_weapons->firing_position = b_w_position;
		//		b_boss_weapons->b_a_aiming = b_w_boss->boss_rotation;
		//		b_boss_weapons->b_a_Bullet_Fowrad = b_w_boss->boss_forward;
		//	}
		//}
	}
	if (b_a_player->GetGameEndState() == 1)
	{
		DeleteGO(this);
	}
	boss_Drill_Render.Update();

	//b_w_rotation.SetRotationY(atan2(b_w_Fowrad.x, b_w_Fowrad.z));
	//boss_Riser_Render.SetPosition(b_w_position);
	//boss_Riser_Render.SetRotation(b_w_rotation);
	//boss_Riser_Render.Update();
	//PlayerSearch();

	boss_Drill_Render.SetScale(Drill_scale);
	boss_Drill_Render.Update();
	if (drill_HP<=0.0f)
	{
		//drop_item = NewGO<Drop_item>(1, "drop_item");
		//drop_item->Drop_position.y += 50.0f;
		//defeatState = true;
		
		//自分が死ぬと同時にショベルも消す
		if (Death_count == 0){
			m_explosionAnother = NewGO<EffectEmitter>(0);
			m_explosionAnother->Init(enBoss_Explosion_Another);
			m_explosionAnother->SetScale({ 25.0f,25.0f,25.0f });
			
			//efeLP += b_w_position;
			m_explosionAnother->SetPosition(efeLP + m_position);
			m_explosionAnother->SetRotation(m_rotation);
			m_explosionAnother->Play();
		}
		if (Death_count == 140) {
			Damage();
		}
		if (Death_count>=320&&Death_count<340) {
			Drill_scale -= 1.0f;
			boss_Drill_Render.SetScale(Drill_scale);
		}
		if (Death_count == 320) {
			Explosion_efe = NewGO<EffectEmitter>(0);
			Explosion_efe->Init(enBoss_Explosion);
			Explosion_efe->SetScale({ 70.0f,70.0f,70.0f });
			
			//efeLP += b_w_position;
			Explosion_efe->SetPosition(efeLP + m_position);
			Explosion_efe->SetRotation(m_rotation);
			Explosion_efe->Play();
		}
		if (Death_count == 340) {
			DeleteGO(m_boss->GetShovel());
			DeleteGO(this);
		}
		

		Death_count++;
	}
}

void Boss_Drill::Move()
{
	//ここは丸パクリでOK
	Quaternion originRotation = m_boss->GetRotation();
	m_position = m_boss->GetPosition();
	Vector3 lp = b_w_localposition;
	originRotation.Multiply(lp);
	m_position += lp;
	m_rotation = originRotation;
	boss_Drill_Render.SetPosition(m_position);
	boss_Drill_Render.SetRotation(m_rotation);
}

void Boss_Drill::PlayerSearch()
{
	////エネミーからプレイヤーが入ってきたら追いかける。
	//Vector3 toPlayer = b_w_player->GetPlayerPosition() - b_w_position;

	////プレイヤーとの距離を計算する。
	//float distToPlayer = toPlayer.Length();
	////プレイヤーに向かって伸びるベクトルを正規化する。
	//Vector3 toPlayerDir = toPlayer;
	//toPlayerDir.Normalize();
	////エネミーの全方向とtoPlayerDirとの内積を計算する。
	//float t = toPlayerDir.Dot(b_w_Fowrad);
	////内積の結果をacos関数に渡して、m_enemyFowradとtoPlayerDirのなす角度を求める。
	//float angle = acos(t);

	//

	//b_w_Fowrad = toPlayerDir;

}
void Boss_Drill::Damage()
{
	efePosi = m_position;
		//---------------------------------------------------------------------------------------------------
		if (b_a_player != nullptr)	//プレイヤーの情報が入っているなら
		{
			//弾とプレイヤーの距離を測る
			Vector3 diffPlayer = efePosi - Vector3{ b_a_player->GetPlayerPosition().x, b_a_player->GetPlayerPosition().y + 50.0f, b_a_player->GetPlayerPosition().z };

			//武器によってダメージを変える
			float a = diffPlayer.Length();
				//距離を測り一定以下なら体力減少
			if (diffPlayer.Length() <= 2000.0f) //ダメージが入る範囲
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
			Vector3 diffLeftLeg = efePosi - m_leftLeg->GetPosition();

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
			Vector3 diffRightArm = efePosi - m_rightArm->GetPosition();

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
			Vector3 diffRightLeg = efePosi - m_rightLeg->GetPosition();

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
			Vector3 diffShoulder = efePosi - m_shoulder->GetPosition();

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
	boss_Drill_Render.Draw(rc);
}