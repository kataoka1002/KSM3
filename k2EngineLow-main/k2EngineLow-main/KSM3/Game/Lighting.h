#pragma once
class Lighting:public IGameObject
{
public:
	Lighting();
	~Lighting();
	void Update();
	bool Start();



	Vector3 Light_Direction = { 0.0f,-1.0f,0.0f };
	Vector3 spLightDirection = { 0.0f,0.0f,1.0f };
	Vector3 Light_Color = { 0.6f,0.6f,0.6f };
	Vector3 spLightColor = { 1.0f,1.0f,1.0f };

private:

};

