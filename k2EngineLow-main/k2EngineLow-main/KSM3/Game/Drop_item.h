#pragma once
class Player;
class Customize_UI;
class Customize_UI_ver2;
class Left_arm_weapons;

class Drop_item:public IGameObject
{
public:
	Drop_item();
	~Drop_item();

	void Update();
	void Render(RenderContext& rc);
	void Float();
	void Set_Drop_item();
	Quaternion Drop_rotation;

	ModelRender Drop_item_Render;

	Player* drop_player;
	Left_arm_weapons* left_arm_weapons;
	Customize_UI* customize_UI = nullptr;
	Customize_UI_ver2* customize_UI_ver2 = nullptr;

	Vector3 Drop_position;//DropˆÊ’u

	bool GetState = false;
	int float_counter = 0;
	float float_level = 0.25;
	int touch_flag = 0;


	int drop_weapons[12] = {  0,	//non
							  0,	//Battleship_gun
							  0,
							  0,
							  0,
							  0,
							  0,
							  0,
							  0,
							  0,
							  0,
							  0 };
	int drop_kinds = 0;
};

