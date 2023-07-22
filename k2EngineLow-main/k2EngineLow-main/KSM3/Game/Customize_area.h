#pragma once
class Player;

class Customize_area : public IGameObject, Noncopyable
{
public:
	Customize_area();
	~Customize_area();
	bool Start();
	void Render(RenderContext& rc);

private:
	Player* m_player;

	std::unique_ptr<ModelRender> m_customizeAreaModel;

	Vector3 m_position = { 10000.0f,0.0f,0.0f };
	Vector3 m_scale = { 3.0f,3.0f,3.0f };

};

