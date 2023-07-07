//ライザーパーツ。

#include "stdafx.h"
#include "Boss_Riser.h"
#include "Player.h"
#include "Boss.h"
#include "Boss_Riser_attack.h"
#include "Drop_item.h"
#include "Game.h"

Boss_Riser::Boss_Riser()
{
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");
}

Boss_Riser::~Boss_Riser()
{
	DeleteGO(m_riserAttack);	
}

void Boss_Riser::Setup()
{
	m_animationClip[enAnimationClip_Idle].Load("Assets/animData/dozar_idol.tka");
	m_animationClip[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClip[enAnimationClip_attack].Load("Assets/animData/dozar_attack.tka");
	m_animationClip[enAnimationClip_attack].SetLoopFlag(true);


	m_setWeapon = 1;
	m_boss = FindGO<Boss>("boss");
	if (m_setWeapon == 1)
	{
		m_riserModel.Init("Assets/modelData/Boss_do-ze-1.tkm", true, false, m_animationClip, enAnimationClip_Num, enModelUpAxisZ);
		m_riserModel.Update();
	}
	
}

void Boss_Riser::Update()
{
	if (m_fastFlag == 0)
	{
		Setup();
	}
	m_fastFlag++;
	
	if (m_player->GetGameState() == MAIN_GAME_NUM && m_fastFlag != 0)
	{
		if (m_fastFlag >= 540 && m_fastFlag < 810) {
			m_riserModel.PlayAnimation(enAnimationClip_attack,0.5f);
		}
		else {
			m_riserModel.PlayAnimation(enAnimationClip_Idle,0.5f);
		}
		if (m_fastFlag == 809) {
			DeleteGO(m_weaponEffect);
			m_weaponEffect = nullptr;
			m_fastFlag = 1;
		}
		
		if (m_fastFlag == 540) {
			m_dozarChageSE = NewGO<SoundSource>(0);			//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
			m_dozarChageSE->Init(en_Boss_Dozar_Charge_SE);		//初期化
			m_dozarChageSE->SetVolume(2.0f * m_game->GetSEVol());	//音量調整
			m_dozarChageSE->Play(false);
		}
		if (m_fastFlag == 640) {
			m_weaponEffect = NewGO<EffectEmitter>(0);
			m_weaponEffect->Init(enBoss_Dozar_Charge);
			m_weaponEffect->SetScale({ 30.0f,30.0f,30.0f });
			
			m_weaponEffect->SetPosition(m_effectLocalPos + m_position);
			m_weaponEffect->SetRotation(m_rotation);
			m_weaponEffect->Play();
		}

		if (m_fastFlag == 665)
		{
			m_riserAttack = NewGO<Boss_Riser_attack>(1, "boss_Riser_attack");
			m_riserAttack->SetPosition(m_position);
			m_riserAttack->SetRotation(m_boss->GetRotation());
			m_riserAttack->SetForward(m_boss->GetForward());
		}
		Move();
	}
	if (m_player->GetGameEndState() == 1)
	{
		DeleteGO(this);
	}
	m_riserModel.Update();


	m_riserModel.SetScale(m_scale);
	if (m_HP<=0.0f)
	{
		DeleteGO(this);
	}
}

void Boss_Riser::Move()
{
	//ここは丸パクリでOK
	Quaternion originRotation = m_boss->GetRotation();
	m_position = m_boss->GetPosition();
	Vector3 lp = m_localPosition;
	originRotation.Multiply(lp);
	m_position += lp;
	m_rotation = originRotation;
	m_riserModel.SetPosition(m_position);
	m_riserModel.SetRotation(m_rotation);
}

void Boss_Riser::Render(RenderContext& rc)
{
	m_riserModel.Draw(rc);
}