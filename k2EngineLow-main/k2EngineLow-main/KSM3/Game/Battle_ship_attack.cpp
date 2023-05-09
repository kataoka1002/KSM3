#include "stdafx.h"
#include "Battle_ship_attack.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy_Far.h"
#include "Enemy_Near.h"
#include "Game.h"
#include "Boss.h"
#include "Boss_Riser.h"
#include "Boss_Drill.h"

Battle_ship_attack::Battle_ship_attack() 
{
	
}

bool Battle_ship_attack::Start()
{
	m_player = FindGO<Player>("player");
	m_game = FindGO<Game>("game");
	//m_boss = FindGO<Boss>("boss");

	Setup();

	return true;
}

void Battle_ship_attack::Setup() 
{
	//モデルの初期化
	m_bulletModel.Init("Assets/modelData/battleship_gun_bullet.tkm");
	m_bulletModel.SetScale(5.0f);

	m_bulletForward = m_player->playerFowrad;
	firing_position.y += 10.0f;
	//更新
	m_bulletModel.SetRotation(B_S_aiming);
	m_bulletModel.SetPosition(firing_position);
}

Battle_ship_attack::~Battle_ship_attack() 
{
	if (m_player->p_custom_point[0][2] != 0)
		m_player->attack_state_ra = false;
	if (m_player->p_custom_point[0][1] != 0)
		m_player->attack_state_s = false;
	if (m_player->p_custom_point[0][0] != 0)
		m_player->attack_state_la = false;
	if (m_player->p_custom_point[1][0] != 0)
		m_player->attack_state_ll = false;
	if (m_player->p_custom_point[1][2] != 0)
		m_player->attack_state_rl = false;
}

void Battle_ship_attack::Update()
{
	if (m_player->game_state == 0)
	{
		Move();
		Damage();
		m_bulletModel.Update();
		if (firing_position.y <= 0.0f)
		{
			m_player->attack_state_la = false;
			m_player->attack_state_ra = false;
			m_player->attack_state_s = false;
			m_player->attack_state_ll = false;
			m_player->attack_state_rl = false;

			DeleteGO(this);
		}
	}
}

void Battle_ship_attack::Move() 
{
	firing_position += m_bulletForward * move_speed;
	firing_position.y -= fall_speed;
	move_speed -= 0.05f;
	fall_speed += 0.1f;
	m_bulletModel.SetPosition(firing_position);
}

void Battle_ship_attack::Damage()
{
	//エネミーの数だけ繰り返す
	for (auto enemy : m_game->m_enemyObject)
	{
		//弾とエネミーの距離を測り一定以下なら体力減少
		Vector3 diff = firing_position - enemy->m_enemyPosition;
		if (diff.Length() <= 100.0f)
		{
			enemy->m_enemyHP -= 50.0f;
			DeleteGO(this);	//弾は消える
		}
	}
	//エネミーFarの数だけ繰り返す
	for (auto enemyFar : m_game->m_enemyFarObject)
	{
		//弾とエネミーの距離を測り一定以下なら体力減少
		Vector3 diff = firing_position - enemyFar->m_enemyPosition;
		if (diff.Length() <= 100.0f)
		{
			enemyFar->m_enemyHP -= 50.0f;
			DeleteGO(this);	//弾は消える
		}
	}
	//エネミーNearの数だけ繰り返す
	for (auto enemyNear : m_game->m_enemyNearObject)
	{
		//弾とエネミーの距離を測り一定以下なら体力減少
		Vector3 diff = firing_position - enemyNear->m_enemyPosition;
		if (diff.Length() <= 100.0f)
		{
			enemyNear->m_enemyHP -= 50.0f;
			DeleteGO(this);	//弾は消える
		}
	}

	//弾とボスの距離を測り一定以下なら体力減少
	if (m_game->boss != nullptr)
	{
		Vector3 diff = firing_position - m_game->boss->boss_position;
		if (diff.Length() <= 500.0f)
		{
			m_game->boss->boss_HP -= 50.0f;
			DeleteGO(this);	//弾は消える
		}
	}

	//弾とドリルの距離を測り一定以下なら体力減少
	if (m_game->boss != nullptr)
	{
		if (m_game->boss->b_boss_drill != nullptr)
		{
			Vector3 diff = firing_position - m_game->boss->b_boss_drill->b_w_position;
			if (diff.Length() <= 500.0f)
			{
				m_game->boss->b_boss_drill->drill_HP -= 50.0f;
				DeleteGO(this);	//弾は消える
			}
		}
	}
}

void Battle_ship_attack::Render(RenderContext& rc) 
{
	m_bulletModel.Draw(rc);
}