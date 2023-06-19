#include "stdafx.h"
#include "GuideLight.h"
#include "Game.h"
#include "Player.h"

GuideLight::GuideLight()
{

}

GuideLight::~GuideLight()
{

}

bool GuideLight::Start()
{

	//�������̊m��
	m_modelRender = std::make_unique<ModelRender>();


	//���f���̏�����
	m_modelRender->Init("Assets/modelData/V_P_Bullet.tkm");
	m_modelRender->SetPosition(m_position);
	m_modelRender->SetScale(SCALE);
	m_modelRender->Update();
	
	return true;
}

void GuideLight::Update()
{
	//���f���̈ړ��n�̏���
	const float BULLET_SPPED = 20.0f;
	const float CURVATURE_RADIUS = 30.0f;
	const float DAMPING = 0.1f;

	CalcVelocity(BULLET_SPPED, CURVATURE_RADIUS, DAMPING);
	m_position += m_velocity;
	m_modelRender->SetPosition(m_position);
	m_modelRender->Update();

	//2�t���[�����Ɍ�����
	if (count % 2 == 0)
	{
		m_guideLightEffect = NewGO<EffectEmitter>(0);
		m_guideLightEffect->Init(enGuide);
		m_guideLightEffect->SetScale({ 0.5f,0.5f,0.5f });
		m_guideLightEffect->SetPosition(m_position);
		m_guideLightEffect->Play();
	}

	//������x���Ԃ����Ə�����
	if (count >= 120)
	{
		DeleteGO(this);
	}
	count++;
}

void GuideLight::CalcVelocity(const float speed, const float curvatureRadius,const float damping)
{
	//?
	float maxCentripetalAccel = speed * speed / curvatureRadius;
	float propulsion = speed * damping;

	Vector3 targetPosition = m_targetPosition;
	Vector3 toTarget = targetPosition - m_position;
	Vector3 vn = m_velocity;
	vn.Normalize();
	float dot = toTarget.Dot(vn);
	Vector3 centripetalAccel = toTarget - (vn * dot);
	float centripetalAccelMagnitude = centripetalAccel.Length();
	if (centripetalAccelMagnitude > 1.0f)
	{
		centripetalAccel /= centripetalAccelMagnitude;
	}
	Vector3 force = centripetalAccel * curvatureRadius;
	force += vn * propulsion;
	force -= m_velocity * damping;
	m_velocity += force * g_gameTime->GetFrameDeltaTime();
}

void GuideLight::Render(RenderContext& rc)
{
	//�e�͌����Ȃ��Ă悢
	//m_modelRender->Draw(rc);
}