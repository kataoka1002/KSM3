#include "stdafx.h"
#include "Wave.h"
#include "Game.h"
#include "Player.h"
#include "Boss.h"

Wave::Wave()
{
	//�ŏ��̓E�F�[�u1�̃X�v���C�g�ŏ�����
	m_waveStartSprite.Init("Assets/sprite/wave/wave1.DDS", 1920.0f, 1080.0f);
	m_waveStartSprite.SetPosition(SPRITE_POSITION);
	m_waveStartSprite.Update();

	m_waveStartWakuSprite.Init("Assets/sprite/wave/waveWaku.DDS", 1920.0f, 1080.0f);
	m_waveStartWakuSprite.SetPosition({ 0.0f,0.0f,0.0f });
	m_waveStartWakuSprite.SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
	m_waveStartWakuSprite.Update();

	m_waveGageNakami.Init("Assets/sprite/wave/waveGageNakami3.dds", 380.0f, 18.0f);
	m_waveGageNakami.SetPosition({ -750.0f,420.0f,0.0f });
	m_waveGageNakami.SetPivot({ 0.0f,0.5f });
	m_waveGageNakami.Update();

	m_waveGageWaku.Init("Assets/sprite/wave/waveGageWaku.dds", 400.0f, 25.0f);
	m_waveGageWaku.SetPosition({ -755.0f,420.0f,0.0f });
	m_waveGageWaku.SetPivot({ 0.0f,0.5f });
	m_waveGageWaku.Update();

	//Boss�ւ̑J�ڂ�Loading��ʂ̓ǂݍ���
	Loading_Render.Init("Assets/sprite/NOW_LOADING.DDS", 1632.0f, 918.0f);
	Loading_Render.SetMulColor(Loading_color);
	Loading_Render.Update();
}

Wave::~Wave()
{

}

bool Wave::Start()
{
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");
	

	m_timer = TIME_LIMIT;			//�^�C�����~�b�g�������Ă��
	m_spritePos = SPRITE_POSITION;	//�X�v���C�g�̏ꏊ�̏���

	return true;
}

void Wave::Update()
{
	if (m_player->game_state == 1)
	{
		return;
	}

	//�X�^�[�g��
	if (m_waveNum == 0)
	{
		m_ensyutuNow = true;
		//���o���o��
		SpritePlay();
		return;
	}

	//�{�X��ɓ���u��
	if (m_player->player_position.z >= 9550.0f && m_boss == nullptr /*&& m_wave->m_goBoss == true*/)
	{
		if (Loading_count >= 0 && Loading_count < 10) {
			Loading_color.w += 0.1f;
			Loading_Render.SetMulColor(Loading_color);
			Loading_Render.Update();
		}	
		Loading_count++;
	}
	//�{�X��̍Œ�
	if (m_boss != nullptr)
	{
		if (Loading_count >= 11 && Loading_count < 21)
		{
			Loading_color.w -= 0.1f;
			Loading_Render.SetMulColor(Loading_color);
			Loading_Render.Update();
		}

		Loading_count++;
	}

	//�Q�[�����̂ݎ��Ԍo��
	if (m_player->game_state == 0)
	{
		//�ŏI�E�F�[�u����Ȃ��Ƃ�
		if (m_waveNum != 3)
		{
			//�v���C���[���G�l�~�[��10�̓|�����A�E�F�[�u�^�C�}�[��0�ɂȂ�ƒǉ��ŃG�l�~�[����
			if (m_timer <= 0.0f || m_player->killEnemy == 10)
			{
				//���o�J�n
				m_ensyutuNow = true;
			}
		}
		else if (m_waveNum == 3)
		{
			//�G�l�~�[��10�̓|�����A�E�F�[�u�^�C�}�[��0�ɂȂ�ƃ{�X��֍s����悤�ɂȂ�
			if (m_timer <= 0.0f || m_player->killEnemy == 10)
			{
				m_goBoss = true;
			}
		}

		//�E�F�[�u�ύX���o��
		if (m_ensyutuNow == true)
		{
			//���o���o��
			SpritePlay();
		}

		//�c�莞�Ԃ̌v��
		TimeCount();

		//�T�C�Y������������
		GageSetScale();
	}
	else if (m_player->game_state == 1)
	{

	}
	else if (m_player->game_state == 2)
	{

	}
	else if (m_player->game_state == 3)
	{

	}
	else if (m_player->game_state == 4)
	{

	}
}

void Wave::TimeCount()
{
	//���Ԍo��
	m_timer -= g_gameTime->GetFrameDeltaTime();
	if (m_timer <= 0.0f)
	{
		m_timer = 0.0f;
	}

	//�c�莞�Ԃ̕\��
	wchar_t text[256];
	int minute = (int)m_timer / 60;
	int sec = (int)m_timer % 60;
	swprintf_s(text, 256, L"�E�F�[�u%d/3          �@        %02d:%02d",m_waveNum, minute, sec);
	m_timerFont.SetText(text);
	m_timerFont.SetPosition(Vector3(-905.0f, 480.0f, 0.0f));
	m_timerFont.SetShadowParam(true, 1.0f, Vector4(0.0f, 0.0f, 0.0f, 1.0f));
	m_timerFont.SetScale(0.6f);
	m_timerFont.SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
}

void Wave::SpritePlay()
{
	if (m_ensyutuCount >= 0 && m_ensyutuCount < 60)
	{
		//�^�[�Q�b�g���Z�b�g����,�^�[�Q�b�g�Ǝ����̏ꏊ�̍������������𑬓x�ɂ���
		Vector3 m_targetPos = { 0.0f,0.0f,0.0f };
		m_moveSpeed.x = (m_targetPos.x - m_spritePos.x) / 5.0f;
		m_spritePos.x += m_moveSpeed.x;

		//�g���J�E���g�ɍ��킹�Ă��񂾂�o�������Ă���
		m_wakuA += 1.0f / 60.0f;
	}
	else if (m_ensyutuCount >= 60 && m_ensyutuCount < 80)
	{
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
			m_player->killEnemy -= 10;		//�E�����������Z�b�g
			m_timer = TIME_LIMIT;			//�^�C�}�[�����Z�b�g
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

	m_ensyutuCount++;

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

void Wave::Render(RenderContext& rc)
{
	if (m_player->game_state == 0 || m_player->game_state == 1)
	{
		if (m_player->bossState != 1)	//�{�X�킶��Ȃ��Ȃ�\��
		{
			m_waveGageWaku.Draw(rc);
			m_waveGageNakami.Draw(rc);
			m_timerFont.Draw(rc);

			//���o���̂ݕ\��
			if (m_ensyutuNow == true)
			{
				m_waveStartWakuSprite.Draw(rc);
				m_waveStartSprite.Draw(rc);
			}
		}
	}
	Loading_Render.Draw(rc);
}