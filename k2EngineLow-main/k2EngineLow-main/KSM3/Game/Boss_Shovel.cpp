//ショベルのパーツ。

#include "stdafx.h"
#include "Boss_Shovel.h"
#include "Player.h"
#include "Boss.h"
#include "Boss_Shovel_attack.h"
#include "Drop_item.h"
#include "Game.h"
#include "Left_arm_weapons.h"
#include "Left_leg_weapons.h"
#include "Right_arm_weapons.h"
#include "Right_leg_weapons.h"
#include "Shoulder_weapons.h"

Boss_Shovel::Boss_Shovel()
{
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");
}

Boss_Shovel::~Boss_Shovel()
{
	DeleteGO(m_shovelAttack);
}

bool Boss_Shovel::Start()
{
	m_animationClip[enAnimationClip_Idle].Load("Assets/animData/Boss_shovel_idol01.tka");
	m_animationClip[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClip[enAnimationClip_Idle2].Load("Assets/animData/Boss_shovel_idol02.tka");
	m_animationClip[enAnimationClip_Idle2].SetLoopFlag(true);
	m_animationClip[enAnimationClip_Shock_Ground].Load("Assets/animData/Boss_shovel_crash.tka");
	m_animationClip[enAnimationClip_Shock_Ground].SetLoopFlag(true);
	//初期化
	m_shovelModel.Init("Assets/modelData/Boss_shovel4.tkm", true, true , m_animationClip, enAnimationClip_Num, enModelUpAxisZ);
	
	return true;
}

void Boss_Shovel::Setup()
{m_boss = FindGO<Boss>("boss");
	m_setWeapon = 1;
	
	if (m_setWeapon == 1)
	{
		m_shovelModel.Update();
	}

	m_shovelModel.SetScale(m_scale);
	m_shovelModel.Update();
}

void Boss_Shovel::Update()
{
	
	
	if (m_fastFlag == 0)
	{
		Setup();
		
	}
	m_fastFlag++;
	if (m_player->GetGameState() == MAIN_GAME_NUM && m_fastFlag != 0)
	{
		if (m_fastFlag == 400) {
			m_shovelRoarSE = NewGO<SoundSource>(0);			//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
			m_shovelRoarSE->Init(enBoss_Shovel_roar);		//初期化
			m_shovelRoarSE->SetVolume(2.0f * m_game->GetSEVol());	//音量調整
			m_shovelRoarSE->Play(false);
		}
		if (m_fastFlag == 1300) {
			m_shovelRoarSE = NewGO<SoundSource>(0);			//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
			m_shovelRoarSE->Init(enBoss_Shovel_roar);		//初期化
			m_shovelRoarSE->SetVolume(2.0f * m_game->GetSEVol());	//音量調整
			m_shovelRoarSE->Play(false);
		}
		if (m_fastFlag >=270&&m_fastFlag<630) {
			m_shovelModel.PlayAnimation(enAnimationClip_Idle2,0.5f);
		}
		
		else if (m_fastFlag >= 1170 && m_fastFlag < 1500) {
			if (m_fastFlag == 1400) {

				m_shovelShockSE = NewGO<SoundSource>(0);			//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
				m_shovelShockSE->Init(en_Boss_Shovel_shock);		//初期化
				m_shovelShockSE->SetVolume(2.0f * m_game->GetSEVol());	//音量調整
				m_shovelShockSE->Play(false);

				m_shovelShock = NewGO<EffectEmitter>(0);
				m_shovelShock->Init(enBoss_Shovel_shock);
				m_shovelShock->SetScale({ 70.0f,70.0f,70.0f });
				m_shovelShock->SetPosition(m_position+ m_shockEffectLocalPos);
				m_shovelShock->SetRotation(m_rotation);
				m_shovelShock->Play();
				Damage(0);
			}
			m_shovelModel.PlayAnimation(enAnimationClip_Shock_Ground, 0.5f);
		}
		else if (m_fastFlag == 1680) {
			
			DeleteGO(m_shovelShock);
			m_shovelShock = nullptr;
			m_fastFlag = 0;
		}
		else {
			m_shovelModel.PlayAnimation(enAnimationClip_Idle,0.5f);
		}
		
		Move();
	}
	if (m_player->GetGameEndState() == 1)
	{
		DeleteGO(this);
	}


	
	m_shovelModel.Update();

	if (m_HP<=0.0f)
	{
		DeleteGO(this);
	}
}

void Boss_Shovel::Move()
{
	//ここは丸パクリでOK
	Quaternion originRotation = m_boss->GetRotation();
	m_position = m_boss->GetPosition();
	Vector3 lp = m_localPosition;
	originRotation.Multiply(lp);
	m_position += lp;
	m_rotation = originRotation;
	m_shovelModel.SetPosition(m_position);
	m_shovelModel.SetRotation(m_rotation);
}

void Boss_Shovel::Damage(int attack_Num) {
	if (attack_Num == 0) {
		//---------------------------------------------------------------------------------------------------
		if (m_player != nullptr)	//プレイヤーの情報が入っているなら
		{
			//弾とプレイヤーの距離を測る
			Vector3 diffPlayer = m_position + m_shockEffectLocalPos - Vector3{ m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y + 50.0f, m_player->GetPlayerPosition().z };

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffPlayer.Length() <= 2000.0f) //ダメージが入る範囲
			{
				m_player->ApplyDamage(10.0f);
				

			}

		}



		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_leftArm != nullptr)	//左腕に情報が入っているなら
		{
			//弾と左腕の距離を測る
			Vector3 diffLeftArm = m_position + m_shockEffectLocalPos - m_leftArm->GetPosition();

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffLeftArm.Length() <= 2000.0f) //ダメージが入る範囲
			{
				m_leftArm->ApplyDamage(10.0f);
				

			}
		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_leftLeg != nullptr)	//左足に情報が入っているなら
		{
			//弾と左腕の距離を測る
			Vector3 diffLeftLeg = m_position + m_shockEffectLocalPos - m_leftLeg->GetPosition();

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffLeftLeg.Length() <= 2000.0f) //ダメージが入る範囲
			{
				m_leftLeg->ApplyDamage(10.0f);
				

			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_rightArm != nullptr)	//右手に情報が入っているなら
		{
			//弾と左腕の距離を測る
			Vector3 diffRightArm = m_position + m_shockEffectLocalPos - m_rightArm->GetPosition();

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffRightArm.Length() <= 2000.0f) //ダメージが入る範囲
			{
				m_rightArm->ApplyDamage(10.0f);
				

			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_rightLeg != nullptr)	//右足に情報が入っているなら
		{
			//弾と左腕の距離を測る
			Vector3 diffRightLeg = m_position + m_shockEffectLocalPos - m_rightLeg->GetPosition();

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffRightLeg.Length() <= 2000.0f) //ダメージが入る範囲
			{
				m_rightLeg->ApplyDamage(10.0f);
				

			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_shoulder != nullptr)	//肩に情報が入っているなら
		{
			//弾と左腕の距離を測る
			Vector3 diffShoulder = m_position + m_shockEffectLocalPos - m_shoulder->GetPosition();

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffShoulder.Length() <= 2000.0f) //ダメージが入る範囲
			{
				m_shoulder->ApplyDamage(10.0f);
				Effect();

			}

		}
		//---------------------------------------------------------------------------------------------------
	}
}

void Boss_Shovel::Render(RenderContext& rc)
{
	m_shovelModel.Draw(rc);
}