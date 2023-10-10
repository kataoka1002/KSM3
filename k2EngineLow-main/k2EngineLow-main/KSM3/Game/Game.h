#pragma once
#include "LevelRender.h"
#include "PushButton.h"
class Player;		//プレイヤー
class Title;		//タイトル
class Result;		//リザルト
class Lighting;		//ライティング
class Enemy_Near;
class Enemy;		//エネミー
class Enemy_Far;
class Drop_item;
class BackGround;
class Core_weapons;
class GameCamera;
class Boss;
class Enemy_HP_UI;
class SoundManage;
class PlayerUI;
class Customize_UI_ver2;
class Wave;
class Title;
class GuideLight;
class Combo;
class Customize_area;

/// <summary>
/// int型を2つ保存するクラス
/// </summary>
class IntPair {
public:
	int first;
	int second;

	// コンストラクタ（初期化リストを使用）
	IntPair(int a = 0, int b = 0) : first(a), second(b) {}
};


/// <summary>
/// カスタムポイントのナンバー
/// </summary>
namespace
{
	const IntPair NON = { -1,-1 };

	const IntPair RECOVERY = { 9,9 };

	const IntPair RIGHT_ARM = { 0,0 };
	const IntPair RIGHT_LEG = { 1,0 };
	const IntPair LEFT_ARM = { 0,2 };
	const IntPair LEFT_LEG = { 1,2 };
	const IntPair SHOULDER = { 0,1 };
}

/// <summary>
/// //部位のナンバー
/// </summary>
namespace 
{
	const int RIGHT_ARM_NUM = 1;
	const int RIGHT_LEG_NUM = 2;
	const int LEFT_ARM_NUM = 3;
	const int LEFT_LEG_NUM = 4;
	const int SHOULDER_NUM = 5;
}

/// <summary>
/// 武器のナンバー
/// </summary>
namespace
{
	const int NO_WEAPON_NUM = 0;
	const int GIGAPLASMA_NUM = 1;
	const int MACHINEGUN_NUM = 2;
	const int HELLFIRE_NUM = 3;
	const int GIGATONCANNON_NUM = 4;
	const int MISSILE_NUM = 5;
	const int BATTLESHIPGUN_NUM = 6;
}


/// <summary>
/// ゲームステートのナンバー
/// </summary>
namespace
{
	const int MAIN_GAME_NUM = 0;
	const int PAUSE_NUM = 1;
	const int RESULT_NUM = 2;
	const int CUSTOMIZE_NUM = 3;
	const int OP_NUM = 4;
}


/// <summary>
/// エフェクトの名前
/// </summary>
enum EffectName 
{
	enSunabokori,				//砂ぼこり
	enMasinganHibana,			//マシンガンから出る火花
	enHidan,					//被弾
	enTyakudan,					//弾が着弾した時
	enEnemyDead,				//敵死亡時のエフェ
	enSenkanhouKemuri,			//戦艦砲の弾の煙
	enMasinganKemuri,			//マシンガンの弾の煙
	enGigatonAttack,			//ギガトンキャノンの攻撃エフェ
	enEnemyHassei,				//エネミーが生成されるときの魔法陣
	enBoss_Cannon_Charge,		//ボスのcannonの攻撃のChargeエフェ
	enBoss_Cannon_Landing,		//ボスのキャノンの攻撃着弾エフェ
	enBoss_Magic_Circle,		//ボスのエフェ1(魔法陣)
	enBoss_Cannon_Bullet,		//ボスの弾丸エフェ
	enGuide,					//ボス戦へのガイド光
	enBoss_Dozar_Charge,		//ボスドーザーの攻撃Charge
	enBoss_Dozar_efe,			//ボスドーザーの攻撃エフェ
	enBoss_Dozar_Landing,		//ボスドーザーの着弾エフェ
	enBoss_Explosion,			//ボスの破壊爆発エフェ
	enBoss_Explosion_Another,	//ボスの破壊ダメージエフェ
	enBoss_Death,				//ボスの死
	enBoss_Death2,				//ボスの死2
	enBoss_Drill,				//ボスドリルの攻撃エフェ
	enBoss_Drill_Landing,		//ボスドリルの着弾エフェ
	enBoss_Shovel_shock,		//ボスショベルのshockエフェ
	enTatumaki_charge,
	enTatumaki_fire,
	enImpact,
	enSword,					//プレイヤーが死んだときの剣
	enFeatherBall,
	en_Boss_attack,				//ボスの攻撃エフェ
	en_Boss_attack_Explosion	//ボス攻撃の爆発エフェ
};


/// <summary>
/// サウンドの名前
/// </summary>
enum SoundName 
{
	enRunning,					//移動中の音(プレイヤーもエネミーも)
	enDash,						//ダッシュ中の音(エネミーのみ)
	enMachineGun,				//マシンガン
	enGigatonCannon,			//ギガトンキャノン
	enButtleShipGun,			//戦艦砲
	enEnemyDeadSE,				//敵死亡時のSE
	enButtleShipTyakudan,		//戦艦砲の着弾SE
	enPlayerRun,				//プレイヤーの足音(速い方)
	enGameBGM,					//ゲーム中のBGM
	enBossBGM,					//ボス戦BGM
	enCustomizeBGM,				//カスタマイズ画面BGM
	enKetteiSE,					//決定音
	enCancelSE,					//キャンセル音
	enSentakuIdouSE,			//カーソル移動音
	enSoutyakuSE,				//装着音
	enByuSE,					//ドロップアイテム取得時の音
	enPlayerDead,				//プレイヤー死亡時の音
	enKetteiSE_Title,			//決定音(Title用のトラックのため使用しないで)
	enCancelSE_Title,			//キャンセル音(Title用のトラックのため使用しないで)
	enSentakuIdouSE_Title,		//カーソル移動音(Title用のトラックのため使用しないで)
	enStartSE,					//Titleのスタートの音(Title用のトラックのため使用しないで)
	enResultBGM,				//リザルトのBGM
	enVoice,					//登場シーンの音声
	enPutun,					//プツン音
	enTatumaki,
	enBisi,						//エネミーのビシッの音
	enBoss_Cannon_Charge_SE,	//ボスキャノンのCharge音
	enBoss_Shovel_roar,			//ボスショベルの吠える
	en_Boss_Drill,				//ボスドリル音
	en_Boss_Drill_sonic,		//ボスDrill通過
	en_Boss_Dozar_Charge_SE,	//ボスドーザーチャージ
	en_Boss_Shovel_shock,		//ボスショベル衝撃
	en_Boss_cannon_Langing_SE,	//ボスキャノン着弾
	en_Boss_Dozar_Langing_SE,	//ボスドーザー着弾
	en_PushButton				//ボタンを押せ
};

class Game :public IGameObject, Noncopyable
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void GameNow();
	void TitleToGame();
	void SetUp();
	void MakePlayerUI();
	void MakeEnemy();
	void DeleteEnemy();
	Vector3 RandomPosition();
	void Render(RenderContext& rc);
	void InitEffect();
	void InitSound();


	/// <summary>
	/// エネミーのオブジェクトをリストから消す
	/// </summary>
	/// <param name="enemy">消したいエネミーのポインタ</param>
	void RemoveEnemyFromList(Enemy* enemy)
	{
		std::vector<Enemy*>::iterator it = std::find(
			m_enemyObject.begin()	//エネミーのリストの最初
			, m_enemyObject.end()	//エネミーのリストの最後
			,enemy);				//探しているエネミー

		if (it != m_enemyObject.end()) {
			m_enemyObject.erase(it);
		}
	}


	/// <summary>
	/// エネミーのオブジェクトをリストから消す
	/// </summary>
	/// <param name="enemyNear">消したいエネミーのポインタ</param>
	void RemoveEnemyNearFromList(Enemy_Near* enemyNear)
	{
		std::vector<Enemy_Near*>::iterator it = std::find(
			m_enemyNearObject.begin()
			, m_enemyNearObject.end()
			, enemyNear);

		if (it != m_enemyNearObject.end()) {
			m_enemyNearObject.erase(it);
		}
	}


	/// <summary>
	/// エネミーのオブジェクトをリストから消す
	/// </summary>
	/// <param name="enemyFar">消したいエネミーのポインタ</param>
	void RemoveEnemyFarFromList(Enemy_Far* enemyFar)
	{
		std::vector<Enemy_Far*>::iterator it = std::find(
			m_enemyFarObject.begin()
			, m_enemyFarObject.end()
			, enemyFar);

		if (it != m_enemyFarObject.end()) {
			m_enemyFarObject.erase(it);
		}
	}


	/// <summary>
	/// ドロップアイテムのオブジェクトをリストから消す
	/// </summary>
	/// <param name="dropItem">消したいドロップアイテムのポインタ</param>
	void RemoveDropItemFromList(Drop_item* dropItem)
	{
		std::vector<Drop_item*>::iterator it = std::find(
			m_dropItemObject.begin()
			, m_dropItemObject.end()
			, dropItem);

		if (it != m_dropItemObject.end()) {
			m_dropItemObject.erase(it);
		}
	}


	/// <summary>
	/// 死んだエネミーの数を増やす
	/// </summary>
	void AddDefeatedEnemyNumber()
	{
		m_numDefeatedEnemy++;
	}

	//ボタンを押せを生成
	void SetPushButton()
	{
		m_pushButton = NewGO<PushButton>(0, "pushbutton");
	}
	void SetOffPushButton()
	{
		DeleteGO(m_pushButton);
		m_pushButton = nullptr;
	}
	void PlayNiziButton()
	{
		m_pushButton->SetNiziButtonFlag();
	}

	//時止め系
	void StopWorld()
	{
		m_isStopWorld = true;
	}
	void ReStartWorld()
	{
		m_isStopWorld = false;
	}
	bool IsStopWorld() const
	{
		return m_isStopWorld;
	}


	//getter関数------------------------------------------------------------------


	/// <summary>
	/// エネミーのオブジェクトを返す
	/// </summary>
	/// <returns>エネミーのオブジェクト</returns>
	const std::vector<Enemy*>& GetEnemyObject() const
	{
		return m_enemyObject;
	}


	/// <summary>
	/// エネミーのオブジェクトを返す
	/// </summary>
	/// <returns>エネミーのオブジェクト</returns>
	const std::vector<Enemy_Far*>& GetEnemyFarObject() const
	{
		return m_enemyFarObject;
	}


	/// <summary>
	/// エネミーのオブジェクトを返す
	/// </summary>
	/// <returns>エネミーのオブジェクト</returns>
	const std::vector<Enemy_Near*>& GetEnemyNearObject() const
	{
		return m_enemyNearObject;
	}


	/// <summary>
	/// ドロップアイテムのオブジェクトを返す
	/// </summary>
	/// <returns>ドロップアイテムのオブジェクト</returns>
	const std::vector<Drop_item*>& GetDropItemObject() const
	{
		return m_dropItemObject;
	}

	void PushDropItem(Drop_item* item)
	{
		m_dropItemObject.push_back(item);
	}

	/// <summary>
	/// ボスのポインタを返す
	/// </summary>
	/// <returns>ボスのポインタ</returns>
	Boss* GetBoss() const
	{
		return m_boss;
	}


	/// <summary>
	/// BGMの音量を返す
	/// </summary>
	/// <returns>BGMの音量</returns>
	float GetBGMVol() const
	{
		return m_BGMvol;
	}


	/// <summary>
	/// SEの音量を返す
	/// </summary>
	/// <returns>SEの音量</returns>
	float GetSEVol() const
	{
		return m_SEvol;
	}


	/// <summary>
	/// セーブしたSEの音量を返す
	/// </summary>
	/// <returns>セーブしたSEの音量</returns>
	float GetSaveSEvol() const
	{
		return m_saveSEvol;
	}


	/// <summary>
	/// エネミーの数を返す
	/// </summary>
	/// <returns>エネミーの数</returns>
	int GetEnemyNum() const
	{
		return m_numEnemy;
	}

	/// <summary>
	/// 死んだエネミーの数を返す
	/// </summary>
	/// <returns>死んだエネミーの数</returns>
	int GetDefeatedEnemyNum() const
	{
		return m_numDefeatedEnemy;
	}

	//----------------------------------------------------------------------------


	//setter関数------------------------------------------------------------------


	/// <summary>
	/// SEの音量をセットする
	/// </summary>
	/// <param name="vol">新しい音量</param>
	void SetSEVol(float vol)
	{
		m_SEvol = vol;

		m_SEvol = max(m_SEvol, 0.0f);
	}


	/// <summary>
	/// BGMの音量をセットする
	/// </summary>
	/// <param name="vol">新しい音量</param>
	void SetBGM(float vol)
	{
		m_BGMvol = vol;

		m_BGMvol = max(m_BGMvol, 0.0f);
	}


	/// <summary>
	/// プレイヤーカラーのデータをセットする
	/// </summary>
	/// <param name="col">プレイヤーカラーデータ</param>
	void SetPlayerColorData(int col)
	{
		m_playerColorDate = col;
	}


	//----------------------------------------------------------------------------

private:
	Player*				m_player = nullptr;			
	Title*				m_title = nullptr;			
	Lighting*			m_lighting = nullptr;		
	SoundManage*		m_soundManage = nullptr;
	Drop_item*			m_dropItem = nullptr;
	BackGround*			m_backGround = nullptr;
	Core_weapons*		m_coreWeapon = nullptr;
	GameCamera*			m_gameCamera = nullptr;
	Boss*				m_boss = nullptr;
	PlayerUI*			m_playerUI = nullptr;
	Wave*				m_wave = nullptr;
	SkyCube*			m_skyCube = nullptr;
	GuideLight*			m_guide = nullptr;
	Combo*				m_combo = nullptr;
	Customize_UI_ver2*	m_customizeUI = nullptr;
	Customize_area*		m_customizeArea = nullptr;
	PushButton*			 m_pushButton = nullptr;


	std::vector<Enemy*>			m_enemyObject;
	std::vector<Enemy_Far*>		m_enemyFarObject;
	std::vector<Enemy_Near*>	m_enemyNearObject;
	std::vector<Drop_item*>		m_dropItemObject;

	float	m_BGMvol			= 1.0f;		//こいつらを音量にかけてやることで調整する
	float	m_SEvol				= 1.0f;		//こいつらを音量にかけてやることで調整する
	float	m_saveSEvol			= 0.0f;		//効果音の大きさを保存しておく変数
	int		m_playerColorDate	= 0;		//プレイヤーのカラーデータ
	int		m_numEnemy			= 0;		//エネミーの数。
	int		m_numDefeatedEnemy	= 0;		//倒されたエネミーの数。
	bool    m_isStopWorld		= false;	//時が止まっているかどうか
};

