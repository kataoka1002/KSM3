#include "stdafx.h"
#include "Enemy_HP_UI.h"
#include "Enemy_Near.h"
#include "Enemy.h"
#include "Enemy_Far.h"
#include "Player.h"
#include "Game.h"
#include "GameCamera.h"


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
	m_camera = FindGO<GameCamera>("gamecamera");

	m_HPSprite.Init("Assets/sprite/enemy/enemyHP3.dds", HP_BER_SIZE.x, HP_BER_SIZE.y);
	m_HPSprite.SetScale(m_scale);
	m_HPFrameSprite.Init("Assets/sprite/enemy/enemyHPFrame.dds", HP_FRAME_SIZE.x, HP_FRAME_SIZE.y);
	m_HPFrameSprite.SetScale(m_scale);


	return true;
}

void Enemy_HP_UI::Update()
{	
	Damage();
	SetPosition();
}

void Enemy_HP_UI::SetPosition()
{
	Vector3 pos;

	//�e�ɂ���ă|�W�V������ς���
	if (m_enemyNear != nullptr)
	{
		pos = m_enemyNear->GetPos();
		//�G�l�~�[�̏�̕��ɉ摜��\���������̂�,y���W�������傫������B
		pos.y += 160.0f;
	}
	else if (m_enemy != nullptr)
	{
		pos = m_enemy->GetPos();
		//�G�l�~�[�̏�̕��ɉ摜��\���������̂�,y���W�������傫������B
		pos.y += 130.0f;
	}
	else if (m_enemyFar != nullptr)
	{
		pos = m_enemyFar->GetPos();
		//�G�l�~�[�̏�̕��ɉ摜��\���������̂�,y���W�������傫������B
		pos.y += 250.0f;
	}

	
	//���[���h���W����X�N���[�����W���v�Z�B
	//�v�Z���ʂ�m_position�ɑ�������B
	g_camera3D->CalcScreenPositionFromWorldPosition(m_position, pos);

	m_HPFrameSprite.SetPosition(Vector3(m_position.x, m_position.y, 0.0f));
	m_HPFrameSprite.Update();

	//�摜�����Ɋ񂹂�
	Vector3 BerSizeSubtraction = HPBerSend(HP_BER_SIZE, m_scale);
	m_position.x -= BerSizeSubtraction.x;

	m_HPSprite.SetPosition(Vector3(m_position.x, m_position.y, 0.0f));
	m_HPSprite.Update();	
}

void Enemy_HP_UI::Damage()
{
	//�e�ɂ���ăT�C�Y��ς���B
	//�e�̗̑͂̊�������UI�̃T�C�Y���v�Z���Ă���B
	if (m_enemyNear != nullptr)
	{
		m_scale.x = m_enemyNear->GetHP() * (1.0 / m_enemyNear->GetMaxHP());
	}
	else if (m_enemy != nullptr)
	{
		m_scale.x = m_enemy->GetHP() * (1.0 / m_enemy->GetMaxHP());
	}
	else if (m_enemyFar != nullptr)
	{
		m_scale.x = m_enemyFar->GetHP() * (1.0 / m_enemyFar->GetMaxHP());
	}

	//�T�C�Y��0��菬�����Ȃ�Ȃ�
	if (m_scale.x <= 0.0f)
	{
		m_scale.x = 0.0f;
	}
	
	m_HPSprite.SetScale(m_scale);
	m_HPSprite.Update();
}

Vector3 Enemy_HP_UI::HPBerSend(Vector3 size, Vector3 scale)
{
	Vector3 BerSize = size;									//�摜�̌��̑傫��
	Vector3 changeBerSize = Vector3::Zero;					//�摜���X�P�[���ϊ��������Ƃ̑傫��
	Vector3 BerSizeSubtraction = Vector3::Zero;				//���摜�ƕϊ���摜�̍�

	changeBerSize.x = BerSize.x * scale.x;
	BerSizeSubtraction.x = BerSize.x - changeBerSize.x;
	BerSizeSubtraction.x *= 0.5f;	//�T�C�Y�����ʂ��Q�Ŋ��邱�Ƃ�,�ړ������鋗�������߂�

	return BerSizeSubtraction;
}

void Enemy_HP_UI::Render(RenderContext& rc)
{
	if (m_player->GetGameState() == 0 && m_player->GetPlayerDead() == false)
	{
		//��苗���ȓ�&�J�����̎���ɓ����Ă���Ȃ�̗͕\��
		if (m_enemyNear != nullptr)
		{
			//�J��������G�l�~�[�̈ʒu�ւ̃x�N�g�������߂�
			Vector3 toEnemy = m_enemyNear->GetPos() - m_camera->pos;
			toEnemy.Normalize();
			//�J�����̑O�����ƃJ��������G�l�~�[�ւ̃x�N�g���̓��ς����߂�
			float angle = m_camera->m_cameraForward.Dot(toEnemy);
			angle = acos(angle);	//���ς̌��ʂ���p�x�����߂�

			//�J�������猩�ăG�l�~�[�����p�x�ȓ��̂Ƃ�
			if (fabsf(angle) <= Math::DegToRad(50.0f))
			{			
				//�v���C���[�ƃG�l�~�[�̋��������߂�
				Vector3 diff = m_enemyNear->GetPos() - m_player->GetPlayerPosition();
				if (diff.Length() <= 2000.0f)
				{
					m_HPFrameSprite.Draw(rc);
					m_HPSprite.Draw(rc);
				}
			}
		}
		if (m_enemy != nullptr)
		{
			//�v�Z�̕��@�͏�ƈꏏ
			Vector3 toEnemy = m_enemy->GetPos() - m_camera->pos;
			toEnemy.Normalize();

			float angle = m_camera->m_cameraForward.Dot(toEnemy);
			angle = acos(angle);

			if (fabsf(angle) <= Math::DegToRad(50.0f))
			{
				Vector3 diff = m_enemy->GetPos() - m_player->GetPlayerPosition();

				if (diff.Length() <= 2000.0f)
				{
					m_HPFrameSprite.Draw(rc);
					m_HPSprite.Draw(rc);
				}
			}
		}
		if (m_enemyFar != nullptr)
		{
			//�v�Z�̕��@�͏�ƈꏏ
			Vector3 toEnemy = m_enemyFar->GetPos() - m_camera->pos;
			toEnemy.Normalize();

			float angle = m_camera->m_cameraForward.Dot(toEnemy);
			angle = acos(angle);

			if (fabsf(angle) <= Math::DegToRad(50.0f))
			{
				Vector3 diff = m_enemyFar->GetPos() - m_player->GetPlayerPosition();
				if (diff.Length() <= 2000.0f)
				{
					m_HPFrameSprite.Draw(rc);
					m_HPSprite.Draw(rc);
				}
			}
		}
	}
}