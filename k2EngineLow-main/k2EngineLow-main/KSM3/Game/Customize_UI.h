#pragma once

class Player;
class Drop_item;
class Left_arm_weapons;
class Right_arm_weapons;

class Customize_UI:public IGameObject
{
public:
	Customize_UI();
	~Customize_UI();
	void Update();
	void Render(RenderContext& rc);
	void Custom_UI();

	int custom_kinds = 0;
	SpriteRender C_UI_Render;
	SpriteRender C_UI_Select_arrow;
	SpriteRender C_UI_window;

	SpriteRender slot_1_RA;
	SpriteRender slot_2_SD;
	SpriteRender slot_3_LA;
	SpriteRender slot_4_RL;
	SpriteRender slot_5_LL;
	SpriteRender slot_6_CI;

	Player* custom_player;
	Drop_item* c_ui_drop_item;
	Left_arm_weapons* left_arm_weapons;
	Right_arm_weapons* right_arm_weapons;
	
	int custom_point[2][3] = { {0,0,0},
						   {0,0,0} };

	int selection_position[2][3] = { {1,0,0},
								  {0,0,0} };

	Vector3 s_a_position = { -300.0f,95.0f,0.0f };

	Vector3 slot_1_position = {-333.8f,121.5f,0.0f};
	Vector3 slot_2_position = {270.0f,250.0f,0.0f};
	Vector3 slot_3_position = {338.0f,129.0f,0.0f};
	Vector3 slot_4_position = {-443.0f,-36.0f,0.0f};
	Vector3 slot_5_position = {453.0f,-28.5f,0.0f};
	Vector3 slot_6_position = {505.0f,-292.0f,0.0f};

	int cr = 0,cg = 0;
	int s_a_m_state = 0;
	bool window_open = false;
	bool delete_window_open = false;
	bool window_select = true;
	bool error_window_open = false;
	int fast_push_state = 0;
	int change_slot_x = 0, change_slot_y = 0;

	Vector3 scalec = { 0.85f,0.85f,0.0f };

};

