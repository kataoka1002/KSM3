#pragma once

class Player;
class Left_arm_weapons;
class Right_arm_weapons;
class CollisionObject;

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
	Right_arm_weapons* b_s_right_arm_weapons;

	ModelRender B_S_Bullet;
	Quaternion B_S_aiming;
	Vector3 firing_position;
	Vector3 B_S_Bullet_Fowrad; 
	CollisionObject* b_s_collisionObject = nullptr;

	bool Landing_state_BB = false;
	float move_speed = 30.0f;
	float fall_speed = 0.0f;

	
};

