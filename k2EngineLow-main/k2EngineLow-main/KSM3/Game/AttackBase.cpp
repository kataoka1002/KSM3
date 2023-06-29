#include "stdafx.h"
#include "AttackBase.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy_Far.h"
#include "Enemy_Near.h"
#include "Boss.h"
#include "Boss_Drill.h"

namespace
{
	const float ENEMY_NEAR_RANGEDISTANCE = 150.0f;
	const float ENEMY_RANGEDISTANCE = 150.0f;
	const float ENEMY_FAR_RANGEDISTANCE = 300.0f;
}


bool AttackBase::Start()
{

	//�Q�[����T��
	m_game = FindGO<Game>("game");


	//�v���C���[��T��
	m_player = FindGO<Player>("player");


	//�S�ʂ̃Z�b�g�A�b�v
	SetUp();

	return true;

}

void AttackBase::BulletSetUp(float scale)
{

	m_bulletModel = std::make_unique<ModelRender>();

	//�e�̃��f���̏�����
	m_bulletModel->Init("Assets/modelData/battleship_gun_bullet.tkm");
	m_bulletModel->SetScale(scale);


	//�G�l�~�[���猩�Đ������ʒu�ɒe��ݒ�
	m_originRotation.Multiply(m_bulletLocalPosition);	//�|���Z


	//�ŏI�I�Ȓe�̉�]������
	m_rot = m_originRotation;


	//����ɐe���猩���ʒu�𑫂��čŏI�I�ȕ���̈ʒu������
	m_position += m_bulletLocalPosition;				


	//�O�����̓v���C���[�ƈꏏ
	m_bulletForward = m_player->GetPlayerForward();


	//�X�V
	m_bulletModel->SetRotation(m_rot);
	m_bulletModel->SetPosition(m_position);
	m_bulletModel->Update();

}

void AttackBase::Move(float deleteDir)
{

	//�|�W�V�����ɁA�O�����ɑ������|�����l�𑫂�
	m_position += m_bulletForward * m_moveSpeed;


	//�e����v���C���[�܂ł̃x�N�g�������߂�
	Vector3 m_toPlayer = m_player->GetPlayerPosition() - m_position;


	//�����Â��ɗ��Ƃ�
	m_position.y -= m_fallSpeed;


	//�X�s�[�h�������Âx������
	m_moveSpeed -= m_decreaseSpeed;


	//������X�s�[�h�������Â�������
	m_fallSpeed += m_addFallSpeed;



	//�e����v���C���[�܂ł̋��������߂�
	float m_dirToPlayer = m_toPlayer.Length();


	//��苗���ȏ�Ȃ�
	if (m_dirToPlayer >= deleteDir)
	{

		//�e����������
		DestroyWithImpactEffect();

	}
	//�n�ʂɒ�������
	else if (m_position.y <= 0.0f)
	{

		//�e����������
		DestroyWithImpactEffect();

	}


	//�o���b�g�̍X�V
	m_bulletModel->SetPosition(m_position);
	m_bulletModel->Update();

}

void AttackBase::PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale)
{

	//�G�t�F�N�g�̍Đ�
	EffectEmitter* m_effect = NewGO<EffectEmitter>(0);
	m_effect->Init(name);
	m_effect->SetPosition(pos);
	m_effect->SetRotation(rot);
	m_effect->SetScale(scale);
	m_effect->Play();

}

void AttackBase::DamageEvent(float damage)
{

	//�G�l�~�[�̐������J��Ԃ�
	for (auto enemy : m_game->GetEnemyObject())
	{

		//�e�ƃG�l�~�[�̋����𑪂�
		Vector3 diff = m_position - enemy->GetPos();


		//��苗���ȉ��Ȃ�
		if (diff.Length() <= ENEMY_RANGEDISTANCE)
		{

			//�_���[�W��^����
			enemy->ApplyDamage(damage);


			//�e��������Ƃ��̏���
			DestroyWithImpactEffect();

		}

	}


	//�G�l�~�[Far�̐������J��Ԃ�
	for (auto enemyFar : m_game->GetEnemyFarObject())
	{

		//�e�ƃG�l�~�[�̋����𑪂�
		Vector3 diff = m_position - enemyFar->GetPos();


		//��苗���ȉ��Ȃ�
		if (diff.Length() <= ENEMY_FAR_RANGEDISTANCE)
		{

			//�_���[�W��^����
			enemyFar->ApplyDamage(damage);


			//�e��������Ƃ��̏���
			DestroyWithImpactEffect();

		}

	}


	//�G�l�~�[Near�̐������J��Ԃ�
	for (auto enemyNear : m_game->GetEnemyNearObject())
	{

		//�e�ƃG�l�~�[�̋����𑪂�
		Vector3 diff = Vector3{ m_position.x,m_position.y + 20.0f,m_position.z } - enemyNear->GetPos();


		//��苗���ȉ��Ȃ�
		if (diff.Length() <= ENEMY_NEAR_RANGEDISTANCE)
		{

			//�_���[�W��^����
			enemyNear->ApplyDamage(damage);


			//�e��������Ƃ��̏���
			DestroyWithImpactEffect();

		}

	}


	//�{�X���k�����Ⴂ�Ȃ��Ƃ�
	if (m_game->GetBoss() != nullptr)
	{

		//�e�ƃ{�X�̋����𑪂�
		Vector3 diff = m_position - m_game->GetBoss()->GetPosition();


		//��苗���ȉ��Ȃ�
		if (diff.Length() <= 400.0f)
		{

			//�_���[�W��^����
			m_game->GetBoss()->ApplyDamage(damage);


			//�e��������Ƃ��̏���
			DestroyWithImpactEffect();

		}

	}


	//�{�X���k������Ȃ��Ƃ�
	if (m_game->GetBoss() != nullptr)
	{

		//�h�������k������Ȃ��Ƃ�
		if (m_game->GetBoss()->GetDrill() != nullptr)
		{

			//�e�ƃh�����̋����𑪂�
			Vector3 diff = m_position - m_game->GetBoss()->GetDrill()->b_w_position;


			//��苗���ȉ��Ȃ�
			if (diff.Length() <= 400.0f)
			{

				//�_���[�W��^����
				m_game->GetBoss()->GetDrill()->drill_HP -= damage;


				//�e��������Ƃ��̏���
				DestroyWithImpactEffect();

			}

		}

	}

}