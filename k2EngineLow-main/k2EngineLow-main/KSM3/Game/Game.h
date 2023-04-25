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

	Player* player;//プレイヤー
	Title* title;//タイトル
	Result* result;//リザルト
	Lighting* lighting;//ライティング
	Enemy_Near*enemy_near[2];
	Enemy* enemy[2];//エネミー
	Enemy_Far* enemy_far[2];
	Left_arm_weapons* s_left_arm_weapons;
	Drop_item* drop_item;
	BackGround* background;
	Core_weapons* core_weapons;
	GameCamera* gamecamera;

	

	
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

