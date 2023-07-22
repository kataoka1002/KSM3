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
	//���S�͂����߂�
	float maxCentripetalAccel = speed * speed / curvatureRadius;

	//�X�s�[�h�Ɍ������������ċt�����ւ̗͂����߂�
	float propulsion = speed * damping;

	//�ڕW�̒n�_
	Vector3 targetPosition = m_targetPosition;

	//�ڕW�܂ł̃x�N�g��
	Vector3 toTarget = targetPosition - m_position;

	//���x��ݒ肵�A���K�����đł��o���ꂽ�������擾
	Vector3 vn = m_velocity;
	vn.Normalize();

	//�ڕW�܂ł̃x�N�g���Ƒł��o���ꂽ�����̓��ς����߂�(�G�֌������x�N�g����vn�Ɏˉe�� T'�̑傫�������܂�)
	float dot = toTarget.Dot(vn);

	//T'����ڕW�܂ł̃x�N�g��(�Ȃ��邽�߂ɉ���������x)�����߂�
	Vector3 centripetalAccel = toTarget - (vn * dot);

	//���̒��������߂�
	float centripetalAccelMagnitude = centripetalAccel.Length();

	//1�ȏ�Ȃ璷����1�ɐ��K����,1�����Ȃ炻�̂܂�
	if (centripetalAccelMagnitude > 1.0f)
	{
		//�x�N�g���̐��K�����s��
		centripetalAccel /= centripetalAccelMagnitude;
	}

	//������maxCentripetalAccel�ȉ��Ȃ炻�̂܂܁A�ȏ�Ȃ璷����maxCentripetalAccel�ɂ���
	Vector3 force = centripetalAccel * maxCentripetalAccel;

	//���i��
	force += vn * propulsion;

	//��C��R
	force -= m_velocity * damping;

	//���x�ϕ�
	m_velocity += force * g_gameTime->GetFrameDeltaTime();
}

void GuideLight::Render(RenderContext& rc)
{
	//�e�͌����Ȃ��Ă悢
	//m_modelRender->Draw(rc);
}