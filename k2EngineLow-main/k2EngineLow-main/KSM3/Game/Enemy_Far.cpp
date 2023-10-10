#include "stdafx.h"
#include <time.h>
#include <stdlib.h>
#include "Enemy_Far.h"
#include "Player.h"
#include "Game.h"
#include "Drop_item.h"
#include "Enemy_Bullet.h"
#include "Enemy_HP_UI.h"
#include "GameCamera.h"
#include "Combo.h"


Enemy_Far::Enemy_Far()
{

	//�X�e�[�^�X�̏�����----------------------------------------

	//�̗�
	m_enemyHP = 200;

	//�̗͂̍ő�l
	m_enemyHPMax = 200;

	//����̎��
	m_setWeapon = 6;

	//����̃��[�J���|�W�V����
	m_weaponLocalPos = { 0.0f,120.0f,150.0f };

	//�G�l�~�[�̈ړ����x
	m_enemySpeed = 200.0f;

	//----------------------------------------------------------

}

Enemy_Far::~Enemy_Far()
{

	//�G�l�~�[�̑����̍폜
	DeleteGO(m_asiotoSE);

	//HP��UI���폜
	DeleteGO(m_HPUI);

	//�G�l�~�[�̎��SSE���폜
	DeleteGO(m_enemyDeadSE);

	//�r�V�����폜
	DeleteGO(m_bisiSE);

	//��͖CSE�̍폜
	DeleteGO(m_battleShipGunSE);

}

void Enemy_Far::GameSetUp()
{

	//�쐬����UI�N���X�Ɏ����̃|�C���^��������
	m_HPUI->SetEnemyFar(this);	

}

void Enemy_Far::InitEnemyModel()
{

	//�G�l�~�[�̐ݒ�
	m_enemyModel->Init("Assets/modelData/Enemy_model_type2.tkm");
	m_enemyModel->SetScale(m_enemySize);
	m_enemyModel->SetRotation(m_enemyRotation);
	m_enemyModel->SetPosition(m_enemyPosition);


	//�L�����N�^�[�R���g���[���[���������B
	m_enemyCharacterController.Init(
		200.0f,			//���a�B
		70.0f,			//�����B
		m_enemyPosition	//���W�B
	);

}

void Enemy_Far::Update()
{
	//���E���~�܂��Ă���Ƃ�
	if (m_game->IsStopWorld() != false)
	{
		if (m_deleteGoThisFlag == true)
		{
			ToPushButton();
		}

		return;
	}

	//���C���Q�[����
	if (m_player->GetGameState() == MAIN_GAME_NUM)
	{

		//�����Ă����
		if (m_defeatState == false)
		{

			//�G�l�~�[�ɋ��ʂ��铮��
			NormalAction(5000.0f);


			//�̗͂�0�ɂȂ������̏���
			HPUnder0();

		}
		//���񂾂�
		else if (m_defeatState == true)	
		{
			
			//�܂��ł܂��Ă���Ƃ�
			if (m_flashFinishFlag == false)	
			{

				//��莞�Ԍo�߂�����
				if (m_flashTime < 0)
				{

					//���S���̏���
					ExecuteOnEnemyDefeated();


					//�Ռ��������I������t���O�𗧂Ă�
					m_flashFinishFlag = true;

				}


				//���Ԍv��
				m_flashTime--;

				return;
			}

			
			//�T�C�Y�����������Ă���
			m_enemySize -= 0.15f;
			

			//�T�C�Y��0�ȉ��ɂȂ��
			if (m_enemySize <= 0.0f)
			{

				//�������g�̍폜
				DeleteGO(this);


				//���X�g�������
				m_game->RemoveEnemyFarFromList(this);

			}


			//���f���T�C�Y�̍X�V
			m_enemyModel->SetScale(m_enemySize);
			m_enemyModel->Update();

		}
	}
	else if (m_player->GetGameState() == PAUSE_NUM || m_player->GetGameState() == CUSTOMIZE_NUM)
	{

		//������~
		AsiotoSEManage(false);

	}
}


void Enemy_Far::PlayerSearch()
{

	//�G�l�~�[�̑O������toPlayerDir�Ƃ̓��ς��v�Z����
	float t = m_toPlayerDir.Dot(m_enemyForward);


	//���ς̌��ʂ�acos�֐��ɓn���āAm_enemyFowrad��toPlayerDir�̂Ȃ��p�x�����߂�B
	float angle = acos(t);


	//�G�l�~�[�̎���Ƀv���C���[�������Ă���&������3000�ȉ��ɂȂ� & �v���C���[�̕����������Ă���
	if (fabsf(angle) < Math::DegToRad(45.0f) && m_distToPlayer <= 3000.0f && m_enemyDirState == 0) 
	{

		//�U���\
		m_atackOK = true;

	}
	else 
	{

		//�U���s��
		m_atackOK = false;

	}


	//���x�v�Z
	CalcSpeed(m_enemySpeed, m_enemyDirState);


	//��ނ��ĂȂ��Ȃ�
	if (m_enemyEscape != true)
	{

		//�G�l�~�[�̑O�������g���āA��]�N�H�[�^�j�I�����v�Z����B
		m_enemyRotation.SetRotationY(atan2(m_enemyForward.x, m_enemyForward.z));

	}

}

void Enemy_Far::Move()
{
	
	//�v���C���[����
	if (m_enemyDirState == 0) 
	{

		//�����𖞂����Ă���Ԃ����v���C���[�Ɍ������Ĉړ�����
		if (m_distToPlayer >= 3000.0f && m_distToPlayer <= 5000.0f)
		{

			//�G�l�~�[�̈ړ�
			m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());


			//���ڂ���̔���
			DustEffect();


			//�����Đ�
			AsiotoSEManage(true);

		}
		else
		{

			//������~
			AsiotoSEManage(false);

		}


		//�G�l�~�[�ƃv���C���[�̋������߂��� & ���m��
		if (m_distToPlayer <= 1500.0f && rand() % 150 == 1)
		{

			//��ރX�e�[�g
			m_enemyDirState = 1;
			

			//�ړ����x�̐ݒ�
			m_enemyMoveSpeed = m_enemyForward * -250.0f;	


			//��ޒ��t���O�𗧂Ă�
			m_enemyEscape = true;

		}
		//�G�l�~�[�ƃv���C���[�̋������߂��� & ���m��
		else if (m_distToPlayer < 2800.0f && rand() % 900 == 1)
		{
			
			//���ړ��X�e�[�g
			m_enemyDirState = 2;

		}
		//�G�l�~�[�ƃv���C���[�̋������߂��� & ���m��
		else if (m_distToPlayer < 2800.0f && rand() % 900 == 1)
		{

			//���ړ��X�e�[�g
			m_enemyDirState = 3;

		}

	}
	//������
	else if (m_enemyDirState == 1)	
	{

		//�ړ�������B
		m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());


		//�����Đ�
		AsiotoSEManage(true);


		//��苗���ȏ� or ���m��
		if (m_distToPlayer > 2800.0f || rand() % 300 == 1)
		{
			
			//��ރX�g�b�v
			m_enemyEscape = false;


			//�O�����X�e�[�g�ɕύX
			m_enemyDirState = 0;


			//������~
			AsiotoSEManage(false);

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

			//�O�����X�e�[�g�ɕύX
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

			//�O�����X�e�[�g�ɖ߂�
			m_enemyDirState = 0;


			//������~
			AsiotoSEManage(false);

		}

	}

}

void Enemy_Far::Attack()
{
	//�U�����\�Ȃ�
	if (m_atackOK == true)
	{

		//�U���^�C�~���O�̌v�Z
		m_attackCount++;


		//����ɂ���Ă̕���
		switch (m_setWeapon)
		{
		case MISSILE_NUM://�~�T�C��


			//���̃J�E���g�ɂȂ��
			if (m_attackCount % 180 == 0)
			{

				//����
				Fire(MISSILE_NUM);


				//�J�E���g���Z�b�g
				m_attackCount = 0;

			}

			break;


		case BATTLESHIPGUN_NUM://��͖C


			//���̃J�E���g�ɂȂ��
			if (m_attackCount >= 120)
			{

				//����
				Fire(BATTLESHIPGUN_NUM);
							
							
				//�J�E���g���Z�b�g
				m_attackCount = 0;

			}

			break;


		default:
			break;

		}

	}

}

void Enemy_Far::Fire(int m_weaponNum)
{
	
	//��͖C�Ȃ�
	if (m_weaponNum == BATTLESHIPGUN_NUM)
	{

		//�e�̐���
		Enemy_Bullet* m_enemyBullet;
		m_enemyBullet = NewGO<Enemy_Bullet>(1, "enemy_bullet");
		m_enemyBullet->SetEnemyFarMama(this);
		m_enemyBullet->SetPosition(m_enemyPosition);						//�e�̈ʒu��ݒ�
		m_enemyBullet->SetLocalPosition({105.0f,140.0f,290.0f});	//���[�J���|�W�V�����ݒ�
		//m_enemyBullet->m_bulletFowrad = m_enemyForward;						//�e�̑O�����̐ݒ�		
		m_enemyBullet->SetRotation(m_enemyRotation);					//��]�̓G�l�~�[�Ɠ���


		//�e�̐���
		Enemy_Bullet* m_enemyBullet2;
		m_enemyBullet2 = NewGO<Enemy_Bullet>(1, "enemy_bullet");
		m_enemyBullet2->SetEnemyFarMama(this);
		m_enemyBullet2->SetPosition(m_enemyPosition);						//�e�̈ʒu��ݒ�
		m_enemyBullet2->SetLocalPosition({-105.0f,140.0f,290.0f});	//���[�J���|�W�V�����ݒ�
		m_enemyBullet2->SetRotation(m_enemyRotation);					//��]�̓G�l�~�[�Ɠ���


		//�e�̐���
		Enemy_Bullet* m_enemyBullet3;
		m_enemyBullet3 = NewGO<Enemy_Bullet>(1, "enemy_bullet");
		m_enemyBullet3->SetEnemyFarMama(this);
		m_enemyBullet3->SetPosition(m_enemyPosition);						//�e�̈ʒu��ݒ�
		m_enemyBullet3->SetLocalPosition({0.0f,140.0f,290.0f});		//���[�J���|�W�V�����ݒ�
		m_enemyBullet3->SetRotation(m_enemyRotation);					//��]�̓G�l�~�[�Ɠ���


		//���ˉ��̐ݒ�ƍĐ�
		m_battleShipGunSE = NewGO<SoundSource>(0);	//���Đ�����ƏI���Ȃ̂ŃC���X�^���X��ێ������Ȃ��ׂɂ�����NewGO����
		m_battleShipGunSE->Init(enButtleShipGun);	//������
		m_battleShipGunSE->SetVolume(1.0f * m_game->GetSEVol());			//���ʒ���
		m_battleShipGunSE->Play(false);

	}
}

void Enemy_Far::HPUnder0()
{

	//HP��0�ȉ��ɂȂ��
	if (m_enemyHP <= 0.0f)
	{

		//���S�t���O�𗧂Ă�
		m_defeatState = true;


		//�Ռ����܂��������ĂȂ��Ȃ�
		if (m_impactPlay == false)
		{

			//�Ռ��G�t�F�N�g�̍Đ�
			PlayEffect(enImpact, m_enemyPosition, m_enemyRotation, { 10.0f,10.0f,10.0f });


			//�Ռ���SE���Đ�
			m_bisiSE = NewGO<SoundSource>(0);
			m_bisiSE->Init(enBisi);								//������
			m_bisiSE->SetVolume(3.8f * m_game->GetSEVol());		//���ʒ���
			m_bisiSE->Play(false);								//�Đ�


			//�Ռ������t���O�𗧂Ă�
			m_impactPlay = true;

		}
		
		//���f���𔒂�������
		//m_enemyModel->PlayFlash();

	}

}

void Enemy_Far::EnemyDead()
{

	//�����G�t�F�N�g�̍Đ�
	PlayEffect(enEnemyDead, m_enemyPosition, m_enemyRotation, { 5.0f,5.0f,5.0f });


	//�ʂ̔����G�t�F�N�g�̍Đ�
	PlayEffect(enTyakudan, m_enemyPosition, m_enemyRotation, { 15.7f,15.7f,15.7f });


	//�������̐ݒ�ƍĐ�
	m_enemyDeadSE = NewGO<SoundSource>(0);	//���Đ�����ƏI���Ȃ̂ŃC���X�^���X��ێ������Ȃ��ׂɂ�����NewGO����
	m_enemyDeadSE->Init(enEnemyDeadSE);		//������
	m_enemyDeadSE->SetVolume(1.5f * m_game->GetSEVol());			//���ʒ���
	m_enemyDeadSE->Play(false);

}

void Enemy_Far::DeleteGoThis()
{
	//�������g�̍폜
	DeleteGO(this);

	//���X�g�������
	m_game->RemoveEnemyFarFromList(this);
}


void Enemy_Far::Render(RenderContext& rc)
{

	//���f���̕`��B
	m_enemyModel->Draw(rc);

	//�����Ă����
	if (m_defeatState == false)
	{
		//����\��
		m_enemyWeaponModel->Draw(rc);
	}

}
