#pragma once
class Enemy;
class Player;
class BattleShipBullet;
class Game;
class GameCamera;

class Enemy_HP_UI:public IGameObject
{
public:
	Enemy_HP_UI();
	~Enemy_HP_UI();
	bool Start();
	void Update();
	void Enemy_HP_Position();
	void Render(RenderContext& rc);


	SpriteRender hp_render;
	Vector3 hp_position;
	Vector3 hp_scale;
	Vector3 hp_movespeed;
	Enemy* enemy;
	Player* player;
	BattleShipBullet* b_s_attack;
	Game* game;
	GameCamera* game_camera;
};

