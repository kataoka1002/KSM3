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

enum EffectName {
	enSunabokori,		//砂ぼこり
	enMasinganHibana	//マシンガンから出る火花
};


class Game :public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	enum EnAnimationClip {
		enAnimClip_Idle,
		enAnimClip_Num,
	};
	AnimationClip animationClips[enAnimClip_Num];

	void AddDefeatedEnemyNumber()
	{
		m_numDefeatedEnemy++;
	}
	int						m_numEnemy = 0;					//エネミーの数。
	int						m_numDefeatedEnemy = 0;			//倒されたエネミーの数。

	Player* player;//プレイヤー
	Title* title;//タイトル
	Result* result;//リザルト
	Lighting* lighting;//ライティング
	
	Left_arm_weapons* s_left_arm_weapons;
	Drop_item* drop_item;
	BackGround* background;
	Core_weapons* core_weapons;
	GameCamera* gamecamera;
	Boss* boss;
	Boss_Riser* boss_riser;
	Game_UI* game_ui;
	Enemy_HP_UI* e_h_ui;

	std::vector<Enemy*>	m_enemyObject;
	std::vector<Enemy_Far*> m_enemyFarObject;
	std::vector<Enemy_Near*>m_enemyNearObject;
	

	
	Vector3 dv;

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

