#include "stdafx.h"
#include "Right_leg_weapons.h"
#include "Player.h"
#include "Enumeration.h"
#include "Battle_ship_attack.h"
#include "MachineGunAttack.h"
#include "GigatonCannonAttack.h"
#include "Customize_UI_ver2.h"
#include "PlayerUI.h"


Right_leg_weapons::Right_leg_weapons() 
{
	r_l_w_player = FindGO<Player>("player");
	m_customizeUI = FindGO<Customize_UI_ver2>("customize_ui_ver2");

	m_playerUI = FindGO<PlayerUI>("playerui");
	m_playerUI->WeaponUISetUp(2);		//UIの初期化
	m_playerUI->m_rightLeg = (this);	//自分のポインタを教える
}

Right_leg_weapons::~Right_leg_weapons() 
{
	//UIの中身を空にする
	m_playerUI->m_rightLeg = nullptr;
}

void Right_leg_weapons::R_l_w_set() 
{
	switch (r_l_w_player->p_custom_point[1][0])
	{
	case 2:
		Right_leg_weapons_Render.Init("Assets/modelData/machine_gun_drop.tkm");
		Right_leg_weapons_Render.SetScale(scale2);
		Right_leg_weapons_Render.Update();
		set_weapons = r_l_w_player->p_custom_point[1][0];
		//武器の体力の設定
		R_l_w_HP = 700.0f;
		R_l_w_HPMax = 700.0f;
		break;
	case 4:
		Right_leg_weapons_Render.Init("Assets/modelData/GIgaton_cannon.tkm");
		Right_leg_weapons_Render.SetScale(0.8f);
		Right_leg_weapons_Render.Update();
		set_weapons = r_l_w_player->p_custom_point[1][0];
		//武器の体力の設定
		R_l_w_HP = 500.0f;
		R_l_w_HPMax = 500.0f;
		break;
	case 6:
		Right_leg_weapons_Render.Init("Assets/modelData/battleship_gun_Drop.tkm");
		Right_leg_weapons_Render.SetScale(scale2);
		Right_leg_weapons_Render.Update();
		set_weapons = r_l_w_player->p_custom_point[1][0];
		//武器の体力の設定
		R_l_w_HP = 400.0f;
		R_l_w_HPMax = 400.0f;
		break;

	default:
		break;
	}
}

void Right_leg_weapons::Update() 
{
	if (fast == 0) 
	{
		R_l_w_set();
	}

	fast++;

	if (r_l_w_player->game_state == 0) 
	{
		Move();

		//HPが0以下になると消える
		if (R_l_w_HP <= 0)
		{
			//プレイヤーの設定武器を空にする
			r_l_w_player->p_custom_point[1][0] = 0;
			m_customizeUI->Right_leg_weapon_set = false;
			m_customizeUI->m_rightLegWeapon = nullptr;
			DeleteGO(this);
		}


		//攻撃
		if (g_pad[0]->IsPress(enButtonLB1))
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
		else 
		{
			firing_cound = 0;
		}

		if (r_l_w_player->game_end_state == 1) 
		{
			DeleteGO(this);
		}

		r_l_w_player->attack_state_rl = atack_state;
		Right_leg_weapons_Render.Update();
	}
}

void Right_leg_weapons::Move() 
{
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

void Right_leg_weapons::Render(RenderContext& rc) 
{
	if (r_l_w_player->m_deadBakuhaPlay == true)
	{
		return;
	}
	Right_leg_weapons_Render.Draw(rc);
}