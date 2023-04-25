#include "stdafx.h"
#include "Enemy_Far.h"
#include "Player.h"
#include "Game.h"
#include <time.h>
#include <stdlib.h>
#include "Battle_ship_attack.h"
#include "Drop_item.h"


Enemy_Far::Enemy_Far()
{
	m_pointList.push_back({ Vector3(0.0f,0.0f,0.0f),1 });		//��Ԗڂ̃|�C���g
	m_pointList.push_back({ Vector3(0.0f,0.0f,100.0f),2 });		//��Ԗڂ̃|�C���g
	m_pointList.push_back({ Vector3(100.0f,0.0f,200.0f),3 });	//�O�Ԗڂ̃|�C���g
	m_pointList.push_back({ Vector3(-100.0f,0.0f,200.0f),4 });	//�l�Ԗڂ̃|�C���g
	m_point = &m_pointList[0];									//��Ԗڂ̃|�C���g������
}

Enemy_Far::~Enemy_Far()
{
	m_player->enemy_survival = false;	//�G�l�~�[�������Ă��邩���v���[���[�ɋ�����
	//�G�l�~�[���ǂ̕���������Ă������擾���A�h���b�v����A�C�e�������߂�
	if (m_defeatState == true) {
		m_dropItem->drop_kinds = m_setWeapon;
	}
}

bool Enemy_Far::Start()
{
	m_player = FindGO<Player>("player");

	//�G�l�~�[�̐ݒ�
	m_enemyModel.Init("Assets/modelData/Enemy_model_type2.tkm");
	m_enemyModel.SetScale(2.0f);
	m_enemyModel.SetRotation(m_enemyRotation);
	m_enemyModel.SetPosition(m_enemyPosition);
	//�L�����N�^�[�R���g���[���[���������B
	m_enemyCharacterController.Init(
		50.0f,			//���a�B
		40.0f,			//�����B
		m_enemyPosition	//���W�B
	);

	SetUp();	//���퐶��

	return true;
}

void Enemy_Far::SetUp()
{
	//�G�̕���̎�ނ̊m��
	m_setWeapon = 1;//�����͂������񉼂Œ萔�ݒ肵�Ă邾���Ō�X�����_���ɂ��Ă����\��
	//set_weapons = rand() % 2 + 1;
	if (m_setWeapon == 1) {	//�~�T�C��
		m_enemyWeaponModel.Init("Assets/modelData/battleship_gun_enemy.tkm");
		m_enemyWeaponModel.SetScale(2.0f);
		m_enemyWeaponModel.SetPosition(m_weaponPosition);
		m_enemyWeaponModel.SetRotation(m_weaponRotation);
		m_enemyWeaponModel.Update();
	}
	else if (m_setWeapon == 2) { //��͖C
		m_enemyWeaponModel.Init("Assets/modelData/machine_gun_enemy.tkm");
		m_enemyWeaponModel.SetScale(2.0f);
		m_enemyWeaponModel.SetPosition(m_weaponPosition);
		m_enemyWeaponModel.SetRotation(m_weaponRotation);
		m_enemyWeaponModel.Update();
	}
}

void Enemy_Far::Update()
{
	if (m_player->game_state == 0)
	{
		//�G�l�~�[����v���C���[�ւ̃x�N�g��
		m_toPlayer = m_player->player_position - m_enemyPosition;
		//�v���C���[�Ƃ̋������v�Z����
		m_distToPlayer = m_toPlayer.Length();
		//�v���C���[�Ɍ������ĐL�т�x�N�g���𐳋K������
		m_toPlayerDir = m_toPlayer;
		m_toPlayerDir.Normalize();


		if (m_distToPlayer > 5000.0f)
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

void Enemy_Far::PassMove()
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

void Enemy_Far::PlayerSearch()
{
	//�G�l�~�[�̑O������toPlayerDir�Ƃ̓��ς��v�Z����
	float t = m_toPlayerDir.Dot(m_enemyForward);
	//���ς̌��ʂ�acos�֐��ɓn���āAm_enemyFowrad��toPlayerDir�̂Ȃ��p�x�����߂�B
	float angle = acos(t);

	//�G�l�~�[�̎���Ƀv���C���[�������Ă���&������1500�ȉ��ɂȂ�&�v���C���[�̕����������Ă���
	if (fabsf(angle) < Math::DegToRad(45.0f) && m_distToPlayer <= 1500.0f && m_enemyDirState == 0) {
		m_atackOK = true;
	}
	else {
		m_atackOK = false;
	}


	//�G�l�~�[�̑O�������X�V����
	if (m_enemyDirState == 0)
	{
		m_enemyForward = m_toPlayerDir;					//�v���C���[����
		m_enemyMoveSpeed = m_enemyForward * 250.0f;		//�ړ����x��ݒ�
	}
	else if (m_enemyDirState == 1)
	{
		m_enemyForward = m_toPlayerDir * -1.0;			//�v���C���[�Ɣ��Ό���
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

	//��ނ��ĂȂ��Ȃ��]����
	if (m_enemyEscape != true)
	{
		//�G�l�~�[�̑O�������g���āA��]�N�H�[�^�j�I�����v�Z����B
		m_enemyRotation.SetRotationY(atan2(m_enemyForward.x, m_enemyForward.z));
	}
}

void Enemy_Far::Move()
{
	if (m_enemyDirState == 0) //�v���C���[����
	{
		//�����𖞂����Ă���Ԃ����v���C���[�Ɍ������Ĉړ�����
		if (m_distToPlayer >= 3000.0f && m_distToPlayer <= 5000.0f)
		{
			//�G�l�~�[�̈ړ�
			m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());
		}

		//�G�l�~�[�ƃv���C���[�̋������߂����A���m���Ō�ނ���
		if (m_distToPlayer <= 1500.0f && rand() % 150 == 1)
		{
			m_enemyDirState = 1;
			m_enemyMoveSpeed = m_enemyForward * -250.0f;	//�ړ����x�̐ݒ�()
			m_enemyEscape = true;
		}
		//�G�l�~�[�ƃv���C���[�̋������߂����A���m���ŉ��ړ�����
		else if (m_distToPlayer < 2800.0f && rand() % 900 == 1)
		{
			m_enemyDirState = 2;
		}
		//�G�l�~�[�ƃv���C���[�̋������߂����A���m���ŉ��ړ�����
		else if (m_distToPlayer < 2800.0f && rand() % 900 == 1)
		{
			m_enemyDirState = 3;
		}
	}
	else if (m_enemyDirState == 1)	//������
	{
		//�ړ�������B
		m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());
		//��苗���ȏ�ɂȂ�ƌ�ރX�g�b�v
		if (m_distToPlayer > 2800.0f || rand() % 400 == 1)
		{
			m_enemyEscape = false;
			m_enemyDirState = 0;
		}
	}
	else if (m_enemyDirState == 2)	//������
	{
		//�ړ�������B
		m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());
		//������x������X�g�b�v
		if (rand() % 200 == 1)
		{
			m_enemyDirState = 0;
		}
	}
	else if (m_enemyDirState == 3)	//������
	{
		//�ړ�������B
		m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());
		//������x������X�g�b�v
		if (rand() % 200 == 1)
		{
			m_enemyDirState = 0;
		}
	}
}

void Enemy_Far::Attack()
{
	if (m_atackOK == true)
	{
		//�U���^�C�~���O�̌v�Z
		m_attackCount++;

		//����ɂ���Ă̕���
		switch (m_setWeapon)
		{
		case 1://�~�T�C��
			if (m_attackCount % 180 == 0)
			{
				Fire();	//����
				m_attackCount = 0;
			}
			break;
		case 2://��͖C
			if (m_attackCount % 60 == 0)
			{
				Fire();	//����
				m_attackCount = 0;
			}
			break;
		default:
			break;
		}
	}
}

void Enemy_Far::Fire()
{
	////�e�̐���
	//m_enemyAttack = NewGO<Enemy_Bullet>(1, "enemy_attack");
	//m_enemyAttack->firing_position = m_position;	//�e�̈ʒu��ݒ�
	//m_enemyAttack->e_a_Bullet_Fowrad = m_enemy->m_enemyForward;	//�e�̑O�����̐ݒ�
	//m_atackState = true;

	////���킪��͖C�Ȃ�
	//if (weponNom == 1)
	//{
	//	m_enemyAttack->e_a_aiming = m_enemy->m_enemyRotation;
	//}
}

void Enemy_Far::ItemDrop()
{
	//�̗͂�0�ɂȂ�����A�C�e���𗎂Ƃ�
	if (m_enemyHP <= 0.0f)
	{
		m_dropItem = NewGO<Drop_item>(1, "drop_item");
		m_dropItem->Drop_position = m_enemyPosition;
		m_dropItem->Drop_position.y += 50.0f;
		m_defeatState = true;
		DeleteGO(this);
	}
}

void Enemy_Far::WeaponMove()
{
	//���킪�G�l�~�[�Ɠ�������������悤�ɂ���(�e�q�֌W)
	Quaternion originRotation = m_enemyRotation;			//��]�̓G�l�~�[�Ɠ���
	Vector3 localPosition = { 0.0f,40.0f,40.0f };			//�e���猩���ʒu�̒�`
	originRotation.Multiply(localPosition);					//��������̌v�Z
	//�ŏI�I�ȕ���̉�]������
	m_weaponRotation = originRotation;

	m_weaponPosition = m_enemyPosition;		//�܂�,����̈ʒu���G�l�~�[�Ɠ����ɐݒ肵
	m_weaponPosition += localPosition;		//����ɐe���猩���ʒu�𑫂��čŏI�I�ȕ���̈ʒu������
}

void Enemy_Far::Render(RenderContext& rc)
{
	//���f���̕`��B
	m_enemyModel.Draw(rc);
	m_enemyWeaponModel.Draw(rc);
}
