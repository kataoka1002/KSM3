#pragma once

class Player;
class Boss;
class Boss_Shovel_attack;
class Game;
class Left_arm_weapons;
class Left_leg_weapons;
class Right_arm_weapons;
class Right_leg_weapons;
class Shoulder_weapons;

class Boss_Shovel :public IGameObject
{
public:
	Boss_Shovel();
	~Boss_Shovel();

	void Setup();
	void Update();
	void Move();
	void Damage(int attack_Num);
	void Render(RenderContext& rc);
	bool Start();

	enum EnAnimation {
		enAnimationClip_Idle,
		enAnimationClip_Idle2,
		enAnimationClip_Shock_Ground,
		enAnimationClip_Num
	};

	Vector3 GetPosirion()
	{
		return m_position;
	}

	Quaternion GetRotation()
	{
		return m_rotation;
	}

	Vector3 GetForward()
	{
		return m_forward;
	}

	float GetScale()
	{
		return m_scale;
	}

	void ApplyDamage(float damage)
	{
		m_HP -= damage;
	}

	void SetShovelAttack(Boss_Shovel_attack* pointa)
	{
		m_shovelAttack = pointa;
	}

	/// <summary>
	/// ショベルの大きさ減少
	/// </summary>
	/// <param name="amount">減少量</param>
	void DecreaseScale(float amount)
	{
		m_scale -= amount;
	}

	/// <summary>
	/// ショベルの大きさを設定
	/// </summary>
	void SetShovelScale()
	{
		m_shovelModel.SetScale(m_scale);
	}

	/// <summary>
	/// 攻撃できるかどうかを設定
	/// </summary>
	/// <param name="attack"></param>
	void SetAttackOK(bool attack)
	{
		m_attackOK = attack;
	}


private:
	AnimationClip m_animationClip[enAnimationClip_Num];
	Player* m_player = nullptr;
	Left_arm_weapons* m_leftArm = nullptr;
	Left_leg_weapons* m_leftLeg = nullptr;
	Right_arm_weapons* m_rightArm = nullptr;
	Right_leg_weapons* m_rightLeg = nullptr;
	Shoulder_weapons* m_shoulder = nullptr;
	SoundSource* m_shovelRoarSE = nullptr;
	SoundSource* m_shovelShockSE = nullptr;
	Boss* m_boss = nullptr;
	Boss_Shovel_attack* m_shovelAttack = nullptr;
	Game* m_game = nullptr;
	EffectEmitter* m_shovelShock = nullptr;

	ModelRender m_shovelModel;
	Quaternion m_rotation;
	Vector3 m_position = Vector3::Zero;
	Vector3 m_forward = { 0.0f,0.0f,1.0f };
	Vector3 m_localPosition = { 00.0f,230.0f,950.0f };
	Vector3 m_shockEffectLocalPos = { 0.0f,-229.0f,-1000.0f };

	bool m_attackOK = false;
	int m_setWeapon = 0;
	int m_fastFlag = 0;
	float m_HP = 500.0f;
	float m_scale = 15.0f;
};