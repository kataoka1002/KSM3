#pragma once

class Player;
class Battle_ship_attack;

class Left_arm_weapons :public IGameObject
{
public:
	Left_arm_weapons();
	~Left_arm_weapons();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void L_a_w_set();

	Player* l_a_w_player = nullptr;
	Battle_ship_attack* battle_ship_attack;

	Quaternion originRotation;
	Vector3 l_a_w_position;
	Vector3 l_a_w_moveSpeed;
	Vector3 l_a_w_Fowrad = { 0.0f, 0.0f, 1.0f };//¶˜r‘•”õ‚Ì³–ÊƒxƒNƒgƒ‹
	int game_state = 0;
	ModelRender Left_arm_weapons_Render;

	Vector3 l_a_w_localPosition = { -55.0f,90.0f,5.0f };

	bool atack_state = false;
	int drop_weapons [12] = {0,0,0,0,0,0,0,0,0,0,0,0 };

	int fast = 0;
};

