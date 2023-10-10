#include "stdafx.h"
#include "PushButton.h"
#include "Game.h"

bool PushButton::Start()
{
	//�W����
	m_syuutyuuSprite.Init("Assets/sprite/Button/syuutyuu.DDS", 1600.0f, 900.0f);

	//A�{�^��
	m_buttonSprite.Init("Assets/sprite/Button/Abutton.DDS", 1600.0f, 900.0f);
	m_buttonSprite.SetPivot({ 0.5f, 0.0f });
	m_buttonSprite.SetPosition({ 0.0f,-420.0f,0.0f });
	m_buttonSprite.Update();

	//���{�^��
	m_niziButtonSprite.Init("Assets/sprite/Button/niziButton.DDS", 1600.0f, 900.0f);
	m_niziButtonSprite.SetPosition({ 0.0f,-200.0f,0.0f });
	m_niziButtonSprite.Update();

	//����
	m_oseSprite.Init("Assets/sprite/Button/ose.DDS", 1600.0f, 900.0f);

	return true;
}

void PushButton::Update()
{
	//�傫���̌v�Z
	CalcScale();

	if (m_niziButtonFlag == true)
	{
		//���{�^���������Â傫������
		PlayNiziButton();
	}

	if (m_niziButtonScale.x >= 2.0f)
	{
		//�{�^��������������
		Game* m_game = FindGO<Game>("game");
		m_game->SetOffPushButton();
	}
}

void PushButton::CalcScale()
{
	//�W�����������Â傫������
	m_syuutyuuScale.x += 0.0003f;
	m_syuutyuuSprite.SetScale(m_syuutyuuScale);
	m_syuutyuuSprite.Update();

	//�����������Â傫������
	float m_moveSpeedOse = (1.0f - m_oseScale.x) / 30.0f;
	m_oseScale.x += m_moveSpeedOse;
	m_oseScale.y += m_moveSpeedOse;
	m_oseSprite.SetScale(m_oseScale);
	m_oseSprite.Update();

	//A�{�^���������Â傫������
	float m_moveSpeedButton = (1.0f - m_buttonScale.x) / 30.0f;
	m_buttonScale.x += m_moveSpeedButton;
	m_buttonScale.y += m_moveSpeedButton;
	m_buttonSprite.SetScale(m_buttonScale);
	m_buttonSprite.Update();
}

void PushButton::PlayNiziButton()
{
	//���{�^���������Â傫������
	m_niziButtonScale.x += 0.1f;
	m_niziButtonScale.y += 0.1f;

	m_niziButtonSprite.SetScale(m_niziButtonScale);
	m_niziButtonSprite.Update();
}

void PushButton::Render(RenderContext& rc)
{
	m_syuutyuuSprite.Draw(rc);
	if (m_niziButtonFlag == true)
	{
		m_niziButtonSprite.Draw(rc);
	}
	m_oseSprite.Draw(rc);
	m_buttonSprite.Draw(rc);
}