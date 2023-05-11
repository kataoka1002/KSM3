#pragma once
class Player;
class Battle_ship_attack;
class Shoulder_UI;
class MachineGunAttack;
class GigatonCannonAttack;


class Shoulder_weapons:public IGameObject
{
public:
	Shoulder_weapons();
	~Shoulder_weapons();

	void Update();
	void Render(RenderContext& rc);
	void Move();
	void Move2();	//マシンガン用
	void S_w_set();

	Player* s_w_player = nullptr;
	Battle_ship_attack* battle_ship_attack = nullptr;
	Battle_ship_attack* battle_ship_attack2 = nullptr;
	Shoulder_UI* shoulder_ui = nullptr;
	MachineGunAttack* m_machineGunAttack = nullptr;
	MachineGunAttack* m_machineGunAttack2 = nullptr;
	GigatonCannonAttack* m_gigatonAttack = nullptr;


	Quaternion Shoulder_Rotation;
	Quaternion Shoulder_Rotation2;
	Vector3 s_w_position = Vector3::Zero;
	Vector3 s_w_position2 = Vector3::Zero;
	Vector3 s_w_moveSpeed = Vector3::Zero;
	Vector3 s_w_Fowrad = { 0.0f,0.0f,1.0f };//肩装備の正面ベクトル
	int game_state = 0;
	ModelRender Shoulder_weapons_Render;
	ModelRender Shoulder_weapons_Render2;	//マシンガンの2個目

	Vector3 s_w_localPosition = { 0.0f,110.0f,0.0f };
	Vector3 scale2 = { 2.0f,2.0f,2.0f };

	bool atack_state = false;
	int set_weapons = 0;

	int firing_cound = 0;
	int fast = 0;

	float S_w_HP = 0.0f;
};

