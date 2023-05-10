#pragma once
#include "sound/SoundSource.h"

class Core_weapons;
class Enemy;
class Enemy_Near;
class Enemy_Far;
class Player;
class Game;

class Enemy_Bullet:public IGameObject
{
public:
	Enemy_Bullet();
	~Enemy_Bullet();

	void Setup();
	void Update();
	void Move();
	void MoveNear();
	void MoveFar();
	bool Start();
	void Effect(int num);
	void Render(RenderContext& rc);
	void EffectDelete(int num);
	void Damage(int weaponNum);

	Core_weapons* m_coreWeapons = nullptr;
	Player* m_player = nullptr; 
	Game* m_game = nullptr;
	SoundSource* m_soundSource = nullptr;
	SoundSource* m_battleShipGunTyakutiSE = nullptr;			//戦艦砲SE


	Enemy* m_enemyMama = nullptr;
	Enemy_Near* m_enemyNearMama = nullptr;
	Enemy_Far* m_enemyFarMama = nullptr;
	EffectEmitter* m_weaponEffect = nullptr;
	EffectEmitter* m_tyakudanEffect = nullptr;


	ModelRender m_bulletModel;	//マシンガンの弾のモデル
	Quaternion m_aim;
	Quaternion m_rot;
	Quaternion originRotation;
	Vector3 m_position;
	Vector3 m_bulletFowrad;
	Vector3 m_toCoreWeapons;
	Vector3 m_bulletSpeed;
	Vector3 m_bulletLocalPosition;	//弾のローカルポジション
	float m_fallSpeed = 0.0f;
	bool m_attuckState = true;
	bool Landing_state = false;

	
};

