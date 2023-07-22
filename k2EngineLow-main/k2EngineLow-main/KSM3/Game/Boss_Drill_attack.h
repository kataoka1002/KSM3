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

class Boss_Drill_attack :public IGameObject, Noncopyable
{
public:
	Boss_Drill_attack();
	~Boss_Drill_attack();

	bool Start();
	void Effect();
	void SetUp();
	void Update();
	void Damage();
	void Move();
	float PlayerSearch();
	void Render(RenderContext& rc);

	void SetPosition(Vector3 pos)
	{
		m_firePosition = pos;
	}

	void SetRotation(Quaternion rot)
	{
		m_aim = rot;
	}

	void SetForward(Vector3 forward)
	{
		m_bulletForward = forward;
	}

private:

	Boss_Drill* m_weapon = nullptr;
	Customize_UI_ver2* m_customizeUI = nullptr;
	Boss* m_boss = nullptr;
	Core_weapons* m_coreWeapon = nullptr;
	Player* m_player = nullptr;
	Left_arm_weapons* m_leftArm = nullptr;
	Left_leg_weapons* m_leftLeg = nullptr;
	Right_arm_weapons* m_rightArm = nullptr;
	Right_leg_weapons* m_rightLeg = nullptr;
	Shoulder_weapons* m_shoulder = nullptr;
	Game* m_game = nullptr;
	SoundSource* m_attackSE = nullptr;
	SoundSource* m_battleShipGunTyakutiSE = nullptr;
	EffectEmitter* m_weaponEffect = nullptr;
	EffectEmitter* m_tyakudanEffect = nullptr;
	EffectEmitter* m_BulletEffect = nullptr;
	EffectEmitter* m_BulletEffect2 = nullptr;

	ModelRender m_bulletModel;
	Quaternion m_aim;
	Quaternion m_rot;
	Quaternion m_effectRotation;
	Vector3 m_firePosition = Vector3::Zero;
	Vector3 m_bulletForward = Vector3::Zero;
	Vector3 m_bulletLocalPosition = { 0.0f,100.0f,1000.0f };	//弾のローカルポジション
	Vector3 m_effectPosition = Vector3::Zero;
	Vector3 m_moveSpeed = Vector3::Zero;
	Vector3 m_lockPosition = Vector3::Zero;
	Vector3 m_effectLocalPos1 = { 340.0f,0.0f,0.0f };
	Vector3 m_effectLocalPos2 = { -340.0f,0.0f,0.0f };
	Vector3 m_effectForward = Vector3::Zero;
	Vector3 m_lastForward = Vector3::Zero;

	float m_fallSpeed = 0.0f;
	bool m_attackState = true;
	bool m_fastFlag = true;
	int m_loadingCount = 0;
	int m_bulletEfeCount = 0;
	int m_drillCount = 0;
};