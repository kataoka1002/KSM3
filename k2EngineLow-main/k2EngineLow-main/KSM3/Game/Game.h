#pragma once
#include "LevelRender.h"
class BoxMove;
class Player; //�v���C���[
class Title;//�^�C�g��
class Result;//���U���g

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

	Player* player;//�v���C���[
	Title* title;//�^�C�g��
	Result* result;//���U���g

private:
	ModelRender m_modelRender;
	SpriteRender m_spriteRender;
	LevelRender m_levelRender;
	std::vector<BoxMove*> m_boxmoves;				//move�{�b�N�X
	FontRender m_fontRender;
	float m_timer = 0.0f;
	DirectionLight directionLight;

	Vector3 dv;
};

