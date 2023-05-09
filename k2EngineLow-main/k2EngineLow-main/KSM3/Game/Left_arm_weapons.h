#pragma once

class Player;
class Battle_ship_attack;
class Left_arm_UI;
class MachineGunAttack;

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
	Battle_ship_attack* battle_ship_attack = nullptr;
	Left_arm_UI* left_arm_ui = nullptr;
	MachineGunAttack* m_machineGunAttack = nullptr;


	Quaternion l_a_Rotation;
	Vector3 l_a_w_position;
	Vector3 l_a_w_moveSpeed;
	Vector3 l_a_w_Fowrad = { 0.0f, 0.0f, 1.0f };//ç∂òrëïîıÇÃê≥ñ ÉxÉNÉgÉã
	int game_state = 0;
	ModelRender Left_arm_weapons_Render;

	Vector3 l_a_w_localPosition = { -60.0f,70.0f,-10.0f };
	Vector3 scale2 = { 2.0f,2.0f,2.0f };

	bool atack_state = false;
	int set_weapons=0;

	int firing_cound = 0;
	int fast = 0;

	float L_a_w_HP = 0.0f;
};

