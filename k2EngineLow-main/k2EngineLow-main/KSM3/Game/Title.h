#pragma once
class Lighting;
class SoundManage;
//class Fade;

class Title:public IGameObject
{
public:
	Title();
	~Title();
	void Update();
	bool Start();
	void SetUp();
	void S();
	void Title_Move();
	void Menu();
	void Render(RenderContext& rc);
	void PlaySE(int track_number, float vol);

	Lighting* lighting = nullptr;

	SpriteRender title_Render;
	SpriteRender gameStart_Render;	//�X�^�[�g�{�^���B
	SpriteRender system_Render;		//�V�X�e���ݒ�{�^���B
	SpriteRender nannka_Render;		//�v���X�łȂ񂩂������Ƃ��́B
	SpriteRender yajirusi_Render;	//����I�𒆂�������p�̂₶�邵�B
	//bool m_isWaitFadeout = false;
	//float m_alpha = 0.0f;
	//Fade* m_fade = nullptr;
	int State = 0;

	ModelRender model_batt;//battleship_gun
	ModelRender model_mac;//machine_gun
	ModelRender model_giga;//Giga_Plasma
	ModelRender title_back;//�w�i�B
	Quaternion x_Rot;//���f����x����]�B
	Quaternion y_Rot;//���f����y����]�B
	Quaternion m_Rot;//���̑��̉�]�B
	Vector3 model_position = { -300.0f,50.0f,200.0f };//���f�������̋��ꏊ�B
	Vector3 titel_back = {0.0f,-100.0f,100.0f};
	int scale = 10.0f;//���f���̑傫���B
	Vector3 target = { -300.0f,50.0f,200.0f };
	Vector3 pos= { -300.0f,-50.0f,-50.0f };//�J�����̋��ꏊ�B
	float m_timer;//���ԁB
	int time = 0;//time���ĂȂ��Ă邯�ǃX�e�[�g�ł��B
	int pattern = 0;//�p�^�[�����S���B


	float x;
	float y;

	Vector3 title_scale{ 0.85f,0.85f,0.0f };

	int  title_state = 0;//0:�^�C�g�� 1:�J�ڑO�� 2:�J�ڌ㔼 3:���C�����j���[ 4:Loading 5:option 6:

	//�^�C�g���̃X�v���C�g�����_�[�̐錾
	int select_point = 0;
	int fast_count=1;

	SpriteRender Title_Render;
	SpriteRender Press_Render;
	Vector4 Press_Render_coler = { 1.0f,1.0f,1.0f,1.0f };
	int Press_count = 0;
	int Press_direction = -1;
	
	SpriteRender Whiteout;
	Vector4 whiteout_color = { 1.0f,1.0f,1.0f,0.0f };
	int whiteout_count = 0;

	SpriteRender Side_line_Render;
	SpriteRender MAIN_MENU_Render;
	SpriteRender Main_menu_foundation_Render;
	Vector4 Main_menu_foundation_Render_color = { 1.0f,1.0f,1.0f,0.5f };

	SpriteRender OK_BACK_Render;
	SpriteRender Select_point_Render;
	SpriteRender Select_point_pow_Render;
	Vector4 Select_point_pow_color = { 1.0f,1.0f,1.0f,2.0f };
	int Select_point_pow_count = 0;
	int Select_point_pow_direction = -1;
	Vector3 Select_position = { 0.0f,0.0f,0.0f };

	SpriteRender Loading_Render;
	Vector4  Loading_color = { 1.0f,1.0f,1.0f,0.0f };
	int Loading_count = 0;
	int Loading_direction = -1;

	SpriteRender Option_Render;

	SpriteRender Sound_Render;
	SpriteRender Sound_Render2;
	SpriteRender Sound_Render3;
	int sound_set_state = 0;//0:�����Ȃ� 1:BGM 2:SE
	SpriteRender BGM_Sound_ber;
	float BGM_volume = 1.0f;//BGM�̃{�����[��
	SpriteRender SE_Sound_ber;
	float SE_volume = 1.0f;//SE�̃{�����[��
	Vector2 BGM_ber_pivot = { 0.0f,0.5f };
	Vector2 SE_ber_pivot = { 0.0f,0.5f };
	Vector3 BGM_ber_scale = { 0.85f,0.85f,1.0f };
	Vector3 SE_ber_scale = { 0.85f,0.85f,1.0f };
	Vector3 BGM_ber_position = { -352.7f,169.4f,0.0f };
	Vector3 SE_ber_position = { -352.7f,101.5f,0.0f };
	Vector4 SOUND_color = { 1.0f,1.0f,1.0f,1.0f };

	SpriteRender CONTROLES_Render;

	SpriteRender Menu_trance[9];
	Vector3 Menu_trance_position0 = { -651.0f,316.5f,0.0f};//�^�C�g������
	Vector3 Menu_trance_position1 = { -646.0f,170.0f,0.0f };//���j���[1�i��
	Vector3 Menu_trance_position2 = { -646.0f,100.0f,0.0f };//���j���[2�i��
	Vector3 Menu_trance_position3 = { -646.0f,30.0f,0.0f };//���j���[3�i��
	Vector3 Menu_trance_position4 = { -646.0f,-39.5f,0.0f };//���j���[4�i��
	Vector3 Menu_trance_position5 = { -646.0f,-107.0f,0.0f };//���j���[5�i��
	Vector3 Menu_trance_position6 = { -646.0f,-176.5f,0.0f };//���j���[6�i��
	Vector3 Menu_trance_position7 = { -646.0f,-244.0f,0.0f };//���j���[6�i��
	Vector3 Menu_trance_position8 = { -646.0f,-394.0f,0.0f };//OK_BACK����

	Vector2 Menu_trance_pivot0 = { 0.0f,0.5f };
	Vector2 Menu_trance_pivot1 = { 0.0f,0.5f };
	Vector2 Menu_trance_pivot2 = { 0.0f,0.5f };
	Vector2 Menu_trance_pivot3 = { 0.0f,0.5f };
	Vector2 Menu_trance_pivot4 = { 0.0f,0.5f };
	Vector2 Menu_trance_pivot5 = { 0.0f,0.5f };
	Vector2 Menu_trance_pivot6 = { 0.0f,0.5f };
	Vector2 Menu_trance_pivot7 = { 0.0f,0.5f };
	Vector2 Menu_trance_pivot8 = { 0.0f,0.5f };

	Vector3 Trance_sheet_scale = { 0.0f,0.85f,1.0f };

	SpriteRender Player_Color_Render;
	int player_color_date = 0;
};

