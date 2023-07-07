//ターボのパーツ。

#include "stdafx.h"
#include "Boss_Turbo.h"
#include "Player.h"
#include "Boss.h"
#include "Boss_Turbo_attack.h"
#include "Drop_item.h"
#include "Game.h"

Boss_Turbo::Boss_Turbo()
{
	m_animationClip[enAnimationClip_Idle].Load("Assets/animData/Boss_turbo.tka");
	m_animationClip[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClip[enAnimationClip_Attack].Load("Assets/animData/Boss_turbo_attack.tka");
	m_animationClip[enAnimationClip_Attack].SetLoopFlag(true);
	m_player = FindGO<Player>("player");
}

Boss_Turbo::~Boss_Turbo()
{
	DeleteGO(m_turboAttack);
	DeleteGO(m_tatumakiSE);
}

bool Boss_Turbo::Start()
{
	Setup();

	return true;
}

void Boss_Turbo::Setup()
{
	m_boss = FindGO<Boss>("boss");
	m_tarboModel.Init("Assets/modelData/Boss_turbo2.tkm", true, true, m_animationClip, enAnimationClip_Num, enModelUpAxisZ);
	m_tarboModel.Update();

	m_tarboModel.SetScale(m_scale);
	m_tarboModel.Update();
}

void Boss_Turbo::Update()
{
	if (m_player->GetGameState() == MAIN_GAME_NUM)
	{
		Move();
		Rotation();

		m_attackCount++;//攻撃のタイミングの計算。



		if (m_attackCount == 350)
		{


		}
		if (m_attackCount >= 500) {
			m_tarboModel.PlayAnimation(enAnimationClip_Attack, 0.5f);
		}
		else {
			m_tarboModel.PlayAnimation(enAnimationClip_Idle, 0.5f);
		}
		if (m_attackCount == 500) {

			m_weaponEffect = NewGO<EffectEmitter>(0);
			m_weaponEffect->Init(enTatumaki_fire);
			m_weaponEffect->SetScale({ 40.0f,40.0f,30.0f });
			m_weaponEffect->SetPosition(m_effectLocalPos + m_position);
			m_weaponEffect->SetRotation(m_rotation);
			m_weaponEffect->Play();

			m_tatumakiSE = NewGO<SoundSource>(0);
			m_tatumakiSE->Init(enTatumaki);
			m_tatumakiSE->Play(false);
			m_roteFlag = true;
		}


		if (m_attackCount > 700) {
			m_turboAttack = NewGO<Boss_Turbo_attack>(1, "boss_Turbo_attack");
			m_turboAttack->SetPosition(m_position);
			m_turboAttack->SetRotation(m_rotation);
			m_turboAttack->SetForward(m_boss->GetForward());
			if (m_attackCount == 900) {
				m_attackCount = 0;
				m_roteFlag = false;

			}
		}

		if (m_attackOK == true)
		{

		}
	}
	if (m_player->GetGameEndState() == 1)
	{
		DeleteGO(this);
	}

	m_tarboModel.SetPosition(m_position);
	m_tarboModel.Update();
}

void Boss_Turbo::Rotation() 
{
	
	if (m_roteFlag == false) 
	{
		//エネミーからプレイヤーが入ってきたら追いかける。
		Vector3 toPlayer = m_player->GetPlayerPosition() - m_position;

		//プレイヤーとの距離を計算する。
		float distToPlayer = toPlayer.Length();
		//プレイヤーに向かって伸びるベクトルを正規化する。
		Vector3 toPlayerDir = toPlayer;
		toPlayerDir.Normalize();
		m_forward = toPlayerDir;

		m_rotation.SetRotationY(atan2(m_forward.x, m_forward.z));
		m_tarboModel.SetRotation(m_rotation);
	}
	else
	{
		
	}
	
}

void Boss_Turbo::Move()
{
	//ここは丸パクリでOK
	Quaternion originRotation = m_boss->GetRotation();
	m_position = m_boss->GetPosition();
	Vector3 lp = m_localPosition;
	originRotation.Multiply(lp);
	m_position += lp;
	m_rotation = originRotation;
	m_tarboModel.SetPosition(m_position);
}

void Boss_Turbo::Render(RenderContext& rc)
{
	m_tarboModel.Draw(rc);
}