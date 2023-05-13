#include "stdafx.h"
#include "Right_leg_weapons.h"
#include "Player.h"
#include "Enumeration.h"
#include "Battle_ship_attack.h"
#include "MachineGunAttack.h"
#include "Right_leg_UI.h"
#include "GigatonCannonAttack.h"


Right_leg_weapons::Right_leg_weapons() {
	r_l_w_player = FindGO<Player>("player");
	right_leg_ui = FindGO<Right_leg_UI>("right_leg_UI");
}

Right_leg_weapons::~Right_leg_weapons() {
	/*if (atack_state == true) {
		if (battle_ship_attack->Landing_state_BB == false) {
			DeleteGO(battle_ship_attack);
		}
	}*/
	DeleteGO(right_leg_ui);
}

void Right_leg_weapons::R_l_w_set() {
	switch (r_l_w_player->p_custom_point[1][0])
	{
	case 2:
		Right_leg_weapons_Render.Init("Assets/modelData/machine_gun_drop.tkm");
		Right_leg_weapons_Render.SetScale(scale2);
		Right_leg_weapons_Render.Update();
		set_weapons = r_l_w_player->p_custom_point[1][0];
		break;
	case 4:
		Right_leg_weapons_Render.Init("Assets/modelData/GIgaton_cannon.tkm");
		Right_leg_weapons_Render.SetScale(0.8f);
		Right_leg_weapons_Render.Update();
		set_weapons = r_l_w_player->p_custom_point[1][0];
		break;
	case 6:
		Right_leg_weapons_Render.Init("Assets/modelData/battleship_gun_Drop.tkm");
		Right_leg_weapons_Render.SetScale(scale2);
		Right_leg_weapons_Render.Update();
		set_weapons = r_l_w_player->p_custom_point[1][0];
		break;

	default:
		break;
	}
}

void Right_leg_weapons::Update() {
	if (fast == 0) {
		R_l_w_set();
		right_leg_ui= NewGO<Right_leg_UI>(1, "right_leg_UI");
	}
	fast++;
	if (r_l_w_player->game_state == 0) {
		Move();
		//攻撃
		if (g_pad[0]->IsPress(enButtonRB1)) 
		{
			//武器がマシンガンの場合
			if (r_l_w_player->p_custom_point[1][0] == 2 && firing_cound % 5 == 0)
			{
				//弾にポジションと回転を教えて生成する
				m_machineGunAttack = NewGO<MachineGunAttack>(1, "machinegunattack");
				m_machineGunAttack->originRotation = r_l_Rotation;
				m_machineGunAttack->m_bulletLocalPosition = Vector3{ 0.0f,-10.0f,170.0f };
				m_machineGunAttack->m_position = r_l_w_position;
				atack_state = true;
			}
			else if (r_l_w_player->p_custom_point[1][0] == 4 && firing_cound % 180 == 0)
			{
				//弾にポジションと回転を教えて生成する
				m_gigatonAttack = NewGO<GigatonCannonAttack>(1, "gigatoncannonattack");
				m_gigatonAttack->originRotation = r_l_Rotation;
				m_gigatonAttack->m_bulletLocalPosition = Vector3{ 0.0f,0.0f,100.0f };
				m_gigatonAttack->m_position = r_l_w_position;
				atack_state = true;
			}
			else if (r_l_w_player->p_custom_point[1][0] == 6 && firing_cound % 180 == 0) 
			{
				battle_ship_attack = NewGO<Battle_ship_attack>(1,"battle_ship_attack");
				battle_ship_attack->originRotation = r_l_Rotation;
				battle_ship_attack->m_bulletLocalPosition = Vector3{ 0.0f,-37.0f,70.0f };
				battle_ship_attack->firing_position = r_l_w_position;
				atack_state = true;
			}
			firing_cound++;
		}
		else {
			firing_cound = 0;
		}
		if (r_l_w_player->game_end_state == 1) {
			DeleteGO(this);
		}
		r_l_w_player->attack_state_rl = atack_state;
		Right_leg_weapons_Render.Update();
	}
}

void Right_leg_weapons::Move() {
	Quaternion originRotation = r_l_w_player->player_rotation;
	r_l_w_position = r_l_w_player->player_position;

	//武器によって取り付けるポジションの変更
	Vector3 lp;
	switch (r_l_w_player->p_custom_point[1][0])
	{
	case 2:	//マシンガン
		lp = { 90.0f,30.0f,0.0f };
		break;
	case 4:	//ギガトンキャノン
		lp = { 55.0f,40.0f,27.0f };
		break;
	case 6:	//戦艦砲
		lp = { 60.0f,40.0f,40.0f };
		break;
	default:
		break;
	}
	originRotation.Multiply(lp);
	r_l_w_position += lp;
	r_l_Rotation = originRotation;
	Right_leg_weapons_Render.SetPosition(r_l_w_position);
	Right_leg_weapons_Render.SetRotation(r_l_Rotation);
}

void Right_leg_weapons::Render(RenderContext& rc) {
	Right_leg_weapons_Render.Draw(rc);
}