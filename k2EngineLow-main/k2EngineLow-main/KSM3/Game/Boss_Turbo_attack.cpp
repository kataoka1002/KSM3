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
		// ���e�����玀��
		DeleteGO(this);
	}
}

void Boss_Turbo_attack::SetUp()
{
		m_aim.Multiply(m_bulletLocalPosition);	//�|���Z
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
		DeleteGO(this);	//���U���g��ʂɍs���Ə���
	}

	if (m_player->GetGameEndState() == 1)
	{
		DeleteGO(this);	//�v���C���[���|�[�Y��ʂ���Q�[�����I��������Ə���
	}
}


void Boss_Turbo_attack::Move()
{
	//�e��O�ɔ�΂�����
	m_moveSpeed += m_bulletForward *3.5f;
	m_firePosition += m_moveSpeed;
	//�o���b�g�̍X�V
	m_bulletModel.SetRotation(m_rot);
	m_bulletModel.SetPosition(m_firePosition);
	m_bulletModel.Update();
}


void Boss_Turbo_attack::Damage(bool No_tyakudan) 
{
	 if (No_tyakudan == false) {


		//---------------------------------------------------------------------------------------------------
		if (m_player != nullptr)	//�v���C���[�̏�񂪓����Ă���Ȃ�
		{
			//�e�ƃv���C���[�̋����𑪂�
			Vector3 diffPlayer = m_firePosition - Vector3{m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y + 50.0f, m_player->GetPlayerPosition().z};

			//����ɂ���ă_���[�W��ς���

				//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffPlayer.Length() <= 400.0f) //�_���[�W������͈�
			{
				m_player->ApplyDamage(0.2f);
				DestroyWithImpactEffect();
			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_leftArm != nullptr)	//���r�ɏ�񂪓����Ă���Ȃ�
		{
			//�e�ƍ��r�̋����𑪂�
			Vector3 diffLeftArm = m_firePosition - m_leftArm->GetPosition();

			//����ɂ���ă_���[�W��ς���

				//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffLeftArm.Length() <= 400.0f) //�_���[�W������͈�
			{
				m_leftArm->ApplyDamage(1.0f);
				DestroyWithImpactEffect();
			}
		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_leftLeg != nullptr)	//�����ɏ�񂪓����Ă���Ȃ�
		{
			//�e�ƍ��r�̋����𑪂�
			Vector3 diffLeftLeg = m_firePosition - m_leftLeg->GetPosition();

			//����ɂ���ă_���[�W��ς���

				//�����𑪂���ȉ��Ȃ��e�͌���
			if (diffLeftLeg.Length() <= 400.0f) //�_���[�W������͈�
			{
				m_leftLeg->ApplyDamage(1.0f);
				DestroyWithImpactEffect();
			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_rightArm != nullptr)	//�E��ɏ�񂪓����Ă���Ȃ�
		{
			//�e�ƍ��r�̋����𑪂�
			Vector3 diffRightArm = m_firePosition - m_rightArm->GetPosition();

			//����ɂ���ă_���[�W��ς���

				//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffRightArm.Length() <= 400.0f) //�_���[�W������͈�
			{
				m_rightArm->ApplyDamage(1.0f);
				DestroyWithImpactEffect();
			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_rightLeg != nullptr)	//�E���ɏ�񂪓����Ă���Ȃ�
		{
			//�e�ƍ��r�̋����𑪂�
			Vector3 diffRightLeg = m_firePosition - m_rightLeg->GetPosition();

			//����ɂ���ă_���[�W��ς���

				//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffRightLeg.Length() <= 400.0f) //�_���[�W������͈�
			{
				m_rightLeg->ApplyDamage(1.0f);
				DestroyWithImpactEffect();
			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_shoulder != nullptr)	//���ɏ�񂪓����Ă���Ȃ�
		{
			//�e�ƍ��r�̋����𑪂�
			Vector3 diffShoulder = m_firePosition - m_shoulder->GetPosition();

			//����ɂ���ă_���[�W��ς���

				//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffShoulder.Length() <= 400.0f) //�_���[�W������͈�
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