#pragma once
class Game;
class Player;
class Customize_UI_ver2;
//ゲーム中のカメラを制御する。
class GameCamera : public IGameObject, Noncopyable
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void OPMove();
	void Update();
	void ManageVibration();
	void CalcRotation();

	/// <summary>
	/// 画面揺れの処理を行う
	/// </summary>
	/// <param name="decline">減少量</param>
	/// <param name="maxVib">揺れの最大値</param>
	/// <param name="flag">true：揺れている , false：揺れていない</param>
	/// <param name="vibration">揺れの大きさ</param>
	void PlayVibration(int decline, int maxVib, bool& flag, int& vibration);


	/// <summary>
	/// 揺れているかどうかのフラグをセットする
	/// </summary>
	/// <param name="flag">true：揺れている , false：揺れていない</param>
	void SetVibFlag(bool flag)
	{
		m_vibFlag = flag;
	}


	/// <summary>
	/// 揺れているかどうかのフラグをセットする
	/// </summary>
	/// <param name="flag">true：揺れている , false：揺れていない</param>
	void SetBigVibFlag(bool flag)
	{
		m_bigVibFlag = flag;
	}


	/// <summary>
	/// 揺れているかどうかのフラグをセットする
	/// </summary>
	/// <param name="flag">true：揺れている , false：揺れていない</param>
	void SetFinalVibFlag(bool flag)
	{
		m_finalVibFlag = flag;
	}


	/// <summary>
	/// 注視点から見たカメラのポジションをセットする
	/// </summary>
	/// <param name="pos">ポジション</param>
	void SetToCameraPos(Vector3 pos)
	{
		m_toCameraPos.Set(pos);
	}


	/// <summary>
	/// ターゲットをセットする
	/// </summary>
	/// <param name="target">ターゲット</param>
	void SetTarget(Vector3 target)
	{
		m_target = target;
	}


	/// <summary>
	/// ステートの設定
	/// </summary>
	/// <param name="state">ステート</param>
	void SetCameraState(int state)
	{
		m_cameraState = state;
	}


	/// <summary>
	/// カメラのポジションを返す
	/// </summary>
	/// <returns>カメラのポジション</returns>
	Vector3 GetCameraPos() const
	{
		return m_position;
	}


	/// <summary>
	/// カメラの前方向を返す
	/// </summary>
	/// <returns>カメラの前方向</returns>
	Vector3 GetCameraForward() const
	{
		return m_cameraForward;
	}


	/// <summary>
	/// ばねカメラを返す
	/// </summary>
	/// <returns>ばねカメラ</returns>
	const SpringCamera& GetSpringCamera() const
	{
		return m_springCamera;
	}


	/// <summary>
	/// ばねカメラを瞬間移動させる
	/// </summary>
	void SpringCameraRefresh()
	{
		m_springCamera.Refresh();
	}


	/// <summary>
	/// カメラステートを返す
	/// </summary>
	/// <returns>ステート</returns>
	int GetCameraState() const
	{
		return m_cameraState;
	}

private:
	/////////////////////////////////////
	//メンバ変数
	/////////////////////////////////////
	Game* m_game = nullptr;
	Player* m_player = nullptr;						
	SoundSource* m_walkSE = nullptr;				//足音SE
	EffectEmitter* m_sunabokoriEffect = nullptr;	//砂ぼこりエフェクト

	Vector3 m_position = Vector3::Zero;
	Vector3 m_cameraForward = { 0.0f,0.0f,1.0f };
	Vector3 m_toCameraPos = Vector3::Zero;			//注視点から視点に向かうベクトル
	Vector3 m_target = Vector3::Zero;
	SpringCamera m_springCamera;					//ばねカメラ

	int m_cameraState = 4;			//1バトル中,2空白,3カスタマイズ,4登場シーン
	int m_opCount = 0;
	int BGX = 0, BGY = 0;			//最終的な揺れの大きさ
	int m_effectCount = 0;
	bool m_vibFlag = false;			//画面が揺れているかどうか
	bool m_bigVibFlag = false;		//画面が揺れているかどうか(大)
	bool m_finalVibFlag = false;	//画面が揺れているかどうか(最終)
	float m_stickPowerX = 0;
	float m_stickPowerY = 0;
};
