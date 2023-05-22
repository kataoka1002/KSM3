#include "stdafx.h"
#include "Wave.h"
#include "Game.h"
#include "Player.h"
#include "Boss.h"

Wave::Wave()
{
	//最初はウェーブ1のスプライトで初期化
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

	//Bossへの遷移のLoading画面の読み込み
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
	

	m_timer = TIME_LIMIT;			//タイムリミットを教えてやる
	m_spritePos = SPRITE_POSITION;	//スプライトの場所の初期

	return true;
}

void Wave::Update()
{
	if (m_player->game_state == 1)
	{
		return;
	}

	//スタート時
	if (m_waveNum == 0)
	{
		m_ensyutuNow = true;
		//演出を出す
		SpritePlay();
		return;
	}

	//ボス戦に入る瞬間
	if (m_player->player_position.z >= 9550.0f && m_boss == nullptr /*&& m_wave->m_goBoss == true*/)
	{
		if (Loading_count >= 0 && Loading_count < 10) {
			Loading_color.w += 0.1f;
			Loading_Render.SetMulColor(Loading_color);
			Loading_Render.Update();
		}	
		Loading_count++;
	}
	//ボス戦の最中
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
		else if (m_waveNum == 3)
		{
			//エネミーを10体倒すか、ウェーブタイマーが0になるとボス戦へ行けるようになる
			if (m_timer <= 0.0f || m_player->killEnemy == 10)
			{
				m_goBoss = true;
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
	swprintf_s(text, 256, L"ウェーブ%d/3          　        %02d:%02d",m_waveNum, minute, sec);
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
		//ターゲットをセットして,ターゲットと自分の場所の差を割った物を速度にする
		Vector3 m_targetPos = { 0.0f,0.0f,0.0f };
		m_moveSpeed.x = (m_targetPos.x - m_spritePos.x) / 5.0f;
		m_spritePos.x += m_moveSpeed.x;

		//枠をカウントに合わせてだんだん出現させていく
		m_wakuA += 1.0f / 60.0f;
	}
	else if (m_ensyutuCount >= 60 && m_ensyutuCount < 80)
	{
		m_spritePos.x -= 200.0f;

		//枠をだんだん消していく
		m_wakuA -= 1.0f / 20.0f;
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
		m_wakuA = 0.0f;						//透明度を0にする

		//ウェーブによって画像を変更
		if (m_waveNum == 1)
		{
			//ウェーブ2スタート画像
			m_waveStartSprite.Init("Assets/sprite/wave/wave2.DDS", 1920.0f, 1080.0f);
		}
		else if (m_waveNum == 2)
		{
			//ウェーブ3スタート画像
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
	float m_scaleX = m_timer * (1.0f / TIME_LIMIT);	//時間が減るほどゲージが減っていく

	max(0, m_scaleX);	//スケールは0以下にならない

	m_waveGageNakami.SetScale({ m_scaleX,1.0f,1.0f });
	m_waveGageNakami.Update();
}

void Wave::Render(RenderContext& rc)
{
	if (m_player->game_state == 0 || m_player->game_state == 1)
	{
		if (m_player->bossState != 1)	//ボス戦じゃないなら表示
		{
			m_waveGageWaku.Draw(rc);
			m_waveGageNakami.Draw(rc);
			m_timerFont.Draw(rc);

			//演出中のみ表示
			if (m_ensyutuNow == true)
			{
				m_waveStartWakuSprite.Draw(rc);
				m_waveStartSprite.Draw(rc);
			}
		}
	}
	Loading_Render.Draw(rc);
}