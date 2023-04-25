#include "stdafx.h"
#include "Shoulder_UI.h"
#include "Shoulder_weapons.h"
#include "Player.h"


Shoulder_UI::Shoulder_UI()
{
	shoulder_weapons = FindGO<Shoulder_weapons>("shoulder_weapons");
	player = FindGO<Player>("player");
}

Shoulder_UI::~Shoulder_UI()
{
}

bool Shoulder_UI::Start() {
	for (int i = 0; i < 5; i++) {
		s_w_hp_render[0].Init("Assets/sprite/s_w_green1.dds", 700.0f, 600.0f);
		s_w_hp_render[i].SetPosition({ 650.0f,-250.0f,0.0f });
	}
	return true;
}

void Shoulder_UI::Update() {
	for (int i = 0; i < 5; i++) {
		s_w_hp_render[i].Update();
	}
}

void Shoulder_UI::Render(RenderContext& rc) {
	for (int i = 0; i < 5; i++) {
		if (player->game_state == 0) {
			switch (player->p_custom_point[0][1])
			{
			case 1:
			{
				if (shoulder_weapons->S_w_HP == 0.0f)
				{
					s_w_hp_render[0].Draw(rc);
				}
			}
			}
		}
	}
}