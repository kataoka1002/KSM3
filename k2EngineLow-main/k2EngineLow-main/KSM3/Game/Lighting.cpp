#include "stdafx.h"
#include "Lighting.h"

Lighting::Lighting()
{

	//ライト方向の正規化
	m_dirLightDirection.Normalize();
	m_spLightDirection.Normalize();


	//ディレクションライトの設定
	g_renderingEngine->SetDirectionLight(m_dirLightDirection, m_dirLightColor);


	//カスタムエリアのライトの設定
	g_renderingEngine->SetSpotLight(0, m_spLightPosition, m_spLightRange, m_spLightColor, m_spLightDirection, m_spLightAngle);

}

