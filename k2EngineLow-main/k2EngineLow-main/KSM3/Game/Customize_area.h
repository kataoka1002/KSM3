#pragma once
class Player;
class Customize_area:public IGameObject
{
public:
	Customize_area();
	~Customize_area();

	Player* c_area_player;
	void Render(RenderContext& rc);
	ModelRender customize_area_render;

	Vector3 C_area_position = { 10000.0f,0.0f,0.0f };
	Vector3 c_area_scale = { 3.0f,3.0f,3.0f };
};

