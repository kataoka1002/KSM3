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


namespace
{
	const float RANGE_DISTANCE = 100.0f;

	const float ENEMY_MACHINEGUN_DAMAGE = 0.5f;
	const float ENEMY_GIGATONCANNON_DAMAGE = 50.0f;
	const float ENEMY_BATTLESHIPGUN_DAMAGE = 25.0f;
}


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
		if (m_enemyMama->GetWeponKind() == MACHINEGUN_NUM)//�}�V���K���̒e�̉��G�t�F
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
		if (m_enemyNearMama->GetWeponKind() == GIGATONCANNON_NUM)//�M�K�g���L���m���̒e�̉��G�t�F
		{
			//��ʂ�h�炷
			GameCamera* m_camera = FindGO<GameCamera>("gamecamera");
			m_camera->VibFlag = true;
		}
	}
	else if (m_enemyFarMama != nullptr)
	{
		if (m_enemyFarMama->GetWeponKind() == BATTLESHIPGUN_NUM)	//��͖C�̉��G�t�F�N�g
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
	if (m_player->GetGameState() == 2)
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
	if (m_player->GetPlayerDead() == true)
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

	//�������̊m��(make_unique�֐�������new���Ă���)
	m_bulletModel = std::make_unique<ModelRender>();


	//�e�ɂ���ď�������ς���
	if (m_enemyMama != nullptr)
	{
		switch (m_enemyMama->GetWeponKind())
		{
		case GIGAPLASMA_NUM:	//�M�K�v���Y�}
			break;

		case MACHINEGUN_NUM:	//�}�V���K��

			//���f���̏�����
			m_bulletModel->Init("Assets/modelData/V_P_bullet.tkm");
			m_bulletModel->SetScale(4.0f);
			//�G�l�~�[���猩�Đ������ʒu�ɒe��ݒ�
			originRotation.Multiply(m_bulletLocalPosition);	//�|���Z

			//�ŏI�I�Ȓe�̉�]������
			m_rot = originRotation;
			m_position += m_bulletLocalPosition;				//����ɐe���猩���ʒu�𑫂��čŏI�I�ȕ���̈ʒu������
			//�o���b�g�̑O�����̐ݒ�
			m_bulletFowrad = m_enemyMama->GetForward();
			//�X�V
			m_bulletModel->SetRotation(m_enemyMama->GetRot());
			m_bulletModel->SetPosition(m_position);

			//���̓G�l�~�[���Ŗ炵�Ă���

			//�G�t�F�N�g�̍Đ�
			Effect(MACHINEGUN_NUM);
			break;

		case HELLFIRE_NUM:	//�w�C���t�@�C���[���C�t��
			break;

		default:
			break;
		}
	}
	else if (m_enemyNearMama != nullptr)
	{
		switch (m_enemyNearMama->GetWeponKind())
		{
		case GIGATONCANNON_NUM:	//�M�K�g���L���m��

			//���f���̏�����
			m_bulletModel->Init("Assets/modelData/V_P_bullet.tkm");
			m_bulletModel->SetScale({ 15.0f ,15.0f,10.0f });
			//�G�l�~�[���猩�Đ������ʒu�ɒe��ݒ�
			originRotation.Multiply(m_bulletLocalPosition);	//�|���Z
			//�ŏI�I�Ȓe�̉�]������
			m_rot = originRotation;
			m_position += m_bulletLocalPosition;				//����ɐe���猩���ʒu�𑫂��čŏI�I�ȕ���̈ʒu������
			//�o���b�g�̑O�����̐ݒ�
			m_bulletFowrad = m_enemyNearMama->GetForward();
			//�X�V
			m_bulletModel->SetRotation(m_enemyNearMama->GetRot());
			m_bulletModel->SetPosition(m_position);

			//�������̓G�l�~�[���Ŗ炵�Ă���

			//�G�t�F�N�g�̍Đ�
			Effect(GIGATONCANNON_NUM);



			break;

		default:
			break;
		}
	}
	else if (m_enemyFarMama != nullptr)
	{
		switch (m_enemyFarMama->GetWeponKind())
		{
		case MISSILE_NUM:	//�~�T�C��

			//���ʉ��̏�����
			break;

		case BATTLESHIPGUN_NUM:	//��͖C

			//���f���̏�����
			m_bulletModel->Init("Assets/modelData/V_P_bullet.tkm");
			m_bulletModel->SetScale(10.0f);
			//�G�l�~�[���猩�Đ������ʒu�ɒe��ݒ�
			originRotation.Multiply(m_bulletLocalPosition);	//�|���Z
			//�ŏI�I�Ȓe�̉�]������
			m_rot = originRotation;
			m_position += m_bulletLocalPosition;				//����ɐe���猩���ʒu�𑫂��čŏI�I�ȕ���̈ʒu������
			//�o���b�g�̑O�����̐ݒ�
			m_bulletFowrad = m_enemyFarMama->GetForward();
			//�X�V
			m_bulletModel->SetRotation(m_enemyFarMama->GetRot());
			m_bulletModel->SetPosition(m_position);

			//�G�t�F�N�g�̍Đ�
			Effect(BATTLESHIPGUN_NUM);
			break;

		default:
			break;
		}
	}
}

void Enemy_Bullet::Update() 
{

	if (m_player->GetGameState() == 0)
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
	else if (m_player->GetGameState() == 2)
	{
		DeleteGO(this);	//���U���g��ʂɍs���Ə���
	}

	if (m_player->GetGameEndState() == 1)
	{
		DeleteGO(this);	//�v���C���[���|�[�Y��ʂ���Q�[�����I��������Ə���
	}
}

void Enemy_Bullet::Move()
{
	if (m_enemyMama->GetWeponKind() == GIGAPLASMA_NUM)	//�M�K�v���Y�}
	{

	}
	if (m_enemyMama->GetWeponKind() == MACHINEGUN_NUM)	//�}�V���K��
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
		m_bulletModel->SetRotation(m_rot);
		m_bulletModel->SetPosition(m_position);
		m_bulletModel->Update();
	}
	if (m_enemyMama->GetWeponKind() == HELLFIRE_NUM)	//�w���t�@�C�����C�t��
	{

	}
}

void Enemy_Bullet::MoveNear()
{
	if (m_enemyNearMama->GetWeponKind() == GIGATONCANNON_NUM)	//�M�K�g���L���m��
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
		m_bulletModel->SetRotation(m_rot);
		m_bulletModel->SetPosition(m_position);
		m_bulletModel->Update();
	}
}

void Enemy_Bullet::MoveFar()
{
	if (m_enemyFarMama->GetWeponKind() == MISSILE_NUM)	//�~�T�C��
	{

	}
	else if (m_enemyFarMama->GetWeponKind() == BATTLESHIPGUN_NUM)	//��͖C
	{
		//�e��O�ɔ�΂�����
		m_bulletSpeed += m_bulletFowrad * 1.7f;
		m_bulletSpeed.y -= 0.1f;
		m_position += m_bulletSpeed;

		//�o���b�g�̍X�V
		m_bulletModel->SetRotation(m_rot);
		m_bulletModel->SetPosition(m_position);
		m_bulletModel->Update();
	}
}

void Enemy_Bullet::Effect(int num)
{
	if (num == GIGAPLASMA_NUM)
	{
	}
	else if (num == MACHINEGUN_NUM)
	{
		//�G�t�F�N�g�̏������ƍĐ�
		m_weaponEffect = NewGO<EffectEmitter>(0);
		m_weaponEffect->Init(enMasinganHibana);
		m_weaponEffect->SetScale({ 0.7f,0.7f,0.7f });
		m_weaponEffect->SetPosition(m_position);
		m_weaponEffect->Play();
	}
	else if (num == HELLFIRE_NUM)
	{

	}
	else if (num == GIGATONCANNON_NUM)
	{
		//�G�t�F�N�g�̏������ƍĐ�
		m_weaponEffect = NewGO<EffectEmitter>(0);
		m_weaponEffect->Init(enHidan);
		m_weaponEffect->SetScale({ 1.5f,1.5f,1.5f });
		m_weaponEffect->SetPosition(m_position);
		m_weaponEffect->Play();
	}
	else if (num == MISSILE_NUM)
	{

	}
	else if (num == BATTLESHIPGUN_NUM)
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
		Vector3 diffPlayer = m_position - Vector3{ m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y + 50.0f, m_player->GetPlayerPosition().z };

		//����ɂ���ă_���[�W��ς���
		if (weaponNum == MACHINEGUN_NUM)			//�}�V���K��
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffPlayer.Length() <= RANGE_DISTANCE) //�_���[�W������͈�
			{
				m_player->ApplyDamage(ENEMY_MACHINEGUN_DAMAGE);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == GIGATONCANNON_NUM)		//�M�K�g���L���m��
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffPlayer.Length() <= RANGE_DISTANCE) //�_���[�W������͈�
			{
				m_player->ApplyDamage(ENEMY_GIGATONCANNON_DAMAGE);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == BATTLESHIPGUN_NUM)	//��͖C
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffPlayer.Length() <= RANGE_DISTANCE) //�_���[�W������͈�
			{
				m_player->ApplyDamage(ENEMY_BATTLESHIPGUN_DAMAGE);
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
		if (weaponNum == MACHINEGUN_NUM)			//�}�V���K��
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffLeftArm.Length() <= RANGE_DISTANCE) //�_���[�W������͈�
			{
				m_leftArm->ApplyDamage(ENEMY_MACHINEGUN_DAMAGE);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == GIGATONCANNON_NUM)		//�M�K�g���L���m��
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffLeftArm.Length() <= RANGE_DISTANCE) //�_���[�W������͈�
			{
				m_leftArm->ApplyDamage(ENEMY_GIGATONCANNON_DAMAGE);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == BATTLESHIPGUN_NUM)	//��͖C
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffLeftArm.Length() <= RANGE_DISTANCE) //�_���[�W������͈�
			{
				m_leftArm->ApplyDamage(ENEMY_BATTLESHIPGUN_DAMAGE);
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
		if (weaponNum == MACHINEGUN_NUM)			//�}�V���K��
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffLeftLeg.Length() <= RANGE_DISTANCE) //�_���[�W������͈�
			{
				m_leftLeg->ApplyDamage(ENEMY_MACHINEGUN_DAMAGE);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == GIGATONCANNON_NUM)		//�M�K�g���L���m��
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffLeftLeg.Length() <= RANGE_DISTANCE) //�_���[�W������͈�
			{
				m_leftLeg->ApplyDamage(ENEMY_GIGATONCANNON_DAMAGE);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == BATTLESHIPGUN_NUM)	//��͖C
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffLeftLeg.Length() <= RANGE_DISTANCE) //�_���[�W������͈�
			{
				m_leftLeg->ApplyDamage(ENEMY_BATTLESHIPGUN_DAMAGE);
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
		if (weaponNum == MACHINEGUN_NUM)			//�}�V���K��
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffRightArm.Length() <= RANGE_DISTANCE) //�_���[�W������͈�
			{
				m_rightArm->ApplyDamage(ENEMY_MACHINEGUN_DAMAGE);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == GIGATONCANNON_NUM)		//�M�K�g���L���m��
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffRightArm.Length() <= RANGE_DISTANCE) //�_���[�W������͈�
			{
				m_rightArm->ApplyDamage(ENEMY_GIGATONCANNON_DAMAGE);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == BATTLESHIPGUN_NUM)	//��͖C
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffRightArm.Length() <= RANGE_DISTANCE) //�_���[�W������͈�
			{
				m_rightArm->ApplyDamage(ENEMY_BATTLESHIPGUN_DAMAGE);
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
		if (weaponNum == MACHINEGUN_NUM)			//�}�V���K��
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffRightLeg.Length() <= RANGE_DISTANCE) //�_���[�W������͈�
			{
				m_rightLeg->ApplyDamage(ENEMY_MACHINEGUN_DAMAGE);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == GIGATONCANNON_NUM)		//�M�K�g���L���m��
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffRightLeg.Length() <= RANGE_DISTANCE) //�_���[�W������͈�
			{
				m_rightLeg->ApplyDamage(ENEMY_GIGATONCANNON_DAMAGE);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == BATTLESHIPGUN_NUM)	//��͖C
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffRightLeg.Length() <= RANGE_DISTANCE) //�_���[�W������͈�
			{
				m_rightLeg->ApplyDamage(ENEMY_BATTLESHIPGUN_DAMAGE);
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
		if (weaponNum == MACHINEGUN_NUM)			//�}�V���K��
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffShoulder.Length() <= RANGE_DISTANCE) //�_���[�W������͈�
			{
				m_shoulder->ApplyDamage(ENEMY_MACHINEGUN_DAMAGE);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == GIGATONCANNON_NUM)		//�M�K�g���L���m��
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffShoulder.Length() <= RANGE_DISTANCE) //�_���[�W������͈�
			{
				m_shoulder->ApplyDamage(ENEMY_GIGATONCANNON_DAMAGE);
				DestroyWithImpactEffect();
			}
		}
		else if (weaponNum == BATTLESHIPGUN_NUM)	//��͖C
		{
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffShoulder.Length() <= RANGE_DISTANCE) //�_���[�W������͈�
			{
				m_shoulder->ApplyDamage(ENEMY_BATTLESHIPGUN_DAMAGE);
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
		if (m_enemyMama->GetWeponKind() == GIGAPLASMA_NUM)	//�M�K�v���Y�}
		{

		}
		else if (m_enemyMama->GetWeponKind() == MACHINEGUN_NUM)	//�}�V���K��
		{
			m_bulletModel->Draw(rc);
		}
		else if (m_enemyMama->GetWeponKind() == HELLFIRE_NUM)	//�w�C���t�@�C���[���C�t��
		{

		}
	}
	else if (m_enemyNearMama != nullptr)
	{
		if (m_enemyNearMama->GetWeponKind() == GIGATONCANNON_NUM)	//�M�K�g���L���m��
		{
			m_bulletModel->Draw(rc);
		}
	}
	else if (m_enemyFarMama != nullptr)
	{
		if (m_enemyFarMama->GetWeponKind() == MISSILE_NUM)	//�~�T�C��
		{

		}
		else if (m_enemyFarMama->GetWeponKind() == BATTLESHIPGUN_NUM)	//��͖C
		{
			m_bulletModel->Draw(rc);
		}
	}
}