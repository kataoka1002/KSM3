#pragma once
class Player;
class Core_weapons;
class Enemy;


class Core_weapons_attack:public IGameObject
{
public:
	Core_weapons_attack();
	~Core_weapons_attack();

	void Setup();
	void Update();
	void Move();
	void Render(RenderContext& rc);

	Player* C_W_A_player;
	Core_weapons* C_W_A_core_weapons;
	Enemy* c_w_a_enemy;

	ModelRender C_W_Bullet;
	Quaternion C_W_aiming;
	Vector3 firing_position;
	Vector3 C_W_Bullet_Fowrad;

	bool Landing_state_cw = false;
	float move_speed = 30.0f;
	float fall_speed = 0.0f;
	bool stack_state = true;

	float damage_volume = 0.0f;
};

