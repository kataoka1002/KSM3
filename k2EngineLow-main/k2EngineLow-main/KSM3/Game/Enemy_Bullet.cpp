#include "stdafx.h"
#include "Customize_UI_ver2.h"
#include "Enemy_Bullet.h"
#include "Core_weapons.h"
#include "Enemy.h"
#include "Enemy_Near.h"
#include "Enemy_Far.h"
#include "Player.h"
#include "Game.h"
#include "GameCamera.h"
#include "sound/SoundEngine.h"
#include "Left_arm_weapons.h"
#include "Left_leg_weapons.h"
#include "Right_arm_weapons.h"
#include "Right_leg_weapons.h"
#include "Shoulder_weapons.h"

Enemy_Bullet::Enemy_Bullet() 
{
	
}

Enemy_Bullet::~Enemy_Bullet() 
{
	
}
void Enemy_Bullet::DestroyWithImpactEffect()
{
	//�e�ɂ���ăG�t�F�N�g��ς���
	if (m_enemyMama != nullptr)
	{
		if (m_enemyMama->GetWeponKind() == 2)//�}�V���K���̒e�̉��G�t�F
		{
			m_tyakudanEffect = NewGO<EffectEmitter>(0);
			m_tyakudanEffect->Init(enMasinganKemuri);
			m_tyakudanEffect->SetScale({ 10.0f,10.0f,10.0f });
			m_tyakudanEffect->SetPosition({ m_position.x,m_position.y,m_position.z });
			m_tyakudanEffect->Play();
		}
	}
	else if (m_enemyNearMama != nullptr)
	{
		if (m_enemyNearMama->GetWeponKind() == 4)//�M�K�g���L���m���̒e�̉��G�t�F
		{
			//��ʂ�h�炷
			GameCamera* m_camera = FindGO<GameCamera>("gamecamera");
			m_camera->VibFlag = true;
		}
	}
	else if (m_enemyFarMama != nullptr)
	{
		if (m_enemyFarMama->GetWeponKind() == 6)	//��͖C�̉��G�t�F�N�g
		{
			//��͖C�G�t�F�N�g�̏������ƍĐ�
			m_weaponEffect = NewGO<EffectEmitter>(0);
			m_weaponEffect->Init(enTyakudan);
			m_weaponEffect->SetScale({ 5.7f,5.7f,5.7f });
			m_weaponEffect->SetPosition(m_position);
			m_weaponEffect->Play();

			//���e��������ʉ�����
			m_battleShipGunTyakutiSE = NewGO<SoundSource>(0);			//���Đ�����ƏI���Ȃ̂ŃC���X�^���X��ێ������Ȃ��ׂɂ�����NewGO����
			m_battleShipGunTyakutiSE->Init(enButtleShipTyakudan);		//������
			m_battleShipGunTyakutiSE->SetVolume(2.0f * m_game->GetSEVol());	//���ʒ���
			m_battleShipGunTyakutiSE->Play(false);

			//��ʂ�h�炷
			GameCamera* m_camera = FindGO<GameCamera>("gamecamera");
			m_camera->VibFlag = true;
		}
	}
	// ���e�����玀��
	DeleteGO(this);
}
bool Enemy_Bullet::Start()
{
	m_customizeUI = FindGO<Customize_UI_ver2>("customize_ui_ver2");
	m_player = FindGO<Player>("player");
	if (m_player->game_state == 2)
	{
		DeleteGO(this);
	}
	m_coreWeapons = FindGO<Core_weapons>("core_weapons");
	m_game = FindGO<Game>("game");

	FindWeapon();	//�v���C���[�̕������������
	Setup();		//�����G�t�F�N�g�̐ݒ�
		
	return true;
}

void Enemy_Bullet::FindWeapon()
{
	if (m_player->m_playerDead == true)
	{
		return;
	}

	//���r
	if (m_customizeUI->m_leftArmWeapon != nullptr)
	{
		m_leftArm = m_customizeUI->m_leftArmWeapon;	//�J�X�^�}�C�YUI�ɂ���|�C���^��n���Ă��
	}
	//����
	if (m_customizeUI->m_leftLegWeapon != nullptr)
	{
		m_leftLeg = m_customizeUI->m_leftLegWeapon;	//�J�X�^�}�C�YUI�ɂ���|�C���^��n���Ă��
	}
	//�E�r
	if (m_customizeUI->m_rightArmWeapon != nullptr)
	{
		m_rightArm = m_customizeUI->m_rightArmWeapon;	//�J�X�^�}�C�YUI�ɂ���|�C���^��n���Ă��
	}
	//�E��
	if (m_customizeUI->m_rightLegWeapon != nullptr)
	{
		m_rightLeg = m_customizeUI->m_rightLegWeapon;	//�J�X�^�}�C�YUI�ɂ���|�C���^��n���Ă��
	}
	//��
	if (m_customizeUI->m_shoulderWeapon != nullptr)
	{
		m_shoulder = m_customizeUI->m_shoulderWeapon;	//�J�X�^�}�C�YUI�ɂ���|�C���^��n���Ă��
	}
}

void Enemy_Bullet::Setup() 
{
	//�e�ɂ���ď�������ς���
	if (m_enemyMama != nullptr)
	{
		switch (m_enemyMama->GetWeponKind())
		{
		case 1:	//�M�K�v���Y�}
			break;

		case 2:	//�}�V���K��

			//���f���̏�����
			m_bulletModel.Init("Assets/modelData/V_P_bullet.tkm");
			m_bulletModel.SetScale(4.0f);
			//�G�l�~�[���猩�Đ������ʒu�ɒe��ݒ�
			originRotation.Multiply(m_bulletLocalPosition);	//�|���Z

			//�ŏI�I�Ȓe�̉�]������
			m_rot = originRotation;
			m_position += m_bulletLocalPosition;				//����ɐe���猩���ʒu�𑫂��čŏI�I�ȕ���̈ʒu������
			//�o���b�g�̑O�����̐ݒ�
			m_bulletFowrad = m_enemyMama->GetForward();
			//�X�V
			m_bulletModel.SetRotation(m_enemyMama->GetRot());
			m_bulletModel.SetPosition(m_position);

			//���̓G�l�~�[���Ŗ炵�Ă���

			//�G�t�F�N�g�̍Đ�
			Effect(2);
			break;

		case 3:	//�w�C���t�@�C���[���C�t��
			break;

		default:
			break;
		}
	}
	else if (m_enemyNearMama != nullptr)
	{
		switch (m_enemyNearMama->GetWeponKind())
		{
		case 4:	//�M�K�g���L���m��

			//���f���̏�����
			m_bulletModel.Init("Assets/modelData/V_P_bullet.tkm");
			m_bulletModel.SetScale({ 15.0f ,15.0f,10.0f });
			//�G�l�~�[���猩�Đ������ʒu�ɒe��ݒ�
			originRotation.Multiply(m_bulletLocalPosition);	//�|���Z
			//�ŏI�I�Ȓe�̉�]������
			m_rot = originRotation;
			m_position += m_bulletLocalPosition;				//����ɐe���猩���ʒu�𑫂��čŏI�I�ȕ���̈ʒu������
			//�o���b�g�̑O�����̐ݒ�
			m_bulletFowrad = m_enemyNearMama->GetForward();
			//�X�V
			m_bulletModel.SetRotation(m_enemyNearMama->GetRot());
			m_bulletModel.SetPosition(m_position);

			//�������̓G�l�~�[���Ŗ炵�Ă���

			//�G�t�F�N�g�̍Đ�
			Effect(4);



			break;

		default:
			break;
		}
	}
	else if (m_enemyFarMama != nullptr)
	{
		switch (m_enemyFarMama->GetWeponKind())
		{
		case 5:	//�~�T�C��

			//���ʉ��̏�����
			break;

		case 6:	//��͖C

			//���f���̏�����
			m_bulletModel.Init("Assets/modelData/V_P_bullet.tkm");
			m_bulletModel.SetScale(10.0f);
			//�G�l�~�[���猩�Đ������ʒu�ɒe��ݒ�
			originRotation.Multiply(m_bulletLocalPosition);	//�|���Z
			//�ŏI�I�Ȓe�̉�]������
			m_rot = originRotation;
			m_position += m_bulletLocalPosition;				//����ɐe���猩���ʒu�𑫂��čŏI�I�ȕ���̈ʒu������
			//�o���b�g�̑O�����̐ݒ�
			m_bulletFowrad = m_enemyFarMama->GetForward();
			//�X�V
			m_bulletModel.SetRotation(m_enemyFarMama->GetRot());
			m_bulletModel.SetPosition(m_position);

			//�G�t�F�N�g�̍Đ�
			Effect(6);
			break;

		default:
			break;
		}
	}
}

void Enemy_Bullet::Update() 
{

	if (m_player->game_state == 0)
	{
		//�ʒu��0�ȉ��ɂȂ�Ə�����(�S�Ă̒e����)
		if (m_position.y <= 0.0f)
		{
			DestroyWithImpactEffect();
		}

		//�e�ɂ���Ċ֐���ς���
		if (m_enemyMama != nullptr)
		{
			Move();	
			Damage(m_enemyMama->GetWeponKind());
		}
		else if (m_enemyNearMama != nullptr)
		{
			MoveNear();
			Damage(m_enemyNearMama->GetWeponKind());
		}
		else if (m_enemyFarMama != nullptr)
		{
			MoveFar();
			Damage(m_enemyFarMama->GetWeponKind());
		}
	}
	else if (m_player->game_state == 2)
	{
		DeleteGO(this);	//���U���g��ʂɍs���Ə���
	}

	if (m_player->game_end_state == 1)
	{
		DeleteGO(this);	//�v���C���[���|�[�Y��ʂ���Q�[�����I��������Ə���
	}
}

void Enemy_Bullet::Move()
{
	if (m_enemyMama->GetWeponKind() == 1)	//�M�K�v���Y�}
	{

	}
	if (m_enemyMama->GetWeponKind() == 2)	//�}�V���K��
	{
		//�e��O�ɔ�΂�����
		m_bulletSpeed += m_bulletFowrad * 2.0f;
		m_position += m_bulletSpeed;

		//�e�ƃG�l�~�[(�e)�̋������v�Z���Ĉ�苗���ȏ�Ȃ�e������
		Vector3 m_toEnemy = m_enemyMama->GetPos() - m_position;
		float m_dirToEnemy = m_toEnemy.Length();
		if (m_dirToEnemy >= 1800.0f)
		{
			DestroyWithImpactEffect();
		}

		//�o���b�g�̍X�V
		m_bulletModel.SetRotation(m_rot);
		m_bulletModel.SetPosition(m_position);
		m_bulletModel.Update();
	}
	if (m_enemyMama->GetWeponKind() == 3)	//�w���t�@�C�����C�t��
	{

	}
}

void Enemy_Bullet::MoveNear()
{
	if (m_enemyNearMama->GetWeponKind() == 4)	//�M�K�g���L���m��
	{
		//�e��O�ɔ�΂�����
		m_bulletSpeed += m_bulletFowrad * 2.0f;
		m_position += m_bulletSpeed;

		//�e�ƃG�l�~�[(�e)�̋������v�Z���Ĉ�苗���ȏ�Ȃ�e������
		Vector3 m_toEnemy = m_enemyNearMama->GetPos() - m_position;
		float m_dirToEnemy = m_toEnemy.Length();
		if (m_dirToEnemy >= 100.0f)
		{
			DestroyWithImpactEffect();
		}

		//�o���b�g�̍X�V
		m_bulletModel.SetRotation(m_rot);
		m_bulletModel.SetPosition(m_position);
		m_bulletModel.Update();
	}
}

void Enemy_Bullet::MoveFar()
{
	if (m_enemyFarMama->GetWeponKind() == 5)	//�~�T�C��
	{

	}
	else if (m_enemyFarMama->GetWeponKind() == 6)	//��͖C
	{
		//�e��O�ɔ�΂�����
		m_bulletSpeed += m_bulletFowrad * 1.7f;
		m_bulletSpeed.y -= 0.1f;
		m_position += m_bulletSpeed;

		//�o���b�g�̍X�V
		m_bulletModel.SetRotation(m_rot);
		m_bulletModel.SetPosition(m_position);
		m_bulletModel.Update();
	}
}

void Enemy_Bullet::Effect(int num)
{
	if (num == 1)
	{
	}
	else if (num == 2)
	{
		//�G�t�F�N�g�̏������ƍĐ�
		m_weaponEffect = NewGO<EffectEmitter>(0);
		m_weaponEffect->Init(enMasinganHibana);
		m_weaponEffect->SetScale({ 0.7f,0.7f,0.7f });
		m_weaponEffect->SetPosition(m_position);
		m_weaponEffect->Play();
	}
	else if (num == 3)
	{

	}
	else if (num == 4)
	{
		//�G�t�F�N�g�̏������ƍĐ�
		m_weaponEffect = NewGO<EffectEmitter>(0);
		m_weaponEffect->Init(enHidan);
		m_weaponEffect->SetScale({ 1.5f,1.5f,1.5f });
		m_weaponEffect->SetPosition(m_position);
		m_weaponEffect->Play();
	}
	else if (num == 5)
	{

	}
	else if (num == 6)
	{
		//�G�t�F�N�g�̏������ƍĐ�
		m_weaponEffect = NewGO<EffectEmitter>(0);
		m_weaponEffect->Init(enMasinganHibana);
		m_weaponEffect->SetScale({ 0.7f,0.7f,0.7f });
		m_weaponEffect->SetPosition(m_position);
		m_weaponEffect->Play();
	}
}

void Enemy_Bullet::Damage(int weaponNum)
{
	//---------------------------------------------------------------------------------------------------
	if (m_player != nullptr)	//�v���C���[�̏�񂪓����Ă���Ȃ�
	{
		//�e�ƃv���C���[�̋����𑪂�
		Vector3 diffPlayer = m_position - Vector3{ m_player->player_position.x, m_player->player_position.y + 50.0f, m_player->player_position.z };

		//����ɂ���ă_���[�W��ς���
		if (weaponNum == 2)			//�}�V���K��
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffPlayer.Length() <= 100.0f) //�_���[�W������͈�
			{
				m_player->m_playerHP -= 0.5f;
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == 4)		//�M�K�g���L���m��
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffPlayer.Length() <= 100.0f) //�_���[�W������͈�
			{
				m_player->m_playerHP -= 0.5f;
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == 6)	//��͖C
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffPlayer.Length() <= 100.0f) //�_���[�W������͈�
			{
				m_player->m_playerHP -= 0.5f;
				DestroyWithImpactEffect();
			}
		}
	}
	//---------------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------------
	if (m_leftArm != nullptr)	//���r�ɏ�񂪓����Ă���Ȃ�
	{
		//�e�ƍ��r�̋����𑪂�
		Vector3 diffLeftArm = m_position - m_leftArm->GetPosition();
		
		//����ɂ���ă_���[�W��ς���
		if (weaponNum == 2)			//�}�V���K��
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffLeftArm.Length() <= 100.0f) //�_���[�W������͈�
			{
				m_leftArm->ApplyDamage(0.5f);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == 4)		//�M�K�g���L���m��
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffLeftArm.Length() <= 100.0f) //�_���[�W������͈�
			{
				m_leftArm->ApplyDamage(0.5f);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == 6)	//��͖C
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffLeftArm.Length() <= 100.0f) //�_���[�W������͈�
			{
				m_leftArm->ApplyDamage(0.5f);
				DestroyWithImpactEffect();
			}
		}
	}
	//---------------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------------
	if (m_leftLeg != nullptr)	//�����ɏ�񂪓����Ă���Ȃ�
	{
		//�e�ƍ��r�̋����𑪂�
		Vector3 diffLeftLeg = m_position - m_leftLeg->GetPosition();

		//����ɂ���ă_���[�W��ς���
		if (weaponNum == 2)			//�}�V���K��
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffLeftLeg.Length() <= 100.0f) //�_���[�W������͈�
			{
				m_leftLeg->ApplyDamage(0.5f);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == 4)		//�M�K�g���L���m��
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffLeftLeg.Length() <= 100.0f) //�_���[�W������͈�
			{
				m_leftLeg->ApplyDamage(0.5f);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == 6)	//��͖C
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffLeftLeg.Length() <= 100.0f) //�_���[�W������͈�
			{
				m_leftLeg->ApplyDamage(0.5f);
				DestroyWithImpactEffect();
			}
		}
	}
	//---------------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------------
	if (m_rightArm != nullptr)	//�E��ɏ�񂪓����Ă���Ȃ�
	{
		//�e�ƍ��r�̋����𑪂�
		Vector3 diffRightArm = m_position - m_rightArm->GetPosition();

		//����ɂ���ă_���[�W��ς���
		if (weaponNum == 2)			//�}�V���K��
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffRightArm.Length() <= 100.0f) //�_���[�W������͈�
			{
				m_rightArm->ApplyDamage(0.5f);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == 4)		//�M�K�g���L���m��
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffRightArm.Length() <= 100.0f) //�_���[�W������͈�
			{
				m_rightArm->ApplyDamage(0.5f);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == 6)	//��͖C
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffRightArm.Length() <= 100.0f) //�_���[�W������͈�
			{
				m_rightArm->ApplyDamage(0.5f);
				DestroyWithImpactEffect();
			}
		}
	}
	//---------------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------------
	if (m_rightLeg != nullptr)	//�E���ɏ�񂪓����Ă���Ȃ�
	{
		//�e�ƍ��r�̋����𑪂�
		Vector3 diffRightLeg = m_position - m_rightLeg->GetPosition();

		//����ɂ���ă_���[�W��ς���
		if (weaponNum == 2)			//�}�V���K��
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffRightLeg.Length() <= 100.0f) //�_���[�W������͈�
			{
				m_rightLeg->ApplyDamage(0.5f);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == 4)		//�M�K�g���L���m��
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffRightLeg.Length() <= 100.0f) //�_���[�W������͈�
			{
				m_rightLeg->ApplyDamage(0.5f);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == 6)	//��͖C
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffRightLeg.Length() <= 100.0f) //�_���[�W������͈�
			{
				m_rightLeg->ApplyDamage(0.5f);
				DestroyWithImpactEffect();
			}
		}
	}
	//---------------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------------
	if (m_shoulder != nullptr)	//���ɏ�񂪓����Ă���Ȃ�
	{
		//�e�ƍ��r�̋����𑪂�
		Vector3 diffShoulder = m_position - m_shoulder->GetPosition();

		//����ɂ���ă_���[�W��ς���
		if (weaponNum == 2)			//�}�V���K��
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffShoulder.Length() <= 100.0f) //�_���[�W������͈�
			{
				m_shoulder->ApplyDamage(0.5f);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == 4)		//�M�K�g���L���m��
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffShoulder.Length() <= 100.0f) //�_���[�W������͈�
			{
				m_shoulder->ApplyDamage(0.5f);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == 6)	//��͖C
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffShoulder.Length() <= 100.0f) //�_���[�W������͈�
			{
				m_shoulder->ApplyDamage(0.5f);
				DestroyWithImpactEffect();
			}
		}
	}
	//---------------------------------------------------------------------------------------------------
}

void Enemy_Bullet::Render(RenderContext& rc)
{
	if (m_enemyMama != nullptr)
	{
		if (m_enemyMama->GetWeponKind() == 1)	//�M�K�v���Y�}
		{

		}
		else if (m_enemyMama->GetWeponKind() == 2)	//�}�V���K��
		{
			m_bulletModel.Draw(rc);
		}
		else if (m_enemyMama->GetWeponKind() == 3)	//�w�C���t�@�C���[���C�t��
		{

		}
	}
	else if (m_enemyNearMama != nullptr)
	{
		if (m_enemyNearMama->GetWeponKind() == 4)	//�M�K�g���L���m��
		{
			m_bulletModel.Draw(rc);
		}
	}
	else if (m_enemyFarMama != nullptr)
	{
		if (m_enemyFarMama->GetWeponKind() == 5)	//�~�T�C��
		{

		}
		else if (m_enemyFarMama->GetWeponKind() == 6)	//��͖C
		{
			m_bulletModel.Draw(rc);
		}
	}
}