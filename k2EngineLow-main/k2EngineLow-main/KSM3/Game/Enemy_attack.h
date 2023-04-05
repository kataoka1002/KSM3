#pragma once
#include "sound/SoundSource.h"

class Enemy_weapons;
class Core_weapons;
class Enemy;
class Player;

class Enemy_attack:public IGameObject
{
public:
	Enemy_attack();
	~Enemy_attack();

	void Setup();
	void Update();
	void Move();
	void Render(RenderContext& rc);

	Enemy_weapons* e_a_enemy_weapons;
	Core_weapons* e_a_core_weapons;
	Enemy* e_a_enemy;
	Player* e_a_player; 
	SoundSource* e_atack_SE;

	ModelRender e_a_Bullet;
	Quaternion e_a_aiming;
	Vector3 firing_position;
	Vector3 e_a_Bullet_Fowrad;
	Vector3 to_core_weapons;

	bool Landing_state = false;
	float move_speed = 30.0f;
	float fall_speed = 0.0f;
	bool atack_state = true;
	bool fast_count = true;
};

