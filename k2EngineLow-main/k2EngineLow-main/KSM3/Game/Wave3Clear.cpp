#include "stdafx.h"
#include "Wave3Clear.h"
#include "Wave.h"

namespace
{
	//�ŏ��̃T�C�Y
	const float SPRITE_FIRST_SCALE = 3.5f;			
	
	//�ŏI�I�ȃT�C�Y
	const float SPRITE_LAST_SCALE = 1.3f;	

	//�X�v���C�g�̃T�C�Y
	float m_spriteScale = SPRITE_FIRST_SCALE;	
}

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
	
	//�ڕW�̃T�C�Y�Ƃ̍�
	float m_scaleDiff = m_spriteScale - SPRITE_LAST_SCALE;	
	
	//�傫�����ς�鑬��
	float m_scaleChangeSpeed = m_scaleDiff / 5.0f;			

	
	//���񂾂񏬂�������
	m_spriteScale -= m_scaleChangeSpeed;		


	//2�t���[���ڂȂ�
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

	
	//�J�E���g�A�b�v
	m_count++;	


	//�t���b�V��������Ȃ��Ȃ�
	if (m_flashPlay == false)	
	{

		//�����T�C�Y��������x�������Ȃ����玟�̕����ɕύX
		if (m_spriteState == 0 && m_scaleDiff <= 0.0035f)
		{

			m_fontSprite.Init("Assets/sprite/wave/senBlack.dds", 1600.0f, 900.0f);

			//���̏�����
			InitInformation();

		}
		else if (m_spriteState == 1 && m_scaleDiff <= 0.007f)
		{

			m_fontSprite.Init("Assets/sprite/wave/metuBlack.dds", 1600.0f, 900.0f);
			
			//���̏�����
			InitInformation();

		}
		else if (m_spriteState == 2 && m_scaleDiff <= 0.00003f)
		{
			
			//��񍕂ɖ߂�
			m_fontSprite.Init("Assets/sprite/wave/metuBlack.dds", 1600.0f, 900.0f);	
			
			//�J�E���g�̏�����
			m_count = 0;						
			
			//�����t���b�V���𔭐�������
			m_flashPlay = true;			

		}

	}
	//�t���b�V�����Ȃ�
	else	
	{
		//�t���b�V���̏���
		PlayFlash();
	}
	

	//�X�V
	m_fontSprite.SetScale(m_spriteScale);
	m_fontSprite.Update();

}

void Wave3Clear::InitInformation()
{	
	
	//�X�e�[�g�����ɐi�߂�
	m_spriteState++;					
	
	//�����T�C�Y�̏�����
	m_spriteScale = SPRITE_FIRST_SCALE;	
	
	//�J�E���g�̏�����
	m_count = 0;		

}

void Wave3Clear::PlayFlash()
{
	if (m_deleteFlash == false)
	{
		//���t���b�V�������񂾂�傫������
		m_flashSpriteScale += 0.5f;	
	}
	else
	{
		//���t���b�V�������񂾂񏬂�������
		m_flashSpriteScale -= 1.0f;	

		//�t���b�V���̃T�C�Y��0�ɂȂ�����
		if (m_flashSpriteScale <= 0.0f)
		{

			//�������g�̍폜
			DeleteGO(this);


			//�������g�̃f�[�^����ɂ���
			Wave* m_wave = FindGO<Wave>("wave");
			m_wave->m_waveClear = nullptr;

		}
	}


	//�t���b�V���̃X�v���C�g�̍X�V
	m_flashSprite.SetScale(m_flashSpriteScale);
	m_flashSprite.Update();


	//���t���b�V����������x�̑傫���ɂȂ�A�t���b�V���폜���łȂ��Ȃ�
	if (m_flashSpriteScale >= 20.0f && m_deleteFlash == false)	
	{

		//���F�t���b�V�����I����ĂȂ��Ȃ�
		if (m_yellowFinish == false)
		{
			
			//���F�t���b�V���̓����x���グ��
			m_yellowSpriteA += 0.1f;		

			
			//������x�̔Z���ɂȂ�����
			if (m_yellowSpriteA >= 0.9f)	
			{
				
				//���F�t���b�V���I��
				m_yellowFinish = true;		
				
				//�r�ł̕���������
				m_fontDrawStop = true;		

			}

		}
		else
		{
			
			//���F�t���b�V���̓����x��������
			m_yellowSpriteA -= 0.1f;		

			
			//���F�t���b�V���������Ȃ��Ȃ�����
			if (m_yellowSpriteA <= 0.0f)	
			{
				
				//���͔��t���b�V��������
				m_deleteFlash = true;	

			}
		}


		//�X�V
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
	
	
	//�t���b�V���Đ���
	if(m_flashPlay == true)	
	{ 
		m_flashSprite.Draw(rc);
		m_yellowSprite.Draw(rc);
	}

}