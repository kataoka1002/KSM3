#include "stdafx.h"
#include "Shoulder_weapons.h"
#include "Player.h"
#include "Enumeration.h"
#include "Battle_ship_attack.h"

Shoulder_weapons::Shoulder_weapons() {
	s_w_player = FindGO<Player>("player");
}

Shoulder_weapons::~Shoulder_weapons() {
	if (atack_state == true) {
		if (battle_ship_attack->Landing_state_BB == false) {
			DeleteGO(battle_ship_attack);
		}
	}
}

void Shoulder_weapons::S_w_set() {
	switch (s_w_player->p_custom_point[0][1])
	{
	case 1:
		Shoulder_weapons_Render.Init("Assets/modelData/battleship_gun_shoulder.tkm");
		Shoulder_weapons_Render.SetScale(scale2);
		Shoulder_weapons_Render.Update();
		set_weapons = s_w_player->p_custom_point[0][1];
	default:
		break;
	}
}

void Shoulder_weapons::Update() {
	if (fast == 0) {
		S_w_set();
	}
	fast++;
	if (s_w_player->game_state == 0) {
		Move();
		//UŒ‚
		if (g_pad[0]->IsPress(enButtonRB1)) {
			if (s_w_player->p_custom_point[0][1] == 1 && firing_cound % 180 == 0) {
				battle_ship_attack = NewGO<Battle_ship_attack>(1, "battle_ship_attack");
				battle_ship_attack->B_S_aiming = Shoulder_Rotation;
				battle_ship_attack->firing_position = s_w_position;
				atack_state = true;
			}
			firing_cound++;
		}
		else {
			firing_cound = 0;
		}
		if (s_w_player->game_end_state == 1) {
			DeleteGO(this);
		}
		s_w_player->attack_state_s = atack_state;
		Shoulder_weapons_Render.Update();
	}
}

void Shoulder_weapons::Move() {
	Quaternion originRotation = s_w_player->player_rotation;
	s_w_position = s_w_player->player_position;
	Vector3 lp = s_w_localPosition;
	originRotation.Multiply(lp);
	s_w_position += lp;
	Shoulder_Rotation = originRotation;
	Shoulder_weapons_Render.SetPosition(s_w_position);
	Shoulder_weapons_Render.SetRotation(Shoulder_Rotation);
}

void Shoulder_weapons::Render(RenderContext& rc) {
	Shoulder_weapons_Render.Draw(rc);
}
