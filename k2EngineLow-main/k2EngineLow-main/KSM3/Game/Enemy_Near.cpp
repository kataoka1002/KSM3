#include "stdafx.h"
#include "Enemy_Near.h"
#include "Player.h"
#include "Game.h"
#include <time.h>
#include <stdlib.h>
#include "Battle_ship_attack.h"
#include "Drop_item.h"
#include "Enemy_Bullet.h"


Enemy_Near::Enemy_Near()
{
	//�����̐���(���������鉹���Ȃ̂ŃC���X�^���X��ێ�������)
	m_asiotoSE = NewGO<SoundSource>(0);
	m_dashSE = NewGO<SoundSource>(0);
	
	m_pointList.push_back({ Vector3(0.0f,0.0f,0.0f),1 });		//��Ԗڂ̃|�C���g
	m_pointList.push_back({ Vector3(0.0f,0.0f,100.0f),2 });		//��Ԗڂ̃|�C���g
	m_pointList.push_back({ Vector3(100.0f,0.0f,200.0f),3 });	//�O�Ԗڂ̃|�C���g
	m_pointList.push_back({ Vector3(-100.0f,0.0f,200.0f),4 });	//�l�Ԗڂ̃|�C���g
	m_point = &m_pointList[0];									//��Ԗڂ̃|�C���g������
}

Enemy_Near::~Enemy_Near()
{
	//�G�l�~�[�������Ă��邩���v���[���[�ɋ�����
	//m_player->enemy_survival = false;	

	m_player->killEnemy++;	//�E�������𑝂₷

	DeleteGO(m_asiotoSE);
	DeleteGO(m_dashSE);
}

bool Enemy_Near::Start()
{
	m_player = FindGO<Player>("player");
	m_game = FindGO<Game>("game");

	//�G�l�~�[�̐ݒ�
	m_enemyModel.Init("Assets/modelData/enemy_model.tkm");
	m_enemyModel.SetScale(2.0f);
	m_enemyModel.SetRotation(m_enemyRotation);
	m_enemyModel.SetPosition(m_enemyPosition);
	//�L�����N�^�[�R���g���[���[���������B
	m_enemyCharacterController.Init(
		50.0f,			//���a�B
		40.0f,			//�����B
		m_enemyPosition	//���W�B
	);

	//�����̐ݒ�
	m_asiotoSE->Init(enRunning);	//������
	m_asiotoSE->SetVolume(0.8f);	//���ʒ���
	m_asiotoSE->Play(true);			//�Đ�
	m_asiotoSE->Stop();				//��~

	//�����̐ݒ�
	m_dashSE->Init(enDash);			//������
	m_dashSE->SetVolume(0.8f);		//���ʒ���
	m_dashSE->Play(true);			//�Đ�
	m_dashSE->Stop();				//��~


	SetUp();	//���퐶��

	return true;
}

void Enemy_Near::SetUp()
{
	//�G�̕���̎�ނ̊m��
	m_setWeapon = 4;//�����͂������񉼂Œ萔�ݒ肵�Ă邾���Ō�X�����_���ɂ��Ă����\��
	//set_weapons = rand() % 1 + 1;
	if (m_setWeapon == 4) {	//�M�K�g���L���m��
		m_enemyWeaponModel.Init("Assets/modelData/GIgaton_cannon.tkm");
		m_enemyWeaponModel.SetScale(1.3f);
		m_enemyWeaponModel.SetPosition(m_weaponPosition);
		m_enemyWeaponModel.SetRotation(m_weaponRotation);
		m_enemyWeaponModel.Update();
	}
}

void Enemy_Near::Update()
{
	//���ڂ���̊Ԋu�J�E���g
	m_sunaHassei++;

	if (m_player->game_state == 0)
	{
		//�G�l�~�[����v���C���[�ւ̃x�N�g��
		m_toPlayer = m_player->player_position - m_enemyPosition;
		//�v���C���[�Ƃ̋������v�Z����
		m_distToPlayer = m_toPlayer.Length();
		//�v���C���[�Ɍ������ĐL�т�x�N�g���𐳋K������
		m_toPlayerDir = m_toPlayer;
		m_toPlayerDir.Normalize();

		if (m_distToPlayer > 4000.0f && m_targetFlag == false)
		{
			m_lockOn = true;
		}
		else
		{
			m_lockOn = false;
		}

		//���b�N�I�����ĂȂ��Ȃ�p�X�ړ�����
		if (m_lockOn == true)
		{
			PassMove();
		}
		if (m_lockOn == false)
		{
			PlayerSearch();		//���G
			Move();				//�G�l�~�[�ړ�
			Attack();			//�U��
		}

		WeaponMove();		//����̈ړ���]	
		ItemDrop();			//�|�������ɃA�C�e���𗎂Ƃ�����


		//�G�l�~�[�ƕ���̍X�V
		m_enemyModel.SetPosition(m_enemyPosition);
		m_enemyModel.SetRotation(m_enemyRotation);
		m_enemyModel.Update();
		m_enemyWeaponModel.SetPosition(m_weaponPosition);
		m_enemyWeaponModel.SetRotation(m_weaponRotation);
		m_enemyWeaponModel.Update();

	}
}

void Enemy_Near::PassMove()
{
	//�����̃|�W�V��������ڕW�Ƃ���|�C���g�̃x�N�g��
	Vector3 m_toPoint = m_point->m_position - m_enemyPosition;
	//�������v�Z
	float m_diffToPoint = m_toPoint.Length();
	//�����̌v�Z
	Vector3 m_toPointDir = m_toPoint;
	m_toPointDir.Normalize();
	//�O�����̐ݒ�
	m_enemyForward = m_toPointDir;

	//���������ȓ��Ȃ�ړI�n�Ƃ���|�C���g��ς���
	if (m_diffToPoint < 20.0f)
	{
		//���ړI�n�Ƃ��Ă���|�C���g���z��̍Ō�̗v�f�Ȃ�
		//��ԍŏ��̃|�C���g��ړI�n�Ƃ���
		if (m_point->m_num == m_pointList.size()) {
			m_point = &m_pointList[0];
		}

		//�����łȂ��Ȃ�z��̎��̗v�f�̃|�C���g��ړI�n�Ƃ���
		else {
			m_point = &m_pointList[m_point->m_num];
		}
	}

	//�ړ�������B
	m_enemyMoveSpeed = m_enemyForward * 200.0f;
	m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());

	//�G�l�~�[�̑O�������g���āA��]�N�H�[�^�j�I�����v�Z����B
	m_enemyRotation.SetRotationY(atan2(m_enemyForward.x, m_enemyForward.z));
}

void Enemy_Near::PlayerSearch()
{
	//�G�l�~�[�̑O������toPlayerDir�Ƃ̓��ς��v�Z����
	float t = m_toPlayerDir.Dot(m_enemyForward);
	//���ς̌��ʂ�acos�֐��ɓn���āAm_enemyFowrad��toPlayerDir�̂Ȃ��p�x�����߂�B
	float angle = acos(t);

	//�G�l�~�[�̑O�������X�V����
	if (m_enemyDirState == 0)
	{
		//�_�b�V��������Ȃ��Ȃ�
		if (m_dashFlag != true)
		{
			m_enemyForward = m_toPlayerDir;					//�v���C���[����
			m_enemyMoveSpeed = m_enemyForward * 250.0f;		//�ړ����x��ݒ�
		}
	}
	else if (m_enemyDirState == 2)
	{
		m_enemyForward = Cross(m_Up, m_toPlayerDir);	//�O�ς���G�l�~�[�̉��������擾
		m_enemyMoveSpeed = m_enemyForward * 250.0f;		//�ړ����x�̐ݒ�
	}
	else if (m_enemyDirState == 3)
	{
		m_enemyForward = Cross(m_toPlayerDir, m_Up);	//�O�ς���G�l�~�[�̉��������擾
		m_enemyMoveSpeed = m_enemyForward * 250.0f;		//�ړ����x�̐ݒ�
	}
	else if (m_enemyDirState == 4)
	{
		//�U����
	}
	else if (m_enemyDirState == 5)	//�����œ����Ȃ�
	{	
		//���Ԍo��
		m_recoilCount--;			

		if (m_recoilCount <= 0)
		{
			//�v���C���[�̕�������悤�ɂȂ�(�ҋ@���)
			m_enemyForward = m_toPlayer;
		}

		if (m_recoilCount <= -180)
		{
			//�܂��퓬��ԂɂȂ�
			m_attackFlag = false;	
			m_targetFlag = false;
			m_enemyDirState = 0;
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
	if (m_enemyDirState == 0) //�v���C���[����
	{
		//�v���C���[�Ɍ������Ĉړ�����(�ʏ�X�s�[�h)
		if (m_distToPlayer >= 1500.0f && m_distToPlayer <= 4000.0f)
		{
			//�G�l�~�[�̈ړ�
			m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());
			//���ڂ���̔���
			if (m_sunaHassei >= 10)
			{
				Effect();
				m_sunaHassei = 0;
			}
			//�����Đ�
			if (m_asiotoSE->IsPlaying() != true)
			{
				m_asiotoSE->Play(true);
			}

		}
		//�v���C���[�Ɍ������Ĉړ�����(�_�b�V��)
		else if (m_distToPlayer < 1500.0f && m_attackFlag == false)
		{
			//�^�[�Q�b�g�̐ݒ�(1��̂�)
			if (m_targetFlag == false)
			{
				m_enemyTargetPos = m_player->player_position;	//�v���C���[���������܂ł����ꏊ
				m_targetFlag = true;
			}

			//�_�b�V����
			m_dashFlag = true;	
			
			//�G�l�~�[�̈ړ�
			m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());
			//���ڂ���̔���
			if (m_sunaHassei >= 10)
			{
				Effect();
				m_sunaHassei = 0;
			}
			//�����Đ�
			if (m_dashSE->IsPlaying() != true)
			{
				//�_�b�V���̌��ʉ��𗬂��ĕ��ʂ̑���������
				m_dashSE->Play(true);
				m_asiotoSE->Stop();
			}
		}	

		//�^�[�Q�b�g�����܂�����
		if (m_targetFlag == true)	
		{
			//�^�[�Q�b�g�܂ł̋����v�Z
			m_toTarget = m_enemyTargetPos - m_enemyPosition;
			m_distTarget = m_toTarget.Length();
			m_toTarget.Normalize();

			m_enemyForward = m_toTarget;					//�^�[�Q�b�g����
			m_enemyMoveSpeed = m_enemyForward * 700.0f;		//�ړ����x���v�Z(�_�b�V��)


			//�߂Â�����U��
			if (m_distTarget <= 150.0f)
			{
				m_fireFlag = true;
				m_enemyDirState = 4;
				//������~
				m_dashSE->Stop();
			}
		}
	}
	else if (m_enemyDirState == 2)	//������
	{
		//�ړ�������B
		m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());
		//���ڂ���̔���
		if (m_sunaHassei >= 10)
		{
			Effect();
			m_sunaHassei = 0;
		}
		//�����Đ�
		if (m_asiotoSE->IsPlaying() != true)
		{
			m_asiotoSE->Play(true);
		}


		//������x������X�g�b�v
		if (rand() % 200 == 1)
		{
			m_enemyDirState = 0;
			//������~
			m_asiotoSE->Stop();	
		}
	}
	else if (m_enemyDirState == 3)	//������
	{
		//�ړ�������B
		m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());
		//���ڂ���̔���
		if (m_sunaHassei >= 10)
		{
			Effect();
			m_sunaHassei = 0;
		}
		//�����Đ�
		if (m_asiotoSE->IsPlaying() != true)
		{
			m_asiotoSE->Play(true);
		}


		//������x������X�g�b�v
		if (rand() % 200 == 1)
		{
			m_enemyDirState = 0;
			//������~
			m_asiotoSE->Stop();	
		}
	}
	else if (m_enemyDirState == 4)
	{
		if (m_attackFlag == true)
		{
			m_dashFlag = false;
			m_enemyDirState = 5;	//�e���������甽���œ����Ȃ�
			return;
		}
	}
}

void Enemy_Near::Attack()
{
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
				Fire(4);	//����
				m_attackCount = 0;
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
	if (weaponNum == 4)
	{
		//�e�̐���
		Enemy_Bullet* m_enemyBullet;
		m_enemyBullet = NewGO<Enemy_Bullet>(1, "enemy_bullet");
		m_enemyBullet->m_enemyNearMama = this;
		m_enemyBullet->m_position = m_enemyPosition;						//�e�̈ʒu��ݒ�
		m_enemyBullet->m_bulletLocalPosition = { 0.0f,50.0f,100.0f };		//���[�J���|�W�V�����ݒ�
		m_enemyBullet->originRotation = m_enemyRotation;					//��]�̓G�l�~�[�Ɠ���

		//�������̐ݒ�ƍĐ�
		m_cannonSE = NewGO<SoundSource>(0);
		m_cannonSE->Init(enGigatonCannon);					//������
		m_cannonSE->SetVolume(2.0f);			//���ʒ���
		m_cannonSE->Play(false);

		m_attackFlag = true;		//�e���������t���O�𗧂Ă�
	}
}

void Enemy_Near::ItemDrop()
{
	//�̗͂�0�ɂȂ�����A�C�e���𗎂Ƃ�
	if (m_enemyHP <= 0.0f)
	{
		DeleteGO(this);
		m_dropItem = NewGO<Drop_item>(1, "drop_item");
		m_dropItem->Drop_position = m_enemyPosition;
		m_dropItem->Drop_position.y += 50.0f;
		//�G�l�~�[���ǂ̕���������Ă������擾���A�h���b�v����A�C�e�������߂�
		m_dropItem->drop_kinds = m_setWeapon;

		//�R���e�i�ɂ�������
		m_game->m_dropItemObject.push_back(m_dropItem);
		m_game->AddDefeatedEnemyNumber();//�|�������𑝂₷

		m_defeatState = true;
		//DeleteGO(this);
	}
}

void Enemy_Near::WeaponMove()
{
	//���킪�G�l�~�[�Ɠ�������������悤�ɂ���(�e�q�֌W)
	Quaternion originRotation = m_enemyRotation;			//��]�̓G�l�~�[�Ɠ���
	Vector3 localPosition = { 0.0f,40.0f,0.0f };			//�e���猩���ʒu�̒�`
	originRotation.Multiply(localPosition);					//��������̌v�Z
	//�ŏI�I�ȕ���̉�]������
	m_weaponRotation = originRotation;

	m_weaponPosition = m_enemyPosition;		//�܂�,����̈ʒu���G�l�~�[�Ɠ����ɐݒ肵
	m_weaponPosition += localPosition;		//����ɐe���猩���ʒu�𑫂��čŏI�I�ȕ���̈ʒu������
}

void Enemy_Near::Effect()
{
	//���ڂ���G�t�F�N�g�̏������ƍĐ�
	sunabokoriEffect = NewGO<EffectEmitter>(0);
	sunabokoriEffect->Init(enSunabokori);
	sunabokoriEffect->SetScale({ 4.0f,4.0f,4.0f });
	sunabokoriEffect->SetRotation(m_enemyRotation);
	sunabokoriEffect->SetPosition({ m_enemyPosition.x,m_enemyPosition.y + 10.0f ,m_enemyPosition.z });
	sunabokoriEffect->Play();
}

void Enemy_Near::SE()
{

}

void Enemy_Near::Render(RenderContext& rc)
{
	//���f���̕`��B
	m_enemyModel.Draw(rc);
	m_enemyWeaponModel.Draw(rc);
}