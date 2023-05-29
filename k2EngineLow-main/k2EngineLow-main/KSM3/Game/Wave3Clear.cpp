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
	float m_scaleDiff = m_spriteScale - SPRITE_LAST_SCALE;	//目標のサイズとの差
	float m_scaleChangeSpeed = m_scaleDiff / 5.0f;			//大きさが変わる速さ

	m_spriteScale -= m_scaleChangeSpeed;					//だんだん小さくする

	if (m_count == 1)
	{
		// 文字を白色にする
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
	m_count++;	//カウントアップ

	if (m_flashPlay == false)	//フラッシュ中じゃないなら
	{
		//文字サイズがある程度小さくなったら次の文字に変更
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
			m_fontSprite.Init("Assets/sprite/wave/metuBlack.dds", 1600.0f, 900.0f);	//一回黒に戻す
			m_count = 0;						//カウントの初期化
			m_flashPlay = true;					//白いフラッシュを発生させる
		}
	}
	else	//フラッシュ中なら
	{
		PlayFlash();
	}
	
	m_fontSprite.SetScale(m_spriteScale);
	m_fontSprite.Update();
}

void Wave3Clear::InitInformation()
{	
	m_spriteState++;					//ステートを次に進める
	m_spriteScale = SPRITE_FIRST_SCALE;	//文字サイズの初期化
	m_count = 0;						//カウントの初期化
}

void Wave3Clear::PlayFlash()
{
	if (m_deleteFlash == false)
	{
		m_flashSpriteScale += 0.5f;	//白フラッシュをだんだん大きくする
	}
	else
	{
		m_flashSpriteScale -= 1.0f;	//白フラッシュをだんだん小さくする

		if (m_flashSpriteScale <= 0.0f)
		{
			DeleteGO(this);
			Wave* m_wave = FindGO<Wave>("wave");
			m_wave->m_waveClear = nullptr;
		}
	}
	m_flashSprite.SetScale(m_flashSpriteScale);
	m_flashSprite.Update();

	//白フラッシュがある程度の大きさになり、フラッシュ削除中でないなら
	if (m_flashSpriteScale >= 20.0f && m_deleteFlash == false)	
	{
		static bool m_yellowFinish = false;	//黄色フラッシュが終わったかどうか

		if (m_yellowFinish == false)
		{
			m_yellowSpriteA += 0.1f;		//黄色フラッシュの透明度を上げる

			if (m_yellowSpriteA >= 0.9f)	//ある程度の濃さになったら
			{
				m_yellowFinish = true;		//黄色フラッシュ終了
				m_fontDrawStop = true;		//殲滅の文字を消す
			}
		}
		else
		{
			m_yellowSpriteA -= 0.1f;		//黄色フラッシュの透明度を下げる

			if (m_yellowSpriteA <= 0.0f)	//黄色フラッシュが見えなくなったら
			{
				m_deleteFlash = true;		//次は白フラッシュを消す
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
	
	if(m_flashPlay == true)	//フラッシュ再生中の描画
	{ 
		m_flashSprite.Draw(rc);
		m_yellowSprite.Draw(rc);
	}
}