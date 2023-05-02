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

	Vector3 title_scale{ 0.85f,0.85f,0.0f };
};

