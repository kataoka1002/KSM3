#pragma once
#include "Game.h"
#include "GameCamera.h"

class Game;
class Player;
class Drop_item;
class GameCamera;
class Combo;
class Enemy_HP_UI;


class EnemyBase : public IGameObject, Noncopyable
{
public:

	//コンストラクタ
	EnemyBase(){}


	//デストラクタはバーチャルにしておく
	virtual ~EnemyBase(){}


	bool Start();
	void CalcDistance(float dist);				//引数はプレイヤーをロックオンするまでの距離
	void CalcSpeed(float speed,int dirState);	//移動速度計算
	void NormalAction(float dist);				//引数はプレイヤーをロックオンするまでの距離
	void MakePoint();							//パス移動用のポイントを生成
	Vector3 RandPos();							//ランダムなポジションを設定する
	void DustEffect();							//砂ぼこりエフェクト
	void ExecuteOnEnemyDefeated();				//死亡時の処理
	void ItemDrop();							//アイテムドロップ
	void WeaponSetUp();							//武器セット
	void WeaponMove();							//離れる処理
	void PassMove();							//パス移動
	void PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale);
	void AsiotoSEManage(bool play);
	void PushButton();
	void ToPushButton();

	//純粋仮想関数にして、派生クラスで実装する。
	virtual void GameSetUp()				= 0;	//ゲーム全般の初期化
	virtual void Update()					= 0;	//更新処理
	virtual void Render(RenderContext& rc)	= 0;	//描画処理
	virtual void Move()						= 0;	//移動処理
	virtual void PlayerSearch()				= 0;	//索敵処理
	virtual void Attack()					= 0;	//武器を選んで攻撃
	virtual void Fire(int m_weaponNum)		= 0;	//発射
	virtual void EnemyDead()				= 0;
	virtual void HPUnder0()					= 0;
	virtual void InitEnemyModel()			= 0;
	virtual void DeleteGoThis()             = 0;


	//getter関数-------------------------------------------------------------
	
	/// <summary>
	/// 回転量を返す
	/// </summary>
	/// <returns></returns>
	Quaternion GetRot() const
	{
		return m_enemyRotation;
	}

	/// <summary>
	/// 前方向を返す
	/// </summary>
	/// <returns></returns>
	Vector3 GetForward() const
	{
		return m_enemyForward;
	}

	
	/// <summary>
	/// ポジションを返す
	/// </summary>
	/// <returns></returns>
	Vector3 GetPos() const
	{
		return m_enemyPosition;
	}

	
	/// <summary>
	/// 取り付けている武器の種類を返す
	/// </summary>
	/// <returns></returns>
	int GetWeponKind() const
	{		
		return m_setWeapon;
	}
	

	/// <summary>
	/// 現在のHPを返す
	/// </summary>
	/// <returns></returns>
	float GetHP() const
	{
		return m_enemyHP;
	}
	

	/// <summary>
	/// HPの最大値を返す
	/// </summary>
	/// <returns></returns>
	float GetMaxHP() const
	{
		return m_enemyHPMax;
	}

	
	/// <summary>
	/// スピードを返す
	/// </summary>
	/// <returns></returns>
	float GetSpeed() const
	{
		return m_enemySpeed;
	}

	//-------------------------------------------------------------------------


	//setter関数---------------------------------------------------------------

	/// <summary>
	/// ダメージ処理
	/// </summary>
	/// <param name="damage">ダメージ量</param>
	void ApplyDamage(float damage)
	{

		//今のHPからダメージ分を引く
		m_enemyHP -= damage;


		//0.0f以下にならないようにする
		m_enemyHP = max(m_enemyHP, 0.0f);

	}

	/// <summary>
	/// ポジションをセット
	/// </summary>
	/// <param name="pos">新しいポジション</param>
	void SetPosition(Vector3 pos)
	{

		//新しいポジションをセット
		m_enemyPosition = pos;

	}

	//-------------------------------------------------------------------------


//派生クラスからアクセスできるようにprotectedにしておく
protected:

	/// <summary>
	/// パス移動用の構造体
	/// </summary>
	struct Point 
	{
		Vector3 m_position;	//ポイントの座標
		int m_num;			//ポイントの番号
	};
	//パス移動に必要な奴ら
	std::vector<Point> m_pointList;
	Point* m_point = nullptr;


	Game* m_game = nullptr;
	Player* m_player = nullptr;
	GameCamera* m_gameCamera = nullptr;
	Drop_item* m_dropItem = nullptr;
	Enemy_HP_UI* m_HPUI = nullptr;
	SoundSource* m_enemyDeadSE = nullptr;			//死んだときの爆破SE
	SoundSource* m_asiotoSE = nullptr;				//足音


	std::unique_ptr<ModelRender> m_enemyModel;						//エネミーモデル
	std::unique_ptr<ModelRender> m_enemyWeaponModel;					//武器モデル
	CharacterController m_enemyCharacterController;	//エネミーキャラコン
	Quaternion m_weaponRotation;					//武器クォータニオン
	Vector3 m_weaponPosition = Vector3::Zero;		//武器ポジション
	Vector3 m_weaponLocalPos = Vector3::Zero;		//武器ローカルポジション
	Vector3 m_toPlayer = Vector3::Zero;				//プレイヤーへのベクトル
	Vector3 m_toPlayerDir = Vector3::Zero;			//プレイヤーへの方向
	Vector3 m_enemyMoveSpeed = Vector3::Zero;		//エネミー移動速度
	Vector3 m_Up = { 0.0f,1.0f,0.0f };				//上方向の設定	


	bool m_lockOn = false;							//エネミーがパスのポイントをロックオンしているかどうか
	bool m_running = false;							//走っているかどうか
	bool m_asiotoPlay = false;						//足音がなっているかどうか
	int m_enemyDirState = 0;						//エネミーの向き
	int m_attackCount = 0;							//攻撃の間隔
	int m_sunaHassei = 0;							//砂ぼこりが発生する間隔
	float m_distToPlayer = 0;						//プレイヤーまでの距離


	//ここから、派生クラス外からいじられる変数
	Quaternion m_enemyRotation;						//エネミークォータニオン
	Vector3 m_enemyForward = Vector3::Zero;			//エネミーの正面ベクトル
	Vector3 m_enemyPosition = Vector3::Zero;		//エネミー座標
	int m_setWeapon = 0;							//武器の種類
	float m_enemyHP = 0;							//エネミーの体力
	float m_enemyHPMax = 0;							//エネミーの体力の最大値
	float m_enemySpeed = 0;							//エネミーの移動速度
	int m_pushTimer = 300;							//爆発するまでの時間
	bool m_deleteGoThisFlag = false;				//消される直前かどうか
};

