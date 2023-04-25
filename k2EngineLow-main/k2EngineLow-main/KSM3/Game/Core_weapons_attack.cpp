#include "stdafx.h"
#include "Core_weapons_attack.h"
#include "Player.h"
#include "Core_weapons.h"
#include "Enemy.h"

Core_weapons_attack::Core_weapons_attack() {
	C_W_A_player = FindGO<Player>("player");
	C_W_A_core_weapons = FindGO<Core_weapons>("core_weapons");
	c_w_a_enemy = FindGO<Enemy>("enemy");
	Setup();
}

void Core_weapons_attack::Setup() {
	switch (C_W_A_core_weapons->set_weapons)
	{
	case 1:
		break;
	case 2:
		C_W_Bullet.Init("Assets/modelData/V_P_bullet.tkm");
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
		C_W_Bullet.Update();
		if (firing_position.y <= 0.0f) {
			DeleteGO(this);
		}
		if (C_W_A_player->enemy_survival == true) {
			Vector3 diff = firing_position - c_w_a_enemy->m_enemyPosition;
			if (diff.Length() <= 100.0f)
			{
				if (C_W_A_core_weapons->set_weapons == 2) {
					c_w_a_enemy->m_enemyHP -= 10.0f;
				}
				DeleteGO(this);
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

