#pragma once

class Player;
class Battle_ship_attack;

class Right_arm_weapons :public IGameObject
{
public:
	Right_arm_weapons();
	~Right_arm_weapons();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void R_a_w_set();

	Player* r_a_w_player = nullptr;
	Battle_ship_attack* battle_ship_attack;

	Quaternion r_a_Rotation;
	Vector3 r_a_w_position;
	Vector3 r_a_w_moveSpeed;
	Vector3 r_a_w_Fowrad = { 0.0f, 0.0f, 1.0f };//¶˜r‘•”õ‚Ì³–ÊƒxƒNƒgƒ‹
	int game_state = 0;
	ModelRender Right_arm_weapons_Render;

	Vector3 r_a_w_localPosition = { 55.0f,90.0f,5.0f };

	bool atack_state = false;
	int set_weapons[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };

	int fast = 0;
};

