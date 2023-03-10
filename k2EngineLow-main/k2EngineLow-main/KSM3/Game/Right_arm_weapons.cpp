#include "stdafx.h"
#include "Right_arm_weapons.h"
#include "Player.h"
#include "Enumeration.h"
#include "Battle_ship_attack.h"

Right_arm_weapons::Right_arm_weapons() {
	r_a_w_player = FindGO<Player>("player");
}

Right_arm_weapons::~Right_arm_weapons() {
	if (atack_state == true) {
		if (battle_ship_attack->Landing_state_BB = false) {
			DeleteGO(battle_ship_attack);
		}
	}
}

void Right_arm_weapons::R_a_w_set() {
	if (set_weapons[1] == 1) {
		Right_arm_weapons_Render.Init("Assets/modelData/battleship_gun_right_arm.tkm");
	}
}

void Right_arm_weapons::Update() {
	if (fast == 0) {
		R_a_w_set();
	}
	fast++;
	if (game_state == 0) {
		Move();
		if (g_pad[0]->IsTrigger(enButtonRB1)) {

			if (set_weapons[1] == 1) {
				battle_ship_attack = NewGO< Battle_ship_attack>(1, "battle_ship_attack");
				battle_ship_attack->B_S_aiming = r_a_Rotation;
				battle_ship_attack->firing_position = r_a_w_position;
				atack_state = true;

			}

		}
		if (r_a_w_player->game_end_state == 1) {
			DeleteGO(this);
		}
		r_a_w_player->attack_state_la = atack_state;
		Right_arm_weapons_Render.Update();
	}
}

void Right_arm_weapons::Move() {
	Quaternion originRotation = r_a_w_player->player_rotation;
	r_a_w_position = r_a_w_player->player_position;
	Vector3 lp = r_a_w_localPosition;
	originRotation.Multiply(lp);
	r_a_w_position += lp;
	r_a_Rotation = originRotation;
	Right_arm_weapons_Render.SetPosition(r_a_w_position);
	Right_arm_weapons_Render.SetRotation(r_a_Rotation);
}

void Right_arm_weapons::Render(RenderContext& rc) {
	Right_arm_weapons_Render.Draw(rc);
}