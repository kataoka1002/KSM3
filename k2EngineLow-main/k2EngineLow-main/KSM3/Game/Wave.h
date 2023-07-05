#pragma once
class Game;
class Player;
class Boss;
class GuideLight;
class Wave3Clear;
class Wave : public IGameObject
{
public:
	Wave();
	~Wave();
	bool Start();
	void Update();
	void HandleWaveLogic();
	void MakeGuide();
	void TimeCount();
	void SpritePlay();
	void TimerRotation();
	void GageSetScale();
	void ExecuteBossBattle();
	void Render(RenderContext& rc);

	/// <summary>
	/// メインゲーム中もしくはポーズ画面中かを判定
	/// </summary>
	/// <returns></returns>
	bool IsInMainGameOrPause();

	/// <summary>
	/// ボス戦じゃないかどうかを調べる
	/// </summary>
	/// <returns>true : ボス戦じゃない , false : ボス戦</returns>
	bool IsNotBossBattle() ;

	/// <summary>
	/// ウェーブクリアにポインタをセットする
	/// </summary>
	/// <param name="pointa"></param>
	void SetWaveClear(Wave3Clear* pointa)
	{
		m_waveClear = pointa;
	}


	/// <summary>
	/// ボスをセットする
	/// </summary>
	/// <param name="pointa"></param>
	void SetBoss(Boss* pointa)
	{
		m_boss = pointa;
	}


	/// <summary>
	/// ボス戦に行けるかどうかを返す
	/// </summary>
	/// <returns>true : 行ける , false : 行けない</returns>
	bool GetGoBoss()
	{
		return m_goBoss;
	}


	/// <summary>
	/// ローディングカウントを返す
	/// </summary>
	/// <returns></returns>
	int GetLoadCount()
	{
		return Loading_count;
	}


	/// <summary>
	/// ウェーブクリアを返す
	/// </summary>
	/// <returns></returns>
	Wave3Clear* GetWaveClear()
	{
		return m_waveClear;
	}

private:
	Game* m_game = nullptr;
	Player* m_player = nullptr;
	Boss* m_boss = nullptr;
	GuideLight* m_guide = nullptr;
	Wave3Clear* m_waveClear = nullptr;

	SpriteRender	m_waveStartSprite;							//ウェーブが変わった時に流れるスプライト
	SpriteRender	m_waveStartWakuSprite;						//ウェーブが変わった時に流れるスプライトの枠
	SpriteRender	m_waveGageNakami;							//ウェーブのゲージ中身
	SpriteRender	m_waveGageWaku;								//ウェーブのゲージ枠
	SpriteRender	m_TimerSprite;								//タイマー
	SpriteRender	m_TimerSprite2;								//タイマー2
	SpriteRender	m_missionSprite;							//ミッション
	SpriteRender	m_loadingSprite;

	FontRender		m_timerFont;								//タイマーを表示するフォント
	Vector3			m_spritePos = Vector3::Zero;				//スプライトを動かすための変数
	Vector3         m_moveSpeed = Vector3::Zero;
	Quaternion		m_timerRot;
	Vector4			Loading_color = { 1.0f,1.0f,1.0f,0.0f };

	int				m_waveNum = 0;								//ウェーブのナンバー(全部で3回のウェーブがある)
	int				m_ensyutuCount = 0;
	int				m_guideCount = 0;
	int				Loading_count = 0;
	float			m_timer = 0.0f;								//タイマー
	float			m_wakuA = 0.0f;								//枠のα値
	bool			m_ensyutuNow = false;						//演出中かどうか
	bool			m_goBoss = false;							//ボス戦へ行けるかどうか
	bool			m_spriteChangeFlag = false;
	bool			m_playerUISet = false;

};

