#include "stdafx.h"
#include "Lighting.h"

Lighting::Lighting()
{

	//���C�g�����̐��K��
	m_dirLightDirection.Normalize();
	m_spLightDirection.Normalize();


	//�f�B���N�V�������C�g�̐ݒ�
	g_renderingEngine->SetDirectionLight(m_dirLightDirection, m_dirLightColor);


	//�J�X�^���G���A�̃��C�g�̐ݒ�
	g_renderingEngine->SetSpotLight(0, m_spLightPosition, m_spLightRange, m_spLightColor, m_spLightDirection, m_spLightAngle);

}

