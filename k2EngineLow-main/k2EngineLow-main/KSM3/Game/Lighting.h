#pragma once
class Lighting:public IGameObject, Noncopyable
{
public:
	Lighting();

private:
	//ディレクションライト系
	Vector3 m_dirLightDirection = { 0.0f,-1.0f,0.0f };
	Vector3 m_dirLightColor = { 0.6f,0.6f,0.6f };

	//スポットライト系
	Vector3 m_spLightDirection = { 0.0f,0.0f,1.0f };
	Vector3 m_spLightColor = { 1.0f,1.0f,1.0f };
	Vector3 m_spLightPosition = { 10000.0f,70.0f,-100.0f };
	float m_spLightRange = 1000.0f;
	float m_spLightAngle = 45.0f;
}; 

