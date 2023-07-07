#pragma once
#define HP 500.0f

class Player;
class Boss;
class Boss_Turbo_attack;
class Drop_item;

class Boss_Turbo :public IGameObject
{
public:
	Boss_Turbo();
	~Boss_Turbo();

	void Setup();
	void Update();
	void Rotation();
	void Move();
	void PlayerSearch();
	void Render(RenderContext& rc);

	enum EnAnimation {
		enAnimationClip_Idle,
		enAnimationClip_Attack,
		enAnimationClip_Num
	};

	Player* m_player;
	Boss* m_boss;
	Boss_Turbo_attack* b_boss_weapons;
	Drop_item* m_dropItem;
	EffectEmitter* m_weaponEffect = nullptr;
	SoundSource*TatumakiSE=nullptr;
	AnimationClip m_animationClip[enAnimationClip_Num];
	//CharacterController boss_riser_characterContller;
	Quaternion m_rotation;
	Vector3 m_position;
	Vector3 iranyatu;
	Vector3 m_forward;
	Vector3 m_moveSpeed = Vector3::Zero;
	Vector3 m_effectLocalPos = { 0.0f,410.0f,0.0f };
	int iran = 0;
	ModelRender boss_Turbo_Render;

	//Ç¢ÇÈÅBê‚ëŒÅB
	Vector3 m_localPosition = { -630.0f,20.0f,-100.0f };

	bool m_attackState = false;
	bool m_attackOK = false;
	bool notHituyou = false;
	bool Rote = false;
	int m_setWeapon = 0;

	int iraniran = 0;
	int m_fastFlag = 0;

	float turbo_HP = HP;
	float scale = 13.0f;
};