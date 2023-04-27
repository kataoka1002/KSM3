#include "stdafx.h"
#include "Enemy_Bullet.h"
#include "Core_weapons.h"
#include "Enemy.h"
#include "Player.h"
#include "sound/SoundEngine.h"

Enemy_Bullet::Enemy_Bullet() 
{
	//�o���b�g�̏�����
	m_bulletModel.Init("Assets/modelData/V_P_bullet.tkm");
	m_bulletModel.SetScale(15.0f);
}

Enemy_Bullet::~Enemy_Bullet() 
{
	
}

bool Enemy_Bullet::Start()
{
	m_player = FindGO<Player>("player");
	m_coreWeapons = FindGO<Core_weapons>("core_weapons");


	//����̎�ނɂ���ď�������ς���
	switch (m_enemyMama->m_setWeapon)
	{
	case 1:	//�M�K�v���Y�}
		g_soundEngine->ResistWaveFileBank(2, "Assets/audio/Taihou_kouho1.wav");
		break;
	case 2:	//�}�V���K��
		//���ʉ��̐ݒ�
		g_soundEngine->ResistWaveFileBank(2, "Assets/audio/Taihou_kouho1.wav");
		//�G�l�~�[���猩�Đ������ʒu�ɒe��ݒ�
		originRotation.Multiply(m_macineGunLocalPosition);	//��������̌v�Z
		//�ŏI�I�Ȓe�̉�]������
		m_rot = originRotation;
		m_position += m_macineGunLocalPosition;				//����ɐe���猩���ʒu�𑫂��čŏI�I�ȕ���̈ʒu������
		break;
	case 3:	//�w�C���t�@�C���[���C�t��
		g_soundEngine->ResistWaveFileBank(2, "Assets/audio/Taihou_kouho1.wav");
		break;
	default:
		break;
	}

	m_soundSource = NewGO<SoundSource>(0);	//���ʉ��̍쐬
	m_soundSource->Init(2);					//������
	m_soundSource->SetVolume(0.2f);			//���ʒ���
	m_soundSource->Play(false);				//�Đ�

	//�Z�b�g�A�b�v
	Setup();

	return true;
}

void Enemy_Bullet::Setup() 
{
	m_bulletFowrad = m_enemyMama->m_enemyForward;				//�o���b�g�̑O�����̐ݒ�
	m_bulletModel.SetRotation(m_enemyMama->m_enemyRotation);
	m_bulletModel.SetPosition(m_position);
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

		Move();	//�ړ�����

		//�o���b�g�̍X�V
		m_bulletModel.SetRotation(m_rot);
		m_bulletModel.SetPosition(m_position);
		m_bulletModel.Update();
	}
}

void Enemy_Bullet::Move()
{
	//�e��O�ɔ�΂�����
	m_bulletSpeed += m_bulletFowrad * 2.0f;
	m_position += m_bulletSpeed;

	m_position.y -= 2.0f;
}

void Enemy_Bullet::Render(RenderContext& rc) 
{
	m_bulletModel.Draw(rc);
}