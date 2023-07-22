#include "stdafx.h"
#include "Wave.h"
#include "Game.h"
#include "Player.h"
#include "Boss.h"
#include "GuideLight.h"
#include "Wave3Clear.h"

namespace
{
	//１ウェーブのタイムリミット
	const float		TIME_LIMIT = 180.0f;						
	
	//ウェーブ変更スプライトの初期場所
	const Vector3	SPRITE_POSITION = { 1000.0f,0.0f,0.0f };	

	//ボス戦に行くのに必要な殺した数
	const int REQUIRED_ENEMY_COUNT_FOR_BOSS = 30;

	//ガイドのターゲットポジション
	const Vector3 GUIDE_TARGET_POS = { 0.0f,0.0f,10000.0f };

	//ガイドの速さ
	const float GUIDE_VELOCITY = 8.0f;

	//ガイドが発生する間隔
	const int GUIDE_INTERVAL = 30;

	//ロード画面のα値の変化量
	const float LOADING_SPRITE_DELTA_A = 0.1f;

	//ウェーブスタートの目的位置
	const Vector3 WAVE_START_SPRITE_TARGET = Vector3::Zero;

	//タイマー系の値
	const Vector4 TIMER_FONT_COLOR = { 1.0f,1.0f,1.0f,1.0f };
	const float TIMER_FONT_SCALE = 0.7f;
	const Vector4 TIMER_FONT_SHADOW_COLOR = { 0.0f,0.0f,0.0f,1.0f };
	const Vector3 TIMER_FONT_POSITION = { -880.0f, 440.0f, 0.0f };

}

Wave::Wave()
{

	//最初はウェーブ1のスプライトで初期化
	m_waveStartSprite.Init("Assets/sprite/wave/wave1.DDS", 1920.0f, 1080.0f);
	m_waveStartSprite.SetPosition(SPRITE_POSITION);
	m_waveStartSprite.Update();


	//ウェーブの枠
	m_waveStartWakuSprite.Init("Assets/sprite/wave/waveWaku.DDS", 1920.0f, 1080.0f);
	m_waveStartWakuSprite.SetPosition({ 0.0f,0.0f,0.0f });
	m_waveStartWakuSprite.SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
	m_waveStartWakuSprite.Update();


	//ウェーブの残り時間
	m_waveGageNakami.Init("Assets/sprite/wave/waveGageNakami3.dds", 570.0f, 27.0f);
	m_waveGageNakami.SetPosition({ -730.0f,395.0f,0.0f });
	m_waveGageNakami.SetPivot({ 0.0f,0.5f });
	m_waveGageNakami.Update();


	//ウェーブの残り時間の枠
	m_waveGageWaku.Init("Assets/sprite/wave/waveGageWaku.dds", 600.0f, 42.0f);
	m_waveGageWaku.SetPosition({ -735.0f,395.0f,0.0f });
	m_waveGageWaku.SetPivot({ 0.0f,0.5f });
	m_waveGageWaku.Update();


	//タイマー
	m_TimerSprite.Init("Assets/sprite/wave/Timer2.dds", 1920.0f, 1080.0f);
	m_TimerSprite.SetPosition({ -760.0f,395.0f,0.0f });
	m_TimerSprite.SetScale({ 0.05f,0.05f,0.05f });
	m_TimerSprite.Update();


	//ミッション
	m_missionSprite.Init("Assets/sprite/wave/mission.dds", 1920.0f, 1080.0f);
	m_missionSprite.SetPosition({ 600.0f,200.0f,0.0f });
	m_missionSprite.Update();
	

	//Bossへの遷移のLoading画面の読み込み
	m_loadingSprite.Init("Assets/sprite/NOW_LOADING.DDS", 1632.0f, 918.0f);
	m_loadingSprite.SetMulColor(Loading_color);
	m_loadingSprite.Update();

}

Wave::~Wave()
{

}

bool Wave::Start()
{

	//見つける作業
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");
	

	//タイムリミットを教えてやる
	m_timer = TIME_LIMIT;		

	
	//スプライトの場所の初期
	m_spritePos = SPRITE_POSITION;	


	return true;
}

void Wave::Update()
{
	if (g_pad[0]->IsPress(enButtonB))
	{
		MakeGuide();
	}


	//ポーズ画面中なら
	if (m_player->GetGameState() == PAUSE_NUM)
	{
		return;
	}


	//スタート時
	if (m_waveNum == 0)
	{

		//演出中フラグを立てる
		m_ensyutuNow = true;


		//演出を出す
		SpritePlay();


		return;

	}


	//ボス戦の処理
	ExecuteBossBattle();
	

	//ゲーム中のみ時間経過
	if (m_player->GetGameState() == MAIN_GAME_NUM)
	{

		//ウェーブの管理
		HandleWaveLogic();


		//ウェーブ変更演出中
		if (m_ensyutuNow == true)
		{

			//演出を出す
			SpritePlay();

		}


		//ウェーブ開始演出が終わる
		if (m_waveNum == 1 && m_playerUISet == false)
		{

			//UIを生成する
			m_game->MakePlayerUI();


			//UIのセットが終わったフラグを立てる
			m_playerUISet = true;

		}


		//残り時間の計測
		TimeCount();


		//タイマーの回転
		TimerRotation();


		//サイズを小さくする
		GageSetScale();

	}
	else if (m_player->GetGameState() == PAUSE_NUM)
	{

	}
	else if (m_player->GetGameState() == RESULT_NUM)
	{

	}
	else if (m_player->GetGameState() == CUSTOMIZE_NUM)
	{

	}
	else if (m_player->GetGameState() == OP_NUM)
	{

	}
}

void Wave::HandleWaveLogic()
{

	//最終ウェーブじゃないとき
	if (m_waveNum != 3)
	{

		//プレイヤーがエネミーを倒すか、ウェーブタイマーが0になると追加でエネミー生成
		if (m_timer <= 0.0f || m_game->GetDefeatedEnemyNum() == m_game->GetEnemyNum())
		{

			//演出開始
			m_ensyutuNow = true;

		}

	}
	else if (m_waveNum == 3)
	{

		//エネミーを倒すか、ウェーブタイマーが0になると
		if (m_timer <= 0.0f || m_player->GetKillEnemyAmount() == REQUIRED_ENEMY_COUNT_FOR_BOSS)
		{

			//ボス戦へ行けるようになる
			m_goBoss = true;


			//ボス戦じゃないなら
			if (m_player->GetBossState() != 1)	
			{

				//ガイドの生成
				MakeGuide();

			}


			//ミッションスプライトが変更されてないなら
			if (m_spriteChangeFlag == false)
			{

				//ミッション１クリアのスプライトに変更する
				m_missionSprite.Init("Assets/sprite/wave/mission1clear.dds", 1920.0f, 1080.0f);
				m_missionSprite.Update();


				//殺した数が３０体なら殲滅演出
				if (m_player->GetKillEnemyAmount() == REQUIRED_ENEMY_COUNT_FOR_BOSS)
				{

					//ウェーブ3クリアの演出
					m_waveClear = NewGO<Wave3Clear>(3, "wave3clear");

				}


				//ミッションスプライトを変更したフラグを立てる
				m_spriteChangeFlag = true;

			}

		}

	}

}

void Wave::MakeGuide()
{

	//30フレーム毎にガイドの光が発生
	if (m_guideCount > GUIDE_INTERVAL)
	{
		
		//ガイドの生成
		m_guide = NewGO<GuideLight>(1, "guidelight");		
		

		//飛び出す方向をランダムで決める
		Quaternion rotation;
		rotation.SetRotationDeg(Vector3{ 0.0f,0.0f,1.0f }, rand() % 180);	


		//右方向の設定
		Vector3 m_right = Vector3::AxisX;


		//クォータニオンによる回転が適用された新しいベクトルが得られる
		rotation.Apply(m_right);

		
		//初速
		m_guide->SetVelocity(m_right * GUIDE_VELOCITY);
		

		//ターゲットの設定
		m_guide->SetTargetPosition(GUIDE_TARGET_POS);
		

		//発生位置の設定
		m_guide->SetPosition(m_player->GetPlayerPosition());


		//カウントリセット
		m_guideCount = 0;

	}

	//カウントアップ
	m_guideCount++;

}

void Wave::TimeCount()
{

	//時間経過
	m_timer -= g_gameTime->GetFrameDeltaTime();
	max(0.0f, m_timer);

	//残り時間の表示
	wchar_t text[256];
	int minute = (int)m_timer / 60;
	int sec = (int)m_timer % 60;
	swprintf_s(text, 256, L"ウェーブ%d /3                  %02d  :%02d",m_waveNum, minute, sec);
	m_timerFont.SetText(text);
	m_timerFont.SetPosition(TIMER_FONT_POSITION);
	m_timerFont.SetShadowParam(true, 1.0f, TIMER_FONT_SHADOW_COLOR);
	m_timerFont.SetScale(TIMER_FONT_SCALE);
	m_timerFont.SetColor(TIMER_FONT_COLOR);

}

void Wave::SpritePlay()
{
	if (m_ensyutuCount >= 0 && m_ensyutuCount < 60)
	{

		//ターゲットをセット
		Vector3 m_targetPos = WAVE_START_SPRITE_TARGET;


		//ターゲットと自分の場所の差を割った物を速度にする
		m_moveSpeed.x = (m_targetPos.x - m_spritePos.x) / 5.0f;
		m_spritePos.x += m_moveSpeed.x;


		//枠をカウントに合わせてだんだん出現させていく
		m_wakuA += 1.0f / 60.0f;

	}
	else if (m_ensyutuCount >= 60 && m_ensyutuCount < 80)
	{

		//左へ移動
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


			//タイマーをリセット
			m_timer = TIME_LIMIT;	

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


	//演出カウントアップ
	m_ensyutuCount++;


	//スプライトの更新
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

void Wave::ExecuteBossBattle()
{

	//ボス戦に入る瞬間
	if (m_player->GetPlayerPosition().z >= 9550.0f && m_boss == nullptr/*&& m_goBoss == true*/)
	{

		//ある程度のカウントまでいったら
		if (Loading_count >= 0 && Loading_count < 10)
		{

			//だんだん透明度を上げる
			Loading_color.w += LOADING_SPRITE_DELTA_A;
			m_loadingSprite.SetMulColor(Loading_color);
			m_loadingSprite.Update();

		}


		//カウントアップ
		Loading_count++;

	}


	//ボス戦の最中
	if (m_boss != nullptr)
	{

		//ある程度のカウントまでいったら
		if (Loading_count >= 11 && Loading_count < 21)
		{

			//だんだん透明度を下げる
			Loading_color.w -= LOADING_SPRITE_DELTA_A;
			m_loadingSprite.SetMulColor(Loading_color);
			m_loadingSprite.Update();

		}


		//カウントアップ
		Loading_count++;

	}

}

void Wave::TimerRotation()
{
	const float ROT_SPEED		= 2.0f;		//回転する速さ	

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

	//ロード画面の表示
	m_loadingSprite.Draw(rc);


	//ゲーム中でもポーズ画面でもない
	if (!IsInMainGameOrPause())
	{
		return;
	}


	//ボス戦じゃないなら
	if (IsNotBossBattle())
	{
		
		//プレイヤーUIがセットされる時に一緒に描画
		if (m_playerUISet == true)	
		{

			//ウェーブの残り時間スプライトの表示
			m_waveGageWaku.Draw(rc);
			m_waveGageNakami.Draw(rc);


			//タイマーのスプライトの表示
			m_TimerSprite.Draw(rc);	
			

			//クリア演出中じゃないときのみ表示
			if (m_waveClear == nullptr)
			{

				//タイマーのフォントを表示
				m_timerFont.Draw(rc);

			}

		}


		//ウェーブ変更演出中のみ表示
		if (m_ensyutuNow == true)
		{

			//スタートのスプライトを表示
			m_waveStartWakuSprite.Draw(rc);
			m_waveStartSprite.Draw(rc);

		}

	}


	//プレイヤーが生きている　＆　UIがセットできるなら
	if (m_player->GetPlayerDead() != true && m_playerUISet == true)
	{

		//ミッションを表示する
		m_missionSprite.Draw(rc);

	}

}

bool Wave::IsInMainGameOrPause()
{
	int gameState = m_player->GetGameState();
	return gameState == MAIN_GAME_NUM || gameState == PAUSE_NUM;
}

bool Wave::IsNotBossBattle()
{
	return m_player->GetBossState() != 1;
}