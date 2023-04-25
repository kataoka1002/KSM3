#pragma once
#include "sound/SoundSource.h"

class Core_weapons;
class Enemy;
class Player;

class Enemy_Bullet:public IGameObject
{
public:
	Enemy_Bullet();
	~Enemy_Bullet();

	void Setup();
	void Update();
	void Move();
	bool Start();
	void Render(RenderContext& rc);

	Core_weapons* m_coreWeapons;
	Enemy* m_enemy;
	Player* m_player; 
	SoundSource* m_soundSource;

	ModelRender m_bulletModel;
	Quaternion m_aim;
	Vector3 m_position;
	Vector3 m_bulletFowrad;
	Vector3 m_toCoreWeapons;

	float m_bulletSpeed = 30.0f;
	float m_fallSpeed = 0.0f;
	bool m_attuckState = true;
	bool fast_count = true;
	bool Landing_state = false;
};

