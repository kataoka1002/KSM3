#include "stdafx.h"
#include "Lighting.h"

Lighting::Lighting() {
	//���C�g�����̐��K��
	Light_Direction.Normalize();
	spLightDirection.Normalize();

	//�f�B���N�V�������C�g�̐ݒ�
	g_renderingEngine->SetDirectionLight(Light_Direction, Light_Color);
	//�J�X�^���G���A�̃��C�g�̐ݒ�
	g_renderingEngine->SetSpotLight(0, {10000.0f,70.0f,-100.0f}, 1000.0f, spLightColor, spLightDirection, 45.0f);
}

bool Lighting::Start()
{
	return true;
}

Lighting::~Lighting() {

}

void Lighting::Update()
{

}

