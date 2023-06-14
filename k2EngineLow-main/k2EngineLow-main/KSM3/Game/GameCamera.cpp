#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "Customize_UI_ver2.h"
#include "Game.h"

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	//�v���C���[�̃C���X�^���X��T���B
	m_player = FindGO<Player>("player");
	m_game = FindGO<Game>("game");

	//�΂˃J�����̏������B
	m_springCamera.Init(
		*g_camera3D,		//�΂˃J�����̏������s���J�������w�肷��B
		500.0f,			//�J�����̈ړ����x�̍ő�l�B
		true,				//�J�����ƒn�`�Ƃ̂����蔻�����邩�ǂ����̃t���O�Btrue���Ƃ����蔻����s���B
		5.0f				//�J�����ɐݒ肳��鋅�̃R���W�����̔��a�B��R������true�̎��ɗL���ɂȂ�B
	);

	//���ʉ��̐ݒ�
	m_walkSE = NewGO<SoundSource>(0);
	m_walkSE->Init(enRunning);	//������
	m_walkSE->SetVolume(0.5f * m_game->GetSEVol());	//���ʒ���


	//�����_���王�_�܂ł̃x�N�g����ݒ�B
	//�J�����X�e�[�g��4(�ŏ��̃��[�r�[)�̎��B
	if (CameraState == 4)
	{
		m_toCameraPos.Set(0.0f, 500.0f, -700.0f);
		//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ肷��B
		g_camera3D->SetNear(1.0f);
		g_camera3D->SetFar(80000.0f);

	}


	return true;
}

void GameCamera::Update()
{
	Vector3 toCameraPosOld = m_toCameraPos;

	//�J�X�^�}�C�Y��ʈȊO�Ńv���C���[������łȂ��Ȃ�p�b�h�̓��͂��g���ăJ�������񂷁B
	if (CameraState != 3 && CameraState != 4 && m_player->m_playerDead != true)
	{
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
		//�����_���v�Z����B
		target = m_player->player_position;
		target.y += 180.0f;		//�v���C���̑������炿����Ə�𒍎��_�Ƃ���B

		if (toPosDir.y < 0.1f)
		{
			//�J����������������B
			m_toCameraPos = toCameraPosOld;
		}
		else if (toPosDir.y > 0.8f) 
		{
			//�J�����������������B
			m_toCameraPos = toCameraPosOld;
		}

		//��ʗh��̏���
		//if (g_pad[0]->IsTrigger(enButtonY))VibFlag = true;

		if (VibFlag == true) 
		{
			static int Vibration = VIBRATION_MAX * 16;
			int vib = Vibration / 2;	//�U��
			Vibration -= 10;

			//�h��̑傫����0�ɂȂ�����
			if (vib == 0)
			{
				//�h��ׂ̈ɕK�v�ȕϐ���������
				VibFlag = false;
				BGX = 0; BGY = 0;
				Vibration = VIBRATION_MAX * 16;
			}
			else 
			{
				//���E�ɗh��邽�߂ɔ����̒l������
				int vibHalf = vib / 2;
				BGX = rand() % vib - vibHalf;
				BGY = rand() % vib - vibHalf;
			}
		}
		if (VibBigFlag == true)
		{
			static int Vibration = VIBRATION_BIG_MAX * 16;
			int vib = Vibration / 2;	//�U��
			Vibration -= 10;

			//�h��̑傫����0�ɂȂ�����
			if (vib == 0)
			{
				//�h��ׂ̈ɕK�v�ȕϐ���������
				VibBigFlag = false;
				BGX = 0; BGY = 0;
				Vibration = VIBRATION_BIG_MAX * 16;
			}
			else
			{
				//���E�ɗh��邽�߂ɔ����̒l������
				int vibHalf = vib / 2;
				BGX = rand() % vib - vibHalf;
				BGY = rand() % vib - vibHalf;
			}
		}
		if (VibFinalFlag == true)
		{
			static int Vibration = VIBRATION_FINAL_MAX * 16;
			int vib = Vibration / 2;	//�U��
			Vibration -= 40;

			//�h��̑傫����0�ɂȂ�����
			if (vib == 0)
			{
				//�h��ׂ̈ɕK�v�ȕϐ���������
				VibFinalFlag = false;
				BGX = 0; BGY = 0;
				Vibration = VIBRATION_FINAL_MAX * 16;
			}
			else
			{
				//���E�ɗh��邽�߂ɔ����̒l������
				int vibHalf = vib / 2;
				BGX = rand() % vib - vibHalf;
				BGY = rand() % vib - vibHalf;
			}
		}
	}
	else if (CameraState == 1)//�{�X��̎��̃J�����B
	{
		//�����_���v�Z����B
		target = m_player->player_position;
		target.y += 200.0f;		//�v���C���̑������炿����Ə�𒍎��_�Ƃ���B

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
		m_toCameraPos.Set(0.0f, 10.0f, -300.0f);
		target.y = 100.0f;

		m_toCameraPos = toCameraPosOld;
	}
	else if (CameraState == 3)
	{
		m_toCameraPos.Set(0.0f, 10.0f, -300.0f);
		target.y = 100.0f;
	}
	else if (CameraState == 4)
	{
		Move();
	}

	//�J�X�^����ʂƃ��U���g�ȊO�̎�
	if (CameraState != 3 && m_player->game_state != 2)
	{
		//�h��̑傫���𑫂�
		target.x += BGX;
		target.y += BGY;
	}


	//���_���v�Z����B
	pos = target + m_toCameraPos;
	

	//�΂˃J�����̐ݒ�
	m_springCamera.SetTarget(target);
	m_springCamera.SetPosition(pos);
	m_springCamera.Update();

	//�J�����̑O�����̐ݒ�(���Ƃ��̏�񂾂��ŗǂ�)
	m_cameraForward.x = target.x - pos.x;
	m_cameraForward.z = target.z - pos.z;
	m_cameraForward.Normalize();
}

void GameCamera::Move()
{
	//�����_���v�Z����B
	target = m_player->player_position;
	target.y += 180.0f;		//�v���C���̑������炿����Ə�𒍎��_�Ƃ���B

	if (opCount >= 0 && opCount <= 200)
	{
		//�v���C���[��O�֐i�߂�
		m_player->player_position.z += 5.0f;

		m_toCameraPos.Set(50.0f, 40.0f, 500.0f);
	}
	else if (opCount > 200 && opCount <= 280)
	{
		//�v���C���[��O�֐i�߂�
		m_player->player_position.z += 3.0f;

		//Y������̉�]
		Quaternion YRot;
		YRot.SetRotationDeg(Vector3::AxisY, 1.0f);
		YRot.Apply(m_toCameraPos);

		//X������̉�]
		Quaternion XRot;
		XRot.SetRotationDeg(Vector3::AxisX, -0.95f);
		XRot.Apply(m_toCameraPos);
	}
	else if (opCount > 280 && opCount <= 400)
	{
		//�Q�[�����̎��_�ɍ��킹��
		m_toCameraPos.Set(0.0f, 500.0f, -700.0f);
	}
	else if (opCount > 400)
	{
		m_springCamera.Init(
			*g_camera3D,		//�΂˃J�����̏������s���J�������w�肷��B
			50000.0f,			//�J�����̈ړ����x�̍ő�l�B
			true,				//�J�����ƒn�`�Ƃ̂����蔻�����邩�ǂ����̃t���O�Btrue���Ƃ����蔻����s���B
			5.0f				//�J�����ɐݒ肳��鋅�̃R���W�����̔��a�B��R������true�̎��ɗL���ɂȂ�B
		);

		//�L�����R�����v���C���[��������ʒu�Őݒ�
		m_player->characterController.SetPosition(m_player->player_position);
		m_game->SetUp();
		m_player->game_state = 0;
		CameraState = 0;
	}

	//�����Ă���Ԃ͑����Đ�
	if (m_walkSE->IsPlaying() != true && opCount < 280)
	{
		m_walkSE->Play(true);
	}
	else if (opCount >= 280)
	{
		m_walkSE->Stop();
	}

	//�����Ă����30�t���[�����Ƃɍ��ڂ���𔭐�������
	if (effectCount > 30 && opCount < 280)
	{
		//���ڂ���G�t�F�N�g�̏������ƍĐ�
		sunabokoriEffect = NewGO<EffectEmitter>(0);
		sunabokoriEffect->Init(enSunabokori);
		sunabokoriEffect->SetScale({ 4.0f,4.0f,4.0f });
		sunabokoriEffect->SetRotation(m_player->player_rotation);
		sunabokoriEffect->SetPosition(m_player->player_position);
		sunabokoriEffect->Play();

		effectCount = 0;	//�J�E���g���Z�b�g
	}

	effectCount++;
	opCount++;
}