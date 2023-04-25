#pragma once
#include "sound/SoundSource.h"

class Boss;
class Boss_Shovel;
class Core_weapons;
class Player;

class Boss_Shovel_attack :public IGameObject
{
public:
	Boss_Shovel_attack();
	~Boss_Shovel_attack();

	void SetUp();
	void Update();
	void Move();
	void Render(RenderContext& rc);

	Boss_Shovel* b_a_weapons;
	Boss* b_a_boss;
	Core_weapons* b_a_core_weapons;
	Player* b_a_player;
	SoundSource* b_attack_SE;

	ModelRender b_a_Bullet;
	Quaternion b_a_aiming;
	Vector3 firing_position;
	Vector3 b_a_Bullet_Fowrad;
	Vector3 b_a_Bulet_weapons;
	Vector3 to_core_weapons;

	bool Landing_state = false;
	float move_speed = 30.0f;
	float fall_speed = 0.0f;
	bool attack_state = true;
	bool fast_count = true;
};