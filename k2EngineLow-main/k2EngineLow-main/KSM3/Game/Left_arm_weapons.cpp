#include "stdafx.h"
#include "Left_arm_weapons.h"
#include "Player.h"
#include "Enumeration.h"
#include "Battle_ship_attack.h"

Left_arm_weapons::Left_arm_weapons() {
	l_a_w_player = FindGO<Player>("player");
}

Left_arm_weapons::~Left_arm_weapons() {
	if (atack_state == true) {
		if (battle_ship_attack->Landing_state_BB = false) {
			DeleteGO(battle_ship_attack);
		}
	}
}

void Left_arm_weapons::L_a_w_set() {
	if (set_weapons[1] == 1) {
		Left_arm_weapons_Render.Init("Assets/modelData/battleship_gun_left_arm.tkm");
	}
}

void Left_arm_weapons::Update() {
	if (fast == 0) {
		L_a_w_set();
	}
	fast++;
	if (game_state == 0) {
		Move();
		if (g_pad[0]->IsTrigger(enButtonRB1)) {

			if (set_weapons[1] == 1) {
				battle_ship_attack = NewGO< Battle_ship_attack>(1, "battle_ship_attack");
				battle_ship_attack->B_S_aiming = l_a_Rotation;
				battle_ship_attack->firing_position = l_a_w_position;
				atack_state = true;
				
			}
		
		}
		if (l_a_w_player->game_end_state == 1) {
			DeleteGO(this);
		}
		l_a_w_player->attack_state_la = atack_state;
		Left_arm_weapons_Render.Update();
	}
}

void Left_arm_weapons::Move() {
	Quaternion originRotation = l_a_w_player->player_rotation;
	l_a_w_position = l_a_w_player->player_position;
	Vector3 lp = l_a_w_localPosition;
	originRotation.Multiply(lp);
	l_a_w_position += lp;
	l_a_Rotation = originRotation;
	Left_arm_weapons_Render.SetPosition(l_a_w_position);
	Left_arm_weapons_Render.SetRotation(l_a_Rotation);
}

void Left_arm_weapons::Render(RenderContext& rc) {
	Left_arm_weapons_Render.Draw(rc);
}