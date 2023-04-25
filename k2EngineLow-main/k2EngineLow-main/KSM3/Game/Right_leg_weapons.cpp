#include "stdafx.h"
#include "Right_leg_weapons.h"
#include "Player.h"
#include "Enumeration.h"
#include "Battle_ship_attack.h"
#include "Right_leg_UI.h"

Right_leg_weapons::Right_leg_weapons() {
	r_l_w_player = FindGO<Player>("player");
	right_leg_ui = FindGO<Right_leg_UI>("right_leg_UI");
}

Right_leg_weapons::~Right_leg_weapons() {
	if (atack_state == true) {
		if (battle_ship_attack->Landing_state_BB == false) {
			DeleteGO(battle_ship_attack);
		}
	}
}

void Right_leg_weapons::R_l_w_set() {
	switch (r_l_w_player->p_custom_point[1][0])
	{
	case 1:
		Right_leg_weapons_Render.Init("Assets/modelData/battleship_gun_right_leg01.tkm");
		Right_leg_weapons_Render.SetScale(scale2);
		Right_leg_weapons_Render.Update();
		set_weapons = r_l_w_player->p_custom_point[1][0];
		break;
	default:
		break;
	}
}

void Right_leg_weapons::Update() {
	if (fast == 0) {
		R_l_w_set();
		right_leg_ui= NewGO<Right_leg_UI>(1, "right_leg_UI");
	}
	fast++;
	if (r_l_w_player->game_state == 0) {
		Move();
		//UŒ‚
		if (g_pad[0]->IsPress(enButtonRB1)) {
			if (r_l_w_player->p_custom_point[1][0] == 1 && firing_cound % 180 == 0) {
				battle_ship_attack = NewGO<Battle_ship_attack>(1,"battle_ship_attack");
				battle_ship_attack->B_S_aiming = r_l_Rotation;
				battle_ship_attack->firing_position = r_l_w_position;
				atack_state = true;
			}
			firing_cound++;
		}
		else {
			firing_cound = 0;
		}
		if (r_l_w_player->game_end_state == 1) {
			DeleteGO(this);
		}
		r_l_w_player->attack_state_rl = atack_state;
		Right_leg_weapons_Render.Update();
	}
}

void Right_leg_weapons::Move() {
	Quaternion originRotation = r_l_w_player->player_rotation;
	r_l_w_position = r_l_w_player->player_position;
	Vector3 lp = r_l_w_localPosition;
	originRotation.Multiply(lp);
	r_l_w_position += lp;
	r_l_Rotation = originRotation;
	Right_leg_weapons_Render.SetPosition(r_l_w_position);
	Right_leg_weapons_Render.SetRotation(r_l_Rotation);
}

void Right_leg_weapons::Render(RenderContext& rc) {
	Right_leg_weapons_Render.Draw(rc);
}