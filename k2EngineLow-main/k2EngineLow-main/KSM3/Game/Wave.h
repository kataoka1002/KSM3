#pragma once
class Game;
class Player;
class Wave : public IGameObject
{
public:
	Wave();
	~Wave();
	bool Start();
	void Update();
	void TimeCount();
	void SpritePlay();
	void GageSetScale();
	void Render(RenderContext& rc);

	Game* m_game = nullptr;
	Player* m_player = nullptr;

	SpriteRender	m_waveStartSprite;							//ウェーブが変わった時に流れるスプライト
	SpriteRender	m_waveGage;									//ウェーブのゲージ

	int				m_waveNum = 0;								//ウェーブのナンバー(全部で3回のウェーブがある)
	int				m_ensyutuCount = 0;
	float			m_timer = 0.0f;								//タイマー
	bool			m_ensyutuNow = false;						//演出中かどうか
	FontRender		m_timerFont;								//タイマーを表示するフォント
	Vector3			m_spritePos = Vector3::Zero;				//スプライトを動かすための変数
	Vector3         m_moveSpeed = Vector3::Zero;

	const float		TIME_LIMIT = 180.0f;						//１ウェーブのタイムリミット
	const Vector3	SPRITE_POSITION = { 1000.0f,0.0f,0.0f };	//ウェーブ変更スプライトの初期場所
};

