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
	void TimeCount();
	void SpritePlay();
	void TimerRotation();
	void GageSetScale();
	void Render(RenderContext& rc);

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
	SpriteRender	Loading_Render;


	int				m_waveNum = 0;								//ウェーブのナンバー(全部で3回のウェーブがある)
	int				m_ensyutuCount = 0;
	int				m_guideCount = 0;
	float			m_timer = 0.0f;								//タイマー
	float			m_wakuA = 0.0f;								//枠のα値
	bool			m_ensyutuNow = false;						//演出中かどうか
	bool			m_goBoss = false;							//ボス戦へ行けるかどうか
	FontRender		m_timerFont;								//タイマーを表示するフォント
	Vector3			m_spritePos = Vector3::Zero;				//スプライトを動かすための変数
	Vector3         m_moveSpeed = Vector3::Zero;
	Quaternion m_timerRot;
	Vector4 Loading_color = { 1.0f,1.0f,1.0f,0.0f };
	int Loading_count = 0;


	const float		TIME_LIMIT = 180.0f;						//１ウェーブのタイムリミット
	const Vector3	SPRITE_POSITION = { 1000.0f,0.0f,0.0f };	//ウェーブ変更スプライトの初期場所
};

