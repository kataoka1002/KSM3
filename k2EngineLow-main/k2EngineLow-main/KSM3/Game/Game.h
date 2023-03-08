#pragma once
#include "LevelRender.h"
class BoxMove;
class Player; //プレイヤー
class Title;//タイトル
class Result;//リザルト
class Lighting;//ライティング

class Game:public IGameObject
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

};

