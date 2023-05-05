#pragma once

class Player;
class BattleShipBullet;
class Right_arm_UI;

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
	BattleShipBullet* battle_ship_attack;
	Right_arm_UI* right_arm_ui;

	Quaternion r_a_Rotation;
	Vector3 r_a_w_position;
	Vector3 r_a_w_moveSpeed;
	Vector3 r_a_w_Fowrad = { 0.0f, 0.0f, 1.0f };//���r�����̐��ʃx�N�g��
	int game_state = 0;
	ModelRender Right_arm_weapons_Render;

	Vector3 r_a_w_localPosition = { 60.0f,70.0f,-10.0f };
	Vector3 scale2 = { 2.0f,2.0f,2.0f };

	bool atack_state = false;
	int set_weapons = 0;

	int firing_cound=0;
	int fast = 0;

	float R_a_w_HP = 0.0f;
};

