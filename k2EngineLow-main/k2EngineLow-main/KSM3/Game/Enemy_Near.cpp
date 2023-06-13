#include "stdafx.h"
#include <time.h>
#include <stdlib.h>
#include "Enemy_Near.h"
#include "Player.h"
#include "Game.h"
#include "Drop_item.h"
#include "Enemy_Bullet.h"
#include "Enemy_HP_UI.h"
#include "GameCamera.h"
#include "Combo.h"


Enemy_Near::Enemy_Near()
{

	//�X�e�[�^�X�̏�����----------------------------------------

	//�̗�
	m_enemyHP = 200;

	//�̗͂̍ő�l
	m_enemyHPMax = 200;

	//����̎��
	m_setWeapon = 4;

	//����̃��[�J���|�W�V����
	m_weaponLocalPos = { 0.0f,40.0f,0.0f };

	//�G�l�~�[�̈ړ����x
	m_enemySpeed = 250.0f;

	//----------------------------------------------------------

}

Enemy_Near::~Enemy_Near()
{

	//�G�l�~�[�̑����̍폜
	DeleteGO(m_asiotoSE);

	//HP��UI���폜
	DeleteGO(m_HPUI);

	//�G�l�~�[�̎��SSE���폜
	DeleteGO(m_enemyDeadSE);

	//�L���m����SE���폜
	DeleteGO(m_cannonSE);

}

void Enemy_Near::GameSetUp()
{

	//�쐬����UI�N���X�Ɏ����̃|�C���^��������
	m_HPUI->m_enemyNear = (this);

}

void Enemy_Near::InitEnemyModel()
{
	
	//�G�l�~�[�̐ݒ�
	m_enemyModel.Init("Assets/modelData/enemy_model.tkm");
	m_enemyModel.SetScale(2.0f);
	m_enemyModel.SetRotation(m_enemyRotation);
	m_enemyModel.SetPosition(m_enemyPosition);


	//�L�����N�^�[�R���g���[���[��������
	m_enemyCharacterController.Init(
		50.0f,			//���a�B
		40.0f,			//�����B
		m_enemyPosition	//���W�B
	);

}

void Enemy_Near::Update()
{

	//���C���Q�[����
	if (m_player->game_state == 0)
	{

		//�G�l�~�[�ɋ��ʂ��铮��
		NormalAction(4000.0f);


		//�|�������ɃA�C�e���𗎂Ƃ�����
		HPUnder0();

	}
	else if (m_player->game_state == 1 || m_player->game_state == 3)
	{

		//������~
		AsiotoSEManage(false);

	}
}

void Enemy_Near::PlayerSearch()
{

	//�G�l�~�[�̑O�������X�V����


	//�v���C���[�����̎�
	if (m_enemyDirState == 0)
	{

		//�_�b�V��������Ȃ��Ȃ�
		if (m_dashFlag != true)
		{
			
			//�v���C���[����
			m_enemyForward = m_toPlayerDir;					
			
			//�ړ����x��ݒ�
			m_enemyMoveSpeed = m_enemyForward * 250.0f;		 

		}

	}
	//���ړ���
	else if (m_enemyDirState == 2)
	{

		//�O�ς���G�l�~�[�̉��������擾
		m_enemyForward = Cross(m_Up, m_toPlayerDir);	
		
		
		//�ړ����x�̐ݒ�
		m_enemyMoveSpeed = m_enemyForward * 250.0f;		

	}
	//���ړ���
	else if (m_enemyDirState == 3)
	{

		//�O�ς���G�l�~�[�̉��������擾
		m_enemyForward = Cross(m_toPlayerDir, m_Up);	
		
		
		//�ړ����x�̐ݒ�
		m_enemyMoveSpeed = m_enemyForward * 250.0f;		

	}
	//�U����
	else if (m_enemyDirState == 4)
	{

		//�U��

	}
	//�������œ����Ȃ�
	else if (m_enemyDirState == 5)	
	{	

		//���Ԍo��
		m_recoilCount--;			


		//�J�E���g�����ȉ��ɂȂ�����
		if (m_recoilCount <= 0)
		{

			//�v���C���[�̕�������悤�ɂȂ�(�ҋ@���)
			m_enemyForward = m_toPlayer;

		}


		//�J�E���g�����ȉ��ɂȂ�����
		if (m_recoilCount <= -180)
		{
			//�܂��퓬��ԂɂȂ�
			

			//�e�����������ǂ����t���O�����낷
			m_attackFlag = false;	


			//�^�[�Q�b�g��ݒ肵�Ă��邩�ǂ����t���O�����낷
			m_targetFlag = false;


			//�v���C���[�����X�e�[�g�ɂ���
			m_enemyDirState = 0;


			//�J�E���g���Z�b�g
			m_recoilCount = 180;

		}
	}


	//�_�b�V��������Ȃ��Ȃ��]����
	if (m_dashFlag != true)
	{

		//�G�l�~�[�̑O�������g���āA��]�N�H�[�^�j�I�����v�Z����B
		m_enemyRotation.SetRotationY(atan2(m_enemyForward.x, m_enemyForward.z));

	}

}

void Enemy_Near::Move()
{
	
	//�v���C���[����
	if (m_enemyDirState == 0) 
	{

		//�v���C���[�Ɍ������Ĉړ�����(�ʏ�X�s�[�h)
		if (m_distToPlayer >= 1500.0f && m_distToPlayer <= 4000.0f)
		{

			//�G�l�~�[�̈ړ�
			m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());


			//���ڂ���̔���
			DustEffect();


			//�����Đ�
			AsiotoSEManage(true);

		}
		//��苗���ȓ� & �e���܂������ĂȂ��Ȃ�
		else if (m_distToPlayer < 1500.0f && m_attackFlag == false)
		{
			//�v���C���[�Ɍ������Ĉړ�����(�_�b�V��)
			
			//�^�[�Q�b�g��ݒ肵�ĂȂ��Ȃ�
			if (m_targetFlag == false)
			{

				//�v���C���[���������܂ł����ꏊ���^�[�Q�b�g�̐ݒ�(1��̂�)
				m_enemyTargetPos = m_player->player_position;

				//�^�[�Q�b�g�Z�b�g�t���O�𗧂Ă�
				m_targetFlag = true;

			}


			//�_�b�V����
			m_dashFlag = true;	

			
			//�G�l�~�[�̈ړ�
			m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());


			//���ڂ���̔���
			DustEffect();


			//������~
			AsiotoSEManage(false);

		}	


		//�^�[�Q�b�g�����܂�����
		if (m_targetFlag == true)	
		{

			//�G�l�~�[����^�[�Q�b�g�܂ł̃x�N�g�������߂�
			m_toTarget = m_enemyTargetPos - m_enemyPosition;


			//���̃x�N�g���̋��������߂�
			m_distTarget = m_toTarget.Length();


			//���̃x�N�g���𐳋K��
			m_toTarget.Normalize();

			
			//�^�[�Q�b�g����
			m_enemyForward = m_toTarget;					
			
			
			//�ړ����x���v�Z(�_�b�V��)
			m_enemyMoveSpeed = m_enemyForward * 700.0f;		


			//�߂Â�����U��
			if (m_distTarget <= 150.0f)
			{

				//�U���\�t���O�𗧂Ă�
				m_fireFlag = true;

				//�U�����X�e�[�g�ɕύX
				m_enemyDirState = 4;

			}

		}

	}
	//������
	else if (m_enemyDirState == 2)	
	{

		//�ړ�������B
		m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());


		//���ڂ���̔���
		DustEffect();


		//�����Đ�
		AsiotoSEManage(true);


		//������x������X�g�b�v
		if (rand() % 200 == 1)
		{

			//�v���C���[����
			m_enemyDirState = 0;


			//������~
			AsiotoSEManage(false);

		}

	}
	//������
	else if (m_enemyDirState == 3)	
	{

		//�ړ�������B
		m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());


		//���ڂ���̔���
		DustEffect();


		//�����Đ�
		AsiotoSEManage(true);


		//������x������X�g�b�v
		if (rand() % 200 == 1)
		{

			//�v���C���[����
			m_enemyDirState = 0;


			//������~
			AsiotoSEManage(false);

		}

	}
	//�U����
	else if (m_enemyDirState == 4)
	{
		
		//�e����������
		if (m_attackFlag == true)
		{

			//�_�b�V�����Ă���t���O������
			m_dashFlag = false;


			//�e���������甽���œ����Ȃ��X�e�[�g
			m_enemyDirState = 5;	

			return;
		}

	}

}

void Enemy_Near::Attack()
{

	//�U���\�Ȃ�
	if (m_fireFlag == true)
	{

		//�U���^�C�~���O�̌v�Z
		m_attackCount++;


		//����ɂ���Ă̕���
		switch (m_setWeapon)
		{

		case 4://�M�K�g���L���m��


			if (m_attackCount >= 10)
			{

				//����
				Fire(4);	


				//�J�E���g���Z�b�g
				m_attackCount = 0;


				//�U���\�t���O������
				m_fireFlag = false;

			}


			break;

		default:
			break;

		}

	}

}

void Enemy_Near::Fire(int weaponNum)
{

	//�M�K�g���L���m���Ȃ�
	if (weaponNum == 4)
	{

		//�e�̐���
		Enemy_Bullet* m_enemyBullet;
		m_enemyBullet = NewGO<Enemy_Bullet>(1, "enemy_bullet");
		m_enemyBullet->m_enemyNearMama = this;
		m_enemyBullet->m_position = m_enemyPosition;						//�e�̈ʒu��ݒ�
		m_enemyBullet->m_bulletLocalPosition = { 0.0f,100.0f,130.0f };		//���[�J���|�W�V�����ݒ�
		m_enemyBullet->originRotation = m_enemyRotation;					//��]�̓G�l�~�[�Ɠ���


		//�������̐ݒ�ƍĐ�
		m_cannonSE = NewGO<SoundSource>(0);
		m_cannonSE->Init(enGigatonCannon);					//������
		m_cannonSE->SetVolume(2.0f * m_game->SEvol);		//���ʒ���
		m_cannonSE->Play(false);


		//�e���������t���O�𗧂Ă�
		m_attackFlag = true;	

	}

}

void Enemy_Near::HPUnder0()
{

	//�̗͂�0�ɂȂ�����A�C�e���𗎂Ƃ�
	if (m_enemyHP <= 0.0f)
	{

		//���S���̏���
		ExecuteOnEnemyDefeated();


		//�������g�̍폜
		DeleteGO(this);


		//���X�g�������
		m_game->RemoveEnemyNearFromList(this);

	}

}

void Enemy_Near::EnemyDead()
{

	//�����G�t�F�N�g�̍Đ�
	PlayEffect(enEnemyDead, m_enemyPosition, m_enemyRotation, { 5.0f,5.0f,5.0f });


	//�������̐ݒ�ƍĐ�
	m_enemyDeadSE = NewGO<SoundSource>(0);			//���Đ�����ƏI���Ȃ̂ŃC���X�^���X��ێ������Ȃ��ׂɂ�����NewGO����
	m_enemyDeadSE->Init(enEnemyDeadSE);				//������
	m_enemyDeadSE->SetVolume(1.5f * m_game->SEvol);	//���ʒ���
	m_enemyDeadSE->Play(false);

}

void Enemy_Near::Render(RenderContext& rc)
{

	//���f���̕`��B
	m_enemyModel.Draw(rc);

	//���탂�f���̕`��
	m_enemyWeaponModel.Draw(rc);

}