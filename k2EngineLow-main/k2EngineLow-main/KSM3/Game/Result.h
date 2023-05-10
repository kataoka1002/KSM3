#pragma once
class Enemy;
class Player;
class Boss;
class Customize_UI_ver2;
class Core_weapons;
class Shoulder_weapons;
class Right_arm_weapons;
class Right_leg_weapons;
class Left_arm_weapons;
class Left_leg_weapons;
class Fade;
class Drop_item;
class GameCamera;


class Result:public IGameObject
{
public:
	Result();
	~Result();
	bool Start();
	void Update();
	void BackGround();
	void Enemy_count();
	void Set_count();
	void Font();
	void Rank();
	void Score_OFF();
	void Render(RenderContext& rc);

	int set=0;					//����������
	int enemy_count = 0;		//�G��|������
	int set_score = 0;			//�����������ɉ������X�R�A
	int enemy_count_score = 0;	//�G��|�������ɉ������X�R�A
	int total_score = 0;		//�g�[�^���X�R�A
	int rank = 0;				//�����N
	int result_state=0;			//�X�R�A�\���@0:ON 1:OFF

	float draw_time = 0.0f;	//���U���g��ʂɑJ�ڂ��ĕ\������܂ł̎���

	bool m_isWaitFadeout = false;
	bool time_count = false;

	ModelRender Player_modelrender;			//�v���C���[�̃��f�������_�[
	Vector3 Player_position = { 10000.0f,0.0f,0.0f };
	Quaternion Player_rotation;

	ModelRender Box_render;
	Vector3 Box_position = { 10000.0f,0.0f,0.0f };
	Vector3 Box_scale = { 3.0f,3.0f,3.0f };

	ModelRender custom_model_Core;
	Quaternion custom_model_body_rotation;
	Vector3 cw_lp;

	ModelRender custom_model_shoulder;
	Vector3 sw_lp;

	ModelRender custom_model_Right_arm;
	Vector3 raw_lp;

	ModelRender custom_model_Right_leg;
	Vector3 rlw_lp;

	ModelRender custom_model_Left_arm;
	Vector3 law_lp;

	ModelRender custom_model_Left_leg;
	Vector3 llw_lp;

	Vector3 scale2 = { 2.0f, 2.0f, 2.0f };//2�{��scale


	SpriteRender result_SpriteRender;		//���U���g�̃X�v���C�g�����_�[
	SpriteRender Mozi_render[6];			//�����̃X�v���C�g�����_�[
	SpriteRender Weapon_set_render[6];		//������Z�b�g������
	SpriteRender Boss_time_render;			//�{�X�̓|��������
	SpriteRender Enemy_count_render[31];	//�G��|������
	SpriteRender rank_render[5];			//�����N

	FontRender font_render[5];				//�t�H���g
	FontRender Boss_time_font;				//�{�X��̌o�ߎ���
	FontRender Score_font;					//�g�[�^���X�R�A
	FontRender Time_font;					//����

	Enemy* enemy;
	Player* player;
	Boss* boss;
	Customize_UI_ver2* customize_UI_ver2;
	Fade* m_fade = nullptr;
	Core_weapons* core_weapons;
	Shoulder_weapons* shoulder_weapons;
	Right_arm_weapons* right_arm_weapons;
	Right_leg_weapons* right_leg_weapons;
	Left_arm_weapons* left_arm_weapons;
	Left_leg_weapons* left_leg_weapons;
	Drop_item* drop_item;
	GameCamera* gamecamera;
};

