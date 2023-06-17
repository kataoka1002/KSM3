#include "stdafx.h"
#include "GigatonCannonAttack.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy_Far.h"
#include "Enemy_Near.h"
#include "Game.h"
#include "Boss.h"
#include "Boss_Drill.h"

GigatonCannonAttack::GigatonCannonAttack()
{

	//�X�e�[�^�X�̏�����---------------------------------

	//�e�̃_���[�W
	m_bulletDamage = 100.0f;

	//�����X�s�[�h
	m_fallSpeed = 0.0f;

	//�O�����̃X�s�[�h
	m_moveSpeed = 100.0f;

	//---------------------------------------------------

}

GigatonCannonAttack::~GigatonCannonAttack()
{

}

void GigatonCannonAttack::SetUp()
{

	//�e�̏�����
	BulletSetUp(10.0f);

}

void GigatonCannonAttack::DestroyWithImpactEffect()
{

	//���e�G�t�F�N�g�̍Đ�
	PlayEffect(enGigatonAttack, { m_position.x,m_position.y + 50.0f,m_position.z }, m_rot, { 5.0f,5.0f,5.0f });


	//�������̍Đ�
	m_cannonSE = NewGO<SoundSource>(0);
	m_cannonSE->Init(enGigatonCannon);					//������
	m_cannonSE->SetVolume(2.0f * m_game->GetSEVol());	//���ʒ���
	m_cannonSE->Play(false);


	//�������g�̍폜
	DeleteGO(this);

}

void GigatonCannonAttack::Update()
{

	//���C���Q�[����
	if (m_player->GetGameState() == 0)
	{

		//�ړ�����
		Move(150.0f);


		//�_���[�W����
		DamageEvent(m_bulletDamage);

	}
	//���U���g��
	else if (m_player->GetGameState() == 2)
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

void GigatonCannonAttack::Render(RenderContext& rc)
{

	//�M�K�g���L���m���̒e�͌����Ȃ�
	//m_bulletModel.Draw(rc);

}