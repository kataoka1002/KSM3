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
	/// �������Z�b�g����
	/// </summary>
	/// <param name="vel"></param>
	void SetVelocity(Vector3 vel)
	{
		m_velocity = vel;
	}

	/// <summary>
	/// �^�[�Q�b�g�|�W�V�����̐ݒ�
	/// </summary>
	/// <param name="targetPos">�^�[�Q�b�g�|�W�V����</param>
	void SetTargetPosition(Vector3 targetPos)
	{
		m_targetPosition = targetPos;
	}

	/// <summary>
	/// �|�W�V�����̐ݒ�
	/// </summary>
	/// <param name="pos">�|�W�V����</param>
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

