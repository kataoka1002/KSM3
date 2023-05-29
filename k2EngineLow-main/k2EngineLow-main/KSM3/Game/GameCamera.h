#pragma once
class Game;
class Player;
class Customize_UI_ver2;
//ゲーム中のカメラを制御する。
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Move();
	void Update();
	/////////////////////////////////////
	//メンバ変数
	/////////////////////////////////////
	Game* m_game = nullptr;
	Player* m_player = nullptr;	//プレイヤー。
	Customize_UI_ver2* camera_customize_ui_ver2 = nullptr;
	SoundSource* m_walkSE = nullptr;				//足音SE
	EffectEmitter* sunabokoriEffect = nullptr;		//砂ぼこりエフェクト

	Vector3 pos = Vector3::Zero;
	Vector3 m_cameraForward = { 0.0f,0.0f,1.0f };
	Vector3 m_toCameraPos;	//注視点から視点に向かうベクトル。
	int CameraState = 4;	//1バトル中,2空白,3カスタマイズ,4登場シーン
	Vector3 target;
	SpringCamera m_springCamera;	//ばねカメラ。
	int opCount = 0;
	int fast_count=0;
	bool trance_Finish =false;
	bool VibFlag = false;			//画面が揺れているかどうか
	bool VibBigFlag = false;			//画面が揺れているかどうか(大)
	bool VibFinalFlag = false;			//画面が揺れているかどうか(最終)
	int BGX = 0, BGY = 0;			//最終的な揺れの大きさ
	int effectCount = 0;
	float VIBRATION_MAX = 40.0f;	
	float VIBRATION_BIG_MAX = 160.0f;
	float VIBRATION_FINAL_MAX = 320.0f;
	float x;
	float y;
};
