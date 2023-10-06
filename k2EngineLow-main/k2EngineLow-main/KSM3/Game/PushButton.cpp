#include "stdafx.h"
#include "PushButton.h"

bool PushButton::Start()
{
	m_syuutyuuSprite.Init("Assets/sprite/Button/syuutyuu.DDS", 1600.0f, 900.0f);
	m_buttonSprite.Init("Assets/sprite/Button/Abutton.DDS", 1600.0f, 900.0f);
	m_buttonSprite.SetPivot({ 0.5f, 0.0f });
	m_buttonSprite.SetPosition({ 0.0f,-420.0f,0.0f });
	m_buttonSprite.Update();
	m_oseSprite.Init("Assets/sprite/Button/ose.DDS", 1600.0f, 900.0f);

	return true;
}

void PushButton::Update()
{
	m_syuutyuuScale.x += 0.0003f;
	m_syuutyuuSprite.SetScale(m_syuutyuuScale);
	m_syuutyuuSprite.Update();

	float m_moveSpeedOse = (1.0f - m_oseScale.x) / 30.0f;
	m_oseScale.x += m_moveSpeedOse;
	m_oseScale.y += m_moveSpeedOse;
	m_oseSprite.SetScale(m_oseScale);
	m_oseSprite.Update();

	float m_moveSpeedButton = (1.0f - m_buttonScale.x) / 30.0f;
	m_buttonScale.x += m_moveSpeedButton;
	m_buttonScale.y += m_moveSpeedButton;
	m_buttonSprite.SetScale(m_buttonScale);
	m_buttonSprite.Update();	
}

void PushButton::Render(RenderContext& rc)
{
	m_syuutyuuSprite.Draw(rc);
	m_oseSprite.Draw(rc);
	m_buttonSprite.Draw(rc);
}