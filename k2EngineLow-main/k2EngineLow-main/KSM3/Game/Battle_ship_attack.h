#pragma once

class Player;
class Left_arm_weapons;

class Battle_ship_attack :public IGameObject
{
public:
	Battle_ship_attack();
	~Battle_ship_attack();

	void Setup();
	void Update();
	void Move();
	void Render(RenderContext& rc);

	Player* b_s_attack_player;
	Left_arm_weapons* b_s_left_arm_weapons;

	ModelRender B_S_Bullet;
	Quaternion B_S_aiming;
	Vector3 firing_position;
	Vector3 B_S_Bullet_Fowrad;

	bool Landing_state_BB = false;
	int move_speed=100.0f;
	float fall_speed = 10.0f;
};

