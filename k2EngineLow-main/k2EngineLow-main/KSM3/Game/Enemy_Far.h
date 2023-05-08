#pragma once
#define HP 200.0f

class Player;
class Battle_ship_attack;
class Drop_item;
class Game;

class Enemy_Far :public IGameObject
{
public:

	//パス移動用
	struct Point {
		Vector3 m_position;	//ポイントの座標
		int m_num;			//ポイントの番号
	};

	Enemy_Far();
	~Enemy_Far();

	bool Start();
	void Update();					//更新処理
	void Render(RenderContext& rc);	//描画処理
	void Move();					//移動処理
	void PlayerSearch();			//索敵処理
	void ItemDrop();				//アイテムドロップ
	void WeaponMove();				//離れる処理
	void SetUp();					//武器セット
	void Attack();					//武器を選んで攻撃
	void Fire(int m_weaponNum);		//発射
	void PassMove();				//パス移動
	void Damage();					//被弾
	void Effect();					//エフェクト
	void SE();						//効果音

	//パス移動に必要な奴ら
	std::vector<Point> m_pointList;
	Point* m_point = nullptr;

	Game* m_game = nullptr;
	Player* m_player = nullptr;
	Battle_ship_attack* m_battleShipAttack = nullptr;
	Drop_item* m_dropItem = nullptr;
	EffectEmitter* sunabokoriEffect = nullptr;
	SoundSource* m_battleshipGunSE = nullptr;			//マシンガンSE
	SoundSource* m_asiotoSE = nullptr;					//足音
	SoundSource* m_battleShipGunSE = nullptr;			//戦艦砲SE


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

	bool m_defeatState = false;						//死んだかどうかフラグ
	bool m_enemyEscape = false;						//後退中かどうかフラグ
	bool m_atackOK = false;							//攻撃フラグ
	bool m_lockOn = false;
	int m_setWeapon = 0;							//武器の種類
	int m_enemyDirState = 0;						//エネミーの向き
	int m_enemyGameState = 0;
	int m_attackCount = 0;							//攻撃の間隔
	int m_sunaHassei = 0;							//砂ぼこりの発生間隔
	float m_distToPlayer;							//プレイヤーまでの距離
	float m_enemyHP = HP;							//エネミーの体力
};

