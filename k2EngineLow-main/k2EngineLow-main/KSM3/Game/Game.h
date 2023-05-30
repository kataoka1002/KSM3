#pragma once
#include "LevelRender.h"
//class BoxMove;
class Player;		//プレイヤー
class Title;		//タイトル
class Result;		//リザルト
class Lighting;		//ライティング
class Enemy_Near;
class Enemy;		//エネミー
class Enemy_Far;
class Left_arm_weapons;
class Drop_item;
class BackGround;
class Core_weapons;
class GameCamera;
//class Test;
class Boss;
class Boss_Riser;
class Game_UI;
class Enemy_HP_UI;
class SoundManage;
//class Fade;
class PlayerUI;
class Customize_UI_ver2;
class Wave;
class Title;
class GuideLight;
class Combo;


//エフェクトの列挙
enum EffectName {
	enSunabokori,		//砂ぼこり
	enMasinganHibana,	//マシンガンから出る火花
	enHidan,			//被弾
	enTyakudan,			//弾が着弾した時
	enEnemyDead,		//敵死亡時のエフェ
	enSenkanhouKemuri,	//戦艦砲の弾の煙
	enMasinganKemuri,	//マシンガンの弾の煙
	enGigatonAttack,	//ギガトンキャノンの攻撃エフェ
	enEnemyHassei,

	enBoss_Cannon_Charge,  //ボスのcannonの攻撃のChargeエフェ
	enBoss_Cannon_Landing, //ボスのキャノンの攻撃着弾エフェ
	enBoss_Magic_Circle,		//ボスのエフェ1(魔法陣)
	enBoss_Cannon_Bullet,   //ボスの弾丸エフェ

	enGuide,
	enBoss_Dozar_Charge,	//ボスドーザーの攻撃Charge
	enBoss_Dozar_efe,		//ボスドーザーの攻撃エフェ
	enBoss_Dozar_Landing,	//ボスドーザーの着弾エフェ
	enBoss_Explosion,		//ボスの破壊爆発エフェ
	enBoss_Explosion_Another,//ボスの破壊ダメージエフェ
	enBoss_Death,			//ボスの死
	enBoss_Death2,			//ボスの死2
	enBoss_Drill,			//ボスドリルの攻撃エフェ
	enBoss_Drill_Landing,	//ボスドリルの着弾エフェ
	enBoss_Shovel_shock,		//ボスショベルのshockエフェ
	enTatumaki_charge,
	enTatumaki_fire,
	enImpact,
	enSword,				//プレイヤーが死んだときの剣
	enFeatherBall
};

//サウンドの列挙
enum SoundName {
	enRunning,				//移動中の音(プレイヤーもエネミーも)
	enDash,					//ダッシュ中の音(エネミーのみ)
	enMachineGun,			//マシンガン
	enGigatonCannon,		//ギガトンキャノン
	enButtleShipGun,		//戦艦砲
	enEnemyDeadSE,			//敵死亡時のSE
	enButtleShipTyakudan,	//戦艦砲の着弾SE
	enPlayerRun,			//プレイヤーの足音(速い方)
	enGameBGM,				//ゲーム中のBGM
	enBossBGM,				//ボス戦BGM
	enCustomizeBGM,			//カスタマイズ画面BGM
	enKetteiSE,				//決定音
	enCancelSE,				//キャンセル音
	enSentakuIdouSE,		//カーソル移動音
	enSoutyakuSE,			//装着音
	enByuSE,				//ドロップアイテム取得時の音
	enPlayerDead,			//プレイヤー死亡時の音
	enKetteiSE_Title,		//決定音(Title用のトラックのため使用しないで)
	enCancelSE_Title,		//キャンセル音(Title用のトラックのため使用しないで)
	enSentakuIdouSE_Title,	//カーソル移動音(Title用のトラックのため使用しないで)
	enStartSE,				//Titleのスタートの音(Title用のトラックのため使用しないで)
	enResultBGM,			//リザルトのBGM
	enVoice,				//登場シーンの音声
	enPutun,				//プツン音
	enTatumaki,
	enBisi					//エネミーのビシッの音
};

class Game :public IGameObject
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
	void create_player(int player_color_date);

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

	void AddDefeatedEnemyNumber()
	{
		m_numDefeatedEnemy++;
	}

	int						m_numEnemy = 0;					//エネミーの数。
	int						m_numDefeatedEnemy = 0;			//倒されたエネミーの数。

	bool					m_isWaitFadeout = false;

	Player* player = nullptr;			//プレイヤー
	Title* title = nullptr;			//タイトル
	Result* result = nullptr;			//リザルト
	Lighting* lighting = nullptr;		//ライティング
	SoundManage* m_soundManage = nullptr;
	Left_arm_weapons* s_left_arm_weapons = nullptr;
	Drop_item* drop_item = nullptr;
	BackGround* background = nullptr;
	Core_weapons* core_weapons = nullptr;
	GameCamera* gamecamera = nullptr;
	Game_UI* game_ui = nullptr;
	Enemy_HP_UI* e_h_ui = nullptr;
	Boss* boss = nullptr;
	PlayerUI* m_playerUI = nullptr;
	Wave* m_wave = nullptr;
	SkyCube* m_skyCube = nullptr;
	GuideLight* m_guide = nullptr;
	Combo* m_combo = nullptr;

	//Fade* m_fade = nullptr;		//フェード。

	//std::vector<Boss*>m_bossObject;
	//std::vector<Boss_Riser*>m_riserObject;

	Customize_UI_ver2* m_customizeUI;

	std::vector<Enemy*>	m_enemyObject;
	std::vector<Enemy_Far*> m_enemyFarObject;
	std::vector<Enemy_Near*> m_enemyNearObject;
	std::vector<Drop_item*> m_dropItemObject;
	Vector3 dv;

	//int Loading_count = 0;
	float BGMvol = 1.0f;	//こいつらを音量にかけてやることで調整する
	float SEvol = 1.0f;
	float SaveSEvol = 0.0f;

	int player_color_date = 0;//プレイヤーのカラーデータ
private:
	//ModelRender m_modelRender;		//キャラ
	//ModelRender m_modelRender2;		//床
	//ModelRender m_modelRender3;		//ライト
	//SpriteRender m_spriteRender;
	//LevelRender m_levelRender;
	//std::vector<BoxMove*> m_boxmoves;				//moveボックス
	//FontRender m_fontRender;
	float m_timer = 0.0f;

	//Test* test;

	int m_gameStartState = 0;	//ロード画面からゲームへの遷移

	
};

