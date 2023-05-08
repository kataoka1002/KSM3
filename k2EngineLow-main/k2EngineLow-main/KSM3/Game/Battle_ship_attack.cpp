#include "stdafx.h"
#include "Battle_ship_attack.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy_Far.h"
#include "Enemy_Near.h"
#include "Game.h"

Battle_ship_attack::Battle_ship_attack() 
{
	
}

bool Battle_ship_attack::Start()
{
	m_player = FindGO<Player>("player");
	m_game = FindGO<Game>("game");

	Setup();

	return true;
}

void Battle_ship_attack::Setup() 
{
	//���f���̏�����
	m_bulletModel.Init("Assets/modelData/battleship_gun_bullet.tkm");
	m_bulletModel.SetScale(5.0f);

	m_bulletForward = m_player->playerFowrad;
	firing_position.y += 10.0f;
	//�X�V
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
	//�G�l�~�[�̐������J��Ԃ�
	for (auto enemy : m_game->m_enemyObject)
	{
		//�e�ƃG�l�~�[�̋����𑪂���ȉ��Ȃ�̗͌���
		Vector3 diff = firing_position - enemy->m_enemyPosition;
		if (diff.Length() <= 100.0f)
		{
			enemy->m_enemyHP -= 50.0f;
			DeleteGO(this);	//�e�͏�����
		}
	}
	//�G�l�~�[Far�̐������J��Ԃ�
	for (auto enemyFar : m_game->m_enemyFarObject)
	{
		//�e�ƃG�l�~�[�̋����𑪂���ȉ��Ȃ�̗͌���
		Vector3 diff = firing_position - enemyFar->m_enemyPosition;
		if (diff.Length() <= 100.0f)
		{
			enemyFar->m_enemyHP -= 50.0f;
			DeleteGO(this);	//�e�͏�����
		}
	}
	//�G�l�~�[Near�̐������J��Ԃ�
	for (auto enemyNear : m_game->m_enemyNearObject)
	{
		//�e�ƃG�l�~�[�̋����𑪂���ȉ��Ȃ�̗͌���
		Vector3 diff = firing_position - enemyNear->m_enemyPosition;
		if (diff.Length() <= 100.0f)
		{
			enemyNear->m_enemyHP -= 50.0f;
			DeleteGO(this);	//�e�͏�����
		}
	}
}

void Battle_ship_attack::Render(RenderContext& rc) 
{
	m_bulletModel.Draw(rc);
}