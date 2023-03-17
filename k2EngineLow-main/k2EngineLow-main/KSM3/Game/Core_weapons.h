#pragma once

class Player;
class Core_weapons:public IGameObject
{
public:
	Core_weapons();
	~Core_weapons();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void CW_set();

	Player* cw_player = nullptr;


	Quaternion cw_Rotation;
	Vector3 cw_position;
	Vector3 cw_moveSpeed;
	Vector3 cw_Fowrad = { 0.0f,0.0f,1.0f };
	int game_state = 0;
	ModelRender Core_Weapons_Render;

	Vector3 cw_localPosition = { 0.0f,70.0f,10.0f };
	Vector3 scale = { 1.0f,1.0f,1.5f };
	bool atack_state = false;
	int set_weapons = 1;//0:��I�u�W�F�N�g 1:�M�K�v���Y�}

	int firing_cound = 0;
	int fast = 0;
};

