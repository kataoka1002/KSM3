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

	Player* b_w_player;
	Boss* b_w_boss;
	Boss_Turbo_attack* b_boss_weapons;
	Drop_item* m_dropItem;
	EffectEmitter* m_weaponEffect = nullptr;
	SoundSource*TatumakiSE=nullptr;
	AnimationClip m_animationClip[enAnimationClip_Num];
	//CharacterController boss_riser_characterContller;
	Quaternion b_w_rotation;
	Vector3 b_w_position;
	Vector3 b_w_moveSpeed;
	Vector3 b_w_Fowrad;
	Vector3 Move_speed = Vector3::Zero;
	Vector3 efeLP = { 0.0f,410.0f,0.0f };
	int game_state = 0;
	ModelRender boss_Turbo_Render;

	//Ç¢ÇÈÅBê‚ëŒÅB
	Vector3 b_w_localposition = { -630.0f,20.0f,-100.0f };

	bool m_attackState = false;
	bool attack_ok = false;
	bool defeatState = false;
	bool Rote = false;
	int set_weapons = 0;

	int firing_cound = 0;
	int fast = 0;

	float turbo_HP = HP;
	float scale = 13.0f;
};