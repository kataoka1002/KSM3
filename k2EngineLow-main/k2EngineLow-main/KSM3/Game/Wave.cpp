#include "stdafx.h"
#include "Wave.h"
#include "Game.h"
#include "Player.h"
#include "Boss.h"
#include "GuideLight.h"
#include "Wave3Clear.h"

namespace
{
	//�P�E�F�[�u�̃^�C�����~�b�g
	const float		TIME_LIMIT = 180.0f;						
	
	//�E�F�[�u�ύX�X�v���C�g�̏����ꏊ
	const Vector3	SPRITE_POSITION = { 1000.0f,0.0f,0.0f };	

	//�{�X��ɍs���̂ɕK�v�ȎE������
	const int REQUIRED_ENEMY_COUNT_FOR_BOSS = 30;

	//�K�C�h�̃^�[�Q�b�g�|�W�V����
	const Vector3 GUIDE_TARGET_POS = { 0.0f,0.0f,10000.0f };

	//�K�C�h�̑���
	const float GUIDE_VELOCITY = 8.0f;

	//�K�C�h����������Ԋu
	const int GUIDE_INTERVAL = 30;

	//���[�h��ʂ̃��l�̕ω���
	const float LOADING_SPRITE_DELTA_A = 0.1f;

	//�E�F�[�u�X�^�[�g�̖ړI�ʒu
	const Vector3 WAVE_START_SPRITE_TARGET = Vector3::Zero;

	//�^�C�}�[�n�̒l
	const Vector4 TIMER_FONT_COLOR = { 1.0f,1.0f,1.0f,1.0f };
	const float TIMER_FONT_SCALE = 0.7f;
	const Vector4 TIMER_FONT_SHADOW_COLOR = { 0.0f,0.0f,0.0f,1.0f };
	const Vector3 TIMER_FONT_POSITION = { -880.0f, 440.0f, 0.0f };

}

Wave::Wave()
{

	//�ŏ��̓E�F�[�u1�̃X�v���C�g�ŏ�����
	m_waveStartSprite.Init("Assets/sprite/wave/wave1.DDS", 1920.0f, 1080.0f);
	m_waveStartSprite.SetPosition(SPRITE_POSITION);
	m_waveStartSprite.Update();


	//�E�F�[�u�̘g
	m_waveStartWakuSprite.Init("Assets/sprite/wave/waveWaku.DDS", 1920.0f, 1080.0f);
	m_waveStartWakuSprite.SetPosition({ 0.0f,0.0f,0.0f });
	m_waveStartWakuSprite.SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
	m_waveStartWakuSprite.Update();


	//�E�F�[�u�̎c�莞��
	m_waveGageNakami.Init("Assets/sprite/wave/waveGageNakami3.dds", 570.0f, 27.0f);
	m_waveGageNakami.SetPosition({ -730.0f,395.0f,0.0f });
	m_waveGageNakami.SetPivot({ 0.0f,0.5f });
	m_waveGageNakami.Update();


	//�E�F�[�u�̎c�莞�Ԃ̘g
	m_waveGageWaku.Init("Assets/sprite/wave/waveGageWaku.dds", 600.0f, 42.0f);
	m_waveGageWaku.SetPosition({ -735.0f,395.0f,0.0f });
	m_waveGageWaku.SetPivot({ 0.0f,0.5f });
	m_waveGageWaku.Update();


	//�^�C�}�[
	m_TimerSprite.Init("Assets/sprite/wave/Timer2.dds", 1920.0f, 1080.0f);
	m_TimerSprite.SetPosition({ -760.0f,395.0f,0.0f });
	m_TimerSprite.SetScale({ 0.05f,0.05f,0.05f });
	m_TimerSprite.Update();


	//�~�b�V����
	m_missionSprite.Init("Assets/sprite/wave/mission.dds", 1920.0f, 1080.0f);
	m_missionSprite.SetPosition({ 600.0f,200.0f,0.0f });
	m_missionSprite.Update();
	

	//Boss�ւ̑J�ڂ�Loading��ʂ̓ǂݍ���
	m_loadingSprite.Init("Assets/sprite/NOW_LOADING.DDS", 1632.0f, 918.0f);
	m_loadingSprite.SetMulColor(Loading_color);
	m_loadingSprite.Update();

}

Wave::~Wave()
{

}

bool Wave::Start()
{

	//��������
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");
	

	//�^�C�����~�b�g�������Ă��
	m_timer = TIME_LIMIT;		

	
	//�X�v���C�g�̏ꏊ�̏���
	m_spritePos = SPRITE_POSITION;	


	return true;
}

void Wave::Update()
{
	if (g_pad[0]->IsPress(enButtonB))
	{
		MakeGuide();
	}


	//�|�[�Y��ʒ��Ȃ�
	if (m_player->GetGameState() == PAUSE_NUM)
	{
		return;
	}


	//�X�^�[�g��
	if (m_waveNum == 0)
	{

		//���o���t���O�𗧂Ă�
		m_ensyutuNow = true;


		//���o���o��
		SpritePlay();


		return;

	}


	//�{�X��̏���
	ExecuteBossBattle();
	

	//�Q�[�����̂ݎ��Ԍo��
	if (m_player->GetGameState() == MAIN_GAME_NUM)
	{

		//�E�F�[�u�̊Ǘ�
		HandleWaveLogic();


		//�E�F�[�u�ύX���o��
		if (m_ensyutuNow == true)
		{

			//���o���o��
			SpritePlay();

		}


		//�E�F�[�u�J�n���o���I���
		if (m_waveNum == 1 && m_playerUISet == false)
		{

			//UI�𐶐�����
			m_game->MakePlayerUI();


			//UI�̃Z�b�g���I������t���O�𗧂Ă�
			m_playerUISet = true;

		}


		//�c�莞�Ԃ̌v��
		TimeCount();


		//�^�C�}�[�̉�]
		TimerRotation();


		//�T�C�Y������������
		GageSetScale();

	}
	else if (m_player->GetGameState() == PAUSE_NUM)
	{

	}
	else if (m_player->GetGameState() == RESULT_NUM)
	{

	}
	else if (m_player->GetGameState() == CUSTOMIZE_NUM)
	{

	}
	else if (m_player->GetGameState() == OP_NUM)
	{

	}
}

void Wave::HandleWaveLogic()
{

	//�ŏI�E�F�[�u����Ȃ��Ƃ�
	if (m_waveNum != 3)
	{

		//�v���C���[���G�l�~�[��|�����A�E�F�[�u�^�C�}�[��0�ɂȂ�ƒǉ��ŃG�l�~�[����
		if (m_timer <= 0.0f || m_game->GetDefeatedEnemyNum() == m_game->GetEnemyNum())
		{

			//���o�J�n
			m_ensyutuNow = true;

		}

	}
	else if (m_waveNum == 3)
	{

		//�G�l�~�[��|�����A�E�F�[�u�^�C�}�[��0�ɂȂ��
		if (m_timer <= 0.0f || m_player->GetKillEnemyAmount() == REQUIRED_ENEMY_COUNT_FOR_BOSS)
		{

			//�{�X��֍s����悤�ɂȂ�
			m_goBoss = true;


			//�{�X�킶��Ȃ��Ȃ�
			if (m_player->GetBossState() != 1)	
			{

				//�K�C�h�̐���
				MakeGuide();

			}


			//�~�b�V�����X�v���C�g���ύX����ĂȂ��Ȃ�
			if (m_spriteChangeFlag == false)
			{

				//�~�b�V�����P�N���A�̃X�v���C�g�ɕύX����
				m_missionSprite.Init("Assets/sprite/wave/mission1clear.dds", 1920.0f, 1080.0f);
				m_missionSprite.Update();


				//�E���������R�O�̂Ȃ�r�ŉ��o
				if (m_player->GetKillEnemyAmount() == REQUIRED_ENEMY_COUNT_FOR_BOSS)
				{

					//�E�F�[�u3�N���A�̉��o
					m_waveClear = NewGO<Wave3Clear>(3, "wave3clear");

				}


				//�~�b�V�����X�v���C�g��ύX�����t���O�𗧂Ă�
				m_spriteChangeFlag = true;

			}

		}

	}

}

void Wave::MakeGuide()
{

	//30�t���[�����ɃK�C�h�̌�������
	if (m_guideCount > GUIDE_INTERVAL)
	{
		
		//�K�C�h�̐���
		m_guide = NewGO<GuideLight>(1, "guidelight");		
		

		//��яo�������������_���Ō��߂�
		Quaternion rotation;
		rotation.SetRotationDeg(Vector3{ 0.0f,0.0f,1.0f }, rand() % 180);	


		//�E�����̐ݒ�
		Vector3 m_right = Vector3::AxisX;


		//�N�H�[�^�j�I���ɂ���]���K�p���ꂽ�V�����x�N�g����������
		rotation.Apply(m_right);

		
		//����
		m_guide->SetVelocity(m_right * GUIDE_VELOCITY);
		

		//�^�[�Q�b�g�̐ݒ�
		m_guide->SetTargetPosition(GUIDE_TARGET_POS);
		

		//�����ʒu�̐ݒ�
		m_guide->SetPosition(m_player->GetPlayerPosition());


		//�J�E���g���Z�b�g
		m_guideCount = 0;

	}

	//�J�E���g�A�b�v
	m_guideCount++;

}

void Wave::TimeCount()
{

	//���Ԍo��
	m_timer -= g_gameTime->GetFrameDeltaTime();
	max(0.0f, m_timer);

	//�c�莞�Ԃ̕\��
	wchar_t text[256];
	int minute = (int)m_timer / 60;
	int sec = (int)m_timer % 60;
	swprintf_s(text, 256, L"�E�F�[�u%d /3                  %02d  :%02d",m_waveNum, minute, sec);
	m_timerFont.SetText(text);
	m_timerFont.SetPosition(TIMER_FONT_POSITION);
	m_timerFont.SetShadowParam(true, 1.0f, TIMER_FONT_SHADOW_COLOR);
	m_timerFont.SetScale(TIMER_FONT_SCALE);
	m_timerFont.SetColor(TIMER_FONT_COLOR);

}

void Wave::SpritePlay()
{
	if (m_ensyutuCount >= 0 && m_ensyutuCount < 60)
	{

		//�^�[�Q�b�g���Z�b�g
		Vector3 m_targetPos = WAVE_START_SPRITE_TARGET;


		//�^�[�Q�b�g�Ǝ����̏ꏊ�̍������������𑬓x�ɂ���
		m_moveSpeed.x = (m_targetPos.x - m_spritePos.x) / 5.0f;
		m_spritePos.x += m_moveSpeed.x;


		//�g���J�E���g�ɍ��킹�Ă��񂾂�o�������Ă���
		m_wakuA += 1.0f / 60.0f;

	}
	else if (m_ensyutuCount >= 60 && m_ensyutuCount < 80)
	{

		//���ֈړ�
		m_spritePos.x -= 200.0f;

		//�g�����񂾂�����Ă���
		m_wakuA -= 1.0f / 20.0f;

	}
	else if (m_ensyutuCount >= 80)
	{

		//�Q�[���X�^�[�g���̉��o�͒l�����������Ȃ�
		if (m_waveNum != 0)
		{

			//���o���I���ƃG�l�~�[��ǉ�����
			m_game->MakeEnemy();


			//�^�C�}�[�����Z�b�g
			m_timer = TIME_LIMIT;	

		}


		m_ensyutuCount = 0;					//�J�E���g�����Z�b�g	
		m_spritePos = SPRITE_POSITION;		//�X�v���C�g�̏ꏊ��������
		m_ensyutuNow = false;				//���o�I��
		m_waveNum++;						//���̃E�F�[�u��
		m_wakuA = 0.0f;						//�����x��0�ɂ���


		//�E�F�[�u�ɂ���ĉ摜��ύX
		if (m_waveNum == 1)
		{

			//�E�F�[�u2�X�^�[�g�摜
			m_waveStartSprite.Init("Assets/sprite/wave/wave2.DDS", 1920.0f, 1080.0f);

		}
		else if (m_waveNum == 2)
		{

			//�E�F�[�u3�X�^�[�g�摜
			m_waveStartSprite.Init("Assets/sprite/wave/wave3.DDS", 1920.0f, 1080.0f);

		}

	}


	//���o�J�E���g�A�b�v
	m_ensyutuCount++;


	//�X�v���C�g�̍X�V
	m_waveStartSprite.SetPosition(m_spritePos);
	m_waveStartSprite.Update();

	m_waveStartWakuSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_wakuA });
	m_waveStartWakuSprite.Update();

}

void Wave::GageSetScale()
{
	float m_scaleX = m_timer * (1.0f / TIME_LIMIT);	//���Ԃ�����قǃQ�[�W�������Ă���

	max(0, m_scaleX);	//�X�P�[����0�ȉ��ɂȂ�Ȃ�

	m_waveGageNakami.SetScale({ m_scaleX,1.0f,1.0f });
	m_waveGageNakami.Update();
}

void Wave::ExecuteBossBattle()
{

	//�{�X��ɓ���u��
	if (m_player->GetPlayerPosition().z >= 9550.0f && m_boss == nullptr/*&& m_goBoss == true*/)
	{

		//������x�̃J�E���g�܂ł�������
		if (Loading_count >= 0 && Loading_count < 10)
		{

			//���񂾂񓧖��x���グ��
			Loading_color.w += LOADING_SPRITE_DELTA_A;
			m_loadingSprite.SetMulColor(Loading_color);
			m_loadingSprite.Update();

		}


		//�J�E���g�A�b�v
		Loading_count++;

	}


	//�{�X��̍Œ�
	if (m_boss != nullptr)
	{

		//������x�̃J�E���g�܂ł�������
		if (Loading_count >= 11 && Loading_count < 21)
		{

			//���񂾂񓧖��x��������
			Loading_color.w -= LOADING_SPRITE_DELTA_A;
			m_loadingSprite.SetMulColor(Loading_color);
			m_loadingSprite.Update();

		}


		//�J�E���g�A�b�v
		Loading_count++;

	}

}

void Wave::TimerRotation()
{
	const float ROT_SPEED		= 2.0f;		//��]���鑬��	

	float m_rotSpeed = ROT_SPEED;

	if (m_rotStopFlag == false)
	{
		if (m_rotAmount >= 180.0f && m_halfRot == false)
		{
			m_rotStopFlag = true;	//��]���~�߂�
			m_halfRot = true;		//������]����
		}
		else if (m_rotAmount >= 360.0f)
		{
			m_rotStopFlag = true;	//��]���~�߂�
			m_halfRot = false;		//�S��]����
			m_rotAmount = 0.0f;		//��]�ʂ������l�ɖ߂�
		}
	}
	else if (m_rotStopFlag == true)
	{
		m_rotSpeed = 0.0f;			//��]�X�g�b�v
		m_stopCount++;				//�J�E���g���n�߂�
		if (m_stopCount >= 30)
		{
			m_rotStopFlag = false;	//��]���n�߂�
			m_rotSpeed = ROT_SPEED;	//���������ɖ߂�
			m_stopCount = 0;
		}
	}

	m_rotAmount += m_rotSpeed;

	m_timerRot.SetRotationDegZ(m_rotAmount);
	m_TimerSprite.SetRotation(m_timerRot);
	m_TimerSprite.Update();
}

void Wave::Render(RenderContext& rc)
{

	//���[�h��ʂ̕\��
	m_loadingSprite.Draw(rc);


	//�Q�[�����ł��|�[�Y��ʂł��Ȃ�
	if (!IsInMainGameOrPause())
	{
		return;
	}


	//�{�X�킶��Ȃ��Ȃ�
	if (IsNotBossBattle())
	{
		
		//�v���C���[UI���Z�b�g����鎞�Ɉꏏ�ɕ`��
		if (m_playerUISet == true)	
		{

			//�E�F�[�u�̎c�莞�ԃX�v���C�g�̕\��
			m_waveGageWaku.Draw(rc);
			m_waveGageNakami.Draw(rc);


			//�^�C�}�[�̃X�v���C�g�̕\��
			m_TimerSprite.Draw(rc);	
			

			//�N���A���o������Ȃ��Ƃ��̂ݕ\��
			if (m_waveClear == nullptr)
			{

				//�^�C�}�[�̃t�H���g��\��
				m_timerFont.Draw(rc);

			}

		}


		//�E�F�[�u�ύX���o���̂ݕ\��
		if (m_ensyutuNow == true)
		{

			//�X�^�[�g�̃X�v���C�g��\��
			m_waveStartWakuSprite.Draw(rc);
			m_waveStartSprite.Draw(rc);

		}

	}


	//�v���C���[�������Ă���@���@UI���Z�b�g�ł���Ȃ�
	if (m_player->GetPlayerDead() != true && m_playerUISet == true)
	{

		//�~�b�V������\������
		m_missionSprite.Draw(rc);

	}

}

bool Wave::IsInMainGameOrPause()
{
	int gameState = m_player->GetGameState();
	return gameState == MAIN_GAME_NUM || gameState == PAUSE_NUM;
}

bool Wave::IsNotBossBattle()
{
	return m_player->GetBossState() != 1;
}