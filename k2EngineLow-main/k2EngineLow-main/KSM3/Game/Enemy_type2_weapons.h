#pragma once
class Player;
class Enemy;
class Enemy_attack;

class Enemy_type2_weapons :public IGameObject
{
public:
	Enemy_type2_weapons();
	~Enemy_type2_weapons();

	void Setup();
	void Update();
	void Move();
	void Render(RenderContext& rc);

	Player* e_w_player;
	Enemy* e_w_enemy;
	Enemy_attack* enemy_attack;

	Quaternion e_w_Rotation;
	Vector3 e_w_position;
	Vector3 e_w_moveSpeed;
	Vector3 e_w_Fowrad = { 0.0f,0.0f,1.0f };
	int game_state = 0;
	ModelRender Enemy_weapons_Render;

	Vector3 e_w_localposition = { 0.0f,90.0f,00.0f };

	bool atack_state = false;
	bool atack_ok = false;
	int set_weapons = 0;

	int firing_cound = 0;
	int fast = 0;
};

