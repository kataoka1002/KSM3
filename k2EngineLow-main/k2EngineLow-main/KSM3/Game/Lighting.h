#pragma once
class Lighting:public IGameObject
{
public:
	Lighting();
	~Lighting();
	void Update();

	Vector3 Light_Direction = { 0.0f,-1.0f,0.0f };
	Vector3 Light_Color = { 0.6f,0.6f,0.6f };
};

