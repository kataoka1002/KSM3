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
	//���ʉ��̍쐬
	m_soundSource = NewGO<SoundSource>(0);
}

Enemy_Bullet::~Enemy_Bullet() 
{
	DeleteGO(masinganEffect);
	DeleteGO(m_soundSource);
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
			originRotation.Multiply(m_macineGunLocalPosition);	//�|���Z
			//�ŏI�I�Ȓe�̉�]������
			m_rot = originRotation;
			m_position += m_macineGunLocalPosition;				//����ɐe���猩���ʒu�𑫂��čŏI�I�ȕ���̈ʒu������
			//�o���b�g�̑O�����̐ݒ�
			m_bulletFowrad = m_enemyMama->m_enemyForward;
			m_bulletModel.SetRotation(m_enemyMama->m_enemyRotation);
			m_bulletModel.SetPosition(m_position);

			//���ʉ��̐ݒ�
			g_soundEngine->ResistWaveFileBank(2, "Assets/audio/enemy/masinganHassya.wav");
			m_soundSource->Init(m_enemyMama->m_setWeapon);	//������
			m_soundSource->SetVolume(0.2f);					//���ʒ���
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
		
			//���ʉ��̏�����
			m_soundSource->Init(m_enemyNearMama->m_setWeapon);

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

			//���ʉ��̏�����
			m_soundSource->Init(m_enemyFarMama->m_setWeapon);

			break;

		default:
			break;
		}
	}
		

	//�Z�b�g�A�b�v
	Setup();


	return true;
}

void Enemy_Bullet::Setup() 
{
	//�G�t�F�N�g�̏������ƍĐ�
	masinganEffect = NewGO<EffectEmitter>(0);
	masinganEffect->Init(enMasinganHibana);
	masinganEffect->SetScale({ 0.7f,0.7f,0.7f });
	masinganEffect->SetPosition(m_position);
	masinganEffect->Play();
}

void Enemy_Bullet::Update() 
{
	if (m_player->game_state == 0)
	{
		//�ʒu��0�ȉ��ɂȂ�Ə�����
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

	}

}

void Enemy_Bullet::MoveFar()
{
	if (m_enemyFarMama->m_setWeapon == 5)	//�~�T�C��
	{

	}
	else if (m_enemyFarMama->m_setWeapon == 6)	//��͖C
	{

	}

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