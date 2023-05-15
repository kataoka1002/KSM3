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

	float m_sizeX = 1.0f;
};

