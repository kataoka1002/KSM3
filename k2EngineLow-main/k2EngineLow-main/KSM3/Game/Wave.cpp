#include "stdafx.h"
#include "Wave.h"
#include "Game.h"
#include "Player.h"
#include "Boss.h"
#include "GuideLight.h"
#include "Wave3Clear.h"

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

	m_waveGageNakami.Init("Assets/sprite/wave/waveGageNakami3.dds", 570.0f, 27.0f);
	m_waveGageNakami.SetPosition({ -730.0f,395.0f,0.0f });
	m_waveGageNakami.SetPivot({ 0.0f,0.5f });
	m_waveGageNakami.Update();

	m_waveGageWaku.Init("Assets/sprite/wave/waveGageWaku.dds", 600.0f, 42.0f);
	m_waveGageWaku.SetPosition({ -735.0f,395.0f,0.0f });
	m_waveGageWaku.SetPivot({ 0.0f,0.5f });
	m_waveGageWaku.Update();

	m_TimerSprite.Init("Assets/sprite/wave/Timer2.dds", 1920.0f, 1080.0f);
	//m_TimerSprite.SetPosition({ -110.0f,395.0f,0.0f });
	m_TimerSprite.SetPosition({ -760.0f,395.0f,0.0f });
	m_TimerSprite.SetScale({ 0.05f,0.05f,0.05f });
	m_TimerSprite.Update();

	m_missionSprite.Init("Assets/sprite/wave/mission.dds", 1920.0f, 1080.0f);
	m_missionSprite.SetPosition({ 600.0f,200.0f,0.0f });
	m_missionSprite.Update();
	

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
	if (m_player->player_position.z >= 9550.0f && m_boss == nullptr/*&& m_goBoss == true*/)
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

				if (m_player->bossState != 1)	//ボス戦じゃないなら
				{
					//30フレーム毎にガイドの光が発生
					if (m_guideCount % 30 == 0)
					{
						m_guide = NewGO<GuideLight>(1, "guidelight");		//ガイドの生成
						Quaternion rotation;
						rotation.SetRotationDeg(Vector3{ 0.0f,0.0f,1.0f }, rand() % 180);	//飛び出す方向をランダムで決める
						Vector3 m_right = Vector3::AxisX;
						rotation.Apply(m_right);
						m_guide->m_velocity = (m_right * 8);				//初速
						m_guide->m_targetPosition = { 0.0f,0.0f,10000.0f };	//ターゲットの設定
						m_guide->m_position = m_player->player_position;	//発生位置

						m_guideCount = 0;
					}
					m_guideCount++;
				}

				if (m_spriteChangeFlag == false)
				{
					//ミッション１クリアのスプライトに変更する
					m_missionSprite.Init("Assets/sprite/wave/mission1clear.dds", 1920.0f, 1080.0f);
					m_missionSprite.Update();

					//ウェーブ3クリアの演出
					m_waveClear = NewGO<Wave3Clear>(3, "wave3clear");

					m_spriteChangeFlag = true;
				}
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

		//タイマーの回転
		TimerRotation();

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
	swprintf_s(text, 256, L"ウェーブ%d /3                  %02d  :%02d",m_waveNum, minute, sec);
	m_timerFont.SetText(text);
	m_timerFont.SetPosition(Vector3(-880.0f, 440.0f, 0.0f));
	m_timerFont.SetShadowParam(true, 1.0f, Vector4(0.0f, 0.0f, 0.0f, 1.0f));
	m_timerFont.SetScale(0.7f);
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

void Wave::TimerRotation()
{
	static float ROT_SPEED = 2.0f;		//回転する速さ
	static float m_rotAmount = 0.0f;	//回転量
	static int	m_stopCount = 0;		//回転の静止時間
	static bool	m_halfRot = false;		//半分回転したかどうか
	static bool	m_rotStopFlag = false;	//回転が止まっているかどうか

	float m_rotSpeed = ROT_SPEED;

	if (m_rotStopFlag == false)
	{
		if (m_rotAmount >= 180.0f && m_halfRot == false)
		{
			m_rotStopFlag = true;	//回転を止める
			m_halfRot = true;		//半分回転した
		}
		else if (m_rotAmount >= 360.0f)
		{
			m_rotStopFlag = true;	//回転を止める
			m_halfRot = false;		//全回転した
			m_rotAmount = 0.0f;		//回転量を初期値に戻す
		}
	}
	else if (m_rotStopFlag == true)
	{
		m_rotSpeed = 0.0f;			//回転ストップ
		m_stopCount++;				//カウントを始める
		if (m_stopCount >= 30)
		{
			m_rotStopFlag = false;	//回転を始める
			m_rotSpeed = ROT_SPEED;	//速さも元に戻す
			m_stopCount = 0;
		}
	}

	m_rotAmount += m_rotSpeed;

	m_timerRot.SetRotationDegZ(m_rotAmount);
	m_TimerSprite.SetRotation(m_timerRot);
	m_TimerSprite.Update();
}

void Wave::Render(RenderContext& rc)
{
	if (m_player->game_state == 0 || m_player->game_state == 1)
	{
		if (m_player->bossState != 1)	//ボス戦じゃないなら表示
		{
			m_waveGageWaku.Draw(rc);
			m_waveGageNakami.Draw(rc);
			if (m_waveClear == nullptr)
			{
				m_timerFont.Draw(rc);
			}
			
			m_TimerSprite.Draw(rc);	//クリア演出中は表示しない
			

			//演出中のみ表示
			if (m_ensyutuNow == true)
			{
				m_waveStartWakuSprite.Draw(rc);
				m_waveStartSprite.Draw(rc);
			}
		}

		if (m_player->m_playerDead != true)
		{
			m_missionSprite.Draw(rc);	//プレイヤーが生きているならミッションを表示する
		}
	}
	Loading_Render.Draw(rc);
}