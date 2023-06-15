#include "stdafx.h"
#include "MachineGunAttack.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy_Far.h"
#include "Enemy_Near.h"
#include "Game.h"
#include "Boss.h"
#include "Boss_Drill.h"

MachineGunAttack::MachineGunAttack()
{

	//�X�e�[�^�X�̏�����---------------------------------

	//�e�̃_���[�W
	m_bulletDamage = 5.0f;

	//�����X�s�[�h
	m_fallSpeed = 0.0f;

	//�O�����̃X�s�[�h
	m_moveSpeed = 100.0f;

	//---------------------------------------------------

}

MachineGunAttack::~MachineGunAttack()
{
	
}

void MachineGunAttack::SetUp()
{

	//�e�̏�����
	BulletSetUp(2.0f);

}

void MachineGunAttack::DestroyWithImpactEffect()
{

	//���e�G�t�F�N�g�̍Đ�
	PlayEffect(enMasinganKemuri, m_position, m_rot, { 10.0f,10.0f,10.0f });


	//�������g�̍폜
	DeleteGO(this);

}

void MachineGunAttack::Update()
{

	//���C���Q�[����
	if (m_player->game_state == 0)
	{

		//�ړ�����
		Move(1800.0f);


		//�_���[�W����
		DamageEvent(m_bulletDamage);

	}
	//���U���g��
	else if (m_player->game_state == 2)
	{

		//�������g�̍폜
		DeleteGO(this);	

	}


	//�v���C���[���|�[�Y��ʂ���Q�[�����I��������Ə���
	if (m_player->game_end_state == 1)
	{

		//�������g�̍폜
		DeleteGO(this);	

	}

}

void MachineGunAttack::Render(RenderContext& rc)
{

	//�e���f���̕\��
	m_bulletModel.Draw(rc);

}