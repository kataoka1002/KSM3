#include "stdafx.h"
#include "Core_weapons.h"
#include "Player.h"
#include "Core_weapons_attack.h"

Core_weapons::Core_weapons() {
	
}

Core_weapons::~Core_weapons() {
	if (atack_state == true) {
		DeleteGO(core_weapons_attack);
	}
}

void Core_weapons::CW_set() {
	cw_player= FindGO<Player>("player");
	if (set_weapons == 1) {
		Core_Weapons_Render.Init("Assets/modelData/Giga_Plasma.tkm");
		Core_Weapons_Render.SetScale(scale);
		Core_Weapons_Render.Update();
		core_HP = 200.0f;
	}
	else if (set_weapons == 2) {
		Core_Weapons_Render.Init("Assets/modelData/Versatile_Perforator.tkm");
		Core_Weapons_Render.Update();
		core_HP = 200.0f;
	}
}

void Core_weapons::Update() {
	if (fast == 0) {
		CW_set();
	}

	fast++;

	if (cw_player->game_state == 4)
	{
		Move();
	}

	if(fast!=0) {
		if (cw_player->game_state == 0) {
			Move();
			if (g_pad[0]->IsPress(enButtonRB1)) {

				if (set_weapons == 1 && firing_cound % 60 == 0) {

				}
				else if (set_weapons == 2 && firing_cound % 5 == 0) {
					core_weapons_attack = NewGO<Core_weapons_attack>(1, "core_weapons_attack");
					atack_state = true;
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
	Core_Weapons_Render.Update();
}

void Core_weapons::Render(RenderContext& rc) {
	Core_Weapons_Render.Draw(rc);
}