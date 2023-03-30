#pragma once

class Test :public IGameObject
{
public:
	Test();
	~Test();
	bool Start();
	void Update();
	void Draw(RenderContext& rc);

	Vector3 nana = { -1.0f,-1.0f,1.0f };
	Vector3 col = { 1.0f,1.0f,1.0f };
};

