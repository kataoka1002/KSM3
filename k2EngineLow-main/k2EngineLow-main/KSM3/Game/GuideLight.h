#pragma once
class GuideLight : public IGameObject
{
public:
	GuideLight();
	~GuideLight();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void CalcVelocity(const float speed, const float curvatureRadius, const float damping);

	/// <summary>
	/// 速さをセットする
	/// </summary>
	/// <param name="vel"></param>
	void SetVelocity(Vector3 vel)
	{
		m_velocity = vel;
	}

	/// <summary>
	/// ターゲットポジションの設定
	/// </summary>
	/// <param name="targetPos">ターゲットポジション</param>
	void SetTargetPosition(Vector3 targetPos)
	{
		m_targetPosition = targetPos;
	}

	/// <summary>
	/// ポジションの設定
	/// </summary>
	/// <param name="pos">ポジション</param>
	void SetPosition(Vector3 pos)
	{
		m_position = pos;
	}

private:
	std::unique_ptr<ModelRender> m_modelRender;
	EffectEmitter* m_guideLightEffect = nullptr;
	int count = 0;
	Vector3 m_position = Vector3::Zero;
	Vector3 m_velocity = Vector3::Zero;
	Vector3 m_targetPosition = Vector3::Zero;
	Vector3 SCALE = { 0.5f,0.5f,0.5f };


};

