#pragma once

class Player;
class Drop_item;
class Left_arm_weapons;
class Right_arm_weapons;
class Customize_area;

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

	int custom_kinds = 0;
	

	Player* custom_player;
	Customize_area* customize_area;
	
	ModelRender custom_model_body;

	Quaternion custom_model_body_rotation;
	Vector3 custom_model_body_position = { 10000.0f,0.0f,0.0f };
	int custom_point[2][3] = { {0,0,0},
						   {0,0,0} };

	int selection_position[2][3] = { {1,0,0},
								  {0,0,0} };


};

