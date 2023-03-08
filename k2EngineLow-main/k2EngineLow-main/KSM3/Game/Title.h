#pragma once
class Title:public IGameObject
{
public:
	Title();
	~Title();
	void Update();
	void Render(RenderContext& rc);

	SpriteRender title_Render;
};

