#include "stdafx.h"
#include "MachineGunAttack.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy_Far.h"
#include "Enemy_Near.h"
#include "Game.h"

MachineGunAttack::MachineGunAttack()
{
	
}

MachineGunAttack::~MachineGunAttack()
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

bool MachineGunAttack::Start()
{
	m_player = FindGO<Player>("player");
	m_game = FindGO<Game>("game");

	Setup();
	
	return true;
}

void MachineGunAttack::Setup()
{
	//�e�̃��f���̏�����
	m_bulletModel.Init("Assets/modelData/battleship_gun_bullet.tkm");
	m_bulletModel.SetScale(2.0f);
	m_bulletForward = m_player->playerFowrad;	//�O�����̓v���C���[�ƈꏏ
	//�X�V
	m_bulletModel.SetRotation(m_rot);
	m_bulletModel.SetPosition(m_position);
}

void MachineGunAttack::Update()
{
	if (m_player->game_state == 0)
	{
		Move();
		Damage();

		m_bulletModel.Update();

		if (m_position.y <= 0.0f)
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

void MachineGunAttack::Move()
{
	//�e��O�ɔ�΂�����
	m_moveSpeed += m_bulletForward * 2.0f;
	m_position += m_moveSpeed;

	//�e�ƃv���C���[(�e)�̋������v�Z���Ĉ�苗���ȏ�Ȃ�e������
	Vector3 m_toPlayer = m_player->player_position - m_position;
	float m_dirToPlayer = m_toPlayer.Length();
	if (m_dirToPlayer >= 1800.0f)
	{
		m_player->attack_state_la = false;
		m_player->attack_state_ra = false;
		m_player->attack_state_s = false;
		m_player->attack_state_ll = false;
		m_player->attack_state_rl = false;

		DeleteGO(this);
	}

	//�o���b�g�̍X�V
	m_bulletModel.SetPosition(m_position);
}

void MachineGunAttack::Damage()
{
	//�G�l�~�[�̐������J��Ԃ�
	for (auto enemy : m_game->m_enemyObject)
	{
		//�e�ƃG�l�~�[�̋����𑪂���ȉ��Ȃ�̗͌���
		Vector3 diff = m_position - enemy->m_enemyPosition;
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
		Vector3 diff = m_position - enemyFar->m_enemyPosition;
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
		Vector3 diff = m_position - enemyNear->m_enemyPosition;
		if (diff.Length() <= 100.0f)
		{
			enemyNear->m_enemyHP -= 50.0f;
			DeleteGO(this);	//�e�͏�����
		}
	}
}

void MachineGunAttack::Render(RenderContext& rc)
{
	m_bulletModel.Draw(rc);
}