#pragma once

class Boss;
class Boss_Turbo;
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
	void Damage(bool No_tyakudan);
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
	Boss_Turbo* m_weapon = nullptr;
	Boss* m_boss = nullptr;
	Player* m_player = nullptr;
	SoundSource* m_attackSE = nullptr;
	EffectEmitter* m_weaponEffect = nullptr;
	Left_arm_weapons* m_leftArm = nullptr;
	Left_leg_weapons* m_leftLeg = nullptr;
	Right_arm_weapons* m_rightArm = nullptr;
	Right_leg_weapons* m_rightLeg = nullptr;
	Shoulder_weapons* m_shoulder = nullptr;
	
	ModelRender m_bulletModel;
	Quaternion m_aim;
	Quaternion m_rot;
	Vector3 m_firePosition = Vector3::Zero;
	Vector3 m_bulletForward = Vector3::Zero;
	Vector3 m_moveSpeed = Vector3::Zero;
	Vector3 m_effectPosition = Vector3::Zero;
	Vector3 m_bulletLocalPosition = { 0.0f,410.0f,350.0f };	//弾のローカルポジション

	int m_loadingCount = 0;
};