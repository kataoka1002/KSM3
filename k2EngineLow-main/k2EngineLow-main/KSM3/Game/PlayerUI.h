#pragma once
class Player;
class PlayerUI:public IGameObject
{
public:
	PlayerUI();
	~PlayerUI();
	bool Start();
	void Update();
	void Damage();
	void Render(RenderContext& rc);

	Player* m_player = nullptr;

	SpriteRender m_HPSprite;
	SpriteRender m_rightArmHPSprite;
	SpriteRender m_rightLegHPSprite;
	SpriteRender m_leftArmHPSprite;
	SpriteRender m_leftLegHPSprite;
	SpriteRender m_shoulderHPSprite;

	float m_sizeX = 1.0f;
	float UI_START_COLLAR_G = 1.0f;
	float UI_START_COLLAR_R = 0.0f;
};

