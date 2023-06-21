#include "stdafx.h"
#include "Core_weapons.h"
#include "Core_weapons_attack.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy_Far.h"
#include "Enemy_Near.h"
#include "Game.h"
#include "Boss.h"
#include "Boss_Drill.h"

Core_weapons_attack::Core_weapons_attack() 
{
	
	//�X�e�[�^�X�̏�����---------------------------------

	//�e�̃_���[�W
	m_bulletDamage = 5.0f;

	//�����X�s�[�h
	m_fallSpeed = 0.1f;

	//�O�����̃X�s�[�h
	m_moveSpeed = 200.0f;

	//�X�s�[�h������
	m_decreaseSpeed = 0.05f;

	//�����X�s�[�h������
	m_addFallSpeed = 0.1f;

	//---------------------------------------------------

}

Core_weapons_attack::~Core_weapons_attack()
{

}

void Core_weapons_attack::SetUp() 
{

	//�R�A�����T��
	m_coreWeapon = FindGO<Core_weapons>("core_weapons");


	//���̉�]�ʂ����߂�
	m_originRotation = m_coreWeapon->cw_Rotation;


	//��������ꏊ�����߂�
	m_position = m_coreWeapon->cw_position;


	//�t���Ă���R�A����ɂ���ĕς���
	switch (m_coreWeapon->set_weapons)
	{

	case 1:

		break;

	case 2:

		//���[�J���|�W�V�����̐ݒ�
		m_bulletLocalPosition = { 0.0f,12.0f,0.0f };

		break;

	default:
		break;

	}


	//�e�̏�����
	BulletSetUp(2.0f);

}


void Core_weapons_attack::DestroyWithImpactEffect()
{

	//���e�G�t�F�N�g�̍Đ�
	PlayEffect(enMasinganKemuri, m_position, m_rot, { 10.0f,10.0f,10.0f });


	//�������g�̍폜
	DeleteGO(this);

}

void Core_weapons_attack::Update() 
{

	//���C���Q�[����
	if (m_player->GetGameState() == MAIN_GAME_NUM)
	{

		//�_���[�W����
		DamageEvent(m_bulletDamage);


		//�ړ�����
		Move(2000.0f);

	}
	//���U���g��ʂɍs����
	else if (m_player->GetGameState() == RESULT_NUM)
	{
		
		//�������g�̍폜
		DeleteGO(this);	

	}

	
	//�v���C���[���|�[�Y��ʂ���Q�[�����I���������
	if (m_player->GetGameEndState() == 1)
	{

		//�������g�̍폜
		DeleteGO(this);	

	}

}

void Core_weapons_attack::Render(RenderContext& rc) 
{

	//�e���f���̏�����
	m_bulletModel->Draw(rc);

}

