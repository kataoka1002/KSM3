#pragma once
class Player;
class Battle_ship_attack;
class Left_leg_UI;
class MachineGunAttack;
class GigatonCannonAttack;


class Left_leg_weapons:public IGameObject
{
public:
	Left_leg_weapons();
	~Left_leg_weapons();

	void Update();
	void Render(RenderContext& rc);
	void Move();
	void L_l_w_set();

	Player* l_l_w_player = nullptr;
	Battle_ship_attack* battle_ship_attack = nullptr;
	Left_leg_UI* left_leg_ui = nullptr;
	MachineGunAttack* m_machineGunAttack = nullptr;
	GigatonCannonAttack* m_gigatonAttack = nullptr;


	Quaternion l_l_Rotation;
	Vector3 l_l_w_position;
	Vector3 l_l_w_moveSpeed;
	Vector3 l_l_w_Fowrad = { 0.0f,0.0f,1.0f };//ç∂ë´ëïîıÇÃê≥ñ ÉxÉNÉgÉã
	int game_state = 0;
	ModelRender Left_leg_weapons_Render;

	Vector3 l_l_w_localPosition = { -90.0f,30.0f,55.0f };
	Vector3 scale2 = { 2.0f,2.0f,2.0f };

	bool atack_state = false;
	int set_weapons = 0;

	int firing_cound = 0;
	int fast = 0;

	float L_l_w_HP = 0.0f;
};

