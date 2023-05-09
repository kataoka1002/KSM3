#pragma once

//class Fade;

class Title:public IGameObject
{
public:
	Title();
	~Title();
	void Update();
	bool Start();
	void S();
	void Render(RenderContext& rc);

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
};

