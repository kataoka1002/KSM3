#pragma once
class Player;
class Battle_ship_attack;
class MachineGunAttack;
class GigatonCannonAttack;
class Customize_UI_ver2;
class PlayerUI;

class Right_leg_weapons:public IGameObject
{
public:
	Right_leg_weapons();
	~Right_leg_weapons();

	void Update();
	void Render(RenderContext& rc);
	void Move();
	void R_l_w_set();

	Player* r_l_w_player = nullptr;
	Battle_ship_attack* battle_ship_attack = nullptr;
	MachineGunAttack* m_machineGunAttack = nullptr;
	GigatonCannonAttack* m_gigatonAttack = nullptr;
	Customize_UI_ver2* m_customizeUI = nullptr;
	PlayerUI* m_playerUI = nullptr;

	Quaternion r_l_Rotation;
	Vector3 r_l_w_position;
	Vector3 r_l_w_moveSpeed;
	Vector3 r_l_w_Fowrad = { 0.0f,0.0f,1.0f };//右足装備の正面ベクトル
	int game_state = 0;
	ModelRender Right_leg_weapons_Render;

	Vector3 r_l_w_localPosition = { 90.0f,30.0f,55.0f };
	Vector3 scale2 = { 2.0f,2.0f,2.0f };

	int set_weapons = 0;

	int firing_cound = 0;
	int fast = 0;

	float R_l_w_HP = 100.0f;
	float R_l_w_HPMax = 100.0f;
};

