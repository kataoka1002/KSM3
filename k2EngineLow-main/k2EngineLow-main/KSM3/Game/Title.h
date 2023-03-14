#pragma once
class Title:public IGameObject
{
public:
	Title();
	~Title();
	void Update();
	void Render(RenderContext& rc);

	SpriteRender title_Render;

	Vector3 title_scale{ 0.85f,0.85f,0.0f };
};

