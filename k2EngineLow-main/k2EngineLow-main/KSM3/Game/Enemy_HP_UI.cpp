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
	m_HPSprite.SetPivot({ 0.0f,0.5f });	//�摜���[�̐^�񒆂���_

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

	//�e�ɂ���ă|�W�V������ς���
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

	//�G�l�~�[�̏�̕��ɉ摜��\���������̂�,y���W�������傫������B
	pos.y += 130.0f;
	//���[���h���W����X�N���[�����W���v�Z�B
	//�v�Z���ʂ�m_position�ɑ�������B
	g_camera3D->CalcScreenPositionFromWorldPosition(m_position, pos);
	m_HPSprite.SetPosition(Vector3(m_position.x, m_position.y, 0.0f));
	m_HPSprite.Update();	
}

void Enemy_HP_UI::Damage()
{
	//�e�ɂ���ăT�C�Y��ς���B
	//�e�̗̑͂̊�������UI�̃T�C�Y���v�Z���Ă���B
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

	//�T�C�Y��0��菬�����Ȃ�Ȃ�
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