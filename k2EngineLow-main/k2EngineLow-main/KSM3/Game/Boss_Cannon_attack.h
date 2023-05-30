#pragma once
#include "sound/SoundSource.h"

class Boss;
class Boss_Cannon;
class Core_weapons;
class Customize_UI_ver2;
class Player;
class Game;
class Left_arm_weapons;
class Left_leg_weapons;
class Right_arm_weapons;
class Right_leg_weapons;
class Shoulder_weapons;

class Boss_Cannon_attack :public IGameObject
{
public:
	Boss_Cannon_attack();
	~Boss_Cannon_attack();

	bool Start();
	void Effect();
	void DestroyWithImpactEffect();
	void SetUp();
	void Update();
	void Damage(bool No_tyakudan);
	void Move();
	void Render(RenderContext& rc);

	Customize_UI_ver2* m_customizeUI = nullptr;
	Boss_Cannon* b_a_weapons;
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

	ModelRender b_a_Bullet;
	Quaternion b_a_aiming;
	Quaternion m_rot;
	Vector3 firing_position;
	Vector3 b_a_Bullet_Fowrad;
	Vector3 b_a_Bulet_weapons;
	Vector3 Move_speed = Vector3::Zero;
	EffectEmitter* m_weaponEffect = nullptr;
	EffectEmitter* m_tyakudanEffect = nullptr;
	EffectEmitter* m_BulletEffect = nullptr;
	SoundSource* m_battleShipGunTyakutiSE = nullptr;
	SoundSource* m_Cannon_LangingSE = nullptr;
	Vector3 to_core_weapons;
	Vector3 m_bulletLocalPosition = { 0.0f,680.0f,200.0f };	//弾のローカルポジション

	bool Landing_state = false;
	float move_speed = 30.0f;
	float fall_speed = 0.0f;
	bool attack_state = true;
	bool fast_count = true;

	int Landing_count=0;
	int Bullet_efe_count = 0;
	Vector3 efePosi = Vector3::Zero;
	bool fast = true;
	
};