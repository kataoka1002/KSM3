#pragma once

class Fade;
class Player;
class GameCamera;

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
	GameCamera* gameCamera;
	Player* player;

	ModelRender model_batt;
	ModelRender model_mac;
	ModelRender title_back;
	Vector3 titel_back = {0.0f,0.0f,100.0f};
	int scale = 4.0f;

	Vector3 title_scale{ 0.85f,0.85f,0.0f };
};

