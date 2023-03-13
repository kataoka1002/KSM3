#include "stdafx.h"
#include "Left_arm_weapons.h"
#include "Player.h"
#include "Enumeration.h"
#include "Battle_ship_attack.h"

Left_arm_weapons::Left_arm_weapons() {
	l_a_w_player = FindGO<Player>("player");
}

Left_arm_weapons::~Left_arm_weapons() {
	if (battle_ship_attack->Landing_state_BB = false) {
		DeleteGO(battle_ship_attack);
	}
}

void Left_arm_weapons::L_a_w_set() {
	if (drop_weapons[1] == 1) {
		Left_arm_weapons_Render.Init("Assets/modelData/battleship_gun_Drop.tkm");
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

			if (drop_weapons[1] == 1) {
				battle_ship_attack = NewGO< Battle_ship_attack>(1, "battle_ship_attack");
			}
		
		}
		Left_arm_weapons_Render.Update();
	}
}

void Left_arm_weapons::Move() {
	originRotation = l_a_w_player->player_rotation;
	l_a_w_position = l_a_w_player->player_position;
	Vector3 lp = l_a_w_localPosition;
	originRotation.Multiply(lp);
	l_a_w_position += lp;
	Left_arm_weapons_Render.SetPosition(l_a_w_position);
	Left_arm_weapons_Render.SetRotation(originRotation);
}

void Left_arm_weapons::Render(RenderContext& rc) {
	Left_arm_weapons_Render.Draw(rc);
}