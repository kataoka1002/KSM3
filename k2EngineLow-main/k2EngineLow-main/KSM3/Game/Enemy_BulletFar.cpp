#include "stdafx.h"
#include "Enemy_BulletFar.h"
#include "Core_weapons.h"
#include "Enemy_Far.h"
#include "Player.h"
#include "sound/SoundEngine.h"

Enemy_BulletFar::Enemy_BulletFar()
{
	//�o���b�g�̏�����
	m_bulletModel.Init("Assets/modelData/V_P_bullet.tkm");
}

Enemy_BulletFar::~Enemy_BulletFar()
{
	
}

bool Enemy_BulletFar::Start()
{
	m_enemy = FindGO<Enemy_Far>("enemy_far");
	m_player = FindGO<Player>("player");
	m_coreWeapons = FindGO<Core_weapons>("core_weapons");

	//����̎�ނɂ���Č��ʉ���ς���
	switch (m_enemy->m_setWeapon)
	{
	case 1:	//�~�T�C��
		g_soundEngine->ResistWaveFileBank(2, "Assets/audio/Taihou_kouho1.wav");
		break;
	case 2:	//��͖C
		g_soundEngine->ResistWaveFileBank(2, "Assets/audio/Taihou_kouho1.wav");
		break;
	default:
		break;
	}

	m_soundSource = NewGO<SoundSource>(0);	//���ʉ��̍쐬
	m_soundSource->Init(2);				//������
	m_soundSource->SetVolume(0.2f);		//���ʒ���
	m_soundSource->Play(false);			//�Đ�

	//�Z�b�g�A�b�v
	Setup();

	return true;
}

void Enemy_BulletFar::Setup()
{
	m_bulletFowrad = m_enemy->m_enemyForward;		//�o���b�g�̑O�����̐ݒ�
	m_position.y += 10.0f;							//�ł��o���ʒu�������グ��
	m_bulletModel.SetRotation(m_enemy->m_enemyRotation);
	m_bulletModel.SetPosition(m_position);
}

void Enemy_BulletFar::Update()
{
	if (m_player->game_state == 0)
	{
		//�ʒu��0�ȉ��ɂȂ�Ə�����
		if (m_position.y <= 0.0f)
		{
			DeleteGO(this);
		}

		Move();	//�ړ�����
		m_bulletModel.Update();	//�o���b�g�̍X�V
	}
}

void Enemy_BulletFar::Move()
{
	//�e��O�ɔ�΂�����
	m_position += m_bulletFowrad * m_bulletSpeed;
	if (m_position.y <= m_coreWeapons->cw_position.y && fast_count == true)
	{
		m_position.y += 1.0f;
	}
	else
	{
		fast_count = false;
		m_fallSpeed += 0.1f;
	}
	m_position.y -= m_fallSpeed;
	m_bulletSpeed -= 0.05f;	//���񂾂�x������

	m_bulletModel.SetPosition(m_position);
}

void Enemy_BulletFar::Render(RenderContext& rc)
{
	m_bulletModel.Draw(rc);
}