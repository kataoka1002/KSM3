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

//class Fade;

class Customize_UI_ver2;


//エフェクトの列挙
enum EffectName {
	enSunabokori,		//砂ぼこり
	enMasinganHibana,	//マシンガンから出る火花
	enHidan,			//被弾
	enTyakudan,			//弾が着弾した時
	enEnemyDead			//敵死亡時のエフェ
};

//サウンドの列挙
enum SoundName {
	enRunning,			//移動中の音
	enDash,				//ダッシュ中の音
	enMachineGun,		//マシンガン
	enGigatonCannon,	//ギガトンキャノン
	enButtleShipGun,	//戦艦砲
	enEnemyDeadSE			//敵死亡時のSE
};

class Game :public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);


	void AddDefeatedEnemyNumber()
	{
		m_numDefeatedEnemy++;
	}
	int						m_numEnemy = 0;					//エネミーの数。
	int						m_numDefeatedEnemy = 0;			//倒されたエネミーの数。

	bool					m_isWaitFadeout = false;

	Player* player;//プレイヤー
	Title* title;//タイトル
	Result* result;//リザルト
	Lighting* lighting;//ライティング
	
	Left_arm_weapons* s_left_arm_weapons;
	Drop_item* drop_item;
	BackGround* background;
	Core_weapons* core_weapons;
	GameCamera* gamecamera;
	Game_UI* game_ui;
	Enemy_HP_UI* e_h_ui;
	Boss* boss = nullptr;

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

};

