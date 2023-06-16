#include "stdafx.h"
#include "WeaponBase.h"
#include "Player.h"
#include "PlayerUI.h"
#include "Customize_UI_ver2.h"
#include "Battle_ship_attack.h"
#include "MachineGunAttack.h"
#include "GigatonCannonAttack.h"


bool WeaponBase::Start()
{

	//�v���C���[��������
	m_player = FindGO<Player>("player");


	//�v���C���[UI��������
	m_playerUI = FindGO<PlayerUI>("playerui");


	//�J�X�^�}�C�YUI��������
	m_customizeUI = FindGO<Customize_UI_ver2>("customize_ui_ver2");


	//�S�ʂ̃Z�b�g�A�b�v
	SetUp();

	return true;

}

void WeaponBase::SetWeapon(int customPoint)
{

	//�t���Ă��镐��ɂ���ď�����ύX����
	switch (customPoint)
	{
	case 2:	//�}�V���K���̎�


		//�傫���̐ݒ�
		m_weaponModel.SetScale(MACHINEGUN_SCALE);


		//����̗̑͂̐ݒ�
		m_HPMax = MACHINEGUN_HP_MAX;

		break;


	case 4:	//�M�K�g���L���m���̎�


		//�傫���̐ݒ�
		m_weaponModel.SetScale(GIGATON_SCALE);


		//����̗̑͂̐ݒ�
		m_HPMax = GIGATON_HP_MAX;

		break;


	case 6:	//��͖C�̎�


		//�傫���̐ݒ�
		m_weaponModel.SetScale(BATTLESHIP_SCALE);


		//����̗̑͂̐ݒ�
		m_HPMax = BATTLESHIP_HP_MAX;

		break;


	default:

		break;

	}


	//���f���̍X�V
	m_weaponModel.Update();


	//����̎�ނ��o��������
	m_setWeapon = customPoint;


	//����̗̑͂��o��������
	m_HP = m_HPMax;

}

void WeaponBase::Move()
{

	//���[�J���|�W�V������������
	Vector3 lp = m_localPosition;


	//�v���C���[�̉�]�ʂ�������
	Quaternion originRotation = m_player->player_rotation;


	//�v���C���[�̃|�W�V������������
	m_position = m_player->player_position;


	//��Z
	originRotation.Multiply(lp);


	//�|�W�V�����Ƀ��[�J���|�W�V�����𑫂�
	m_position += lp;


	//�ŏI�I�ȉ�]�ʂ�������
	m_rotation = originRotation;


	//�X�V
	m_weaponModel.SetPosition(m_position);
	m_weaponModel.SetRotation(m_rotation);
	m_weaponModel.Update();

}

void WeaponBase::MakeBullet(int customPoint)
{
	
	//L1�{�^���������ꂽ��
	if (g_pad[0]->IsPress(enButtonLB1))
	{

		//���킪�}�V���K���̏ꍇ
		if (customPoint == 2 && m_firingCount % 5 == 0)
		{

			//�e�Ƀ|�W�V�����Ɖ�]�������Đ�������
			m_machineGunAttack = NewGO<MachineGunAttack>(1, "machinegunattack");
			m_machineGunAttack->SetRotation(m_rotation);
			m_machineGunAttack->SetPosition(m_position);

		}
		//���킪�M�K�g���L���m���̏ꍇ
		else if (customPoint == 4 && m_firingCount % 180 == 0)
		{

			//�e�Ƀ|�W�V�����Ɖ�]�������Đ�������
			m_gigatonAttack = NewGO<GigatonCannonAttack>(1, "gigatoncannonattack");
			m_gigatonAttack->SetRotation(m_rotation);
			m_gigatonAttack->SetPosition(m_position);

		}
		//���킪��͖C�̏ꍇ
		else if (customPoint == 6 && m_firingCount % 180 == 0)
		{

			//�e�Ƀ|�W�V�����Ɖ�]�������Đ�������
			m_battleShipAttack = NewGO<Battle_ship_attack>(1, "battle_ship_attack");
			m_battleShipAttack->SetRotation(m_rotation);
			m_battleShipAttack->SetPosition(m_position);

		}


		//�e�̃��[�J���|�W�V�����̐ݒ�
		SetBulletLocalPosition();


		//�J�E���g�A�b�v
		m_firingCount++;

	}
	//L1�{�^����������ĂȂ��Ƃ�
	else
	{

		//�J�E���g���Z�b�g
		m_firingCount = 0;

	}

}
