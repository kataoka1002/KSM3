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

	//メガホンのスプライトの初期化
	m_voiceSprite.Init("Assets/sprite/OP/voice0.DDS", 1600.0f, 900.0f);
	m_voiceSprite.SetScale({ 1.0f,m_frameScaleY,1.0f });
	m_voiceSprite.SetPosition({ -600.0f,250.0f,0.0f });
	m_voiceSprite.Update();

	//フレームのスプライトの初期化
	m_voiceFrameSprite.Init("Assets/sprite/OP/voiceFrame.DDS", 1600.0f, 900.0f);
	m_voiceFrameSprite.SetScale({ 1.0f,m_frameScaleY,1.0f });
	m_voiceFrameSprite.SetPosition({ 200.0f,250.0f,0.0f });
	m_voiceFrameSprite.Update();

	//OP音声の再生
	m_voiceSE = NewGO<SoundSource>(0);				//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
	m_voiceSE->Init(enVoice);						//初期化
	m_voiceSE->SetVolume(1.5f * m_game->BGMvol);	//音量調整
	m_voiceSE->Play(false);

	return true;
}

void OPVoice::Update()
{
	//スプライトの変形の処理
	if (m_scaleDown != true && m_frameScaleY <= 1.0f)
	{
		float m_addFrameScaleY = (1.0f - m_frameScaleY) / 5.0f;		//Y方向に大きくなる速さ
		m_frameScaleY += m_addFrameScaleY;							//加算
	}
	else if (m_scaleDown == true)
	{
		float m_decFrameScaleY = (0.0f - m_frameScaleY) / 2.0f;		//Y方向に小さくなる速さ
		m_frameScaleY += m_decFrameScaleY;							//加算
	}

	//音声が終わったら
	if(m_voiceSE->IsPlaying() == false && m_scaleDown != true)
	{
		m_scaleDown = true;	//スプライトを小さくする

		//プツン音の再生
		m_putunSE = NewGO<SoundSource>(0);				//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
		m_putunSE->Init(enPutun);						//初期化
		m_putunSE->SetVolume(1.5f * m_game->BGMvol);	//音量調整
		m_putunSE->Play(false);
	}

	ChangeSprite();	//波戦の本数を変える処理

	//プツン音がなり終わったら消す
	if (m_putunSE != nullptr)
	{
		if (m_putunSE->IsPlaying() == false && m_scaleDown == true)
		{
			DeleteGO(this);
		}
	}

	//更新
	m_voiceFrameSprite.SetScale({ 1.0f,m_frameScaleY,1.0f });
	m_voiceFrameSprite.Update();
	m_voiceSprite.SetScale({ 1.0f,m_frameScaleY,1.0f });
	m_voiceSprite.Update();
}

void OPVoice::ChangeSprite()
{
	//一定フレームごとにスプライトを変える
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

		m_voiceSprite.Update();		//更新
		m_spriteChangeCount = 0;	//カウントリセット
	}
	m_spriteChangeCount++;
}

void OPVoice::Render(RenderContext& rc)
{
	m_voiceSprite.Draw(rc);
	m_voiceFrameSprite.Draw(rc);
}