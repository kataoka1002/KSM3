#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "Customize_UI_ver2.h"
#include "Game.h"


namespace
{
	//�X�e�[�g�i���o�[
	const int CAMERA_STATE_ZAKO = 0;
	const int CAMERA_STATE_BOSS = 1;
	const int CAMERA_STATE_QTE = 2;
	const int CAMERA_STATE_CUSTOMIZE = 3;
	const int CAMERA_STATE_OP = 4;

	//stick�̓��͗ʂɂ������鐔
	const float MULTIPLYABLE_NUM = 1.3f;

	//�h��̌�����
	const int VIB_DECREASE_AMOUNT = 10;
	const int BIGVIB_DECREASE_AMOUNT = 10;
	const int FINALVIB_DECREASE_AMOUNT = 40;

	//�h��̍ő�l
	const float VIBRATION_MAX = 640.0f;
	const float VIBRATION_BIG_MAX = 2560.0f;
	const float VIBRATION_FINAL_MAX = 5120.0f;

	//���C���Q�[�����̃J�����|�W�V����
	const Vector3 MAIN_TO_CAMERA_POS = { 0.0f, 500.0f, -700.0f };
	const Vector3 CUSTOMIZE_TO_CAMERA_POS = { 0.0f, 10.0f, -300.0f };

}

GameCamera::GameCamera()
{

	//�΂˃J�����̏�����
	m_springCamera.Init(
		*g_camera3D,		//�΂˃J�����̏������s���J�������w�肷��B
		500.0f,				//�J�����̈ړ����x�̍ő�l�B
		true,				//�J�����ƒn�`�Ƃ̂����蔻�����邩�ǂ����̃t���O�Btrue���Ƃ����蔻����s���B
		5.0f				//�J�����ɐݒ肳��鋅�̃R���W�����̔��a�B��R������true�̎��ɗL���ɂȂ�B
	);


	//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ�
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(80000.0f);


	//�����_���王�_�Ɍ������x�N�g���̐ݒ�
	m_toCameraPos.Set(MAIN_TO_CAMERA_POS);

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{

	//�v���C���[��T��
	m_player = FindGO<Player>("player");


	//�Q�[����T��
	m_game = FindGO<Game>("game");


	//���ʉ��̐ݒ�
	m_walkSE = NewGO<SoundSource>(0);
	m_walkSE->Init(enRunning);						//������
	m_walkSE->SetVolume(0.5f * m_game->GetSEVol());	//���ʒ���


	return true;
}

void GameCamera::Update()
{
	//���E���~�܂��Ă���Ȃ�
	if (m_game->IsStopWorld() != false)
	{
		//���_���v�Z����B
		m_position = m_target + m_toCameraPos;

		//�΂˃J�����̐ݒ�
		m_springCamera.SetTarget(m_target);
		m_springCamera.SetPosition(m_position);
		m_springCamera.UpdateSpringCamera();
		m_springCamera.UpdateCamera();
		return;
	}

	//���O�̃J�����|�W�V������ۑ�
	Vector3 toCameraPosOld = m_toCameraPos;


	//�p�b�h�ɂ���]�ʂ̌v�Z
	CalcRotation();


	//�����_���王�_�܂ł̃x�N�g���𐳋K������
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	

	//�G����̎�
	if (m_cameraState == CAMERA_STATE_ZAKO)
	{

		//�����_��ݒ�
		m_target = m_player->GetPlayerPosition();


		//�v���C���̑������炿����Ə�𒍎��_�Ƃ���
		m_target.y += 180.0f;		


		//�J���������������
		if (toPosDir.y < 0.1f)
		{

			//���O�̃|�W�V�����ɖ߂�
			m_toCameraPos = toCameraPosOld;

		}
		//�J����������������
		else if (toPosDir.y > 0.8f) 
		{

			//���O�̃|�W�V�����ɖ߂�
			m_toCameraPos = toCameraPosOld;

		}


		//��ʗh��̏���
		ManageVibration();

	}
	//�{�X��̎�
	else if (m_cameraState == CAMERA_STATE_BOSS)
	{

		//�����_���v�Z����B
		m_target = m_player->GetPlayerPosition();
		

		//�v���C���̑������炿����Ə�𒍎��_�Ƃ���
		m_target.y += 200.0f;		


		//�J���������������
		if (toPosDir.y < -0.2f)
		{

			//���O�̃|�W�V�����ɖ߂�
			m_toCameraPos = toCameraPosOld;

		}
		//�J����������������
		else if (toPosDir.y > 0.7f)
		{

			//���O�̃|�W�V�����ɖ߂�
			m_toCameraPos = toCameraPosOld;

		}

	}
	else if (m_cameraState == CAMERA_STATE_QTE)
	{
		//QTE�p�ɂ�����
	}
	//�J�X�^�}�C�Y��ʂ̎�
	else if (m_cameraState == CAMERA_STATE_CUSTOMIZE)
	{

		//�|�W�V�����̐ݒ�
		m_toCameraPos.Set(CUSTOMIZE_TO_CAMERA_POS);


		//�v���C���̑������炿����Ə�𒍎��_�Ƃ���
		m_target.y = 100.0f;

	}
	else if (m_cameraState == CAMERA_STATE_OP)
	{
	
		//�I�[�v�j���O���̃J�����ړ�����
		OPMove();

	}


	//�J�X�^����ʂƃ��U���g�ȊO�̎�
	if (m_cameraState != CAMERA_STATE_CUSTOMIZE && m_player->GetGameState() != RESULT_NUM && m_cameraState != CAMERA_STATE_QTE)
	{
		//�h��̑傫���𑫂�
		m_target.x += BGX;
		m_target.y += BGY;
	}


	//���_���v�Z����B
	m_position = m_target + m_toCameraPos;
	

	//�΂˃J�����̐ݒ�
	m_springCamera.SetTarget(m_target);
	m_springCamera.SetPosition(m_position);
	m_springCamera.Update();


	//�J�����̑O�����̐ݒ�(���Ƃ��̏�񂾂��ŗǂ�)
	m_cameraForward.x = m_target.x - m_position.x;
	m_cameraForward.z = m_target.z - m_position.z;
	m_cameraForward.Normalize();

}

void GameCamera::CalcRotation()
{
	//���C���Q�[�����Ƀv���C���[������łȂ��Ȃ�
	if (m_cameraState != CAMERA_STATE_CUSTOMIZE && m_cameraState != CAMERA_STATE_OP && m_player->GetPlayerDead() != true && m_cameraState != CAMERA_STATE_QTE)
	{

		//�p�b�h�̓��͂��g���ăJ��������
		m_stickPowerX = g_pad[0]->GetRStickXF() * MULTIPLYABLE_NUM;
		m_stickPowerY = g_pad[0]->GetRStickYF() * MULTIPLYABLE_NUM;

	}
	else
	{
		//���͗ʂ�0�ɂ���
		m_stickPowerX = 0;
		m_stickPowerY = 0;
	}


	//Y������̉�]
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, m_stickPowerX);
	qRot.Apply(m_toCameraPos);


	//X������̉�]�B
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();

	qRot.SetRotationDeg(axisX, m_stickPowerY);
	qRot.Apply(m_toCameraPos);

}

void GameCamera::OPMove()
{

	//�����_���v�Z����B
	m_target = m_player->GetPlayerPosition();
	

	//�v���C���̑������炿����Ə�𒍎��_�Ƃ���
	m_target.y += 180.0f;		


	if (m_opCount >= 0 && m_opCount <= 200)
	{

		//�v���C���[��O�֐i�߂�
		m_player->AddPositionZ(5.0f);


		//�����_���王�_�܂ł̃x�N�g����ݒ�
		m_toCameraPos.Set(50.0f, 40.0f, 500.0f);

	}
	else if (m_opCount > 200 && m_opCount <= 280)
	{

		//�v���C���[��O�֐i�߂�
		m_player->AddPositionZ(3.0f);


		//Y������̉�]
		Quaternion YRot;
		YRot.SetRotationDeg(Vector3::AxisY, 1.0f);
		YRot.Apply(m_toCameraPos);


		//X������̉�]
		Quaternion XRot;
		XRot.SetRotationDeg(Vector3::AxisX, -0.95f);
		XRot.Apply(m_toCameraPos);

	}
	else if (m_opCount > 280 && m_opCount <= 400)
	{

		//�Q�[�����̎��_�ɍ��킹��
		m_toCameraPos.Set(MAIN_TO_CAMERA_POS);

	}
	else if (m_opCount > 400)
	{

		//�΂˃J�����̏�����
		m_springCamera.Init(
			*g_camera3D,		//�΂˃J�����̏������s���J�������w�肷��B
			50000.0f,			//�J�����̈ړ����x�̍ő�l�B
			true,				//�J�����ƒn�`�Ƃ̂����蔻�����邩�ǂ����̃t���O�Btrue���Ƃ����蔻����s���B
			5.0f				//�J�����ɐݒ肳��鋅�̃R���W�����̔��a�B��R������true�̎��ɗL���ɂȂ�B
		);


		//�L�����R�����v���C���[��������ʒu�Őݒ�
		m_player->SetCharacterControllerPosition(m_player->GetPlayerPosition());
		m_game->SetUp();
		m_player->SetGameState(0);
		m_cameraState = CAMERA_STATE_ZAKO;

	}


	//�����Ă����
	if (m_walkSE->IsPlaying() != true && m_opCount < 280)
	{
		
		//�����Đ�
		m_walkSE->Play(true);

	}
	//�������~�܂�����
	else if (m_opCount >= 280)
	{
		
		//������~
		m_walkSE->Stop();

	}


	//�����Ă���Ԃ�30�t���[���o������
	if (m_effectCount > 30 && m_opCount < 280)
	{

		//���ڂ���G�t�F�N�g�̏������ƍĐ�
		m_sunabokoriEffect = NewGO<EffectEmitter>(0);
		m_sunabokoriEffect->Init(enSunabokori);
		m_sunabokoriEffect->SetScale({ 4.0f,4.0f,4.0f });
		m_sunabokoriEffect->SetRotation(m_player->GetPlayerRotation());
		m_sunabokoriEffect->SetPosition(m_player->GetPlayerPosition());
		m_sunabokoriEffect->Play();

		
		//�J�E���g���Z�b�g
		m_effectCount = 0;

	}


	//�G�t�F�N�g�����Ԋu�̃J�E���g���A�b�v
	m_effectCount++;


	//OP���̃J��������J�E���g���A�b�v
	m_opCount++;

}

void GameCamera::ManageVibration()
{

	//�h��̃t���O����������
	if (m_vibFlag == true)
	{

		//�h��̍ő�l��ݒ�
		static int Vibration = VIBRATION_MAX;


		//�h��̏���
		PlayVibration(VIB_DECREASE_AMOUNT, VIBRATION_MAX, m_vibFlag, Vibration);

	}


	//�傫�ȗh��̃t���O����������
	if (m_bigVibFlag == true)
	{

		//�h��̍ő�l��ݒ�
		static int Vibration = VIBRATION_BIG_MAX;


		//�h��̏���
		PlayVibration(BIGVIB_DECREASE_AMOUNT, VIBRATION_BIG_MAX, m_bigVibFlag, Vibration);

	}


	//�Ō�̗h��̃t���O����������
	if (m_finalVibFlag == true)
	{

		//�h��̍ő�l��ݒ�
		static int Vibration = VIBRATION_FINAL_MAX;


		//�h��̏���
		PlayVibration(FINALVIB_DECREASE_AMOUNT, VIBRATION_FINAL_MAX, m_finalVibFlag, Vibration);

	}

}

void GameCamera::PlayVibration(int decline,int maxVib, bool& flag,int& vibration)
{

		//�U���̐ݒ�
		int vib = vibration / 2;	


		//�h������X�ɏ���������
		vibration -= decline;


		//�h��̑傫����0�ɂȂ�����
		if (vib == 0)
		{
			//�h��ׂ̈ɕK�v�ȕϐ���������
			flag = false;
			BGX = 0; BGY = 0;
			vibration = maxVib;
		}
		else
		{
			//���E�ɗh��邽�߂ɔ����̒l������
			int vibHalf = vib / 2;
			BGX = rand() % vib - vibHalf;
			BGY = rand() % vib - vibHalf;
		}

}

void GameCamera::SetQTE(Vector3 enemyPos)
{
	//�^�[�Q�b�g��G�Ɍ�����
	m_target = enemyPos;

	//�J�����܂ł̋����͔����ɂ���
	m_toCameraPos *= 0.5f;

	//�J�����X�e�[�g��QTE�p
	m_cameraState = CAMERA_STATE_QTE;

	//�����~�߂�
	m_game->StopWorld();

	//�{�^����������\��
	m_game->SetPushButton();
}

void GameCamera::SetOffQTE()
{
	//����i�߂�
	m_game->ReStartWorld();

	//�J�����̂܂ł̋��������ɖ߂�
	m_toCameraPos *= 2.0f;

	//�X�e�[�g���G����ɖ߂�
	m_cameraState = CAMERA_STATE_ZAKO;
}