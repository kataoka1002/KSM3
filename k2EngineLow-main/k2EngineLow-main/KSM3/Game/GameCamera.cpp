#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "Customize_UI_ver2.h"

GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{

	//�΂˃J�����̏������B
	m_springCamera.Init(
		*g_camera3D,		//�΂˃J�����̏������s���J�������w�肷��B
		1000.0f,			//�J�����̈ړ����x�̍ő�l�B
		true,				//�J�����ƒn�`�Ƃ̂����蔻�����邩�ǂ����̃t���O�Btrue���Ƃ����蔻����s���B
		5.0f				//�J�����ɐݒ肳��鋅�̃R���W�����̔��a�B��R������true�̎��ɗL���ɂȂ�B
	);

	//�����_���王�_�܂ł̃x�N�g����ݒ�B
	//�J�����X�e�[�g��0(�E�F�[�u��)�̎��B
	if (CameraState == 0)
	{
		m_toCameraPos.Set(0.0f, 500.0f, -700.0f);
		//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ肷��B
		g_camera3D->SetNear(1.0f);
		g_camera3D->SetFar(25000.0f);

	}
	//�J�����X�e�[�g��1(�{�X)�̎��B
	else if (CameraState == 1)
	{
		m_toCameraPos.Set(0.0f, 125.0f, -400.0f);
		//�ߕ���,�����ʒ������c�B
		g_camera3D->SetNear(1.0f);
		g_camera3D->SetFar(10000.0f);
	}
	//�J�����X�e�[�g��2(�^�C�g���ɂ��܂�)�̎��B
	else if (CameraState == 2)
	{
		m_toCameraPos.Set(0.0f, 500.0f, -700.0f);
		g_camera3D->SetNear(1.0f);
		g_camera3D->SetFar(1000.0f);
	}

	//�v���C���[�̃C���X�^���X��T���B
	m_player = FindGO<Player>("player");

	

	return true;
}
void GameCamera::Update()
{
	Vector3 toCameraPosOld = m_toCameraPos;
	//�J�������X�V�B
	if (CameraState == 3) 
	{
		m_toCameraPos.Set(0.0f, 10.0f, -300.0f);
		target.y = 100.0f;
		/*if (fast_count >= 2) {
			camera_customize_ui_ver2 = FindGO<Customize_UI_ver2>("customize_ui_ver2");
			target = camera_customize_ui_ver2->custom_model_body_position;
		}
		fast_count++;*/
	}
	else 
	{
		//�����_���v�Z����B
		target = m_player->player_position;
	}
	
	if (CameraState==0)
	{
		
		target.y += 80.0f;
	}

	if (CameraState==1)
	{
		//�v���C���̑������炿����Ə�𒍎��_�Ƃ���B
		target.y += 200.0f;
		

	}
	if (m_player->game_state == 3)
	{
		//m_toCameraPos.Set(0.0f, -50.0f, -300.0f);
		////�ߕ���,�����ʒ������c�B
		//g_camera3D->SetNear(1.0f);
		//g_camera3D->SetFar(10000.0f);
		//target.y -= 90.0f;
	}
	else {
		//�J�X�^�}�C�Y��ʈȊO�Ȃ�p�b�h�̓��͂��g���ăJ�������񂷁B
		x = g_pad[0]->GetRStickXF();
		y = g_pad[0]->GetRStickYF();
	}
	//Y������̉�]
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 1.3f * x);
	qRot.Apply(m_toCameraPos);
	//X������̉�]�B
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 1.3f * y);
	qRot.Apply(m_toCameraPos);
	//�J�����̉�]�̏�����`�F�b�N����B
	//�����_���王�_�܂ł̃x�N�g���𐳋K������B
	//���K������ƁA�x�N�g���̑傫�����P�ɂȂ�B
	//�傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ������ƁB
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	
	if (CameraState == 0)//�G����̎��J�����B
	{
		if (toPosDir.y < 0.3f)
		{
			//�J����������������B
			m_toCameraPos = toCameraPosOld;
		}
		else if (toPosDir.y > 0.8f) 
		{
			//�J�����������������B
			m_toCameraPos = toCameraPosOld;
		}
	}
	else if (CameraState == 1)//�{�X��̎��̃J�����B
	{
		if (toPosDir.y < -0.2f)
		{
			//������������Ȃ��悤�ɁB
			m_toCameraPos = toCameraPosOld;
		}
		else if (toPosDir.y > 0.7f)
		{
			//�������������Ȃ��悤�ɁB
			m_toCameraPos = toCameraPosOld;
		}
	}
	else if (CameraState == 2)
	{
		m_toCameraPos = toCameraPosOld;
	}


	//���_���v�Z����B
	Vector3 pos = target + m_toCameraPos;
	//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
	//g_camera3D->SetTarget(target);
	//g_camera3D->SetPosition(pos);

	//�J�����̍X�V�B
	//g_camera3D->Update();

	m_springCamera.SetTarget(target);
	m_springCamera.SetPosition(pos);
	m_springCamera.Update();
}