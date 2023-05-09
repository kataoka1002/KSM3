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
	//c_w_a_enemy = FindGO<Enemy>("enemy");
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
		C_W_Bullet_Fowrad = C_W_A_player->playerFowrad;
		C_W_Bullet.SetPosition(firing_position);
		C_W_Bullet.SetRotation(C_W_aiming);
		damage_volume=10.0f;
		break;
	default:
		break;
	}
}

Core_weapons_attack::~Core_weapons_attack() {
	C_W_A_core_weapons->atack_state = false;
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
}

void Core_weapons_attack::Damage()
{
	//ÉGÉlÉ~Å[ÇÃêîÇæÇØåJÇËï‘Ç∑
	for (auto enemy : m_game->m_enemyObject)
	{
		//íeÇ∆ÉGÉlÉ~Å[ÇÃãóó£Çë™ÇËàÍíËà»â∫Ç»ÇÁëÃóÕå∏è≠
		Vector3 diff = firing_position - enemy->m_enemyPosition;
		if (diff.Length() <= 200.0f)
		{
			enemy->m_enemyHP -= 50.0f;
			DeleteGO(this);	//íeÇÕè¡Ç¶ÇÈ
		}
	}
	//ÉGÉlÉ~Å[FarÇÃêîÇæÇØåJÇËï‘Ç∑
	for (auto enemyFar : m_game->m_enemyFarObject)
	{
		//íeÇ∆ÉGÉlÉ~Å[ÇÃãóó£Çë™ÇËàÍíËà»â∫Ç»ÇÁëÃóÕå∏è≠
		Vector3 diff = firing_position - enemyFar->m_enemyPosition;
		if (diff.Length() <= 200.0f)
		{
			enemyFar->m_enemyHP -= 50.0f;
			DeleteGO(this);	//íeÇÕè¡Ç¶ÇÈ
		}
	}
	//ÉGÉlÉ~Å[NearÇÃêîÇæÇØåJÇËï‘Ç∑
	for (auto enemyNear : m_game->m_enemyNearObject)
	{
		//íeÇ∆ÉGÉlÉ~Å[ÇÃãóó£Çë™ÇËàÍíËà»â∫Ç»ÇÁëÃóÕå∏è≠
		Vector3 diff = firing_position - enemyNear->m_enemyPosition;
		if (diff.Length() <= 200.0f)
		{
			enemyNear->m_enemyHP -= 50.0f;
			DeleteGO(this);	//íeÇÕè¡Ç¶ÇÈ
		}
	}
	//íeÇ∆É{ÉXÇÃãóó£Çë™ÇËàÍíËà»â∫Ç»ÇÁëÃóÕå∏è≠
	if (m_game->boss != nullptr)
	{
		Vector3 diff = firing_position - m_game->boss->boss_position;
		if (diff.Length() <= 1000.0f)
		{
			m_game->boss->boss_HP -= 50.0f;
			DeleteGO(this);	//íeÇÕè¡Ç¶ÇÈ
		}
	}

	//íeÇ∆ÉhÉäÉãÇÃãóó£Çë™ÇËàÍíËà»â∫Ç»ÇÁëÃóÕå∏è≠
	if (m_game->boss != nullptr)
	{
		if (m_game->boss->b_boss_drill != nullptr)
		{
			Vector3 diff = firing_position - m_game->boss->b_boss_drill->b_w_position;
			if (diff.Length() <= 500.0f)
			{
				m_game->boss->b_boss_drill->drill_HP -= 50.0f;
				DeleteGO(this);	//íeÇÕè¡Ç¶ÇÈ
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
}

void Core_weapons_attack::Render(RenderContext& rc) {
	C_W_Bullet.Draw(rc);
}

