#include "stdafx.h"
#include "Left_arm_UI.h"
#include "Left_arm_weapons.h"
#include "Player.h"

Left_arm_UI::Left_arm_UI()
{
	player= FindGO<Player>("player");
	left_arm_weapons = FindGO<Left_arm_weapons>("left_arm_weapons");
}

Left_arm_UI::~Left_arm_UI()
{
}

bool Left_arm_UI::Start()
{
	for (int i = 0; i < 5; i++) {
		l_a_w_hp_render[0].Init("Assets/sprite/l_a_green1.dds", 700.0f, 600.0f);
		l_a_w_hp_render[1].Init("Assets/sprite/l_a_orenzi1.dds", 700.0f, 600.0f);
		l_a_w_hp_render[i].SetPosition({ 650.0f,-250.0f,0.0f });
	}
	return true;
}

void Left_arm_UI::Update()
{
	for (int i = 0; i < 5; i++) {
	
			l_a_w_hp_render[i].Update();
		
	}
}

void Left_arm_UI::Render(RenderContext& rc)
{
	for (int i = 0; i < 5; i++) {
		if (player->game_state == 0) {
			switch (player->p_custom_point[0][2]){
			case 1:
				if (left_arm_weapons->L_a_w_HP == 0.0f)
				{
					l_a_w_hp_render[0].Draw(rc);
				}
				else if (left_arm_weapons->L_a_w_HP == 1.0f)
				{
					l_a_w_hp_render[1].Draw(rc);
				}
				break;
			case 2:
				break;
			}
		}
		l_a_w_hp_render->Update();
	}
}