#include "stdafx.h"
#include "Left_arm_weapons.h"
#include "Player.h"
#include "Enumeration.h"

Left_arm_weapons::Left_arm_weapons() {
	l_a_w_player = FindGO<Player>("player");
}

Left_arm_weapons::~Left_arm_weapons() {

}

void Left_arm_weapons::L_a_w_set() {
	for (int i = 0; i < 12; i++) {
		if (drop_weapons[i] == 1) {
			Left_arm_weapons_Render.Init("Assets/modelData/battleship_gun_Drop.tkm");
		}
	}
}

void Left_arm_weapons::Update() {
	if (fast == 0) {
		L_a_w_set();
	}
	fast++;
	if (game_state == 0) {
		Move();
		Left_arm_weapons_Render.Update();
	}
}

void Left_arm_weapons::Move() {
	Quaternion originRotation = l_a_w_player->player_rotation;
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