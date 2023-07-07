#pragma once

class Player;
class Boss;
class Boss_Turbo_attack;

class Boss_Turbo :public IGameObject
{
public:
	Boss_Turbo();
	~Boss_Turbo();
	bool Start();
	void Setup();
	void Update();
	void Rotation();
	void Move();
	void Render(RenderContext& rc);

	enum EnAnimation {
		enAnimationClip_Idle,
		enAnimationClip_Attack,
		enAnimationClip_Num
	};

	Player* m_player;
	Boss* m_boss;
	Boss_Turbo_attack* m_turboAttack;
	EffectEmitter* m_weaponEffect = nullptr;
	SoundSource*m_tatumakiSE=nullptr;

	ModelRender m_tarboModel;
	AnimationClip m_animationClip[enAnimationClip_Num];
	Quaternion m_rotation;
	Vector3 m_position = Vector3::Zero;
	Vector3 m_forward = Vector3::Zero;
	Vector3 m_moveSpeed = Vector3::Zero;
	Vector3 m_effectLocalPos = { 0.0f,410.0f,0.0f };
	Vector3 m_localPosition = { -630.0f,20.0f,-100.0f };

	bool m_attackState = false;
	bool m_attackOK = false;
	bool m_roteFlag = false;
	int m_attackCount = 0;
	float m_scale = 13.0f;
};