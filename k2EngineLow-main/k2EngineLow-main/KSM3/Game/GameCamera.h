#pragma once

class Player;
class Customize_UI_ver2;
//ゲーム中のカメラを制御する。
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	/////////////////////////////////////
	//メンバ変数
	/////////////////////////////////////
	Player* m_player;	//プレイヤー。
	Customize_UI_ver2* camera_customize_ui_ver2;
	Vector3 m_toCameraPos;	//注視点から視点に向かうベクトル。
	int CameraState = 0;
	Vector3 target;

	int fast_count=0;
	bool trance_Finish =false;

	float x;
	float y;
};
