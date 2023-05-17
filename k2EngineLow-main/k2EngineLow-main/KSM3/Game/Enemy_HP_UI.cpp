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

	m_HPSprite.Init("Assets/sprite/enemy/enemyHP.dds", HP_BER_SIZE.x, HP_BER_SIZE.y);
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
		pos = m_enemyNear->m_enemyPosition;
		//�G�l�~�[�̏�̕��ɉ摜��\���������̂�,y���W�������傫������B
		pos.y += 130.0f;
	}
	else if (m_enemy != nullptr)
	{
		pos = m_enemy->m_enemyPosition;
		//�G�l�~�[�̏�̕��ɉ摜��\���������̂�,y���W�������傫������B
		pos.y += 130.0f;
	}
	else if (m_enemyFar != nullptr)
	{
		pos = m_enemyFar->m_enemyPosition;
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
		m_scale.x = m_enemyNear->m_enemyHP * (1.0 / m_enemyNear->m_enemyHPMax);
	}
	else if (m_enemy != nullptr)
	{
		m_scale.x = m_enemy->m_enemyHP * (1.0 / m_enemy->m_enemyHPMax);
	}
	else if (m_enemyFar != nullptr)
	{
		m_scale.x = m_enemyFar->m_enemyHP * (1.0 / m_enemyFar->m_enemyHPMax);
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
	if (m_player->game_state == 0) 
	{
		//��苗���ȓ��ő̗͕\��
		if (m_enemyNear != nullptr)
		{
			Vector3 diff = m_enemyNear->m_enemyPosition - m_player->player_position;

			if (diff.Length() <= 2000.0f)
			{
				m_HPFrameSprite.Draw(rc);
				m_HPSprite.Draw(rc);
			}
		}
		if (m_enemy != nullptr)
		{
			Vector3 diff = m_enemy->m_enemyPosition - m_player->player_position;

			if (diff.Length() <= 2000.0f)
			{
				m_HPFrameSprite.Draw(rc);
				m_HPSprite.Draw(rc);
			}
		}
		if (m_enemyFar != nullptr)
		{
			Vector3 diff = m_enemyFar->m_enemyPosition - m_player->player_position;
			
			if (diff.Length() <= 2000.0f)
			{
				m_HPFrameSprite.Draw(rc);
				m_HPSprite.Draw(rc);
			}
		}
	}
}