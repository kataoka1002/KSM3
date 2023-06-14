#include "stdafx.h"
#include "GigatonCannonAttack.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy_Far.h"
#include "Enemy_Near.h"
#include "Game.h"
#include "Boss.h"
#include "Boss_Drill.h"

GigatonCannonAttack::GigatonCannonAttack()
{

}

GigatonCannonAttack::~GigatonCannonAttack()
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

void GigatonCannonAttack::DestroyWithImpactEffect()
{
	//���e������G�t�F�N�g�Đ�
	m_tyakudanEffect = NewGO<EffectEmitter>(0);
	m_tyakudanEffect->Init(enGigatonAttack);
	m_tyakudanEffect->SetScale({ 5.0f,5.0f,5.0f });
	m_tyakudanEffect->SetPosition({ m_position.x,m_position.y + 50.0f,m_position.z });
	m_tyakudanEffect->Play();

	//�������̐ݒ�ƍĐ�
	m_cannonSE = NewGO<SoundSource>(0);
	m_cannonSE->Init(enGigatonCannon);					//������
	m_cannonSE->SetVolume(2.0f * m_game->SEvol);		//���ʒ���
	m_cannonSE->Play(false);

	DeleteGO(this);
}

bool GigatonCannonAttack::Start()
{
	m_player = FindGO<Player>("player");
	m_game = FindGO<Game>("game");

	Setup();

	return true;
}

void GigatonCannonAttack::Setup()
{
	//�e�̃��f���̏�����
	m_bulletModel.Init("Assets/modelData/battleship_gun_bullet.tkm");
	m_bulletModel.SetScale(10.0f);

	//�G�l�~�[���猩�Đ������ʒu�ɒe��ݒ�
	originRotation.Multiply(m_bulletLocalPosition);	//�|���Z

	//�ŏI�I�Ȓe�̉�]������
	m_rot = originRotation;
	m_position += m_bulletLocalPosition;				//����ɐe���猩���ʒu�𑫂��čŏI�I�ȕ���̈ʒu������

	//�O�����̓v���C���[�ƈꏏ
	m_bulletForward = m_player->playerForward;	

	//�X�V
	m_bulletModel.SetRotation(m_rot);
	m_bulletModel.SetPosition(m_position);
}

void GigatonCannonAttack::Update()
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

			DestroyWithImpactEffect();
		}
	}
	else if (m_player->game_state == 2)
	{
		DeleteGO(this);	//���U���g��ʂɍs���Ə���
	}

	if (m_player->game_end_state == 1)
	{
		DeleteGO(this);	//�v���C���[���|�[�Y��ʂ���Q�[�����I��������Ə���
	}
}

void GigatonCannonAttack::Move()
{
	//�e��O�ɔ�΂�����
	m_moveSpeed += m_bulletForward * 2.0f;
	m_position += m_moveSpeed;

	//�e�ƃv���C���[(�e)�̋������v�Z���Ĉ�苗���ȏ�Ȃ�e������
	Vector3 m_toPlayer = m_player->player_position - m_position;
	float m_dirToPlayer = m_toPlayer.Length();
	if (m_dirToPlayer >= 150.0f)
	{
		m_player->attack_state_la = false;
		m_player->attack_state_ra = false;
		m_player->attack_state_s = false;
		m_player->attack_state_ll = false;
		m_player->attack_state_rl = false;

		DestroyWithImpactEffect();
	}

	//�o���b�g�̍X�V
	m_bulletModel.SetPosition(m_position);
}

void GigatonCannonAttack::Damage()
{
	//�G�l�~�[�̐������J��Ԃ�
	for (auto enemy : m_game->m_enemyObject)
	{
		//�e�ƃG�l�~�[�̋����𑪂���ȉ��Ȃ�̗͌���
		Vector3 diff = m_position - enemy->GetPos();
		if (diff.Length() <= 300.0f)
		{
			enemy->ApplyDamage(m_bulletDamage);
			DestroyWithImpactEffect();
		}
	}
	//�G�l�~�[Far�̐������J��Ԃ�
	for (auto enemyFar : m_game->m_enemyFarObject)
	{
		//�e�ƃG�l�~�[�̋����𑪂���ȉ��Ȃ�̗͌���
		Vector3 diff = m_position - enemyFar->GetPos();
		if (diff.Length() <= 300.0f)
		{
			enemyFar->ApplyDamage(m_bulletDamage);
			DestroyWithImpactEffect();
		}
	}
	//�G�l�~�[Near�̐������J��Ԃ�
	for (auto enemyNear : m_game->m_enemyNearObject)
	{
		//�e�ƃG�l�~�[�̋����𑪂���ȉ��Ȃ�̗͌���
		Vector3 diff = m_position - enemyNear->GetPos();
		if (diff.Length() <= 300.0f)
		{
			enemyNear->ApplyDamage(m_bulletDamage);
			DestroyWithImpactEffect();
		}
	}
	//�e�ƃ{�X�̋����𑪂���ȉ��Ȃ�̗͌���
	if (m_game->boss != nullptr)
	{
		Vector3 diff = m_position - m_game->boss->boss_position;
		if (diff.Length() <= 300.0f)
		{
			m_game->boss->boss_HP -= m_bulletDamage;
			DestroyWithImpactEffect();
		}
	}
	//�e�ƃh�����̋����𑪂���ȉ��Ȃ�̗͌���
	if (m_game->boss != nullptr)
	{
		if (m_game->boss->b_boss_drill != nullptr)
		{
			Vector3 diff = m_position - m_game->boss->b_boss_drill->b_w_position;
			if (diff.Length() <= 300.0f)
			{
				m_game->boss->b_boss_drill->drill_HP -= m_bulletDamage;
				DestroyWithImpactEffect();
			}
		}
	}
}

void GigatonCannonAttack::Render(RenderContext& rc)
{
	//�M�K�g���L���m���̒e�͌����Ȃ�
	//m_bulletModel.Draw(rc);
}