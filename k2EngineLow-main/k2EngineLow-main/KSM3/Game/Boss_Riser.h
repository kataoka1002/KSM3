#pragma once

class Player;
class Boss;
class Boss_Riser_attack;
class Drop_item;
class Game;

class Boss_Riser : public IGameObject
{
public:
	Boss_Riser();
	~Boss_Riser();

	void Setup();
	void Update();
	void Move();
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

	float GetScale()
	{
		return m_scale;
	}

	void ApplyDamage(float damage)
	{
		m_HP -= damage;
	}

	void SetRiserAttack(Boss_Riser_attack* pointa)
	{
		m_riserAttack = pointa;
	}

	/// <summary>
	/// ライザーの大きさ減少
	/// </summary>
	/// <param name="amount">減少量</param>
	void DecreaseScale(float amount)
	{
		m_scale -= amount;
	}

	/// <summary>
	/// ライザーの大きさを設定
	/// </summary>
	void SetRiserScale()
	{
		m_riserModel.SetScale(m_scale);
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
	EffectEmitter* m_weaponEffect = nullptr;
	Player* m_player;
	Boss* m_boss;
	Boss_Riser_attack* m_riserAttack;
	Drop_item* m_dropItem;
	Game* m_game;
	SoundSource* m_dozarChageSE = nullptr;

	ModelRender m_riserModel;
	Quaternion m_rotation;
	Vector3 m_position = Vector3::Zero;
	Vector3 m_forward = { 0.0f,0.0f,1.0f };
	Vector3 m_localPosition = { 600.0f,300.0f,-100.0f };
	Vector3 m_effectLocalPos = { 0.0f,200.0f,-200.0f };

	bool m_attackOK = false;
	int m_setWeapon = 0;
	int m_fastFlag = 0;
	float m_HP = 500.0f;
	float m_scale = 12.0f;
};