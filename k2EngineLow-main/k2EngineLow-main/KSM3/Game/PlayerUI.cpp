#include "stdafx.h"
#include "PlayerUI.h"
#include "Player.h"

PlayerUI::PlayerUI()
{

}

PlayerUI::~PlayerUI()
{

}

bool PlayerUI::Start()
{
	m_player = FindGO<Player>("player");

	m_HPSprite.Init("Assets/sprite/player/playerUI.dds", 691.0f, 597.0f);
	m_HPSprite.SetPosition({ 600.0f,-300.0f,0.0f });
	m_HPSprite.SetScale({ 0.4f,0.4f,0.4f });
	m_HPSprite.SetMulColor({ UI_START_COLLAR_R,UI_START_COLLAR_G,0.0f,1.0f });
	m_HPSprite.SetMulColor({ 1.0f,0.0,0.0f,1.0f });
	m_HPSprite.Update();

	return true;
}

void PlayerUI::Update()
{
	//Damage();
	float m_collarG;	//�ΐF�̗�
	float m_collarR;	//�ԐF�̗�

	//�̗͂������ȏ�̎�
	if (m_player->m_playerHP >= m_player->m_playerHPMax * 0.5f)
	{
		m_collarR = (1.0f - (m_player->m_playerHP * (1.0f / m_player->m_playerHPMax))) * 2.0f;	//�̗͂�����قǐԐ����������Ă���
		m_collarG = 1.0f;	//�ΐ����͌Œ�
	}
	//�̗͂������ȉ��̎�
	else if (m_player->m_playerHP < m_player->m_playerHPMax * 0.5f)
	{
		m_collarG = (m_player->m_playerHP * (1.0f / m_player->m_playerHPMax)) * 2.0f;	//�̗͂�����قǗΐ����������Ă���
		m_collarR = 1.0f;	//�Ԑ����͌Œ�
	}
	
	m_HPSprite.SetMulColor({ m_collarR,m_collarG,0.0f,1.0f });
	m_HPSprite.Update();
}

void PlayerUI::Damage()
{
	//�̗͂ɂ���đ傫����ς���
	m_sizeX = m_player->m_playerHP * (1.0 / m_player->m_playerHPMax);

	//�T�C�Y��0��菬�����Ȃ�Ȃ�
	if (m_sizeX <= 0.0f)
	{
		m_sizeX = 0.0f;
	}

	m_HPSprite.SetScale({ m_sizeX,1.0f,1.0f });
	m_HPSprite.Update();
}

void PlayerUI::Render(RenderContext& rc)
{
	if (m_player->game_state == 0)
	{
		m_HPSprite.Draw(rc);
	}
}