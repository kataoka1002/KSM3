#pragma once
#include "LevelRender.h"
class BoxMove;
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
class Test;
class Boss;
class Boss_Riser;
class Game_UI;
class Enemy_HP_UI;
class SoundManage;
//class Fade;
class PlayerUI;
class Customize_UI_ver2;


//エフェクトの列挙
enum EffectName {
	enSunabokori,		//砂ぼこり
	enMasinganHibana,	//マシンガンから出る火花
	enHidan,			//被弾
	enTyakudan,			//弾が着弾した時
	enEnemyDead,		//敵死亡時のエフェ
	enSenkanhouKemuri,	//戦艦砲の弾の煙
	enMasinganKemuri,	//マシンガンの弾の煙
	enGigatonAttack		//ギガトンキャノンの攻撃エフェ
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
	enByuSE					//ドロップアイテム取得時の音
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
	void Render(RenderContext& rc);


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

	//Fade* m_fade = nullptr;		//フェード。

	//std::vector<Boss*>m_bossObject;
	//std::vector<Boss_Riser*>m_riserObject;

	Customize_UI_ver2* m_customizeUI;

	std::vector<Enemy*>	m_enemyObject;
	std::vector<Enemy_Far*> m_enemyFarObject;
	std::vector<Enemy_Near*> m_enemyNearObject;
	std::vector<Drop_item*> m_dropItemObject;
	float boss_time = 0.0f;
	float boss_time_score = 0.0f;
	int time_score = 10000;
	Vector3 dv;

	float BGMvol = 1.0f;	//こいつらを音量にかけてやることで調整する
	float SEvol = 1.0f;

private:
	ModelRender m_modelRender;		//キャラ
	ModelRender m_modelRender2;		//床
	ModelRender m_modelRender3;		//ライト
	SpriteRender m_spriteRender;
	LevelRender m_levelRender;
	std::vector<BoxMove*> m_boxmoves;				//moveボックス
	FontRender m_fontRender;
	float m_timer = 0.0f;

	Test* test;

	int m_gameStartState = 0;	//ロード画面からゲームへの遷移
};

