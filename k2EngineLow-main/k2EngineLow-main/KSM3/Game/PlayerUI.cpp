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
	float m_collarG;	//緑色の量
	float m_collarR;	//赤色の量

	//体力が半分以上の時
	if (m_player->m_playerHP >= m_player->m_playerHPMax * 0.5f)
	{
		m_collarR = (1.0f - (m_player->m_playerHP * (1.0f / m_player->m_playerHPMax))) * 2.0f;	//体力が減るほど赤成分が増えていく
		m_collarG = 1.0f;	//緑成分は固定
	}
	//体力が半分以下の時
	else if (m_player->m_playerHP < m_player->m_playerHPMax * 0.5f)
	{
		m_collarG = (m_player->m_playerHP * (1.0f / m_player->m_playerHPMax)) * 2.0f;	//体力が減るほど緑成分が減っていく
		m_collarR = 1.0f;	//赤成分は固定
	}
	
	m_HPSprite.SetMulColor({ m_collarR,m_collarG,0.0f,1.0f });
	m_HPSprite.Update();
}

void PlayerUI::Damage()
{
	//体力によって大きさを変える
	m_sizeX = m_player->m_playerHP * (1.0 / m_player->m_playerHPMax);

	//サイズは0より小さくならない
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