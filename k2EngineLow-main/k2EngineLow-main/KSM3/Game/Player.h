#pragma once
#include "Game.h"

class Customize_UI_ver2;
class Result;
class Game;
class GameCamera;
class Title;

class Player:public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();									//更新処理
	void Render(RenderContext& rc);					//描画処理
	void Move();									//移動処理
	void RunSE();									//ステート管理
	void pause();									//ポーズ画面
	void PauseSelect();
	void MakeSunabokoriEfe();						//砂ぼこりエフェクト再生
	void MakeEfe(EffectName name, Quaternion rot, Vector3 scale = Vector3::One, Vector3 pos = Vector3::Zero);
	void MachineGunSE();
	void PlayerDeadtoResult();
	void PlayerDead();
	void InitSprite();
	void InitModel();
	void InitSE();


	//getter関数----------------------------------------------------------------------


	/// <summary>
	/// 今のゲームステートを返す
	/// </summary>
	/// <returns>0:メインゲーム,1:ポーズ画面,2:リザルト,3:カスタマイズ,4:最初のシーン</returns>
	int GetGameState()
	{
		return m_gameState;
	}


	/// <summary>
	/// ゲームの終了判定を返す
	/// </summary>
	/// <returns>1ならゲーム終了</returns>
	int GetGameEndState()
	{
		return m_gameEndState;
	}


	/// <summary>
	/// ボス戦中かどうかを返す
	/// </summary>
	/// <returns>0：違う , 1：ボス戦</returns>
	int GetBossState()
	{
		return m_bossState;
	}


	/// <summary>
	/// プレイヤーが死んだかどうか
	/// </summary>
	/// <returns>false：生きている , true：死んでいる</returns>
	bool GetPlayerDead()
	{
		return m_playerDead;
	}


	/// <summary>
	/// 武器を取り付けている部分を調べる
	/// </summary>
	/// <param name="line">行</param>
	/// <param name="column">列</param>
	/// <returns>0 : 装備なし </returns>
	int GetCustomPoint(int line, int column)
	{
		return m_customPoint[line][column];
	}
	int GetCustomPoint(IntPair intPair)
	{
		return m_customPoint[intPair.first][intPair.second];
	}


	/// <summary>
	/// プレイヤーの前方向を返す
	/// </summary>
	/// <returns>プレイヤーの前方向</returns>
	Vector3 GetPlayerForward()
	{
		return m_playerForward;
	}


	/// <summary>
	/// プレイヤーが今いる位置を返す
	/// </summary>
	/// <returns>プレイヤーの今いる位置</returns>
	Vector3 GetPlayerPosition()
	{
		return m_playerPosition;
	}


	/// <summary>
	/// プレイヤーの回転を返す
	/// </summary>
	/// <returns>プレイヤーの回転量</returns>
	Quaternion GetPlayerRotation()
	{
		return m_playerRotation;
	}


	/// <summary>
	/// 死亡時の爆破エフェクトを再生したかどうか
	/// </summary>
	/// <returns>true：再生した , false：再生してない</returns>
	bool IsDeadBakuhaPlay()
	{
		return m_deadBakuhaPlay;
	}


	/// <summary>
	/// 殺したエネミーの数を返す
	/// </summary>
	/// <returns></returns>
	int GetKillEnemyAmount()
	{
		return m_killEnemyAmountFont;
	}


	/// <summary>
	/// プレイヤーの今のHPを返す
	/// </summary>
	/// <returns></returns>
	float GetPlayerHP()
	{
		return m_playerHP;
	}


	/// <summary>
	/// プレイヤーのHPの最大値を返す
	/// </summary>
	/// <returns></returns>
	float GetPlayerHPMax()
	{
		return m_playerHPMax;
	}


	/// <summary>
	/// ランダムに選ばれたカラーを返す
	/// </summary>
	/// <returns></returns>
	int GetRandomColor()
	{
		return m_playerColorRandom;
	}



	/// <summary>
	/// キャラコンを返す
	/// </summary>
	/// <returns></returns>
	CharacterController& GetCharacterController()
	{
		return m_characterController;
	}


	//--------------------------------------------------------------------------------


	/// <summary>
	/// プレイヤーのポジションをセットする
	/// </summary>
	/// <param name="position">ポジション</param>
	void SetPosition(Vector3 position)
	{
		m_playerPosition = position;
	}


	/// <summary>
	/// 各部位に武器をセットしているかを教える
	/// </summary>
	/// <param name="line">行</param>
	/// <param name="column">列</param>
	/// <param name="weaponKind">武器の種類</param>
	void SetCustomPoint(int line, int column, int weaponKind)
	{
		m_customPoint[line][column] = weaponKind;
	}
	void SetCustomPoint(IntPair intPair, int weaponKind)
	{
		m_customPoint[intPair.first][intPair.second] = weaponKind;
	}


	/// <summary>
	/// プレイヤーのカラーをセットする
	/// </summary>
	/// <param name="colorData">カラーデータ</param>
	void SetPlayerColorData(int colorData)
	{
		m_playerColorData = colorData;
	}


	/// <summary>
	/// ゲームステートをセットする
	/// </summary>
	/// <param name="gameState">ゲームステート</param>
	void SetGameState(int gameState)
	{
		m_gameState = gameState;
	}


	/// <summary>
	/// ボスのステートを設定する
	/// </summary>
	/// <param name="bossState">ボスのステート</param>
	void SetBossState(int bossState)
	{
		m_bossState = bossState;
	}


	/// <summary>
	/// プレイヤーのHPを回復する
	/// </summary>
	/// <param name="recoveryAmount">回復量</param>
	void HealingHP(float recoveryAmount)
	{
		m_playerHP += recoveryAmount;

		m_playerHP = min(m_playerHP, m_playerHPMax);
	}


	/// <summary>
	/// プレイヤーにダメージを与える関数
	/// </summary>
	/// <param name="damage">ダメージ量</param>
	void ApplyDamage(float damage)
	{
		m_playerHP -= damage;

		m_playerHP = max(m_playerHP, 0.0f);
	}


	/// <summary>
	/// プレイヤーのポジションXに値を加える
	/// </summary>
	/// <param name="delta">増加量</param>
	void AddPositionX(float delta)
	{
		m_playerPosition.x += delta;
	}


	/// <summary>
	/// プレイヤーのポジションYに値を加える
	/// </summary>
	/// <param name="delta">増加量</param>
	void AddPositionY(float delta)
	{
		m_playerPosition.y += delta;
	}


	/// <summary>
	/// プレイヤーのポジションZに値を加える
	/// </summary>
	/// <param name="delta">増加量</param>
	void AddPositionZ(float delta)
	{
		m_playerPosition.z += delta;
	}


	/// <summary>
	/// キャラコンの位置を設定する
	/// </summary>
	/// <param name="position">ポジション</param>
	void SetCharacterControllerPosition(Vector3 position)
	{
		m_characterController.SetPosition(position);
	}


	/// <summary>
	/// 殺したエネミーの数を増やす
	/// </summary>
	void AddKillEnemyAmount()
	{
		m_killEnemyAmountFont++;
	}


private:

	Title* m_title = nullptr;
	Result* m_result = nullptr;
	Game* m_game = nullptr;
	SoundSource* m_machineGunSE = nullptr;			//マシンガンSE
	SoundSource* m_runSE = nullptr;					//足音SE
	SoundSource* m_walkSE = nullptr;				//足音SE
	SoundSource* m_kettei = nullptr;
	SoundSource* m_deadSE = nullptr;
	GameCamera* m_gameCamera = nullptr;

	std::unique_ptr<ModelRender> m_playerModel;					//モデルレンダー
	SpriteRender m_pouseSprite;				//pause画面用のスプライトレンダー
	SpriteRender m_playerDeadSprite;				//プレイヤーが死んだときのスプライトレンダー
	CharacterController m_characterController;		//キャラクターコントローラー
	Vector3 m_playerPosition = {0.0f,0.0f,-1000.0f};	//座標
	Vector3 m_playerMoveSpeed;						//移動速度
	Vector3 m_playerForward = { 0.0f, 0.0f, 1.0f };	//プレイヤーの正面ベクトル
	Quaternion m_playerRotation;						//クォータニオン

	int m_deadCount = 0;
	int m_gameState = 4;								//ゲームがどの状態かの管理(0メインゲーム,1ポーズ画面,2リザルト,3カスタマイズ,4最初のシーン)
	int m_gameEndState = 0;							//ゲームの終了判定
	int m_bossState = 0;								//ボス戦かどうか
	int m_effectCount = 0;							//エフェクト関係
	int m_killEnemyAmountFont = 0;								//敵を殺した数(10になるとウェーブが進む)
	int m_customPoint[2][3] = { {0,0,0},{0,0,0} };	//[0][0]右腕,[0][1]肩,[0][2]左腕,[1][0]右足,[1][2]左足
	int m_playerColorData = 0;
	int m_playerColorRandom = 0;
	float m_accelerator = 0;
	float m_brake = 0;
	float m_throttle = 0;
	float m_move;
	float m_playerHP = 500.0f;						//プレイヤーのHP
	float m_playerHPMax = 500.0f;					//プレイヤーのHPの最大値
	float m_deadSpriteColw = 0.0f;					//プレイヤー死亡時のスプライトの透明度
	bool m_cameraMove = false;						//カメラ切り替え中かどうか
	bool m_playerDead = false;						//プレイヤーが死んだかどうか
	bool m_playDeadSE = false;						//死亡音を鳴らしたかどうか
	bool m_deadBakuhaPlay = false;					//死亡時の爆破を発生させたか
};

