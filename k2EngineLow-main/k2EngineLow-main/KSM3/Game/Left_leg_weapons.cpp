#include "stdafx.h"
#include "Left_leg_weapons.h"
#include "Player.h"
#include "Enumeration.h"
#include "Battle_ship_attack.h"
#include "MachineGunAttack.h"
#include "Left_leg_UI.h"
#include "GigatonCannonAttack.h"

Left_leg_weapons::Left_leg_weapons() {
	l_l_w_player = FindGO<Player>("player");
	left_leg_ui = FindGO<Left_leg_UI>("left_leg_ui");
}

Left_leg_weapons::~Left_leg_weapons() {
	/*if (atack_state == true) {
		if (battle_ship_attack->Landing_state_BB == false) {
			DeleteGO(battle_ship_attack);
		}
	}*/
}

void Left_leg_weapons::L_l_w_set() {
	switch (l_l_w_player->p_custom_point[1][2])
	{
	case 2:
		Left_leg_weapons_Render.Init("Assets/modelData/machine_gun_drop.tkm");
		Left_leg_weapons_Render.SetScale(scale2);
		Left_leg_weapons_Render.Update();
		set_weapons = l_l_w_player->p_custom_point[1][2];
		break;
	case 4:
		Left_leg_weapons_Render.Init("Assets/modelData/GIgaton_cannon.tkm");
		Left_leg_weapons_Render.SetScale(0.8f);
		Left_leg_weapons_Render.Update();
		set_weapons = l_l_w_player->p_custom_point[1][2];
		break;
	case 6:
		Left_leg_weapons_Render.Init("Assets/modelData/battleship_gun_Drop.tkm");
		Left_leg_weapons_Render.SetScale(scale2);
		Left_leg_weapons_Render.Update();
		set_weapons = l_l_w_player->p_custom_point[1][2];
		break;

	default:
		break;
	}
}

void Left_leg_weapons::Update() {
	if (fast == 0) {
		L_l_w_set();
		left_leg_ui = NewGO<Left_leg_UI>(1, "left_leg_ui");
	}
	fast++;
	if (l_l_w_player->game_state == 0) {
		Move();
		//UŒ‚
		if (g_pad[0]->IsPress(enButtonRB1)) 
		{
			if (l_l_w_player->p_custom_point[1][2] == 2 && firing_cound % 5 == 0)
			{
				//’e‚Éƒ|ƒWƒVƒ‡ƒ“‚Æ‰ñ“]‚ğ‹³‚¦‚Ä¶¬‚·‚é
				m_machineGunAttack = NewGO<MachineGunAttack>(1, "machinegunattack");
				m_machineGunAttack->originRotation = l_l_Rotation;
				m_machineGunAttack->m_bulletLocalPosition = Vector3{ 0.0f,-10.0f,170.0f };
				m_machineGunAttack->m_position = l_l_w_position;
				atack_state = true;
			}
			else if (l_l_w_player->p_custom_point[1][2] == 4 && firing_cound % 180 == 0)
			{
				//’e‚Éƒ|ƒWƒVƒ‡ƒ“‚Æ‰ñ“]‚ğ‹³‚¦‚Ä¶¬‚·‚é
				m_gigatonAttack = NewGO<GigatonCannonAttack>(1, "gigatoncannonattack");
				m_gigatonAttack->originRotation = l_l_Rotation;
				m_gigatonAttack->m_bulletLocalPosition = Vector3{ 0.0f,0.0f,100.0f };
				m_gigatonAttack->m_position = l_l_w_position;
				atack_state = true;
			}
			else if (l_l_w_player->p_custom_point[1][2] == 6 && firing_cound % 180 == 0) 
			{
				battle_ship_attack = NewGO<Battle_ship_attack>(1, "battle_ship_attack");
				battle_ship_attack->originRotation = l_l_Rotation;
				battle_ship_attack->m_bulletLocalPosition = Vector3{ 0.0f,-37.0f,70.0f };
				battle_ship_attack->firing_position = l_l_w_position;
				atack_state = true;
			}
			firing_cound++;
		}
		else {
			firing_cound = 0;
		}
		if (l_l_w_player->game_end_state == 1) {
			DeleteGO(this);
		}
		l_l_w_player->attack_state_ll = atack_state;
		Left_leg_weapons_Render.Update();
	}
}

void Left_leg_weapons::Move() {
	Quaternion originRotation = l_l_w_player->player_rotation;
	l_l_w_position = l_l_w_player->player_position;

	//•Ší‚É‚æ‚Á‚Äæ‚è•t‚¯‚éƒ|ƒWƒVƒ‡ƒ“‚Ì•ÏX
	Vector3 lp;
	switch (l_l_w_player->p_custom_point[1][2])
	{
	case 2:	//ƒ}ƒVƒ“ƒKƒ“
		lp = { -90.0f,30.0f,0.0f };
		break;
	case 4:	//ƒMƒKƒgƒ“ƒLƒƒƒmƒ“
		lp = { -55.0f,40.0f,27.0f };
		break;
	case 6:	//íŠÍ–C
		lp = { -60.0f,40.0f,40.0f };
		break;
	default:
		break;
	}
	originRotation.Multiply(lp);
	l_l_w_position += lp;
	l_l_Rotation = originRotation;
	Left_leg_weapons_Render.SetPosition(l_l_w_position);
	Left_leg_weapons_Render.SetRotation(l_l_Rotation);
}

void Left_leg_weapons::Render(RenderContext& rc) {
	Left_leg_weapons_Render.Draw(rc);
}