#pragma once

class Player;
class Boss;
class Boss_Turbo_attack;

class Boss_Turbo :public IGameObject
{
public:
	Boss_Turbo();
	~Boss_Turbo();

	void Setup();
	void Update();
	void Move();
	void PlayerSearch();
	void Render(RenderContext& rc);

	Player* b_w_player;
	Boss* b_w_boss;
	Boss_Turbo_attack* b_boss_weapons;

	//CharacterController boss_riser_characterContller;
	Quaternion b_w_rotation;
	Vector3 b_w_position;
	Vector3 b_w_moveSpeed;
	Vector3 b_w_Fowrad = { 0.0f,0.0f,1.0f };
	int game_state = 0;
	ModelRender boss_Turbo_Render;

	//Ç¢ÇÈÅBê‚ëŒÅB
	Vector3 b_w_localposition = { 500.0f,200.0f,-150.0f };

	bool attack_state = false;
	bool atack_ok = false;
	int set_weapons = 0;

	int firing_cound = 0;
	int fast = 0;

};