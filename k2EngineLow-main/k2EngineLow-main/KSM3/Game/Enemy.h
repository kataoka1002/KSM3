#pragma once
//クラス宣言。
class Player;

class Enemy:public IGameObject
{
public:
	//エネミーステート。
	enum EnemyState {
		EnemyState_Chase,
		EnemyState_Idle,
	};
public:
	Enemy();
	~Enemy();
	void Init(Vector3 initPos);
	bool Start();
	void Update();
	void Render(RenderContext& rc);


	//追跡処理
	void Chase();
	//プレイヤーに向かって視点移動
	void SearchPlayer();
	//各ステートの遷移処理。
	void ManageState();
	//共通のステート遷移処理。
	void ProcessCommonStateTransition();
	//待機処理
	void ProcessIdleStateTransition();
	//追跡処理
	void ProcessChaseStateTransition();

	ModelRender m_modelRender;	//モデルレンダー
	EnemyState m_enemyState;
	Vector3 m_position;		//座標
	Vector3 m_moveSpeed;	//移動速度
	CharacterController	m_charaCon;	   //キャラコン。
	Quaternion m_rotation;	//回転
	Player* m_player = nullptr;		//プレイヤー。
	Vector3	m_forward = { 0.0f, 0.0f, -1.0f };		//エネミーの正面ベクトル。
	float	m_chaseTimer = 0.0f;	//追跡タイマー
	float	m_idleTimer = 0.0f;	   //待機タイマー
};

