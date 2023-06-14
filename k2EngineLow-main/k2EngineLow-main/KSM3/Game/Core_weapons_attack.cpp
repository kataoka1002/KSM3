#include "stdafx.h"
#include "Core_weapons_attack.h"
#include "Player.h"
#include "Core_weapons.h"
#include "Enemy.h"
#include "Enemy_Far.h"
#include "Enemy_Near.h"
#include "Game.h"
#include "Boss.h"
#include "Boss_Drill.h"

Core_weapons_attack::Core_weapons_attack() {
	C_W_A_player = FindGO<Player>("player");
	C_W_A_core_weapons = FindGO<Core_weapons>("core_weapons");
	m_game = FindGO<Game>("game");
	Setup();
}

void Core_weapons_attack::Setup() {
	switch (C_W_A_core_weapons->set_weapons)
	{
	case 1:
		break;
	case 2:
		C_W_Bullet.Init("Assets/modelData/V_P_bullet.tkm");
		C_W_Bullet.SetScale(4.0f);
		C_W_aiming = C_W_A_core_weapons->cw_Rotation;
		firing_position= C_W_A_core_weapons->cw_position;
		firing_position.y += 12.0f;
		move_speed = 200.0f;
		C_W_Bullet_Fowrad = C_W_A_player->playerForward;
		C_W_Bullet.SetPosition(firing_position);
		C_W_Bullet.SetRotation(C_W_aiming);
		damage_volume=10.0f;
		break;
	default:
		break;
	}
}

Core_weapons_attack::~Core_weapons_attack()
{
	C_W_A_core_weapons->atack_state = false;

	//���e������G�t�F�N�g�Đ�
	m_tyakudanEffect = NewGO<EffectEmitter>(0);
	m_tyakudanEffect->Init(enMasinganKemuri);
	m_tyakudanEffect->SetScale({ 10.0f,10.0f,10.0f });
	m_tyakudanEffect->SetPosition({ firing_position.x,firing_position.y,firing_position.z });
	m_tyakudanEffect->Play();
}

void Core_weapons_attack::Update() {
	if (C_W_A_player->game_state == 0) {
		Move();
		Damage();
		C_W_Bullet.Update();
		if (firing_position.y <= 0.0f) {
			DeleteGO(this);
		}
	}
	else if (C_W_A_player->game_state == 2)
	{
		DeleteGO(this);	//���U���g��ʂɍs���Ə���
	}

	if (C_W_A_player->game_end_state == 1)
	{
		DeleteGO(this);	//�v���C���[���|�[�Y��ʂ���Q�[�����I��������Ə���
	}
}

void Core_weapons_attack::Damage()
{
	//�G�l�~�[�̐������J��Ԃ�
	for (auto enemy : m_game->m_enemyObject)
	{
		//�e�ƃG�l�~�[�̋����𑪂���ȉ��Ȃ�̗͌���
		Vector3 diff = firing_position - enemy->GetPos();
		if (diff.Length() <= 200.0f)
		{
			enemy->ApplyDamage(m_bulletDamage);
			DeleteGO(this);	//�e�͏�����
		}
	}
	//�G�l�~�[Far�̐������J��Ԃ�
	for (auto enemyFar : m_game->m_enemyFarObject)
	{
		//�e�ƃG�l�~�[�̋����𑪂���ȉ��Ȃ�̗͌���
		Vector3 diff = firing_position - enemyFar->GetPos();
		if (diff.Length() <= 200.0f)
		{
			enemyFar->ApplyDamage(m_bulletDamage);
			DeleteGO(this);	//�e�͏�����
		}
	}
	//�G�l�~�[Near�̐������J��Ԃ�
	for (auto enemyNear : m_game->m_enemyNearObject)
	{
		//�e�ƃG�l�~�[�̋����𑪂���ȉ��Ȃ�̗͌���
		Vector3 diff = firing_position - enemyNear->GetPos();
		if (diff.Length() <= 200.0f)
		{
			enemyNear->ApplyDamage(m_bulletDamage);
			DeleteGO(this);	//�e�͏�����
		}
	}
	//�e�ƃ{�X�̋����𑪂���ȉ��Ȃ�̗͌���
	if (m_game->boss != nullptr)
	{
		Vector3 diff = firing_position - m_game->boss->boss_position;
		if (diff.Length() <= 200.0f)
		{
			m_game->boss->boss_HP -= m_bulletDamage;
			DeleteGO(this);	//�e�͏�����
		}
	}

	//�e�ƃh�����̋����𑪂���ȉ��Ȃ�̗͌���
	if (m_game->boss != nullptr)
	{
		if (m_game->boss->b_boss_drill != nullptr)
		{
			Vector3 diff = firing_position - m_game->boss->b_boss_drill->b_w_position;
			if (diff.Length() <= 200.0f)
			{
				m_game->boss->b_boss_drill->drill_HP -= m_bulletDamage;
				DeleteGO(this);	//�e�͏�����
			}
		}
	}
}

void Core_weapons_attack::Move() {
	firing_position += C_W_Bullet_Fowrad * move_speed;
	firing_position.y -= fall_speed;
	move_speed -= 0.05f;
	fall_speed += 0.1f;
	C_W_Bullet.SetPosition(firing_position);

	//�e�ƃv���C���[(�e)�̋������v�Z���Ĉ�苗���ȏ�Ȃ�e������
	Vector3 m_toPlayer = C_W_A_player->player_position - firing_position;
	float m_dirToPlayer = m_toPlayer.Length();
	if (m_dirToPlayer >= 2000.0f)
	{
		DeleteGO(this);
	}

}

void Core_weapons_attack::Render(RenderContext& rc) {
	C_W_Bullet.Draw(rc);
}

