#include "stdafx.h"
#include "Left_leg_UI.h"
#include "Left_leg_weapons.h"
#include "Player.h"

Left_leg_UI::Left_leg_UI()
{
	left_leg_weapons = FindGO<Left_leg_weapons>("left_leg_weapons");
	player = FindGO<Player>("player");

}

Left_leg_UI::~Left_leg_UI()
{
}

bool Left_leg_UI::Start()
{
	for (int i = 0; i < 5; i++) {
		l_l_w_hp_render[0].Init("Assets/sprite/L_l_green1.dds", 700.0f, 600.0f);
		l_l_w_hp_render[i].SetPosition({ 650.0f,-250.0f,0.0f });
	}
	return true;
}

void Left_leg_UI::Update()
{
	for (int i = 0; i < 5; i++) {
		l_l_w_hp_render[i].Update();
	}
}

void Left_leg_UI::Render(RenderContext& rc)
{
	for (int i = 0; i < 5; i++) {
		if (player->game_state == 0) {
			switch (player->p_custom_point[1][2])
			{
			case 1:
			{
				if (left_leg_weapons->L_l_w_HP == 0.0f)
				{
					l_l_w_hp_render[0].Draw(rc);
				}
			}
			}
		}
	}
}