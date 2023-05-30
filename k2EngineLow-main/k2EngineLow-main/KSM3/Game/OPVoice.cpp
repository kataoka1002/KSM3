#include "stdafx.h"
#include "OPVoice.h"
#include "Game.h"

OPVoice::OPVoice()
{

}

OPVoice::~OPVoice()
{
	DeleteGO(m_voiceSE);
	DeleteGO(m_putunSE);
}

bool OPVoice::Start()
{
	m_game = FindGO<Game>("game");

	//���K�z���̃X�v���C�g�̏�����
	m_voiceSprite.Init("Assets/sprite/OP/voice0.DDS", 1600.0f, 900.0f);
	m_voiceSprite.SetScale({ 1.0f,m_frameScaleY,1.0f });
	m_voiceSprite.SetPosition({ -600.0f,250.0f,0.0f });
	m_voiceSprite.Update();

	//�t���[���̃X�v���C�g�̏�����
	m_voiceFrameSprite.Init("Assets/sprite/OP/voiceFrame.DDS", 1600.0f, 900.0f);
	m_voiceFrameSprite.SetScale({ 1.0f,m_frameScaleY,1.0f });
	m_voiceFrameSprite.SetPosition({ 200.0f,250.0f,0.0f });
	m_voiceFrameSprite.Update();

	//OP�����̍Đ�
	m_voiceSE = NewGO<SoundSource>(0);				//���Đ�����ƏI���Ȃ̂ŃC���X�^���X��ێ������Ȃ��ׂɂ�����NewGO����
	m_voiceSE->Init(enVoice);						//������
	m_voiceSE->SetVolume(1.5f * m_game->BGMvol);	//���ʒ���
	m_voiceSE->Play(false);

	return true;
}

void OPVoice::Update()
{
	//�X�v���C�g�̕ό`�̏���
	if (m_scaleDown != true && m_frameScaleY <= 1.0f)
	{
		float m_addFrameScaleY = (1.0f - m_frameScaleY) / 5.0f;		//Y�����ɑ傫���Ȃ鑬��
		m_frameScaleY += m_addFrameScaleY;							//���Z
	}
	else if (m_scaleDown == true)
	{
		float m_decFrameScaleY = (0.0f - m_frameScaleY) / 2.0f;		//Y�����ɏ������Ȃ鑬��
		m_frameScaleY += m_decFrameScaleY;							//���Z
	}

	//�������I�������
	if(m_voiceSE->IsPlaying() == false && m_scaleDown != true)
	{
		m_scaleDown = true;	//�X�v���C�g������������

		//�v�c�����̍Đ�
		m_putunSE = NewGO<SoundSource>(0);				//���Đ�����ƏI���Ȃ̂ŃC���X�^���X��ێ������Ȃ��ׂɂ�����NewGO����
		m_putunSE->Init(enPutun);						//������
		m_putunSE->SetVolume(1.5f * m_game->BGMvol);	//���ʒ���
		m_putunSE->Play(false);
	}

	ChangeSprite();	//�g��̖{����ς��鏈��

	//�v�c�������Ȃ�I����������
	if (m_putunSE != nullptr)
	{
		if (m_putunSE->IsPlaying() == false && m_scaleDown == true)
		{
			DeleteGO(this);
		}
	}

	//�X�V
	m_voiceFrameSprite.SetScale({ 1.0f,m_frameScaleY,1.0f });
	m_voiceFrameSprite.Update();
	m_voiceSprite.SetScale({ 1.0f,m_frameScaleY,1.0f });
	m_voiceSprite.Update();
}

void OPVoice::ChangeSprite()
{
	//���t���[�����ƂɃX�v���C�g��ς���
	if (m_spriteChangeCount >= 25)
	{
		if (m_voiceSpriteState == 0)
		{
			m_voiceSprite.Init("Assets/sprite/OP/voice1.DDS", 1600.0f, 900.0f);
			m_voiceSpriteState++;
		}
		else if (m_voiceSpriteState == 1)
		{
			m_voiceSprite.Init("Assets/sprite/OP/voice2.DDS", 1600.0f, 900.0f);
			m_voiceSpriteState++;
		}
		else if (m_voiceSpriteState == 2)
		{
			m_voiceSprite.Init("Assets/sprite/OP/voice3.DDS", 1600.0f, 900.0f);
			m_voiceSpriteState++;
		}
		else if (m_voiceSpriteState == 3)
		{
			m_voiceSprite.Init("Assets/sprite/OP/voice0.DDS", 1600.0f, 900.0f);
			m_voiceSpriteState = 0;
		}

		m_voiceSprite.Update();		//�X�V
		m_spriteChangeCount = 0;	//�J�E���g���Z�b�g
	}
	m_spriteChangeCount++;
}

void OPVoice::Render(RenderContext& rc)
{
	m_voiceSprite.Draw(rc);
	m_voiceFrameSprite.Draw(rc);
}