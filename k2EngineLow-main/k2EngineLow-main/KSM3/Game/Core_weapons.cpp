#include "stdafx.h"
#include "Core_weapons.h"
#include "Player.h"
#include "Core_weapons_attack.h"

Core_weapons::Core_weapons() 
{
	
}

Core_weapons::~Core_weapons() 
{
	DeleteGO(m_coreWeaponAttack);
}

bool Core_weapons::Start()
{
	//�v���C���[��T��
	m_player = FindGO<Player>("player");

	//����̃Z�b�g
	WeaponSet();

	return true;
}

void Core_weapons::WeaponSet() 
{
	//����̎�ނɂ���ă��f����ς���
	if (m_setWeapon == 1) 
	{
		m_coreWeaponModel.Init("Assets/modelData/Giga_Plasma.tkm");
		m_coreWeaponModel.SetScale(m_scale);
	}
	else if (m_setWeapon == 2) 
	{
		m_coreWeaponModel.Init("Assets/modelData/Versatile_Perforator.tkm");
	}

	//�X�V
	m_coreWeaponModel.Update();
}

void Core_weapons::Update()
{

	//�ړ��̏���
	Move();


	//���C���Q�[�����Ȃ�
	if (m_player->GetGameState() == MAIN_GAME_NUM) 
	{
		
		//�e�̐���
		MakeBullet();


		//�Q�[�����I��������
		if (m_player->GetGameEndState() == 1) 
		{
			DeleteGO(this);
		}

	}

}

void Core_weapons::MakeBullet()
{
	//L1��������
	if (g_pad[0]->IsPress(enButtonLB1))
	{

		if (m_setWeapon == 1 && m_firingCount > 60)
		{

		}
		else if (m_setWeapon == 2 && m_firingCount > 5)
		{
			//�e�𐶐�
			m_coreWeaponAttack = NewGO<Core_weapons_attack>(1, "core_weapons_attack");
		}

		//�J�E���g�A�b�v
		m_firingCount++;
	}
	else
	{
		//�J�E���g���Z�b�g
		m_firingCount = 0;
	}
}

void Core_weapons::Move() 
{
	Quaternion originRotation = m_player->GetPlayerRotation();
	m_position = m_player->GetPlayerPosition();
	Vector3 lp = m_localPosition;
	originRotation.Multiply(lp);
	m_position += lp;
	m_rotation = originRotation;
	m_coreWeaponModel.SetPosition(m_position);
	m_coreWeaponModel.SetRotation(m_rotation);
	m_coreWeaponModel.Update();
}

void Core_weapons::Render(RenderContext& rc) 
{

	if (m_player->IsDeadBakuhaPlay() == true)
	{
		return;
	}

	m_coreWeaponModel.Draw(rc);
}