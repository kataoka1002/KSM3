#pragma once
#define HP 500

class Player;
class Boss;
class Boss_Riser_attack;
class Drop_item;

class Boss_Riser :public IGameObject
{
public:
	Boss_Riser();
	~Boss_Riser();

	void Setup();
	void Update();
	void Move();
	void PlayerSearch();
	void Render(RenderContext& rc);

	Player* b_w_player;
	Boss* b_w_boss;
	Boss_Riser_attack* b_boss_weapons;
	Drop_item* drop_item;

	//CharacterController boss_riser_characterContller;
	Quaternion b_w_rotation;
	Vector3 b_w_position;
	Vector3 b_w_moveSpeed;
	Vector3 b_w_Fowrad = { 0.0f,0.0f,1.0f };
	int game_state = 0;
	ModelRender boss_Riser_Render;

	//Ç¢ÇÈÅBê‚ëŒÅB
	Vector3 b_w_localposition = { 600.0f,450.0f,-100.0f };

	bool attack_state = false;
	bool attack_ok = false;
	bool defeatState = false;
	int set_weapons = 0;

	int firing_cound = 0;
	int fast = 0;

	float riser_HP=HP;
};