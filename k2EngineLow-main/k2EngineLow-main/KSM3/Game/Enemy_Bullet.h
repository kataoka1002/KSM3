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

	Enemy* m_enemyMama = nullptr;

	ModelRender m_bulletModel;
	Quaternion m_aim;
	Quaternion m_rot;
	Quaternion originRotation;
	Vector3 m_position;
	Vector3 m_bulletFowrad;
	Vector3 m_toCoreWeapons;
	Vector3 m_bulletSpeed;
	Vector3 m_macineGunLocalPosition;	//マシンガンの弾のローカルポジション
	float m_fallSpeed = 0.0f;
	bool m_attuckState = true;
	bool Landing_state = false;

	
};

