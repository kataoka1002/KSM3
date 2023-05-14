#include "stdafx.h"
#include "Enemy_HP_UI.h"
#include "Enemy_Near.h"
#include "Enemy.h"
#include "Enemy_Far.h"
#include "Player.h"
#include "Game.h"


Enemy_HP_UI::Enemy_HP_UI()
{
	
}

Enemy_HP_UI::~Enemy_HP_UI()
{
	
}

bool Enemy_HP_UI::Start()
{
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");

	m_HPSprite.Init("Assets/sprite/HP4.dds", 160.0f, 80.0f);
	m_HPSprite.SetScale({ m_sizeX,1.0f,1.0f });
	m_HPSprite.SetPivot({ 0.0f,0.5f });	//画像左端の真ん中が基点

	return true;
}

void Enemy_HP_UI::Update()
{	
	SetPosition();
	Damage();
}

void Enemy_HP_UI::SetPosition()
{
	Vector3 pos;

	//親によってポジションを変える
	if (m_enemyNear != nullptr)
	{
		pos = m_enemyNear->m_enemyPosition;
	}
	else if (m_enemy != nullptr)
	{
		pos = m_enemy->m_enemyPosition;
	}
	else if (m_enemyFar != nullptr)
	{
		pos = m_enemyFar->m_enemyPosition;
	}

	//エネミーの上の方に画像を表示したいので,y座標を少し大きくする。
	pos.y += 130.0f;
	//ワールド座標からスクリーン座標を計算。
	//計算結果がm_positionに代入される。
	g_camera3D->CalcScreenPositionFromWorldPosition(m_position, pos);
	m_HPSprite.SetPosition(Vector3(m_position.x, m_position.y, 0.0f));
	m_HPSprite.Update();	
}

void Enemy_HP_UI::Damage()
{
	//親によってサイズを変える。
	//親の体力の割合からUIのサイズを計算している。
	if (m_enemyNear != nullptr)
	{
		m_sizeX = m_enemyNear->m_enemyHP * (1.0 / m_enemyNear->m_enemyHPMax);
	}
	else if (m_enemy != nullptr)
	{
		m_sizeX = m_enemy->m_enemyHP * (1.0 / m_enemy->m_enemyHPMax);
	}
	else if (m_enemyFar != nullptr)
	{
		m_sizeX = m_enemyFar->m_enemyHP * (1.0 / m_enemyFar->m_enemyHPMax);
	}

	//サイズは0より小さくならない
	if (m_sizeX <= 0.0f)
	{
		m_sizeX = 0.0f;
	}
	
	m_HPSprite.SetScale({ m_sizeX,1.0f,1.0f });
	m_HPSprite.Update();
}

void Enemy_HP_UI::Render(RenderContext& rc)
{
	if (m_player->game_state == 0) 
	{
		m_HPSprite.Draw(rc);
	}
}