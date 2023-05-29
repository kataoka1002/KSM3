#include "stdafx.h"
#include "Wave3Clear.h"
#include "Wave.h"

Wave3Clear::Wave3Clear()
{

}

Wave3Clear::~Wave3Clear()
{

}

bool Wave3Clear::Start()
{
	m_fontSprite.Init("Assets/sprite/wave/zakoBlack.dds", 1600.0f, 900.0f);
	m_fontSprite.SetPosition(Vector3::Zero);
	m_fontSprite.SetScale(SPRITE_FIRST_SCALE);
	m_fontSprite.Update();

	m_flashSprite.Init("Assets/sprite/wave/waveFlash.dds", 1600.0f, 900.0f);
	m_flashSprite.SetPosition({-800.0f,450.0f,0.0f});
	m_flashSprite.SetScale(1.0f);
	m_flashSprite.SetPivot({ 0.0f,1.0f });
	m_flashSprite.Update();

	m_yellowSprite.Init("Assets/sprite/wave/kiANDore.dds", 1600.0f, 900.0f);
	m_yellowSprite.SetPosition(Vector3::Zero);
	m_yellowSprite.SetScale(1.0f);
	m_yellowSprite.SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
	m_yellowSprite.Update();
	return true;
}

void Wave3Clear::Update()
{
	float m_scaleDiff = m_spriteScale - SPRITE_LAST_SCALE;	//�ڕW�̃T�C�Y�Ƃ̍�
	float m_scaleChangeSpeed = m_scaleDiff / 5.0f;			//�傫�����ς�鑬��

	m_spriteScale -= m_scaleChangeSpeed;					//���񂾂񏬂�������

	if (m_count == 1)
	{
		// �����𔒐F�ɂ���
		switch (m_spriteState)
		{
		case 0:
			m_fontSprite.Init("Assets/sprite/wave/zakoWhite.dds", 1600.0f, 900.0f);
			break;
		case 1:
			m_fontSprite.Init("Assets/sprite/wave/senWhite.dds", 1600.0f, 900.0f);
			break;
		case 2:
			m_fontSprite.Init("Assets/sprite/wave/metuWhite.dds", 1600.0f, 900.0f);
			break;
		default:
			break;
		}
	}
	m_count++;	//�J�E���g�A�b�v

	if (m_flashPlay == false)	//�t���b�V��������Ȃ��Ȃ�
	{
		//�����T�C�Y��������x�������Ȃ����玟�̕����ɕύX
		if (m_spriteState == 0 && m_scaleDiff <= 0.0035f)
		{
			m_fontSprite.Init("Assets/sprite/wave/senBlack.dds", 1600.0f, 900.0f);
			InitInformation();
		}
		else if (m_spriteState == 1 && m_scaleDiff <= 0.007f)
		{
			m_fontSprite.Init("Assets/sprite/wave/metuBlack.dds", 1600.0f, 900.0f);
			InitInformation();
		}
		else if (m_spriteState == 2 && m_scaleDiff <= 0.00003f)
		{
			m_fontSprite.Init("Assets/sprite/wave/metuBlack.dds", 1600.0f, 900.0f);	//��񍕂ɖ߂�
			m_count = 0;						//�J�E���g�̏�����
			m_flashPlay = true;					//�����t���b�V���𔭐�������
		}
	}
	else	//�t���b�V�����Ȃ�
	{
		PlayFlash();
	}
	
	m_fontSprite.SetScale(m_spriteScale);
	m_fontSprite.Update();
}

void Wave3Clear::InitInformation()
{	
	m_spriteState++;					//�X�e�[�g�����ɐi�߂�
	m_spriteScale = SPRITE_FIRST_SCALE;	//�����T�C�Y�̏�����
	m_count = 0;						//�J�E���g�̏�����
}

void Wave3Clear::PlayFlash()
{
	if (m_deleteFlash == false)
	{
		m_flashSpriteScale += 0.5f;	//���t���b�V�������񂾂�傫������
	}
	else
	{
		m_flashSpriteScale -= 1.0f;	//���t���b�V�������񂾂񏬂�������

		if (m_flashSpriteScale <= 0.0f)
		{
			DeleteGO(this);
			Wave* m_wave = FindGO<Wave>("wave");
			m_wave->m_waveClear = nullptr;
		}
	}
	m_flashSprite.SetScale(m_flashSpriteScale);
	m_flashSprite.Update();

	//���t���b�V����������x�̑傫���ɂȂ�A�t���b�V���폜���łȂ��Ȃ�
	if (m_flashSpriteScale >= 20.0f && m_deleteFlash == false)	
	{
		static bool m_yellowFinish = false;	//���F�t���b�V�����I��������ǂ���

		if (m_yellowFinish == false)
		{
			m_yellowSpriteA += 0.1f;		//���F�t���b�V���̓����x���グ��

			if (m_yellowSpriteA >= 0.9f)	//������x�̔Z���ɂȂ�����
			{
				m_yellowFinish = true;		//���F�t���b�V���I��
				m_fontDrawStop = true;		//�r�ł̕���������
			}
		}
		else
		{
			m_yellowSpriteA -= 0.1f;		//���F�t���b�V���̓����x��������

			if (m_yellowSpriteA <= 0.0f)	//���F�t���b�V���������Ȃ��Ȃ�����
			{
				m_deleteFlash = true;		//���͔��t���b�V��������
			}
		}
		m_yellowSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_yellowSpriteA });
		m_yellowSprite.Update();
	}
}

void Wave3Clear::Render(RenderContext& rc)
{
	if (m_fontDrawStop != true)
	{
		m_fontSprite.Draw(rc);
	}
	
	if(m_flashPlay == true)	//�t���b�V���Đ����̕`��
	{ 
		m_flashSprite.Draw(rc);
		m_yellowSprite.Draw(rc);
	}
}