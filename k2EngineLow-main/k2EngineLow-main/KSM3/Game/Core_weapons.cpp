#include "stdafx.h"
#include "Core_weapons.h"
#include "Player.h"

Core_weapons::Core_weapons() {
	
}

Core_weapons::~Core_weapons() {
	if (atack_state == true) {
		
	}
}

void Core_weapons::CW_set() {
	cw_player= FindGO<Player>("player");
	if (set_weapons == 1) {
		Core_Weapons_Render.Init("Assets/modelData/Giga_Plasma.tkm");
		Core_Weapons_Render.SetScale(scale);
		Core_Weapons_Render.Update();
	}
}

void Core_weapons::Update() {
	if (fast == 0) {
		CW_set();
	}
	fast++;
	if(fast!=0) {
		if (game_state == 0) {
			Move();
			if (g_pad[0]->IsPress(enButtonRB1)) {

				if (set_weapons == 1 && firing_cound % 60 == 0) {

				}
				firing_cound++;
			}
			else {
				firing_cound = 0;
			}
			if (cw_player->game_end_state == 1) {
				DeleteGO(this);
			}
			Core_Weapons_Render.Update();
		}
	}
	
}

void Core_weapons::Move() {
	Quaternion originRotation = cw_player->player_rotation;
	cw_position = cw_player->player_position;
	Vector3 lp = cw_localPosition;
	originRotation.Multiply(lp);
	cw_position += lp;
	cw_Rotation = originRotation;
	Core_Weapons_Render.SetPosition(cw_position);
	Core_Weapons_Render.SetRotation(cw_Rotation);
}

void Core_weapons::Render(RenderContext& rc) {
	Core_Weapons_Render.Draw(rc);
}