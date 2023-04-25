#pragma once
#define HP 200.0f

class Player;
class Battle_ship_attack;
class Drop_item;

class Enemy_Near :public IGameObject
{
public:

	//パス移動用
	struct Point {
		Vector3 m_position;	//ポイントの座標
		int m_num;			//ポイントの番号
	};

	Enemy_Near();
	~Enemy_Near();
	

	bool Start();
	void Update();					//更新処理
	void Render(RenderContext& rc);	//描画処理
	void Move();					//移動処理
	void PlayerSearch();			//索敵処理
	void ItemDrop();				//アイテムドロップ
	void WeaponMove();				//離れる処理
	void SetUp();					//武器セット
	void Attack();					//武器を選んで攻撃
	void Fire();					//発射
	void PassMove();				//パス移動


	//パス移動に必要な奴ら
	std::vector<Point> m_pointList;
	Point* m_point;

	Player* m_player = nullptr;
	Battle_ship_attack* m_battleShipAttack;
	Drop_item* m_dropItem;

	ModelRender m_enemyModel;						//エネミーモデル
	ModelRender m_enemyWeaponModel;					//武器モデル
	CharacterController m_enemyCharacterController;	//エネミーキャラコン
	Quaternion m_enemyRotation;						//エネミークォータニオン
	Quaternion m_weaponRotation;					//武器クォータニオン
	Vector3 m_enemyPosition;						//エネミー座標
	Vector3 m_weaponPosition;						//武器ポジション
	Vector3 m_enemyMoveSpeed;						//エネミー移動速度
	Vector3 m_enemyForward{ 0.0f,0.0f,-1.0f };		//エネミーの正面ベクトル
	Vector3 m_toPlayer;								//プレイヤーへのベクトル
	Vector3 m_toPlayerDir;							//プレイヤーへの方向
	Vector3 m_Up = { 0.0f,1.0f,0.0f };				//上方向の設定	
	Vector3 m_enemyTargetPos = { 0.0f,0.0f,0.0f };	//ターゲットのポジション
	Vector3 m_toTarget;								//ターゲットへの方向

	bool m_defeatState = false;						//死んだかどうかフラグ
	bool m_enemyEscape = false;						//後退中かどうかフラグ
	bool m_attackFlag = false;
	bool m_fireFlag = false;						//攻撃フラグ
	bool m_dashFlag = false;						//ダッシュしているかフラグ
	bool m_targetFlag = false;						//ターゲットを設定しているかどうかフラグ
	bool m_lockOn = false;							//プレイヤーをロックオンしているかどうか
	int m_setWeapon = 0;							//武器の種類
	int m_enemyDirState = 0;						//エネミーの向き
	int m_enemyGameState = 0;
	int m_attackCount = 0;							//攻撃の間隔
	int m_recoilCount = 300;						//反動の時間
	float m_distToPlayer;							//プレイヤーまでの距離
	float m_enemyHP = HP;							//エネミーの体力
	float m_distTarget;								//ターゲットまでの距離

};

