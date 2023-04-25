#include "stdafx.h"
#include "Right_leg_UI.h"
#include "Right_leg_weapons.h"
#include "Player.h"

Right_leg_UI::Right_leg_UI()
{
	right_leg_weapons = FindGO<Right_leg_weapons>("right_leg_weapons");
	player = FindGO<Player>("player");
}

Right_leg_UI::~Right_leg_UI()
{
}

bool Right_leg_UI::Start()
{
	for (int i = 0; i < 5; i++) {
		r_l_w_hp_render[0].Init("Assets/sprite/r_l_green1.dds", 700.0f, 600.0f);
		r_l_w_hp_render[1].Init("Assets/sprite/r_l_orenzi1.dds", 700.0f, 600.0f);
		r_l_w_hp_render[i].SetPosition({ 650.0f,-250.0f,0.0f });
	}
	return true;
}

void Right_leg_UI::Update()
{
	for (int i = 0; i < 5; i++) {
		r_l_w_hp_render[i].Update();
	}
}

void Right_leg_UI::Render(RenderContext& rc)
{
	for (int i = 0; i < 5; i++) {
		if (player->game_state == 0) {
			switch (player->p_custom_point[1][0])
			{
			case 1:
			{
				if (right_leg_weapons->R_l_w_HP == 0.0f)
				{
					r_l_w_hp_render[0].Draw(rc);
				}
			}
			}
		}
	}
}