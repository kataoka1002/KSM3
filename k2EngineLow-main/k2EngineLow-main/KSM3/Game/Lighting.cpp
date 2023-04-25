#include "stdafx.h"
#include "Lighting.h"

Lighting::Lighting() {
	//ライト方向の正規化
	Light_Direction.Normalize();
	spLightDirection.Normalize();

	//ディレクションライトの設定
	g_renderingEngine->SetDirectionLight(Light_Direction, Light_Color);
	//カスタムエリアのライトの設定
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

