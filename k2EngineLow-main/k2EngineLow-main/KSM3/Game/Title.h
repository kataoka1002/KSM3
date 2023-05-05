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
	ModelRender title_back;//背景。
	Quaternion x_Rot;//モデルのx軸回転。
	Quaternion y_Rot;//モデルのy軸回転。
	Quaternion m_Rot;//その他の回転。
	Vector3 model_position = { -300.0f,50.0f,200.0f };//モデルたちの居場所。
	//Vector3 pos = { 0.0f,80.0f,300.0f };//居場所その2。
	Vector3 titel_back = {0.0f,-100.0f,100.0f};
	int scale = 10.0f;//モデルの大きさ。
	float m_timer;//時間。
	int time = 0;//timeってなってるけどステートです。
	int pattern = 0;//パターンを４つ程。


	float x;
	float y;

	Vector3 title_scale{ 0.85f,0.85f,0.0f };
};

