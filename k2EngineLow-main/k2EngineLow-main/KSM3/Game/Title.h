#pragma once

//class Fade;

class Title:public IGameObject
{
public:
	Title();
	~Title();
	void Update();
	void Render(RenderContext& rc);

	SpriteRender title_Render;
	//Fade* m_fade = nullptr;
	bool				m_isWaitFadeout = false;

	Vector3 title_scale{ 0.85f,0.85f,0.0f };
};

