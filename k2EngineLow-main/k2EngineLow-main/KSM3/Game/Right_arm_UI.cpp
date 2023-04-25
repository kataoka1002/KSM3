#include "stdafx.h"
#include "Right_arm_UI.h"
#include "Right_arm_weapons.h"
#include "Player.h"

Right_arm_UI::Right_arm_UI()
{
	player = FindGO<Player>("player");
	right_arm_weapons = FindGO<Right_arm_weapons>("right_arm_weapons");
}

Right_arm_UI::~Right_arm_UI()
{
}

bool Right_arm_UI::Start()
{
	for (int i = 0; i < 5; i++) {
		r_a_w_hp_render[0].Init("Assets/sprite/r_a_green1.dds", 700.0f, 600.0f);
		r_a_w_hp_render[1].Init("Assets/sprite/r_a_orenzi1.dds", 700.0f, 600.0f);
		r_a_w_hp_render[i].SetPosition({ 650.0f,-250.0f,0.0f });
	}
	return true;
}

void Right_arm_UI::Update()
{
	for (int i = 0; i < 5; i++) {
		r_a_w_hp_render[i].Update();
	}
}

void Right_arm_UI::Render(RenderContext& rc)
{
	for (int i = 0; i < 5; i++) {
		if (player->game_state == 0) {
			switch (player->p_custom_point[0][0])
		case 1:
			{
				if (right_arm_weapons->R_a_w_HP == 0.0f)
				{
					r_a_w_hp_render[0].Draw(rc);
				}
			}
		}
	}
}