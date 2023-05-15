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

	m_HPSprite.Init("Assets/sprite/HP4.dds", 160.0f, 80.0f);
	m_HPSprite.SetPosition({ 0.0f,0.0f,0.0f });
	m_HPSprite.SetScale({ m_sizeX,1.0f,1.0f });
	m_HPSprite.SetPivot({ 0.0f,0.5f });	//画像左端の真ん中が基点
	m_HPSprite.Update();

	return true;
}

void PlayerUI::Update()
{
	Damage();
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