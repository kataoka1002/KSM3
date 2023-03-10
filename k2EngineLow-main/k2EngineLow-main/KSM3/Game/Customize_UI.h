#pragma once

class Player;
class Drop_item;
class Left_arm_weapons;

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

	SpriteRender slot_1_LA;
	SpriteRender slot_2_RA;
	SpriteRender slot_3_LL;
	SpriteRender slot_4_RL;
	SpriteRender slot_5_SD;
	SpriteRender slot_6_CI;

	Player* custom_player;
	Drop_item* c_ui_drop_item;
	Left_arm_weapons* left_arm_weapons;
	
	int custom_point[2][3] = { {0,0,0},
						   {0,0,0} };

	int selection_position[2][3] = { {1,0,0},
								  {0,0,0} };

	Vector3 s_a_position = { -300.0f,95.0f,0.0f };
	int cr = 0,cg = 0;
	int s_a_m_state = 0;
	bool window_open = false;
	bool delete_window_open = false;
	bool window_select = true;
	int fast_push_state = 0;

	Vector3 scalec = { 0.85f,0.85f,0.0f };
};

