#include "stdafx.h"
#include "Drop_item.h"
#include "Left_arm_weapons.h"
#include "Player.h"
#include "Customize_UI.h"
#include "Customize_UI_ver2.h"
#include "GameCamera.h"
#include "Game.h"

namespace
{
	//�A�C�e���̑傫��
	const float MACHINEGUN_DROP_SCALE = 2.5f;
	const float GIGATONCANNON_DROP_SCALE = 1.0f;
	const float BATTLESHIPGUN_DROP_SCALE = 2.5f;

	//�傫���Ȃ鑬��
	const float ADD_MACHINEGUN_SCALE = 0.05f;
	const float ADD_GIGATONCANNON_SCALE = 0.02f;
	const float ADD_BATTLESHIPGUN_SCALE = 0.05f;

	//��]��
	const float MODEL_ROT_AMOUNT = 2.0f;

	//���]����܂ł̎���
	const int REVERSAL_COUNT = 90;

	//�A�C�e�����E���鋗��
	const float CAN_GET_DISTANCE = 100.0f;
}

Drop_item::Drop_item() 
{
	
}

Drop_item::~Drop_item() 
{
	
}

bool Drop_item::Start()
{

	//�N���X��T��
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");
	m_gameCamera = FindGO<GameCamera>("gamecamera");
	m_customizeUI = FindGO<Customize_UI_ver2>("customize_ui_ver2");


	//�h���b�v�A�C�e���̏�����
	InitDropItem();


	return true;
}

void Drop_item::InitDropItem()
{

	//�������̊m��(make_unique�֐�������new���Ă���)
	m_dropItemModel = std::make_unique<ModelRender>();


	//���Ƃ�������ɂ���ď���������ύX����
	if (m_dropKinds == MACHINEGUN_NUM)
	{
		m_dropItemModel->Init("Assets/modelData/machine_gun_drop.tkm");
	}
	else if (m_dropKinds == GIGATONCANNON_NUM)
	{
		m_dropItemModel->Init("Assets/modelData/GIgaton_cannon.tkm");
	}
	else if (m_dropKinds == BATTLESHIPGUN_NUM)
	{
		m_dropItemModel->Init("Assets/modelData/battleship_gun_Drop.tkm");
	}
		
	m_dropItemModel->SetScale(m_modelSize);	
	m_dropItemModel->Update();
}

void Drop_item::Update()
{

	//���C���Q�[�����̂ݎ��s
	if (m_player->GetGameState() != MAIN_GAME_NUM)
	{
		return;
	}


	//�T�C�Y�̏���
	CalcModelScale();


	//�����̏���
	Float();


	//�A�C�e���̎擾����
	ExecuteGetItem();


	//���Ԃ��o�߂����
	if (m_deleteCount <= 0)
	{
		//�폜����
		ExecuteDelete();
	}


	//���Ԍo��
	m_deleteCount--;

}

void Drop_item::ExecuteGetItem()
{
	//�v���C���[�ƃA�C�e���̋������v�Z����
	Vector3 diff = m_player->GetPlayerPosition() - m_position;

	if (diff.Length() < CAN_GET_DISTANCE)
	{
		SoundSource* m_SE = NewGO<SoundSource>(0);			//���Đ�����ƏI���Ȃ̂ŃC���X�^���X��ێ������Ȃ��ׂɂ�����NewGO����
		m_SE->Init(enByuSE);								//������
		m_SE->SetVolume(1.0f * m_game->GetSEVol());			//���ʒ���
		m_SE->Play(false);


		//�E��������̎�ނ������Ă��
		m_customizeUI->SetDropItem(m_dropKinds);


		//�J�X�^����ʂ̃Z�b�g�A�b�v���s��
		m_customizeUI->SetUp();


		//�S�Ă̏�����
		m_customizeUI->TranceSetUp();


		//�v���C���[�̃X�e�[�g�ύX(�J�X�^����ʂ�)
		m_player->SetGameState(CUSTOMIZE_NUM);


		//�폜����
		ExecuteDelete();
	}
}

void Drop_item::CalcModelScale()
{	
	//���Ƃ�������ɂ���đ傫����ς���
	if (m_dropKinds == MACHINEGUN_NUM)		//�}�V���K��
	{
		//���񂾂�傫������
		m_modelSize += ADD_MACHINEGUN_SCALE;

		//������x�̑傫���ɂȂ�����X�g�b�v
		m_modelSize = min(m_modelSize, MACHINEGUN_DROP_SCALE);
		
	}
	else if (m_dropKinds == GIGATONCANNON_NUM)	//�M�K�g���L���m��
	{
		//���񂾂�傫������
		m_modelSize += ADD_GIGATONCANNON_SCALE;

		//������x�̑傫���ɂȂ�����X�g�b�v
		m_modelSize = min(m_modelSize, GIGATONCANNON_DROP_SCALE);
		
	}
	else if (m_dropKinds == BATTLESHIPGUN_NUM)	//��͖C
	{
		//���񂾂�傫������
		m_modelSize += ADD_BATTLESHIPGUN_SCALE;

		//������x�̑傫���ɂȂ�����X�g�b�v
		m_modelSize = min(m_modelSize, BATTLESHIPGUN_DROP_SCALE);
		
	}

	//�X�V
	m_dropItemModel->SetScale(m_modelSize);
	m_dropItemModel->Update();
}

void Drop_item::Float() 
{
	//���̃J�E���g���Ƃ�
	if (m_floatCount > REVERSAL_COUNT)
	{
		//�ړ������̔��]
		m_floatLevel *= -1;

		//�J�E���g���Z�b�g
		m_floatCount = 0;
	}

	//�ړ�
	m_position.y += m_floatLevel;

	//��]
	m_rotation.AddRotationDegY(MODEL_ROT_AMOUNT);

	//�X�V
	m_dropItemModel->SetPosition(m_position);
	m_dropItemModel->SetRotation(m_rotation);
	m_dropItemModel->Update();
	
	//�J�E���g�A�b�v
	m_floatCount++;
}

void Drop_item::ExecuteDelete()
{
	//�������g�̍폜
	DeleteGO(this);
	
	//���X�g�������
	m_game->RemoveDropItemFromList(this);	
}

void Drop_item::Render(RenderContext& rc) 
{
	//�`��
	m_dropItemModel->Draw(rc);
}