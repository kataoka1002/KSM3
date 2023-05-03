#pragma once

class Player;
class Boss;
class Boss_Shovel_attack;

class Boss_Shovel :public IGameObject
{
public:
	Boss_Shovel();
	~Boss_Shovel();

	void Setup();
	void Update();
	void Move();
	void PlayerSearch();
	void Render(RenderContext& rc);
	bool Start();

	enum EnAnimation {
		enAnimationClip_Idle,
		enAnimationClip_Num
	};

	AnimationClip m_animationClip[enAnimationClip_Num];
	Player* b_w_player = nullptr;
	Boss* b_w_boss;
	Boss_Shovel_attack* b_boss_weapons;

	//CharacterController boss_riser_characterContller;
	Quaternion b_w_rotation;
	Vector3 b_w_position;
	Vector3 b_w_moveSpeed;
	Vector3 b_w_Fowrad = { 0.0f,0.0f,1.0f };
	int game_state = 0;
	ModelRender boss_Shovel_Render;
	int shovelState = 0;

	//Ç¢ÇÈÅBê‚ëŒÅB
	Vector3 b_w_localposition = { 00.0f,230.0f,950.0f };

	bool attack_state = false;
	bool attack_ok = false;
	int set_weapons = 0;

	int firing_cound = 0;
	int fast = 0;

};