#pragma once
#include "sound/SoundSource.h"

class Boss;
class Boss_Turbo;
class Core_weapons;
class Customize_UI_ver2;
class Player;
class Left_arm_weapons;
class Left_leg_weapons;
class Right_arm_weapons;
class Right_leg_weapons;
class Shoulder_weapons;
class Game;

class Boss_Turbo_attack :public IGameObject
{
public:
	Boss_Turbo_attack();
	~Boss_Turbo_attack();

	bool Start();
	void SetUp();
	void Update();
	void DestroyWithImpactEffect();
	void Move();
	void Rotation();
	void Damage(bool No_tyakudan);
	void Effect();
	void Render(RenderContext& rc);

	Boss_Turbo* m_weapon;
	Boss* m_boss;
	Core_weapons* m_coreWeapon;
	Player* m_player;
	SoundSource* m_attackSE;
	EffectEmitter* m_weaponEffect = nullptr;
	Left_arm_weapons* m_leftArm = nullptr;
	Left_leg_weapons* m_leftLeg = nullptr;
	Right_arm_weapons* m_rightArm = nullptr;
	Right_leg_weapons* m_rightLeg = nullptr;
	Shoulder_weapons* m_shoulder = nullptr;
	Customize_UI_ver2* m_customizeUI = nullptr;
	
	ModelRender m_bulletModel;
	Quaternion m_aim;
	Quaternion m_rot;
	Quaternion Effrot;
	Vector3 m_firePosition;
	Vector3 m_bulletForward;
	Vector3 Efe_Fowrad{ 0.0f,0.0f,-100.0f };
	Vector3 iranran;
	Vector3 to_core_weapons;
	Vector3 m_moveSpeed = Vector3::Zero;
	Vector3 m_effectPosition = Vector3::Zero;
	Vector3 m_bulletLocalPosition = { 0.0f,410.0f,350.0f };	//弾のローカルポジション


	int m_loadingCount = 0;

	bool Landing_state = false;
	float move_speed = 30.0f;
	float m_fallSpeed = 0.0f;
	bool m_attackState = true;
	bool fast_count = true;
};