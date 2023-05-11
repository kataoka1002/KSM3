#include "stdafx.h"
#include "Left_arm_weapons.h"
#include "Left_arm_UI.h"
#include "Player.h"
#include "Enumeration.h"
#include "Battle_ship_attack.h"
#include "MachineGunAttack.h"
#include "GigatonCannonAttack.h"

Left_arm_weapons::Left_arm_weapons() {
	l_a_w_player = FindGO<Player>("player");
	left_arm_ui = FindGO<Left_arm_UI>("left_arm_ui");
}

Left_arm_weapons::~Left_arm_weapons() {
	/*if (atack_state == true) {
		if (battle_ship_attack->Landing_state_BB == false) {
			DeleteGO(battle_ship_attack);
		}
	}*/
}

void Left_arm_weapons::L_a_w_set() {
	if (l_a_w_player->p_custom_point[0][2] == 1) {
		
	}
	switch (l_a_w_player->p_custom_point[0][2])
	{
	case 2:
		Left_arm_weapons_Render.Init("Assets/modelData/machine_gun_drop.tkm");
		Left_arm_weapons_Render.SetScale(scale2);
		Left_arm_weapons_Render.Update();
		set_weapons = l_a_w_player->p_custom_point[0][2];
		atack_state = true;
		break;
	case 4:
		Left_arm_weapons_Render.Init("Assets/modelData/GIgaton_cannon_Left_arm.tkm");
		Left_arm_weapons_Render.SetScale(0.8f);
		Left_arm_weapons_Render.Update();
		set_weapons = l_a_w_player->p_custom_point[0][2];
		atack_state = true;
		break;
	case 6:
		Left_arm_weapons_Render.Init("Assets/modelData/battleship_gun_left_arm.tkm");
		Left_arm_weapons_Render.SetScale(scale2);
		Left_arm_weapons_Render.Update();
		set_weapons = l_a_w_player->p_custom_point[0][2];
		atack_state = true;
		break;

	default:
		break;
	}
}

void Left_arm_weapons::Update() 
{
	if (fast == 0) {
		L_a_w_set();
		left_arm_ui= NewGO<Left_arm_UI>(0, "left_arm_ui");
	}
	fast++;
	if (l_a_w_player->game_state == 0) 
	{
		Move();

		//’e‚Ì¶¬
		if (g_pad[0]->IsPress(enButtonRB1)) 
		{
			if (l_a_w_player->p_custom_point[0][2] == 2 && firing_cound % 5 == 0)
			{
				//’e‚Éƒ|ƒWƒVƒ‡ƒ“‚Æ‰ñ“]‚ğ‹³‚¦‚Ä¶¬‚·‚é
				m_machineGunAttack = NewGO<MachineGunAttack>(1, "machinegunattack");
				m_machineGunAttack->originRotation = l_a_Rotation; 
				m_machineGunAttack->m_bulletLocalPosition = Vector3{ 0.0f,-10.0f,170.0f };
				m_machineGunAttack->m_position = l_a_w_position;
				atack_state = true;
			}
			else if (l_a_w_player->p_custom_point[0][2] == 4 && firing_cound % 180 == 0)
			{
				m_gigatonAttack = NewGO<GigatonCannonAttack>(1, "gigatoncannonattack");
				m_gigatonAttack->originRotation = l_a_Rotation;
				m_gigatonAttack->m_bulletLocalPosition = Vector3{0.0f,0.0f,100.0f};
				m_gigatonAttack->m_position = l_a_w_position;
				atack_state = true;
			}
			else if (l_a_w_player->p_custom_point[0][2] == 6 && firing_cound % 180 == 0) 
			{
				battle_ship_attack = NewGO< Battle_ship_attack>(1, "battle_ship_attack");
				battle_ship_attack->originRotation = l_a_Rotation;
				battle_ship_attack->m_bulletLocalPosition = Vector3{ 0.0f,-30.0f,70.0f };
				battle_ship_attack->firing_position = l_a_w_position;
				atack_state = true;
			}
			firing_cound++;
		}
		else {
			firing_cound = 0;
		}
		if (l_a_w_player->game_end_state == 1) {
			DeleteGO(this);
		}
		l_a_w_player->attack_state_la = atack_state;
		Left_arm_weapons_Render.Update();
	}
}

void Left_arm_weapons::Move() {
	Quaternion originRotation = l_a_w_player->player_rotation;
	l_a_w_position = l_a_w_player->player_position;

	//•Ší‚É‚æ‚Á‚Äæ‚è•t‚¯‚éƒ|ƒWƒVƒ‡ƒ“‚Ì•ÏX
	Vector3 lp;
	switch (l_a_w_player->p_custom_point[0][2])
	{
	case 2:	//ƒ}ƒVƒ“ƒKƒ“
		lp = { -60.0f,100.0f,0.0f };
		break;
	case 4:	//ƒMƒKƒgƒ“ƒLƒƒƒmƒ“
		lp = { -50.0f,100.0f,30.0f };
		break;
	case 6:	//íŠÍ–C
		lp = { -60.0f,80.0f,-10.0f };
		break;
	default:
		break;
	}
	

	originRotation.Multiply(lp);
	l_a_w_position += lp;
	l_a_Rotation = originRotation;
	Left_arm_weapons_Render.SetPosition(l_a_w_position);
	Left_arm_weapons_Render.SetRotation(l_a_Rotation);
}

void Left_arm_weapons::Render(RenderContext& rc) {
	Left_arm_weapons_Render.Draw(rc);
}