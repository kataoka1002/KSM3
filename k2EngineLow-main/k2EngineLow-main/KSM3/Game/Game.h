#pragma once
#include "LevelRender.h"
class BoxMove;
class Player; //プレイヤー
class Title;//タイトル
class Result;//リザルト

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

private:
	ModelRender m_modelRender;
	SpriteRender m_spriteRender;
	LevelRender m_levelRender;
	std::vector<BoxMove*> m_boxmoves;				//moveボックス
	FontRender m_fontRender;
	float m_timer = 0.0f;
	DirectionLight directionLight;

	Vector3 dv;
};

