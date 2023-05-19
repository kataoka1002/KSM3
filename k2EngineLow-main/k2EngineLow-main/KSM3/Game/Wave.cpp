#include "stdafx.h"
#include "Wave.h"
#include "Game.h"
#include "Player.h"

Wave::Wave()
{
	//�ŏ��̓E�F�[�u1�̃X�v���C�g�ŏ�����
	m_waveStartSprite.Init("Assets/sprite/fade.DDS", 800.0f, 500.0f);
	m_waveStartSprite.SetPosition(SPRITE_POSITION);
	m_waveStartSprite.Update();

	m_waveGage.Init("Assets/sprite/HP.dds", 400.0f, 20.0f);
	m_waveGage.SetPosition({ -300.0f,300.0f,0.0f });
	m_waveGage.SetPivot({ 0.0f,0.5f });
	m_waveGage.Update();
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
	//�X�^�[�g��
	if (m_waveNum == 0)
	{
		m_ensyutuNow = true;
		//���o���o��
		SpritePlay();
		return;
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
	swprintf_s(text, 256, L"�E�F�[�u%d�@%02d:%02d",m_waveNum, minute, sec);
	m_timerFont.SetText(text);
	m_timerFont.SetPosition(Vector3(-800.0f, 490.0f, 0.0f));
	m_timerFont.SetShadowParam(true, 1.0f, Vector4(0.0f, 0.0f, 0.0f, 1.0f));
	m_timerFont.SetScale(0.5f);
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
	}
	else if (m_ensyutuCount >= 60 && m_ensyutuCount < 80)
	{
		m_spritePos.x -= 200.0f;
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

		//�E�F�[�u�ɂ���ĉ摜��ύX
		if (m_waveNum == 1)
		{
			//�E�F�[�u2�X�^�[�g�摜
			m_waveStartSprite.Init("Assets/sprite/mozi1.DDS", 800.0f, 500.0f);
		}
		else if (m_waveNum == 2)
		{
			//�E�F�[�u3�X�^�[�g�摜
			m_waveStartSprite.Init("Assets/sprite/mozi2.DDS", 800.0f, 500.0f);
		}
	}

	m_ensyutuCount++;

	m_waveStartSprite.SetPosition(m_spritePos);
	m_waveStartSprite.Update();
}

void Wave::GageSetScale()
{
	float m_scaleX = m_timer * (1.0f / TIME_LIMIT);	//���Ԃ�����قǃQ�[�W�������Ă���

	max(0, m_scaleX);	//�X�P�[����0�ȉ��ɂȂ�Ȃ�

	m_waveGage.SetScale({ m_scaleX,1.0f,1.0f });
	m_waveGage.Update();
}

void Wave::Render(RenderContext& rc)
{
	if (m_player->game_state == 0 || m_player->game_state == 1)
	{
		//���o���̂ݕ\��
		if (m_ensyutuNow == true)
		{
			m_waveStartSprite.Draw(rc);
		}
		m_waveGage.Draw(rc);
		m_timerFont.Draw(rc);
	}
}