#include "stdafx.h"
#include "Right_arm_weapons.h"
#include "Player.h"
#include "Enumeration.h"
#include "Battle_ship_attack.h"
#include "MachineGunAttack.h"
#include "Right_arm_UI.h"
#include "GigatonCannonAttack.h"


Right_arm_weapons::Right_arm_weapons() 
{
	right_arm_ui = NewGO<Right_arm_UI>(1, "right_arm_ui");
}

Right_arm_weapons::~Right_arm_weapons() 
{
	/*if (atack_state == true) 
	{
		if (battle_ship_attack->Landing_state_BB == false) 
		{
			DeleteGO(battle_ship_attack);
		}
	}*/
}

bool Right_arm_weapons::Start()
{
	r_a_w_player = FindGO<Player>("player");
	right_arm_ui = FindGO<Right_arm_UI>("right_arm_ui");

	R_a_w_set();

	return true;
}

void Right_arm_weapons::R_a_w_set() 
{
	if (r_a_w_player->p_custom_point[0][0] == 1) 
	{
		
	}

	//付いている武器によってモデルを変更する
	switch (r_a_w_player->p_custom_point[0][0])
	{
	case 2:
		Right_arm_weapons_Render.Init("Assets/modelData/machine_gun_drop.tkm");
		Right_arm_weapons_Render.SetScale(scale2);
		Right_arm_weapons_Render.Update();
		set_weapons = r_a_w_player->p_custom_point[0][0];
		break;
	case 4:
		Right_arm_weapons_Render.Init("Assets/modelData/GIgaton_cannon.tkm");
		Right_arm_weapons_Render.SetScale(1.0f);
		Right_arm_weapons_Render.Update();
		set_weapons = r_a_w_player->p_custom_point[0][0];
		break;
	case 6:
		Right_arm_weapons_Render.Init("Assets/modelData/battleship_gun_right_arm.tkm");
		Right_arm_weapons_Render.SetScale(scale2);
		Right_arm_weapons_Render.Update();
		set_weapons = r_a_w_player->p_custom_point[0][0];
		break;
	default:
		break;
	}
}

void Right_arm_weapons::Update() 
{
	if (r_a_w_player->game_state == 0) 
	{
		Move();
		//攻撃
		if (g_pad[0]->IsPress(enButtonRB1)) 
		{
			//武器がマシンガンの場合
			if (r_a_w_player->p_custom_point[0][0] == 2 && firing_count % 5 == 0)
			{
				//弾にポジションと回転を教えて生成する
				m_machineGunAttack = NewGO<MachineGunAttack>(1, "machinegunattack");
				m_machineGunAttack->m_rot = r_a_Rotation;
				m_machineGunAttack->m_position = r_a_w_position;
				atack_state = true;
			}
			//武器がギガトンキャノンの場合
			else if (r_a_w_player->p_custom_point[0][0] == 4 && firing_count % 180 == 0)
			{
				//弾にポジションと回転を教えて生成する
				m_gigatonAttack = NewGO<GigatonCannonAttack>(1, "gigatoncannonattack");
				m_gigatonAttack->originRotation = r_a_Rotation;
				m_gigatonAttack->m_bulletLocalPosition = Vector3{ 0.0f,0.0f,100.0f };
				m_gigatonAttack->m_position = r_a_w_position;
				atack_state = true;
			}
			//武器が戦艦砲の場合
			else if (r_a_w_player->p_custom_point[0][0] == 6 && firing_count % 180 == 0)
			{
				//弾にポジションと回転を教えて生成する
				battle_ship_attack = NewGO<Battle_ship_attack>(1, "battle_ship_attack");
				battle_ship_attack->B_S_aiming = r_a_Rotation;
				battle_ship_attack->firing_position = r_a_w_position;
				atack_state = true;
			}
			firing_count++;
		}
		else 
		{
			firing_count = 0;
		}

		if (r_a_w_player->game_end_state == 1) 
		{
			DeleteGO(this);
		}

		r_a_w_player->attack_state_ra = atack_state;
		Right_arm_weapons_Render.Update();
	}
}

void Right_arm_weapons::Move() 
{
	//武器によって取り付けるポジションの変更
	Vector3 lp;
	switch (r_a_w_player->p_custom_point[0][0])
	{
	case 2:	//マシンガン
		lp = { 60.0f,100.0f,-10.0f };
		break;
	case 4:	//ギガトンキャノン
		lp = { 60.0f,100.0f,-10.0f };
		break;
	case 6:	//戦艦砲
		lp = { 60.0f,80.0f,-10.0f };
		break;
	default:
		break;
	}

	//ポジションの計算
	Quaternion originRotation = r_a_w_player->player_rotation;
	r_a_w_position = r_a_w_player->player_position;
	originRotation.Multiply(lp);
	r_a_w_position += lp;
	r_a_Rotation = originRotation;

	//更新
	Right_arm_weapons_Render.SetPosition(r_a_w_position);
	Right_arm_weapons_Render.SetRotation(r_a_Rotation);
}

void Right_arm_weapons::Render(RenderContext& rc) 
{
	Right_arm_weapons_Render.Draw(rc);
}