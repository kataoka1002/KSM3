#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include"Game.h"

#include <time.h>
#include <stdlib.h>

void Enemy::Init(Vector3 initPos)
{
	m_position = initPos;
	m_rotation.SetRotationY(Math::PI);
	// �����o�ϐ���m_player�ɃA�h���X���L�����Ă����B�A
	m_player = FindGO<Player>("Player");
}

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

bool Enemy::Start()
{
	//���f����ǂݍ���
	m_modelRender.Init("Assets/modelData/enemy_model.tkm");
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale({ 1.0f, 1.0f, 1.0f });
	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(
		50.0f,			//���a�B
		-40.0f,			//�����B
		m_position		//���W�B
	);
	//�������������B
	srand((unsigned)time(NULL));

	return true;
}
 
void Enemy::Update()
{
	//�ǐՏ���
	Chase();
	//�v���C���[�Ɍ������Ď��_�ړ�
	SearchPlayer();
	//�X�e�[�g�̑J�ڏ����B
	ManageState();
	//���f���̍X�V
	m_modelRender.Update();
}

 void Enemy::SearchPlayer()
{
	//�G�l�~�[����v���C���[�������Ă�����ǂ�������
	Vector3 toPlayer = m_player->m_position - m_position;

	    //�v���C���[�Ƃ̋������v�Z����
		float distToPlayer = toPlayer.Length();
		   //�v���C���[�Ɍ������ĐL�т�x�N�g���𐳋K������
			Vector3 toPlayerDir = toPlayer;
			toPlayerDir.Normalize();
			//�G�l�~�[�̑O��������toPlayerDir�Ƃ̓��ς��v�Z����
			float t = toPlayerDir.Dot(m_forward);
			//���ς̌��ʂ�acos�֐��ɓn���āAm_enemyFowrad��toPlayerDir�̂Ȃ��p�x�����߂�B
			float angle = acos(t);

				//�G�L�����̑O���������X�V����
				m_forward = toPlayerDir;
		// �G�̑O���������g���āA��]�N�H�[�^�j�I�����v�Z����B
		m_rotation.SetRotationY(atan2(m_forward.x, m_forward.z));
		m_modelRender.SetPosition(m_position);
		m_modelRender.SetRotation(m_rotation);
		m_modelRender.Update();
}

void Enemy::Chase()
{
	//�ǐՃX�e�[�g�łȂ��Ȃ�A�ǐՏ����͂��Ȃ��B
	if (m_enemyState != EnemyState_Chase)
	{
		return;
	}

	//�G�l�~�[����v���C���[�Ɍ������x�N�g�����v�Z����
	Vector3 toPlayer = m_player->m_position - m_position;
	//�x�N�g���𐳋K������B
	toPlayer.Normalize();
	//�ړ����x��ݒ肷��B
	m_moveSpeed = toPlayer * 100.0f;
	//�G�l�~�[���ړ�������
	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	if (m_charaCon.IsOnGround()) {
		//�n�ʂɂ����B
		m_moveSpeed.y = 0.0f;
	}
	Vector3 modelPosition = m_position;
	//������Ƃ������f���̍��W��������B
	modelPosition.y += 2.5f;
	m_modelRender.SetPosition(modelPosition);
}

void Enemy::ProcessCommonStateTransition()
{
	//�e�^�C�}�[��������
	//�ҋ@���ԂƒǐՎ��Ԃ𐧌����邽��
	m_idleTimer = 0.0f;
	m_chaseTimer = 0.0f;
	//�G�l�~�[����v���C���[�Ɍ������x�N�g�����v�Z����
	Vector3 toPlayer = m_player->m_position - m_position;
	//�x�N�g���𐳋K������B
	toPlayer.Normalize();

	int ram = rand() % 100;
	if (ram<50)
	{
		//�ǐՃX�e�[�g�ɑJ�ڂ���B
		m_enemyState = EnemyState_Chase;
		return;
	}
	else
	{
		//�ҋ@�X�e�[�g�ɑJ�ڂ���B
		m_enemyState = EnemyState_Idle;
		return;
	}
}

void Enemy::ProcessIdleStateTransition()
{
	m_idleTimer += g_gameTime->GetFrameDeltaTime();
	//�ҋ@���Ԃ�������x�o�߂�����
	if (m_idleTimer >= 2.0f)
	{
		//���̃X�e�[�g�ɑJ�ڂ���B
		ProcessCommonStateTransition();
	}
}

void Enemy::ProcessChaseStateTransition()
{
	m_chaseTimer += g_gameTime->GetFrameDeltaTime();
	//�ǐՎ��Ԃ�������x�o�߂�����
	if (m_chaseTimer >= 2.0f)
	{
		//���̃X�e�[�g�ɑJ�ڂ���B
		ProcessCommonStateTransition();
	}
}

void Enemy::ManageState()
{
	switch (m_enemyState)
	{
		//�ҋ@�X�e�[�g�̎�
	case Enemy::EnemyState_Idle:
		//�ҋ@�X�e�[�g�̃X�e�[�g�J�ڏ����B
		ProcessIdleStateTransition();
		break;
		//�ǐՃX�e�[�g�̎�
	case Enemy::EnemyState_Chase:
		//�ǐՃX�e�[�g�̃X�e�[�g�J�ڏ����B
		ProcessChaseStateTransition();
		break;
	}
}

void Enemy::Render(RenderContext& rc)
{
	//���f���̕`��B
	m_modelRender.Draw(rc);
}