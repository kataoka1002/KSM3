#pragma once
#include "LevelRender.h"
class BoxMove;

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

private:
	ModelRender m_modelRender;
	ModelRender m_modelRender2;
	ModelRender m_modelRender3;
	SpriteRender m_spriteRender;
	LevelRender m_levelRender;
	std::vector<BoxMove*> m_boxmoves;				//move�{�b�N�X
	FontRender m_fontRender;
	float m_timer = 0.0f;
	Vector3 ptPosition = { 0.0f,30.0f,0.0f };
};

