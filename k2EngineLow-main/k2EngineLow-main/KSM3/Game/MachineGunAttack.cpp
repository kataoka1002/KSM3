#include "stdafx.h"
#include "MachineGunAttack.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy_Far.h"
#include "Enemy_Near.h"
#include "Game.h"
#include "Boss.h"
#include "Boss_Drill.h"

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

	//���e������G�t�F�N�g�Đ�
	m_tyakudanEffect = NewGO<EffectEmitter>(0);
	m_tyakudanEffect->Init(enMasinganKemuri);
	m_tyakudanEffect->SetScale({ 10.0f,10.0f,10.0f });
	m_tyakudanEffect->SetPosition({ m_position.x,m_position.y,m_position.z });
	m_tyakudanEffect->Play();
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

	//�G�l�~�[���猩�Đ������ʒu�ɒe��ݒ�
	originRotation.Multiply(m_bulletLocalPosition);	//�|���Z

	//�ŏI�I�Ȓe�̉�]������
	m_rot = originRotation;
	m_position += m_bulletLocalPosition;				//����ɐe���猩���ʒu�𑫂��čŏI�I�ȕ���̈ʒu������

	//�O�����̓v���C���[�ƈꏏ
	m_bulletForward = m_player->playerFowrad;

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
		if (diff.Length() <= 300.0f)
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
		if (diff.Length() <= 400.0f)
		{
			enemyFar->m_enemyHP -= 50.0f;
			DeleteGO(this);	//�e�͏�����
		}
	}
	//�G�l�~�[Near�̐������J��Ԃ�
	for (auto enemyNear : m_game->m_enemyNearObject)
	{
		//�e�ƃG�l�~�[�̋����𑪂���ȉ��Ȃ�̗͌���
		Vector3 diff = Vector3{ m_position.x,m_position.y + 20.0f,m_position.z } - enemyNear->m_enemyPosition;
		if (diff.Length() <= 400.0f)
		{
			enemyNear->m_enemyHP -= 50.0f;
			DeleteGO(this);	//�e�͏�����
		}
	}
	//�e�ƃ{�X�̋����𑪂���ȉ��Ȃ�̗͌���
	if (m_game->boss != nullptr)
	{
		Vector3 diff = m_position - m_game->boss->boss_position;
		if (diff.Length() <= 400.0f)
		{
			m_game->boss->boss_HP -= 50.0f;
			DeleteGO(this);	//�e�͏�����
		}
	}
	//�e�ƃh�����̋����𑪂���ȉ��Ȃ�̗͌���
	if (m_game->boss != nullptr)
	{
		if (m_game->boss->b_boss_drill != nullptr)
		{
			Vector3 diff = m_position - m_game->boss->b_boss_drill->b_w_position;
			if (diff.Length() <= 400.0f)
			{
				m_game->boss->b_boss_drill->drill_HP -= 50.0f;
				DeleteGO(this);	//�e�͏�����
			}
		}
	}
}

void MachineGunAttack::Render(RenderContext& rc)
{
	m_bulletModel.Draw(rc);
}