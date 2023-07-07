#pragma once

class Player;
class Boss;
class Boss_Drill_attack;
class Drop_item;
class Game;
class Left_arm_weapons;
class Left_leg_weapons;
class Right_arm_weapons;
class Right_leg_weapons;
class Shoulder_weapons;

class Boss_Drill :public IGameObject
{
public:
	Boss_Drill();
	~Boss_Drill();

	void Setup();
	void Update();
	void Move();
	void Damage();
	void Render(RenderContext& rc);

	enum EnAnimation {
		enAnimationClip_Idle,
		enAnimationClip_attack,
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

	void ApplyDamage(float damage)
	{
		m_HP -= damage;
	}

	void SetDrillAttack(Boss_Drill_attack* pointa)
	{
		m_drillAttack = pointa;
	}

	/// <summary>
	/// ドリルの大きさ減少
	/// </summary>
	/// <param name="amount">減少量</param>
	void DecreaseScale(float amount)
	{
		m_scale -= amount;
	}

	/// <summary>
	/// ドリルの大きさを設定
	/// </summary>
	void SetDrillScale()
	{
		m_drillModel.SetScale(m_scale);
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
	Player* m_player;
	Boss* m_boss;
	Boss_Drill_attack* m_drillAttack;
	Drop_item* m_dropItem;
	Game* m_game;
	Left_arm_weapons* m_leftArm = nullptr;
	Left_leg_weapons* m_leftLeg = nullptr;
	Right_arm_weapons* m_rightArm = nullptr;
	Right_leg_weapons* m_rightLeg = nullptr;
	Shoulder_weapons* m_shoulder = nullptr;
	
	ModelRender m_drillModel;
	EffectEmitter* m_explosionEffect = nullptr;
	EffectEmitter* m_explosionAnother = nullptr;
	Quaternion m_rotation;
	Vector3 m_forward = { 0.0f,0.0f,1.0f };
	Vector3 m_position;
	Vector3 m_localPosition = { 0.0f,0.0f,900.0f };
	Vector3 m_effectPosition = Vector3::Zero;
	Vector3 m_effectLocalPos = { 0.0f,0.0f,0.0f };

	bool m_attackState = false;
	bool m_attackOK = false;
	bool notHituyou = false;//死んだかどうかのフラグ。
	float m_HP = 500.0f;
	int m_setWeapon = 0;
	int iraniran = 0;
	int m_fastFlag = 0;
	int m_deathCount = 0;
	int m_scale = 20.0f;
};