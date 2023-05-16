#include "stdafx.h"
#include "Drop_item.h"
#include "Left_arm_weapons.h"
#include "Player.h"
#include "Customize_UI.h"
#include "Customize_UI_ver2.h"
#include "GameCamera.h"
#include "Game.h"
#include <vector>       // �w�b�_�t�@�C���C���N���[�h
using namespace std;

Drop_item::Drop_item() 
{
	
}

Drop_item::~Drop_item() 
{
	
}

bool Drop_item::Start()
{
	drop_player = FindGO<Player>("player");
	customize_UI_ver2 = FindGO<Customize_UI_ver2>("customize_ui_ver2");
	m_gameCamera = FindGO<GameCamera>("gamecamera");
	m_game = FindGO<Game>("game");

	Set_Drop_item();

	return true;
}

void Drop_item::Set_Drop_item()
{
	//���Ƃ�������ɂ���ď���������ύX����
	if (drop_kinds == 2)
	{
		Drop_item_Render.Init("Assets/modelData/machine_gun_drop.tkm");
		Drop_item_Render.SetScale(modelSize);	//�ŏ��͏����߂ɐݒ�
	}
	else if (drop_kinds == 4)
	{
		Drop_item_Render.Init("Assets/modelData/GIgaton_cannon.tkm");
		Drop_item_Render.SetScale(modelSize);	//�ŏ��͏����߂ɐݒ�
	}
	else if (drop_kinds == 6)
	{
		Drop_item_Render.Init("Assets/modelData/battleship_gun_Drop.tkm");
		Drop_item_Render.SetScale(modelSize);	//�ŏ��͏����߂ɐݒ�
	}
}

void Drop_item::Update() 
{
	if (drop_player->game_state == 0) 
	{
		//�T�C�Y�̏���
		SetSize();

		//�����̏���
		Float();

		//�擾����
		Vector3 diff = drop_player->player_position - Drop_position;
		
		if (diff.Length() < 100.0f) 
		{
			SoundSource* m_SE = NewGO<SoundSource>(0);			//���Đ�����ƏI���Ȃ̂ŃC���X�^���X��ێ������Ȃ��ׂɂ�����NewGO����
			m_SE->Init(enByuSE);								//������
			m_SE->SetVolume(1.0f * m_game->SEvol);				//���ʒ���
			m_SE->Play(false);

			GetState = true;
			
			//�A�C�e�����E������J�X�^�}�C�Y��ʂɔ��
			//�E��������̎�ނ������Ă��
			customize_UI_ver2->custom_kinds = drop_kinds;
			//�J�X�^����ʂ̃Z�b�g�A�b�v���s��
			customize_UI_ver2->Setup();
			
			//�S�Ă̏�����
			customize_UI_ver2->trance_setup();
			//�v���C���[�̃X�e�[�g�ύX(�J�X�^����ʂ�)
			drop_player->game_state = 3;
			
			DeleteGO(this);
		}

		if (m_deleteCount <= 0)
		{
			DeleteGO(this);
		}
		m_deleteCount--;
	}
}

void Drop_item::SetSize()
{	
	//���Ƃ�������ɂ���đ傫����ς���
	if (drop_kinds == 2)		//�}�V���K��
	{
		//���񂾂�傫������
		modelSize += 0.05;

		//������x�̑傫���ɂȂ�����X�g�b�v
		if (modelSize >= 2.5f)
		{
			modelSize = 2.5f;
		}
	}
	else if (drop_kinds == 4)	//�M�K�g���L���m��
	{
		//���񂾂�傫������
		modelSize += 0.02;

		//������x�̑傫���ɂȂ�����X�g�b�v
		if (modelSize >= 1.0f)
		{
			modelSize = 1.0f;
		}
	}
	else if (drop_kinds == 6)	//��͖C
	{
		//���񂾂�傫������
		modelSize += 0.05;
		//������x�̑傫���ɂȂ�����X�g�b�v
		if (modelSize >= 2.5f)
		{
			modelSize = 2.5f;
		}
	}

	//�X�V
	Drop_item_Render.SetScale(modelSize);
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