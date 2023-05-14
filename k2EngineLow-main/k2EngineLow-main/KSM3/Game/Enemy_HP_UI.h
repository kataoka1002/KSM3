#pragma once
class Enemy_Near;
class Enemy;
class Enemy_Far;
class Player;
class Game;

class Enemy_HP_UI:public IGameObject
{
public:
	Enemy_HP_UI();
	~Enemy_HP_UI();
	bool Start();
	void Update();
	void SetPosition();
	void Damage();
	void Render(RenderContext& rc);

	Enemy_Near* m_enemyNear = nullptr;
	Enemy* m_enemy = nullptr;
	Enemy_Far* m_enemyFar = nullptr;
	Player* m_player = nullptr;
	Game* m_game = nullptr;

	SpriteRender m_HPSprite;
	Vector2 m_position = Vector2::Zero;
	Vector3 m_scale = Vector3::Zero;

	float m_sizeX = 0.0f;
};

