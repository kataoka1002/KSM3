#pragma once
#define HP 500.0f

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
	void PlayerSearch();
	void Damage();
	void Render(RenderContext& rc);

	enum EnAnimation {
		enAnimationClip_Idle,
		enAnimationClip_attack,
		enAnimationClip_Num
	};

	AnimationClip m_animationClip[enAnimationClip_Num];
	Player* b_a_player;
	Boss* b_w_boss;
	Boss_Drill_attack* b_boss_weapons;
	Drop_item* drop_item;
	Game* m_game;
	Left_arm_weapons* m_leftArm = nullptr;
	Left_leg_weapons* m_leftLeg = nullptr;
	Right_arm_weapons* m_rightArm = nullptr;
	Right_leg_weapons* m_rightLeg = nullptr;
	Shoulder_weapons* m_shoulder = nullptr;
	

	//CharacterController boss_riser_characterContller;
	Quaternion b_w_rotation;
	Vector3 b_w_position;
	Vector3 b_w_moveSpeed;

	EffectEmitter* Explosion_efe = nullptr;
	EffectEmitter* Explosion_Another = nullptr;
	Vector3 b_w_Fowrad = { 0.0f,0.0f,1.0f };
	int game_state = 0;
	ModelRender boss_Drill_Render;

	//いる。絶対。
	Vector3 b_w_localposition = { 0.0f,0.0f,900.0f };

	bool attack_state = false;
	bool attack_ok = false;
	bool defeatState = false;//死んだかどうかのフラグ。
	int set_weapons = 0;

	int firing_cound = 0;
	int fast = 0;

	Vector3 efePosi = Vector3::Zero;
	Vector3 efeLP = { 0.0f,0.0f,0.0f };
	float drill_HP = HP;
	int Death_count = 0;
	int Drill_scale = 20.0f;
};