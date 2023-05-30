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

	//字幕のスプライトの初期化
	m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite1.DDS", 1600.0f, 900.0f);
	m_fontSprite.SetScale({ 1.0f,m_frameScaleY,1.0f });
	m_fontSprite.SetPosition({ 200.0f,250.0f,0.0f });
	m_fontSprite.Update();

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
	ChangeFont();	//字幕を出す

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
	m_fontSprite.SetScale({ 1.0f,m_frameScaleY,1.0f });
	m_fontSprite.Update();
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

void OPVoice::ChangeFont()
{
	//スプライトを変える
	if (m_spriteFontState == 1) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite2.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 2) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite3.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 3) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite4.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 4) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite5.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 5) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite6.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 6) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite7.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 7) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite8.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 8) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite9.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 9) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite10.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 10) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite11.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 11) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite12.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 12) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite13.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 13) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite14.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 14) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite15.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 15) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite16.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 16) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite17.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 17) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite18.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 18) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite19.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 19) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite20.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 20) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite21.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 21) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite22.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 22) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite23.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 23) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite24.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 24) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite25.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 25) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite26.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 26) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite27.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 27) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite28.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 28) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite29.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 29) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite30.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 30) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite31.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 31) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite32.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 32) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite33.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 33) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite34.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 34) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite35.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 35) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite36.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 36) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite37.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 37) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite38.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 38) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite39.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 39) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite40.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 40) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite41.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 41) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite42.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 42) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite43.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 43) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite44.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 44) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite45.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 45) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite46.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 46) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite47.DDS", 1600.0f, 900.0f);
	}
	else if (m_spriteFontState == 47) {
		m_fontSprite.Init("Assets/sprite/OP/fontSprite/fontSprite48.DDS", 1600.0f, 900.0f);
	}
	m_fontSprite.Update();

	//to go.の前までの処理
	if (m_fontCount % 4 == 0 && m_spriteFontState <= 25)
	{
		m_spriteFontState++;
	}

	//to go.の後の待ち時間を過ぎると文字を発生させる
	if (m_fontCount % 3 == 0 && m_fontCount >= 140)
	{
		m_spriteFontState++;
	}

	m_fontCount++;
}

void OPVoice::Render(RenderContext& rc)
{
	m_voiceSprite.Draw(rc);
	m_voiceFrameSprite.Draw(rc);
	m_fontSprite.Draw(rc);
}