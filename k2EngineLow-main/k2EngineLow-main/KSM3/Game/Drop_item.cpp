#include "stdafx.h"
#include "Drop_item.h"
#include "Left_arm_weapons.h"
#include "Player.h"
#include "Customize_UI.h"
#include "Customize_UI_ver2.h"
#include "GameCamera.h"
#include <vector>       // �w�b�_�t�@�C���C���N���[�h
using namespace std;

Drop_item::Drop_item() 
{
	//drop_kinds = 2;

	//drop_weapons[1] = 1;

	//Drop_position = { 200.0f,50.0f,500.0f };

	
}

Drop_item::~Drop_item() 
{
	
}

bool Drop_item::Start()
{
	drop_player = FindGO<Player>("player");
	customize_UI_ver2 = FindGO<Customize_UI_ver2>("customize_ui_ver2");
	m_gameCamera = FindGO<GameCamera>("gamecamera");

	Set_Drop_item();

	return true;
}

void Drop_item::Set_Drop_item()
{
	//���Ƃ�������ɂ���ď���������ύX����
	if (drop_kinds == 2)
	{
		Drop_item_Render.Init("Assets/modelData/machine_gun_drop.tkm");
	}
	else if (drop_kinds == 6)
	{
		Drop_item_Render.Init("Assets/modelData/battleship_gun_Drop.tkm");
	}

	//Drop_item_Render.SetPosition(Drop_position);
}

void Drop_item::Update() 
{
	if (drop_player->game_state == 0) 
	{
		//�����̏���
		Float();

		//�擾����
		Vector3 diff = drop_player->player_position - Drop_position;
		
		if (diff.Length() < 100.0f) 
		{
			GetState = true;
			
			//�A�C�e�����E������J�X�^�}�C�Y��ʂɔ��
			//�J�X�^����ʂ̃Z�b�g�A�b�v���s��
			customize_UI_ver2->Setup();
			//�E��������̎�ނ������Ă��
			customize_UI_ver2->custom_kinds = drop_kinds;
			customize_UI_ver2->trance_setup();
			//�v���C���[�̃X�e�[�g�ύX(�J�X�^����ʂ�)
			drop_player->game_state = 3;
			
			DeleteGO(this);
		}
	}
}

void Drop_item::Float() 
{
	float_counter += 1;
	if (float_counter % 90 == 0) 
	{
		float_level*=-1;
	}
	Drop_position.y += float_level;
	Drop_rotation.AddRotationDegY(2.0f);
	//�A�C�e���̏�Ԃ��X�V
	Drop_item_Render.SetPosition(Drop_position);
	Drop_item_Render.SetRotation(Drop_rotation);
	Drop_item_Render.Update();
}

void Drop_item::Render(RenderContext& rc) 
{
	Drop_item_Render.Draw(rc);
}