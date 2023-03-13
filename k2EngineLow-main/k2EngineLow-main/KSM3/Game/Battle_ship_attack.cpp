#include "stdafx.h"
#include "Battle_ship_attack.h"
#include "Player.h"
#include "Left_arm_weapons.h"

Battle_ship_attack::Battle_ship_attack() {
	b_s_attack_player = FindGO<Player>("player");
	b_s_left_arm_weapons = FindGO<Left_arm_weapons>("left_arm_weapons");
	B_S_Bullet.Init("Assets/modelData/battleship_gun_bullet.tkm");

	Setup();
}

void Battle_ship_attack::Setup() {
	B_S_Bullet_Fowrad = b_s_attack_player->playerFowrad;
	B_S_aiming = b_s_left_arm_weapons->originRotation;
	firing_position = b_s_left_arm_weapons->l_a_w_position;
	firing_position.y += 10.0f;
	B_S_Bullet.SetRotation(B_S_aiming);
	B_S_Bullet.SetPosition(firing_position);
}

Battle_ship_attack::~Battle_ship_attack() {
	
}

void Battle_ship_attack::Update() {
	if (b_s_attack_player->game_state == 0) {
		Move();
		B_S_Bullet.Update();
		if (firing_position.y <= 0.0f) {
			b_s_attack_player->attack_state_la = false;
			b_s_left_arm_weapons->atack_state = false;
			DeleteGO(this);
		}
	}
}

void Battle_ship_attack::Move() {
	firing_position += B_S_Bullet_Fowrad * move_speed;
	firing_position.y -= fall_speed;
	move_speed -= 0.05f;
	fall_speed += 0.1f;
	B_S_Bullet.SetPosition(firing_position);
}

void Battle_ship_attack::Render(RenderContext& rc) {
	B_S_Bullet.Draw(rc);
}