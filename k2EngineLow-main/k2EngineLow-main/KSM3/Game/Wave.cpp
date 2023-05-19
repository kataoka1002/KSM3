#include "stdafx.h"
#include "Wave.h"
#include "Game.h"
#include "Player.h"

Wave::Wave()
{
	//最初はウェーブ1のスプライトで初期化
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

	m_timer = TIME_LIMIT;			//タイムリミットを教えてやる
	m_spritePos = SPRITE_POSITION;	//スプライトの場所の初期

	return true;
}

void Wave::Update()
{
	//スタート時
	if (m_waveNum == 0)
	{
		m_ensyutuNow = true;
		//演出を出す
		SpritePlay();
		return;
	}

	//ゲーム中のみ時間経過
	if (m_player->game_state == 0)
	{
		//最終ウェーブじゃないとき
		if (m_waveNum != 3)
		{
			//プレイヤーがエネミーを10体倒すか、ウェーブタイマーが0になると追加でエネミー生成
			if (m_timer <= 0.0f || m_player->killEnemy == 10)
			{
				//演出開始
				m_ensyutuNow = true;
			}
		}

		//ウェーブ変更演出中
		if (m_ensyutuNow == true)
		{
			//演出を出す
			SpritePlay();
		}

		//残り時間の計測
		TimeCount();

		//サイズを小さくする
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
	//時間経過
	m_timer -= g_gameTime->GetFrameDeltaTime();
	if (m_timer <= 0.0f)
	{
		m_timer = 0.0f;
	}

	//残り時間の表示
	wchar_t text[256];
	int minute = (int)m_timer / 60;
	int sec = (int)m_timer % 60;
	swprintf_s(text, 256, L"ウェーブ%d　%02d:%02d",m_waveNum, minute, sec);
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
		//ターゲットをセットして,ターゲットと自分の場所の差を割った物を速度にする
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
		//ゲームスタート時の演出は値を初期化しない
		if (m_waveNum != 0)
		{
			//演出が終わるとエネミーを追加生成
			m_game->MakeEnemy();
			m_player->killEnemy -= 10;		//殺した数をリセット
			m_timer = TIME_LIMIT;			//タイマーをリセット
		}

		m_ensyutuCount = 0;					//カウントもリセット	
		m_spritePos = SPRITE_POSITION;		//スプライトの場所を初期化
		m_ensyutuNow = false;				//演出終了
		m_waveNum++;						//次のウェーブへ

		//ウェーブによって画像を変更
		if (m_waveNum == 1)
		{
			//ウェーブ2スタート画像
			m_waveStartSprite.Init("Assets/sprite/mozi1.DDS", 800.0f, 500.0f);
		}
		else if (m_waveNum == 2)
		{
			//ウェーブ3スタート画像
			m_waveStartSprite.Init("Assets/sprite/mozi2.DDS", 800.0f, 500.0f);
		}
	}

	m_ensyutuCount++;

	m_waveStartSprite.SetPosition(m_spritePos);
	m_waveStartSprite.Update();
}

void Wave::GageSetScale()
{
	float m_scaleX = m_timer * (1.0f / TIME_LIMIT);	//時間が減るほどゲージが減っていく

	max(0, m_scaleX);	//スケールは0以下にならない

	m_waveGage.SetScale({ m_scaleX,1.0f,1.0f });
	m_waveGage.Update();
}

void Wave::Render(RenderContext& rc)
{
	if (m_player->game_state == 0 || m_player->game_state == 1)
	{
		//演出中のみ表示
		if (m_ensyutuNow == true)
		{
			m_waveStartSprite.Draw(rc);
		}
		m_waveGage.Draw(rc);
		m_timerFont.Draw(rc);
	}
}