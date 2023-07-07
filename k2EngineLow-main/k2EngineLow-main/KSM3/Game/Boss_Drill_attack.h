#pragma once
#include "sound/SoundSource.h"

class Boss;
class Core_weapons;
class Customize_UI_ver2;
class Player;
class Boss_Drill;
class Game;
class Left_arm_weapons;
class Left_leg_weapons;
class Right_arm_weapons;
class Right_leg_weapons;
class Shoulder_weapons;

class Boss_Drill_attack :public IGameObject
{
public:
	Boss_Drill_attack();
	~Boss_Drill_attack();

	bool Start();
	void Effect();
	void DestroyWithImpactEffect();
	void SetUp();
	void Update();
	void Damage();
	void Move();
	float Player_Search();
	void Render(RenderContext& rc);

	Boss_Drill* b_a_weapons;
	Customize_UI_ver2* m_customizeUI = nullptr;
	Boss* b_a_boss;
	Core_weapons* b_a_core_weapons;
	Player* b_a_player;
	Left_arm_weapons* m_leftArm = nullptr;
	Left_leg_weapons* m_leftLeg = nullptr;
	Right_arm_weapons* m_rightArm = nullptr;
	Right_leg_weapons* m_rightLeg = nullptr;
	Shoulder_weapons* m_shoulder = nullptr;
	SoundSource* b_attack_SE;
	Game* m_game;

	ModelRender m_bulletModel;
	Quaternion m_aim;
	Quaternion m_rot;
	Quaternion efe_rot;
	Vector3 m_firePosition;
	Vector3 m_bulletForward;
	Vector3 b_a_Bulet_weapons;
	Vector3 m_moveSpeed = Vector3::Zero;
	EffectEmitter* m_weaponEffect = nullptr;
	EffectEmitter* m_tyakudanEffect = nullptr;
	EffectEmitter* m_BulletEffect = nullptr;
	EffectEmitter* m_BulletEffect2 = nullptr;
	SoundSource* m_battleShipGunTyakutiSE = nullptr;
	Vector3 to_core_weapons;
	Vector3 m_bulletLocalPosition = { 0.0f,100.0f,1000.0f };	//弾のローカルポジション

	bool Landing_state = false;
	float m_fallSpeed = 0.0f;
	bool m_attackState = true;
	bool fast_count = true;

	int m_loadingCount = 0;
	int m_bulletEfeCount = 0;
	Vector3 m_effectPosition = Vector3::Zero;
	bool m_fastFlag = true;

	int drill_count=0;
	Vector3 move_speed=Vector3::Zero;
	Vector3 lock_p_position = Vector3::Zero;

	Vector3 efe_l_pos1 = { 340.0f,0.0f,0.0f };
	Vector3 efe_l_pos2 = { -340.0f,0.0f,0.0f };

	Vector3 efe_fowrad=Vector3::Zero;
	Vector3 last_fowrad = Vector3::Zero;

	bool test = false;

	float return_angle=0;
};