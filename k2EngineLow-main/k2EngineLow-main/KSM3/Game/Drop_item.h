#pragma once
class Player;
class Customize_UI;
class Customize_UI_ver2;
class Left_arm_weapons;
class GameCamera;
class Game;

class Drop_item:public IGameObject
{
public:
	Drop_item();
	~Drop_item();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Float();
	void Set_Drop_item();
	void SetSize();
	Quaternion Drop_rotation;

	std::unique_ptr<ModelRender> Drop_item_Render;	//スマートポインタ

	Player* drop_player = nullptr;
	Left_arm_weapons* left_arm_weapons = nullptr;
	Customize_UI* customize_UI = nullptr;
	Customize_UI_ver2* customize_UI_ver2 = nullptr;
	GameCamera* m_gameCamera = nullptr;
	Game* m_game = nullptr;

	Vector3 Drop_position;//Drop位置

	bool GetState = false;
	int float_counter = 0;
	float float_level = 0.25;
	int touch_flag = 0;
	int dropCount = 0;
	int m_deleteCount = 1800;	//アイテムが消えるまでの時間
	float modelSize = 0.01f;

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

