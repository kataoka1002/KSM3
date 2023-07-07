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

	Boss_Shovel* m_weapon;
	Boss* m_boss;
	Core_weapons* m_coreWeapon;
	Player* m_player;
	SoundSource* m_attackSE;

	ModelRender m_bulletModel;
	Quaternion m_aim;
	Vector3 m_firePosition;
	Vector3 m_bulletForward;
	Vector3 iranran;
	Vector3 to_core_weapons;

	bool Landing_state = false;
	float move_speed = 30.0f;
	float m_fallSpeed = 0.0f;
	bool m_attackState = true;
	bool fast_count = true;
};