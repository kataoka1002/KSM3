#pragma once

class Player;
class Drop_item;
class Left_arm_weapons;
class Right_arm_weapons;
class Customize_area;
class GameCamera;
class Core_weapons;
class Drop_item;
class Shoulder_weapons;
class Right_leg_weapons;
class Left_leg_weapons;


class Customize_UI_ver2 :public IGameObject
{
public:
	Customize_UI_ver2();
	~Customize_UI_ver2();
	bool Start();
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


	GameCamera* m_gameCamera = nullptr;
	Core_weapons* m_coreWeapon = nullptr;
	Drop_item* m_dropItem = nullptr;
	Right_arm_weapons* m_rightArmWeapon = nullptr;
	Left_arm_weapons* m_leftArmWeapon = nullptr;
	Shoulder_weapons* m_shoulderWeapon = nullptr;
	Right_leg_weapons* m_rightLegWeapon = nullptr;
	Left_leg_weapons* m_leftLegWeapon = nullptr;

	SpriteRender m_selectSheet;
	Vector3 m_selectSheetPosition{0.0f,350.0f,0.0f};
	SpriteRender m_parameterSheet;
	Vector3 m_parameterSheetPosition={ -500.0f,38.0f,0.0f };

	SpriteRender m_confirmationWindow;

	Player* m_player = nullptr;
	Customize_area* m_customizeArea;
	
	ModelRender custom_model_body;
	ModelRender custom_model_Core;
	ModelRender custom_model_shoulder;
	ModelRender custom_model_Right_arm;
	ModelRender custom_model_Right_leg;
	ModelRender custom_model_Left_arm;
	ModelRender custom_model_Left_leg;

	Quaternion custom_model_body_rotation;
	Vector3 custom_model_body_position = { 10000.0f,0.0f,0.0f };

	int custom_point[2][3] = { {0,0,0},
							   {0,0,0} };
	int custom_kinds = 0;
	int selection_position=0;
	int fast_count=0;
	int window_count = 0;
	Vector3 cw_lp;
	Vector3 raw_lp;
	Vector3 law_lp;
	Vector3 sw_lp;
	Vector3 rlw_lp;
	Vector3 llw_lp;

	bool right_arm_weapon_set = false;
	bool Left_arm_weapon_set = false;
	bool Shoulder_weapon_set = false;
	bool Right_leg_weapon_set = false;
	bool Left_leg_weapon_set = false;

	Vector3 scale2 = { 2.0f, 2.0f, 2.0f };
	bool window_open=false;
	bool confirmatino_window_open = false;
	bool window_select = false;
	int column = 0, line=0;
};

