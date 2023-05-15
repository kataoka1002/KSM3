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
	Vector3 HPBerSend(Vector3 size, Vector3 scale);	//画像の移動量を求める
	void Render(RenderContext& rc);

	Enemy_Near* m_enemyNear = nullptr;
	Enemy* m_enemy = nullptr;
	Enemy_Far* m_enemyFar = nullptr;
	Player* m_player = nullptr;
	Game* m_game = nullptr;

	SpriteRender m_HPSprite;
	Vector2 m_position = Vector2::Zero;
	Vector3 HP_BER_SIZE = { 160.0f,80.0f,1.0f };	//スプライトのサイズ
	Vector3 m_scale = {1.0f,1.0f,1.0f};
};

