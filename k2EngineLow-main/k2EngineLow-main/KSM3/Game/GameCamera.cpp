#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "Customize_UI_ver2.h"

GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{

	//ばねカメラの初期化。
	m_springCamera.Init(
		*g_camera3D,		//ばねカメラの処理を行うカメラを指定する。
		1000.0f,			//カメラの移動速度の最大値。
		true,				//カメラと地形とのあたり判定を取るかどうかのフラグ。trueだとあたり判定を行う。
		5.0f				//カメラに設定される球体コリジョンの半径。第３引数がtrueの時に有効になる。
	);

	//注視点から視点までのベクトルを設定。
	//カメラステートが0(ウェーブ戦)の時。
	if (CameraState == 0)
	{
		m_toCameraPos.Set(0.0f, 500.0f, -700.0f);
		//カメラのニアクリップとファークリップを設定する。
		g_camera3D->SetNear(1.0f);
		g_camera3D->SetFar(25000.0f);

	}
	//カメラステートが1(ボス)の時。
	else if (CameraState == 1)
	{
		m_toCameraPos.Set(0.0f, 125.0f, -400.0f);
		//近平面,遠平面調整中…。
		g_camera3D->SetNear(1.0f);
		g_camera3D->SetFar(10000.0f);
	}
	//カメラステートが2(タイトルにします)の時。
	else if (CameraState == 2)
	{
		m_toCameraPos.Set(0.0f, 500.0f, -700.0f);
		g_camera3D->SetNear(1.0f);
		g_camera3D->SetFar(1000.0f);
	}

	//プレイヤーのインスタンスを探す。
	m_player = FindGO<Player>("player");

	

	return true;
}
void GameCamera::Update()
{
	Vector3 toCameraPosOld = m_toCameraPos;
	//カメラを更新。
	if (CameraState == 3) 
	{
		m_toCameraPos.Set(0.0f, 10.0f, -300.0f);
		target.y = 100.0f;
		/*if (fast_count >= 2) {
			camera_customize_ui_ver2 = FindGO<Customize_UI_ver2>("customize_ui_ver2");
			target = camera_customize_ui_ver2->custom_model_body_position;
		}
		fast_count++;*/
	}
	else 
	{
		//注視点を計算する。
		target = m_player->player_position;
	}
	
	if (CameraState==0)
	{
		
		target.y += 80.0f;
	}

	if (CameraState==1)
	{
		//プレイヤの足元からちょっと上を注視点とする。
		target.y += 200.0f;
		

	}
	if (m_player->game_state == 3)
	{
		//m_toCameraPos.Set(0.0f, -50.0f, -300.0f);
		////近平面,遠平面調整中…。
		//g_camera3D->SetNear(1.0f);
		//g_camera3D->SetFar(10000.0f);
		//target.y -= 90.0f;
	}
	else {
		//カスタマイズ画面以外ならパッドの入力を使ってカメラを回す。
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
		m_toCameraPos = toCameraPosOld;
	}


	//視点を計算する。
	Vector3 pos = target + m_toCameraPos;
	//メインカメラに注視点と視点を設定する。
	//g_camera3D->SetTarget(target);
	//g_camera3D->SetPosition(pos);

	//カメラの更新。
	//g_camera3D->Update();

	m_springCamera.SetTarget(target);
	m_springCamera.SetPosition(pos);
	m_springCamera.Update();
}