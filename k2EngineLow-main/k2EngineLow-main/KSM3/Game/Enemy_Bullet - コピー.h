#pragma once
#include "sound/SoundSource.h"

class Customize_UI_ver2;
class Core_weapons;
class Enemy;
class Enemy_Near;
class Enemy_Far;
class Player;
class Game;
class Left_arm_weapons;
class Left_leg_weapons;
class Right_arm_weapons;
class Right_leg_weapons;
class Shoulder_weapons;


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
	void FindWeapon();
	void Damage(int weaponNum);
	void DestroyWithImpactEffect();

	Customize_UI_ver2* m_customizeUI = nullptr;
	Core_weapons* m_coreWeapons = nullptr;
	Enemy* m_enemyMama = nullptr;
	Enemy_Near* m_enemyNearMama = nullptr;
	Enemy_Far* m_enemyFarMama = nullptr;
	Player* m_player = nullptr; 
	Game* m_game = nullptr;
	Left_arm_weapons* m_leftArm = nullptr;
	Left_leg_weapons* m_leftLeg = nullptr;
	Right_arm_weapons* m_rightArm = nullptr;
	Right_leg_weapons* m_rightLeg = nullptr;
	Shoulder_weapons* m_shoulder = nullptr;
	EffectEmitter* m_weaponEffect = nullptr;
	EffectEmitter* m_tyakudanEffect = nullptr;
	SoundSource* m_battleShipGunTyakutiSE = nullptr;			//��͖CSE
	std::unique_ptr<ModelRender> m_bulletModel;	//�}�V���K���̒e�̃��f��
	Quaternion m_aim;
	Quaternion m_rot;
	Quaternion originRotation;
	Vector3 m_position = Vector3::Zero;
	Vector3 m_bulletFowrad = Vector3::Zero;
	Vector3 m_toCoreWeapons = Vector3::Zero;
	Vector3 m_bulletSpeed = Vector3::Zero;
	Vector3 m_bulletLocalPosition = Vector3::Zero;	//�e�̃��[�J���|�W�V����

	float m_fallSpeed = 0.0f;
	bool m_attuckState = true;
	bool Landing_state = false;

	
};

