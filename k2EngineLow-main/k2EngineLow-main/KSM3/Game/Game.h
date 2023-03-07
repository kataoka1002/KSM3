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
	ModelRender m_modelRender;		//キャラ
	ModelRender m_modelRender2;		//床
	ModelRender m_modelRender3;		//ライト
	SpriteRender m_spriteRender;
	LevelRender m_levelRender;
	std::vector<BoxMove*> m_boxmoves;				//moveボックス
	FontRender m_fontRender;
	float m_timer = 0.0f;
	Vector3 ptPosition = { 0.0f,30.0f,0.0f };
	Quaternion rot;
	Vector3 groundColor = { 0.7f,0.5f,0.3f };
	Vector3 skyColor = { 0.3f,0.3f,0.7f };
	Vector3 groundNormal = { 0.0f,1.0f,0.0f };
};

