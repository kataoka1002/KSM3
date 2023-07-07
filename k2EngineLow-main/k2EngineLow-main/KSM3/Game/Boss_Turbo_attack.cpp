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
	//���r
	if (m_customizeUI->GetLeftArmWeapon() != nullptr)
	{
		m_leftArm = m_customizeUI->GetLeftArmWeapon();	//�J�X�^�}�C�YUI�ɂ���|�C���^��n���Ă��
	}
	//����
	if (m_customizeUI->GetLeftLegWeapon() != nullptr)
	{
		m_leftLeg = m_customizeUI->GetLeftLegWeapon();	//�J�X�^�}�C�YUI�ɂ���|�C���^��n���Ă��
	}
	//�E�r
	if (m_customizeUI->GetRightArmWeapon() != nullptr)
	{
		m_rightArm = m_customizeUI->GetRightArmWeapon();	//�J�X�^�}�C�YUI�ɂ���|�C���^��n���Ă��
	}
	//�E��
	if (m_customizeUI->GetRightLegWeapon() != nullptr)
	{
		m_rightLeg = m_customizeUI->GetRightLegWeapon();	//�J�X�^�}�C�YUI�ɂ���|�C���^��n���Ă��
	}
	//��
	if (m_customizeUI->GetShoulderWeapon() != nullptr)
	{
		m_shoulder = m_customizeUI->GetShoulderWeapon();	//�J�X�^�}�C�YUI�ɂ���|�C���^��n���Ă��
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
	//�e���f���B
	//b_a_Bullet.Init("Assets/modelData/V_P_bullet.tkm");
	//m_characterController.Init(1170.0f, 150.0f, m_bulletLocalPosition);
	//��(��)
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
	//	//��͖C�G�t�F�N�g�̏������ƍĐ�
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
		// ���e�����玀��
		DeleteGO(this);
	}
}

void Boss_Turbo_attack::SetUp()
{
		//b_a_Bullet.Init("Assets/modelData/V_P_bullet.tkm");
		m_aim.Multiply(m_bulletLocalPosition);	//�|���Z
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
		DeleteGO(this);	//���U���g��ʂɍs���Ə���
	}

	if (m_player->GetGameEndState() == 1)
	{
		DeleteGO(this);	//�v���C���[���|�[�Y��ʂ���Q�[�����I��������Ə���
	}
}

void Boss_Turbo_attack::Rotation() 
{
		//�G�l�~�[����v���C���[�������Ă�����ǂ�������B
		//Vector3 toPlayer = b_a_player->GetPlayerPosition() - firing_position;

		//�v���C���[�Ƃ̋������v�Z����B
		//float distToPlayer = toPlayer.Length();
		////�v���C���[�Ɍ������ĐL�т�x�N�g���𐳋K������B
		//Vector3 toPlayerDir = toPlayer;
		//toPlayerDir.Normalize();
		//b_a_Bullet_Fowrad = toPlayerDir;
		/*m_rot.SetRotationY(atan2(b_a_Bullet_Fowrad.x, b_a_Bullet_Fowrad.z));
		b_a_Bullet.SetRotation(m_rot);*/

}

void Boss_Turbo_attack::Move()
{
	//�e��O�ɔ�΂�����
		m_moveSpeed += m_bulletForward *3.5f;
		//Move_speed.y -= 0.2 + fall_speed;
		//firing_position= b_a_weapons->b_w_position;
		m_firePosition += m_moveSpeed;
	//�o���b�g�̍X�V
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
	//	if (b_a_player != nullptr)	//�v���C���[�̏�񂪓����Ă���Ȃ�
	//	{
	//		//�e�ƃv���C���[�̋����𑪂�
	//		Vector3 diffPlayer = efePosi - Vector3{ b_a_player->GetPlayerPosition().x, b_a_player->GetPlayerPosition().y + 50.0f, b_a_player->GetPlayerPosition().z };

	//		//����ɂ���ă_���[�W��ς���

	//			//�����𑪂���ȉ��Ȃ�̗͌���
	//		if (diffPlayer.Length() <= 500.0f) //�_���[�W������͈�
	//		{
	//			b_a_player->m_playerHP -= 200.0f;

	//		}
	//	}



	//	//---------------------------------------------------------------------------------------------------

	//	//---------------------------------------------------------------------------------------------------
	//	if (m_leftArm != nullptr)	//���r�ɏ�񂪓����Ă���Ȃ�
	//	{
	//		//�e�ƍ��r�̋����𑪂�
	//		Vector3 diffLeftArm = efePosi - Vector3{ m_leftArm->l_a_w_position.x, m_leftArm->l_a_w_position.y, m_leftArm->l_a_w_position.z };

	//		//����ɂ���ă_���[�W��ς���

	//			//�����𑪂���ȉ��Ȃ�̗͌���
	//		if (diffLeftArm.Length() <= 500.0f) //�_���[�W������͈�
	//		{
	//			m_leftArm->L_a_w_HP -= 200.0f;

	//		}
	//	}
	//	//---------------------------------------------------------------------------------------------------

	//	//---------------------------------------------------------------------------------------------------
	//	if (m_leftLeg != nullptr)	//�����ɏ�񂪓����Ă���Ȃ�
	//	{
	//		//�e�ƍ��r�̋����𑪂�
	//		Vector3 diffLeftLeg = efePosi - Vector3{ m_leftLeg->l_l_w_position.x, m_leftLeg->l_l_w_position.y, m_leftLeg->l_l_w_position.z };

	//		//����ɂ���ă_���[�W��ς���

	//			//�����𑪂���ȉ��Ȃ�̗͌���
	//		if (diffLeftLeg.Length() <= 500.0f) //�_���[�W������͈�
	//		{
	//			m_leftLeg->L_l_w_HP -= 200.0f;

	//		}
	//	}
	//	//---------------------------------------------------------------------------------------------------

	//	//---------------------------------------------------------------------------------------------------
	//	if (m_rightArm != nullptr)	//�E��ɏ�񂪓����Ă���Ȃ�
	//	{
	//		//�e�ƍ��r�̋����𑪂�
	//		Vector3 diffRightArm = efePosi - Vector3{ m_rightArm->r_a_w_position.x, m_rightArm->r_a_w_position.y, m_rightArm->r_a_w_position.z };

	//		//����ɂ���ă_���[�W��ς���

	//			//�����𑪂���ȉ��Ȃ�̗͌���
	//		if (diffRightArm.Length() <= 500.0f) //�_���[�W������͈�
	//		{
	//			m_rightArm->m_rightArmHP -= 200.0f;

	//		}

	//	}
	//	//---------------------------------------------------------------------------------------------------

	//	//---------------------------------------------------------------------------------------------------
	//	if (m_rightLeg != nullptr)	//�E���ɏ�񂪓����Ă���Ȃ�
	//	{
	//		//�e�ƍ��r�̋����𑪂�
	//		Vector3 diffRightLeg = efePosi - Vector3{ m_rightLeg->r_l_w_position.x, m_rightLeg->r_l_w_position.y, m_rightLeg->r_l_w_position.z };

	//		//����ɂ���ă_���[�W��ς���

	//			//�����𑪂���ȉ��Ȃ�̗͌���
	//		if (diffRightLeg.Length() <= 500.0f) //�_���[�W������͈�
	//		{
	//			m_rightLeg->R_l_w_HP -= 200.0f;

	//		}

	//	}
	//	//---------------------------------------------------------------------------------------------------

	//	//---------------------------------------------------------------------------------------------------
	//	if (m_shoulder != nullptr)	//���ɏ�񂪓����Ă���Ȃ�
	//	{
	//		//�e�ƍ��r�̋����𑪂�
	//		Vector3 diffShoulder = efePosi - Vector3{ m_shoulder->s_w_position.x, m_shoulder->s_w_position.y, m_shoulder->s_w_position.z };

	//		//����ɂ���ă_���[�W��ς���

	//			//�����𑪂���ȉ��Ȃ�̗͌���
	//		if (diffShoulder.Length() <= 500.0f) //�_���[�W������͈�
	//		{
	//			m_shoulder->S_w_HP -= 200.0f;

	//		}

	//	}
	//	//---------------------------------------------------------------------------------------------------
	//}
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