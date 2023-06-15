#pragma once

class Player;
class Battle_ship_attack;
class MachineGunAttack;
class GigatonCannonAttack;
class Customize_UI_ver2;
class PlayerUI;

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
	MachineGunAttack* m_machineGunAttack = nullptr;
	GigatonCannonAttack* m_gigatonAttack = nullptr;
	Customize_UI_ver2* m_customizeUI = nullptr;
	PlayerUI* m_playerUI = nullptr;


	Quaternion l_a_Rotation;
	Vector3 l_a_w_position;
	Vector3 l_a_w_moveSpeed;
	Vector3 l_a_w_Fowrad = { 0.0f, 0.0f, 1.0f };//ç∂òrëïîıÇÃê≥ñ ÉxÉNÉgÉã
	int game_state = 0;
	ModelRender Left_arm_weapons_Render;

	Vector3 l_a_w_localPosition = { -60.0f,70.0f,-10.0f };
	Vector3 scale2 = { 2.0f,2.0f,2.0f };

	int set_weapons=0;

	int firing_cound = 0;
	int fast = 0;

	float L_a_w_HP = 100.0f;
	float L_a_w_HPMax = 100.0f;
};

