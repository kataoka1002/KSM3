#include "stdafx.h"
#include "Left_leg_weapons.h"
#include "Player.h"
#include "Enumeration.h"
#include "Battle_ship_attack.h"

Left_leg_weapons::Left_leg_weapons() {
	l_l_w_player = FindGO<Player>("player");
}

Left_leg_weapons::~Left_leg_weapons() {
	if (atack_state == true) {
		if (battle_ship_attack->Landing_state_BB == false) {
			DeleteGO(battle_ship_attack);
		}
	}
}

void Left_leg_weapons::L_l_w_set() {
	switch (l_l_w_player->p_custom_point[1][2])
	{
	case 1:
		Left_leg_weapons_Render.Init("Assets/modelData/battleship_gun_left_leg01.tkm");
		Left_leg_weapons_Render.SetScale(scale2);
		Left_leg_weapons_Render.Update();
		set_weapons = l_l_w_player->p_custom_point[1][2];
		break;
	default:
		break;
	}
}

void Left_leg_weapons::Update() {
	if (fast == 0) {
		L_l_w_set();
	}
	fast++;
	if (game_state == 0) {
		Move();
		//UŒ‚
		if (g_pad[0]->IsPress(enButtonRB1)) {
			if (l_l_w_player->p_custom_point[1][2] == 1 && firing_cound % 180 == 0) {
				battle_ship_attack = NewGO<Battle_ship_attack>(1, "battle_ship_attack");
				battle_ship_attack->B_S_aiming = l_l_Rotation;
				battle_ship_attack->firing_position = l_l_w_position;
				atack_state = true;
			}
			firing_cound++;
		}
		else {
			firing_cound = 0;
		}
		if (l_l_w_player->game_end_state == 1) {
			DeleteGO(this);
		}
		l_l_w_player->attack_state_ll = atack_state;
		Left_leg_weapons_Render.Update();
	}
}

void Left_leg_weapons::Move() {
	Quaternion originRotation = l_l_w_player->player_rotation;
	l_l_w_position = l_l_w_player->player_position;
	Vector3 lp = l_l_w_localPosition;
	originRotation.Multiply(lp);
	l_l_w_position += lp;
	l_l_Rotation = originRotation;
	Left_leg_weapons_Render.SetPosition(l_l_w_position);
	Left_leg_weapons_Render.SetRotation(l_l_Rotation);
}

void Left_leg_weapons::Render(RenderContext& rc) {
	Left_leg_weapons_Render.Draw(rc);
}