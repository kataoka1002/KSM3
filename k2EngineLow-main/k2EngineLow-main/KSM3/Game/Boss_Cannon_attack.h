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
	Customize_UI_ver2* m_customizeUI = nullptr;
	Boss_Cannon* m_cannon = nullptr;
	Player* m_player = nullptr;
	Left_arm_weapons* m_leftArm = nullptr;
	Left_leg_weapons* m_leftLeg = nullptr;
	Right_arm_weapons* m_rightArm = nullptr;
	Right_leg_weapons* m_rightLeg = nullptr;
	Shoulder_weapons* m_shoulder = nullptr;
	Game* m_game = nullptr;
	EffectEmitter* m_weaponEffect = nullptr;
	EffectEmitter* m_tyakudanEffect = nullptr;
	EffectEmitter* m_BulletEffect = nullptr;
	SoundSource* m_battleShipGunTyakutiSE = nullptr;
	SoundSource* m_Cannon_LangingSE = nullptr;

	ModelRender m_bulletModel;
	Quaternion m_aim;
	Quaternion m_rot;
	Vector3 m_firePosition = Vector3::Zero;
	Vector3 m_bulletForward = Vector3::Zero;
	Vector3 m_moveSpeed = Vector3::Zero;
	Vector3 m_bulletLocalPosition = { 0.0f,680.0f,200.0f };	//弾のローカルポジション
	Vector3 m_effectPosition = Vector3::Zero;

	float m_fallSpeed = 0.0f;
	int m_loadingCount = 0;
	int m_bulletEfeCount = 0;
	bool m_fastFlag = true;

};