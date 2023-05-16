#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "Customize_UI_ver2.h"
#include "Game.h"

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	//プレイヤーのインスタンスを探す。
	m_player = FindGO<Player>("player");
	m_game = FindGO<Game>("game");

	//ばねカメラの初期化。
	m_springCamera.Init(
		*g_camera3D,		//ばねカメラの処理を行うカメラを指定する。
		500.0f,			//カメラの移動速度の最大値。
		true,				//カメラと地形とのあたり判定を取るかどうかのフラグ。trueだとあたり判定を行う。
		5.0f				//カメラに設定される球体コリジョンの半径。第３引数がtrueの時に有効になる。
	);

	//効果音の設定
	m_walkSE = NewGO<SoundSource>(0);
	m_walkSE->Init(enRunning);	//初期化
	m_walkSE->SetVolume(0.5f * m_game->SEvol);	//音量調整


	//注視点から視点までのベクトルを設定。
	//カメラステートが4(最初のムービー)の時。
	if (CameraState == 4)
	{
		m_toCameraPos.Set(0.0f, 500.0f, -700.0f);
		//カメラのニアクリップとファークリップを設定する。
		g_camera3D->SetNear(1.0f);
		g_camera3D->SetFar(25000.0f);

	}
	//カメラステートが1(ボス)の時。
	//else if (CameraState == 1)
	//{
	//	m_toCameraPos.Set(0.0f, 125.0f, -400.0f);
	//	//近平面,遠平面調整中…。
	//	g_camera3D->SetNear(1.0f);
	//	g_camera3D->SetFar(10000.0f);
	//}
	////カメラステートが2(タイトルにします)の時。
	//else if (CameraState == 2)
	//{
	//	m_toCameraPos.Set(0.0f, 500.0f, -700.0f);
	//	g_camera3D->SetNear(1.0f);
	//	g_camera3D->SetFar(1000.0f);
	//}


	return true;
}

void GameCamera::Update()
{
	Vector3 toCameraPosOld = m_toCameraPos;

	//カスタマイズ画面以外ならパッドの入力を使ってカメラを回す。
	if (CameraState != 3 && CameraState != 4)
	{
		x = g_pad[0]->GetRStickXF();
		y = g_pad[0]->GetRStickYF();
	}
		
	//Y軸周りの回転
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 1.3f * x);
	qRot.Apply(m_toCameraPos);
	//X軸周りの回転。
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 1.3f * y);
	qRot.Apply(m_toCameraPos);
	//カメラの回転の上限をチェックする。
	//注視点から視点までのベクトルを正規化する。
	//正規化すると、ベクトルの大きさが１になる。
	//大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ。
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	
	if (CameraState == 0)//雑魚戦の時カメラ。
	{
		//注視点を計算する。
		target = m_player->player_position;
		target.y += 80.0f;		//プレイヤの足元からちょっと上を注視点とする。

		if (toPosDir.y < 0.3f)
		{
			//カメラが上向きすぎ。
			m_toCameraPos = toCameraPosOld;
		}
		else if (toPosDir.y > 0.8f) 
		{
			//カメラが下向きすぎ。
			m_toCameraPos = toCameraPosOld;
		}
	}
	else if (CameraState == 1)//ボス戦の時のカメラ。
	{
		//注視点を計算する。
		target = m_player->player_position;
		target.y += 200.0f;		//プレイヤの足元からちょっと上を注視点とする。

		if (toPosDir.y < -0.2f)
		{
			//上を向きすぎないように。
			m_toCameraPos = toCameraPosOld;
		}
		else if (toPosDir.y > 0.7f)
		{
			//下を向きすぎないように。
			m_toCameraPos = toCameraPosOld;
		}
	}
	else if (CameraState == 2)
	{
		m_toCameraPos.Set(0.0f, 10.0f, -300.0f);
		target.y = 100.0f;

		m_toCameraPos = toCameraPosOld;
	}
	else if (CameraState == 3)
	{
		m_toCameraPos.Set(0.0f, 10.0f, -300.0f);
		target.y = 100.0f;
	}
	else if (CameraState == 4)
	{
		Move();
	}

	//視点を計算する。
	Vector3 pos = target + m_toCameraPos;

	//ばねカメラの設定
	m_springCamera.SetTarget(target);
	m_springCamera.SetPosition(pos);
	m_springCamera.Update();
}

void GameCamera::Move()
{
	//注視点を計算する。
	target = m_player->player_position;
	target.y += 80.0f;		//プレイヤの足元からちょっと上を注視点とする。

	if (opCount >= 0 && opCount <= 200)
	{
		//プレイヤーを前へ進める
		m_player->player_position.z += 5.0f;

		m_toCameraPos.Set(50.0f, 50.0f, 500.0f);
	}
	else if (opCount > 200 && opCount <= 280)
	{
		//プレイヤーを前へ進める
		m_player->player_position.z += 3.0f;

		//Y軸周りの回転
		Quaternion YRot;
		YRot.SetRotationDeg(Vector3::AxisY, 1.0f);
		YRot.Apply(m_toCameraPos);

		//X軸周りの回転
		Quaternion XRot;
		XRot.SetRotationDeg(Vector3::AxisX, -0.95f);
		XRot.Apply(m_toCameraPos);
	}
	else if (opCount > 280 && opCount <= 400)
	{
		//ゲーム中の視点に合わせる
		m_toCameraPos.Set(0.0f, 500.0f, -700.0f);
	}
	else if (opCount > 400)
	{
		m_springCamera.Init(
			*g_camera3D,		//ばねカメラの処理を行うカメラを指定する。
			50000.0f,			//カメラの移動速度の最大値。
			true,				//カメラと地形とのあたり判定を取るかどうかのフラグ。trueだとあたり判定を行う。
			5.0f				//カメラに設定される球体コリジョンの半径。第３引数がtrueの時に有効になる。
		);

		//キャラコンをプレイヤーが今いる位置で設定
		m_player->characterController.SetPosition(m_player->player_position);
		m_game->SetUp();
		m_player->game_state = 0;
		CameraState = 0;
	}

	//動いている間は足音再生
	if (m_walkSE->IsPlaying() != true && opCount < 280)
	{
		m_walkSE->Play(true);
	}
	else if (opCount >= 280)
	{
		m_walkSE->Stop();
	}

	//動いている間30フレームごとに砂ぼこりを発生させる
	if (effectCount > 30 && opCount < 280)
	{
		//砂ぼこりエフェクトの初期化と再生
		sunabokoriEffect = NewGO<EffectEmitter>(0);
		sunabokoriEffect->Init(enSunabokori);
		sunabokoriEffect->SetScale({ 4.0f,4.0f,4.0f });
		sunabokoriEffect->SetRotation(m_player->player_rotation);
		sunabokoriEffect->SetPosition(m_player->player_position);
		sunabokoriEffect->Play();

		effectCount = 0;	//カウントリセット
	}

	effectCount++;
	opCount++;
}