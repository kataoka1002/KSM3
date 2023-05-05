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
	void trance_setup();
	void trance();

	GameCamera* C_UI_2_GameCamera;

	int custom_kinds = 0;
	
	Core_weapons* cui_core_weapons;
	Drop_item* cui_drop_item;
	Right_arm_weapons* cui_right_arm_weapons;
	Left_arm_weapons* cui_left_arm_weapons;
	Shoulder_weapons* cui_shoulder_weapons;
	Right_leg_weapons* cui_right_leg_weapons;
	Left_leg_weapons* cui_left_leg_weapons;

	SpriteRender select_sheet;
	Vector3 select_sheet_position{0.0f,650.0f,0.0f};//350
	SpriteRender parameter_sheet;
	Vector3 parameter_sheet_position={ -1200.0f,38.0f,0.0f };//-500

	SpriteRender confirmation_window;

	Player* custom_player;
	Customize_area* customize_area;
	
	ModelRender custom_model_body;
	ModelRender custom_model_Core;
	ModelRender custom_model_shoulder;
	ModelRender custom_model_Right_arm;
	ModelRender custom_model_Right_leg;
	ModelRender custom_model_Left_arm;
	ModelRender custom_model_Left_leg;

	Quaternion custom_model_body_rotation;
	Vector3 custom_model_body_position = { 10500.0f,0.0f,0.0f };//10000

	int custom_point[2][3] = { {0,0,0},{0,0,0} };

	int selection_position=0;
	int fast_count=0;
	int window_count = 0;
	Vector3 cw_lp;//�R�A�����̃��[�J���|�W�V����
	Vector3 raw_lp;//�E�r�����̃��[�J���|�W�V����
	Vector3 law_lp;//���r�����̃��[�J���|�W�V����
	Vector3 sw_lp;//�������̃��[�J���|�W�V����
	Vector3 rlw_lp;//�E�������̃��[�J���|�W�V����
	Vector3 llw_lp;//���������̃��[�J���|�W�V����

	bool right_arm_weapon_set = false;//�E��̑������Z�b�g����Ă��邩
	bool Left_arm_weapon_set = false;//����̑������Z�b�g����Ă��邩
	bool Shoulder_weapon_set = false;//���̑������Z�b�g����Ă��邩
	bool Right_leg_weapon_set = false;//�E���̑������Z�b�g����Ă��邩
	bool Left_leg_weapon_set = false;//�����̑������Z�b�g����Ă��邩

	Vector3 scale2 = { 2.0f, 2.0f, 2.0f };//2�{��scale
	bool window_open=false;//�E�B���h�E���I�[�v�����邩
	bool confirmatino_window_open = false;//�m�F�E�B���h�E�̕\���m�F
	bool window_select = false;//�E�B���h�E�̑I�����̂ǂ������I������Ă��邩
	int column = 0, line=0;

	int trance_state = 1;//�J�ڂ̃X�e�[�g0:�J�ڏI�� 1:�J�ڒ�

	SpriteRender trance_sheet[4];//�J�ڎ��̍��B�� 1,2:�� 3,4:��

	Vector3 trance_sheet01_position = { 2880.0f,-530.0f,0.0f };
	Vector3 trance_sheet02_position = { 2880.0f,-530.0f,0.0f };
	Vector3 trance_sheet03_position = { -2880.0f,530.0f,0.0f };
	Vector3 trance_sheet04_position = { -2880.0f,530.0f,0.0f };

	int trance_sheet_count=0;//�J�ڃJ�E���g
	Vector4 trance_sheet_color{ 0.0f,0.0f,0.0f,1.0f };
	//float trance_sheet_�� = 1;//�A���t�@�l
};

