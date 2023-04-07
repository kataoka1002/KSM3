#pragma once

class Player;
class Drop_item;
class Left_arm_weapons;
class Right_arm_weapons;
class Customize_area;
class GameCamera;
class Core_weapons;
class Drop_item;

class Customize_UI_ver2 :public IGameObject
{
public:
	Customize_UI_ver2();
	~Customize_UI_ver2();
	void Update();
	void Setup();
	void Render(RenderContext& rc);
	void Custom_model_body();
	void Custom_model_Left_arm();
	void Custom_model_Right_arm();
	void Custom_model_Left_leg();
	void Custom_model_Right_leg();
	void Custom_model_Shoulder();
	void Custom_model_Core();
	void Custom_UI();
	void Window();
	GameCamera* C_UI_2_GameCamera;

	int custom_kinds = 0;
	
	Core_weapons* cui_core_weapons;
	Drop_item* cui_drop_item;
	Right_arm_weapons* cui_right_arm_weapons;

	SpriteRender select_sheet;
	Vector3 select_sheet_position{0.0f,350.0f,0.0f};
	SpriteRender parameter_sheet;
	Vector3 parameter_sheet_position={ -500.0f,38.0f,0.0f };

	SpriteRender confirmation_window;

	Player* custom_player;
	Customize_area* customize_area;
	
	ModelRender custom_model_body;
	ModelRender custom_model_Core;

	Quaternion custom_model_body_rotation;
	Vector3 custom_model_body_position = { 10000.0f,0.0f,0.0f };
	int custom_point[2][3] = { {0,0,0},{0,0,0} };

	int selection_position=0;
	int fast_count=0;
	int window_count = 0;
	Vector3 lp;

	bool window_open=false;
	bool confirmatino_window_open = false;
	bool window_select = false;
	int column = 0, line=0;
};

