#pragma once
#define HP 500.0f

class Player;
class Boss;
class Boss_Shovel_attack;
class Drop_item;
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
	void PlayerSearch();
	void Damage(int attack_Num);
	void Render(RenderContext& rc);
	bool Start();

	enum EnAnimation {
		enAnimationClip_Idle,
		enAnimationClip_Idle2,
		enAnimationClip_Shock_Ground,
		enAnimationClip_Num
	};

	AnimationClip m_animationClip[enAnimationClip_Num];
	Player* m_player = nullptr;
	Left_arm_weapons* m_leftArm = nullptr;
	Left_leg_weapons* m_leftLeg = nullptr;
	Right_arm_weapons* m_rightArm = nullptr;
	Right_leg_weapons* m_rightLeg = nullptr;
	Shoulder_weapons* m_shoulder = nullptr;
	SoundSource* m_Shovel_roar_SE = nullptr;
	SoundSource* m_Shovel_shock_SE = nullptr;
	Boss* m_boss;
	Boss_Shovel_attack* b_boss_weapons;
	Drop_item* m_dropItem;
	Game* m_game;

	//CharacterController boss_riser_characterContller;
	Quaternion m_rotation;
	Vector3 m_position;
	Vector3 b_w_moveSpeed;
	EffectEmitter* shovel_shock;
	Vector3 m_forward = { 0.0f,0.0f,1.0f };
	int game_state = 0;
	ModelRender boss_Shovel_Render;
	int shovelState = 0;

	//Ç¢ÇÈÅBê‚ëŒÅB
	Vector3 b_w_localposition = { 00.0f,230.0f,950.0f };

	bool m_attackState = false;
	bool attack_ok = false;
	bool defeatState = false;
	int set_weapons = 0;

	int firing_cound = 0;
	int fast = 0;

	float shovel_HP = HP;
	float scale = 15.0f;

	Vector3 shock_efe_lpos = { 0.0f,-229.0f,-1000.0f };
};