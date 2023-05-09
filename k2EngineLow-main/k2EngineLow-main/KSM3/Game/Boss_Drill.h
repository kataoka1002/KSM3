#pragma once
#define HP 500.0f;

class Player;
class Boss;
class Boss_Drill_attack;
class Drop_item;

class Boss_Drill :public IGameObject
{
public:
	Boss_Drill();
	~Boss_Drill();

	void Setup();
	void Update();
	void Move();
	void PlayerSearch();
	void Render(RenderContext& rc);

	Player* b_w_player;
	Boss* b_w_boss;
	Boss_Drill_attack* b_boss_weapons;
	Drop_item* drop_item;

	//CharacterController boss_riser_characterContller;
	Quaternion b_w_rotation;
	Vector3 b_w_position;
	Vector3 b_w_moveSpeed;
	Vector3 b_w_Fowrad = { 0.0f,0.0f,1.0f };
	int game_state = 0;
	ModelRender boss_Drill_Render;

	//����B��΁B
	Vector3 b_w_localposition = { 0.0f,0.0f,900.0f };

	bool attack_state = false;
	bool attack_ok = false;
	bool defeatState = false;//���񂾂��ǂ����̃t���O�B
	int set_weapons = 0;

	int firing_cound = 0;
	int fast = 0;

	float drill_HP = HP;
};