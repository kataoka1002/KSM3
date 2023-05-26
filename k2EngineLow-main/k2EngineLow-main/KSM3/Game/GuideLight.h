#pragma once
class GuideLight : public IGameObject
{
public:
	GuideLight();
	~GuideLight();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	void CalcVelocity(const float speed, const float curvatureRadius, const float damping);

public:
	ModelRender m_modelRender;
	EffectEmitter* m_guideLightEffect = nullptr;
	int count = 0;
	Vector3 m_position = Vector3::Zero;
	Vector3 m_velocity = Vector3::Zero;
	Vector3 m_targetPosition = Vector3::Zero;
	Vector3 SCALE = { 0.5f,0.5f,0.5f };

private:
};

