#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{
}
bool GameCamera::Start()
{
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
	else if (CameraState==1)
	{
		m_toCameraPos.Set(0.0f, 125.0f, -400.0f);
		//近平面,遠平面調整中…。
		g_camera3D->SetNear(1.0f);
		g_camera3D->SetFar(10000.0f);
	}

	//プレイヤーのインスタンスを探す。
	m_player = FindGO<Player>("player");

	

	return true;
}
void GameCamera::Update()
{
	//カメラを更新。
	//注視点を計算する。
	Vector3 target = m_player->player_position;
	
	if (CameraState==0)
	{
		target.y += 80.0f;
	}

	if (CameraState==1)
	{
		//プレイヤの足元からちょっと上を注視点とする。
		target.y += 200.0f;

	}

	Vector3 toCameraPosOld = m_toCameraPos;
	//パッドの入力を使ってカメラを回す。
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();
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
		if (toPosDir.y < 0.5f)
		{
			//カメラが上向きすぎ。
			m_toCameraPos = toCameraPosOld;
		}
		else if (toPosDir.y > 0.7f) 
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
		else if (toPosDir.y > 0.3f)
		{
			//下を向きすぎないように。
			m_toCameraPos = toCameraPosOld;
		}
	}


	//視点を計算する。
	Vector3 pos = target + m_toCameraPos;
	//メインカメラに注視点と視点を設定する。
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);

	//カメラの更新。
	g_camera3D->Update();
}