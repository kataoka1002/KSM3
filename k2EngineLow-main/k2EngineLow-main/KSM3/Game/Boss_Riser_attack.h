#pragma once
#include "sound/SoundSource.h"

class Boss;
class Boss_Riser;
class Core_weapons;
class Player;
class Game;
class Left_arm_weapons;
class Left_leg_weapons;
class Right_arm_weapons;
class Right_leg_weapons;
class Shoulder_weapons;
class Customize_UI_ver2;

class Boss_Riser_attack :public IGameObject
{
public:
	Boss_Riser_attack();
	~Boss_Riser_attack();

	bool Start();
	void Effect();
	void DestroyWithImpactEffect();
	void SetUp();
	void Update();
	void Damage(bool No_tyakudan);
	void Move();
	void Render(RenderContext& rc);

	Customize_UI_ver2* m_customizeUI = nullptr;
	Boss_Riser* b_a_weapons;
	Boss* b_a_boss;
	Core_weapons* b_a_core_weapons;
	Player* m_player;
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
	Vector3 m_firePosition;
	Vector3 m_bulletForward;
	Vector3 b_a_Bulet_weapons;
	Vector3 m_moveSpeed = Vector3::Zero;
	EffectEmitter* m_weaponEffect = nullptr;
	EffectEmitter* m_tyakudanEffect = nullptr;
	EffectEmitter* m_BulletEffect = nullptr;
	SoundSource* m_battleShipGunTyakutiSE = nullptr;
	Vector3 to_core_weapons;
	Vector3 m_bulletLocalPosition = { 0.0f,680.0f,200.0f };	//弾のローカルポジション

	bool Landing_state = false;
	float move_speed = 30.0f;
	float m_fallSpeed = 0.0f;
	bool m_attackState = true;
	bool fast_count = true;

	int m_loadingCount = 0;
	int m_bulletEfeCount = 0;
	Vector3 m_effectPosition = Vector3::Zero;
	bool m_fastFlag = true;
	bool farst = true;
};