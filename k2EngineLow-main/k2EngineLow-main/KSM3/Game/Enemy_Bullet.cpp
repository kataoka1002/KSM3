#include "stdafx.h"
#include "Enemy_Bullet.h"
#include "Core_weapons.h"
#include "Enemy.h"
#include "Enemy_Near.h"
#include "Enemy_Far.h"
#include "Player.h"
#include "sound/SoundEngine.h"

Enemy_Bullet::Enemy_Bullet() 
{
	
}

Enemy_Bullet::~Enemy_Bullet() 
{
	DeleteGO(m_soundSource);

	//�e�ɂ���ăG�t�F�N�g��ς���
	if (m_enemyMama != nullptr)
	{
		
	}
	else if (m_enemyNearMama != nullptr)
	{
		
	}
	else if (m_enemyFarMama != nullptr)
	{
		//�G�t�F�N�g�̏������ƍĐ�
		m_weaponEffect = NewGO<EffectEmitter>(0);
		m_weaponEffect->Init(enTyakudan);
		m_weaponEffect->SetScale({ 5.7f,5.7f,5.7f });
		m_weaponEffect->SetPosition(m_position);
		m_weaponEffect->Play();
	}
}

bool Enemy_Bullet::Start()
{
	m_player = FindGO<Player>("player");
	m_coreWeapons = FindGO<Core_weapons>("core_weapons");


	//�e�ɂ���ď�������ς���
	if (m_enemyMama != nullptr)
	{
		switch (m_enemyMama->m_setWeapon)
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
			m_bulletFowrad = m_enemyMama->m_enemyForward;
			//�X�V
			m_bulletModel.SetRotation(m_enemyMama->m_enemyRotation);
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
		switch (m_enemyNearMama->m_setWeapon)
		{
		case 4:	//�M�K�g���L���m��

			//���f���̏�����
			m_bulletModel.Init("Assets/modelData/V_P_bullet.tkm");
			m_bulletModel.SetScale(15.0f);
			//�G�l�~�[���猩�Đ������ʒu�ɒe��ݒ�
			originRotation.Multiply(m_bulletLocalPosition);	//�|���Z
			//�ŏI�I�Ȓe�̉�]������
			m_rot = originRotation;
			m_position += m_bulletLocalPosition;				//����ɐe���猩���ʒu�𑫂��čŏI�I�ȕ���̈ʒu������
			//�o���b�g�̑O�����̐ݒ�
			m_bulletFowrad = m_enemyNearMama->m_enemyForward;
			//�X�V
			m_bulletModel.SetRotation(m_enemyNearMama->m_enemyRotation);
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
		switch (m_enemyFarMama->m_setWeapon)
		{
		case 5:	//�~�T�C��

			//���ʉ��̏�����
			m_soundSource->Init(m_enemyFarMama->m_setWeapon);
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
			m_bulletFowrad = m_enemyFarMama->m_enemyForward;
			//�X�V
			m_bulletModel.SetRotation(m_enemyFarMama->m_enemyRotation);
			m_bulletModel.SetPosition(m_position);

			//�G�t�F�N�g�̍Đ�
			Effect(6);
			break;

		default:
			break;
		}
	}
		

	return true;
}

void Enemy_Bullet::Setup() 
{

}

void Enemy_Bullet::Update() 
{
	if (m_player->game_state == 0)
	{
		//�ʒu��0�ȉ��ɂȂ�Ə�����(�S�Ă̒e����)
		if (m_position.y <= 0.0f)
		{
			DeleteGO(this);
		}

		//�e�ɂ���Ċ֐���ς���
		if (m_enemyMama != nullptr)
		{
			Move();	
		}
		else if (m_enemyNearMama != nullptr)
		{
			MoveNear();
		}
		else if (m_enemyFarMama != nullptr)
		{
			MoveFar();
		}
	}
}

void Enemy_Bullet::Move()
{
	if (m_enemyMama->m_setWeapon == 1)	//�M�K�v���Y�}
	{

	}
	if (m_enemyMama->m_setWeapon == 2)	//�}�V���K��
	{
		//�e��O�ɔ�΂�����
		m_bulletSpeed += m_bulletFowrad * 2.0f;
		m_position += m_bulletSpeed;

		//�e�ƃG�l�~�[(�e)�̋������v�Z���Ĉ�苗���ȏ�Ȃ�e������
		Vector3 m_toEnemy = m_enemyMama->m_enemyPosition - m_position;
		float m_dirToEnemy = m_toEnemy.Length();
		if (m_dirToEnemy >= 1800.0f)
		{
			DeleteGO(this);
		}

		//�o���b�g�̍X�V
		m_bulletModel.SetRotation(m_rot);
		m_bulletModel.SetPosition(m_position);
		m_bulletModel.Update();
	}
	if (m_enemyMama->m_setWeapon == 3)	//�w���t�@�C�����C�t��
	{

	}
}

void Enemy_Bullet::MoveNear()
{
	if (m_enemyNearMama->m_setWeapon == 4)	//�M�K�g���L���m��
	{
		//�e��O�ɔ�΂�����
		m_bulletSpeed += m_bulletFowrad * 2.0f;
		m_position += m_bulletSpeed;

		//�e�ƃG�l�~�[(�e)�̋������v�Z���Ĉ�苗���ȏ�Ȃ�e������
		Vector3 m_toEnemy = m_enemyNearMama->m_enemyPosition - m_position;
		float m_dirToEnemy = m_toEnemy.Length();
		if (m_dirToEnemy >= 100.0f)
		{
			DeleteGO(this);
		}

		//�o���b�g�̍X�V
		m_bulletModel.SetRotation(m_rot);
		m_bulletModel.SetPosition(m_position);
		m_bulletModel.Update();
	}
}

void Enemy_Bullet::MoveFar()
{
	if (m_enemyFarMama->m_setWeapon == 5)	//�~�T�C��
	{

	}
	else if (m_enemyFarMama->m_setWeapon == 6)	//��͖C
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

void Enemy_Bullet::EffectDelete(int num)
{
	
}

void Enemy_Bullet::Render(RenderContext& rc)
{
	if (m_enemyMama != nullptr)
	{
		if (m_enemyMama->m_setWeapon == 1)	//�M�K�v���Y�}
		{

		}
		else if (m_enemyMama->m_setWeapon == 2)	//�}�V���K��
		{
			m_bulletModel.Draw(rc);
		}
		else if (m_enemyMama->m_setWeapon == 3)	//�w�C���t�@�C���[���C�t��
		{

		}
	}
	else if (m_enemyNearMama != nullptr)
	{
		if (m_enemyNearMama->m_setWeapon == 4)	//�M�K�g���L���m��
		{
			m_bulletModel.Draw(rc);
		}
	}
	else if (m_enemyFarMama != nullptr)
	{
		if (m_enemyFarMama->m_setWeapon == 5)	//�~�T�C��
		{

		}
		else if (m_enemyFarMama->m_setWeapon == 6)	//��͖C
		{
			m_bulletModel.Draw(rc);
		}
	}
}