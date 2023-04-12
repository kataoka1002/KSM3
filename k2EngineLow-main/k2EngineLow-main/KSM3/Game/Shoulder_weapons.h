#pragma once
class Player;
class Battle_ship_attack;

class Shoulder_weapons:public IGameObject
{
public:
	Shoulder_weapons();
	~Shoulder_weapons();

	void Update();
	void Render(RenderContext& rc);
	void Move();
	void S_w_set();

	Player* s_w_player = nullptr;
	Battle_ship_attack* battle_ship_attack;

	Quaternion Shoulder_Rotation;
	Vector3 s_w_position;
	Vector3 s_w_moveSpeed;
	Vector3 s_w_Fowrad = { 0.0f,0.0f,1.0f };//Œ¨‘•”õ‚Ì³–ÊƒxƒNƒgƒ‹
	int game_state = 0;
	ModelRender Shoulder_weapons_Render;

	Vector3 s_w_localPosition = {0.0f,110.0f,0.0f };
	Vector3 scale2 = { 2.0f,2.0f,2.0f };

	bool atack_state = false;
	int set_weapons = 0;

	int firing_cound = 0;
	int fast = 0;

	float S_w_HP = 0.0f;
};

