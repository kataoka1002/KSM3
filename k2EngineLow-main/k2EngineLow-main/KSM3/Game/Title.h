#pragma once

class Fade;

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
	SpriteRender gameStart_Render;
	SpriteRender system_Render;
	SpriteRender nannka_Render;
	SpriteRender yajirusi_Render;
	bool m_isWaitFadeout = false;
	float m_alpha = 0.0f;
	Fade* m_fade = nullptr;
	int State = 0;

	ModelRender model_batt;//battleship_gun
	ModelRender model_mac;//machine_gun
	ModelRender model_giga;//Giga_Plasma
	ModelRender title_back;//�w�i�B
	Quaternion x_Rot;//���f����x����]�B
	Quaternion y_Rot;//���f����y����]�B
	Quaternion m_Rot;//���̑��̉�]�B
	Vector3 model_position = { -300.0f,50.0f,200.0f };//���f�������̋��ꏊ�B
	//Vector3 pos = { 0.0f,80.0f,300.0f };//���ꏊ����2�B
	Vector3 titel_back = {0.0f,-100.0f,100.0f};
	int scale = 10.0f;//���f���̑傫���B
	float m_timer;//���ԁB
	int time = 0;//time���ĂȂ��Ă邯�ǃX�e�[�g�ł��B
	int pattern = 0;//�p�^�[�����S���B


	float x;
	float y;

	Vector3 title_scale{ 0.85f,0.85f,0.0f };
};

