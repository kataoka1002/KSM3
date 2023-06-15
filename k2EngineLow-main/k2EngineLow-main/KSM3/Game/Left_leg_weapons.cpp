#include "stdafx.h"
#include "Left_leg_weapons.h"
#include "Player.h"
#include "Enumeration.h"
#include "Battle_ship_attack.h"
#include "MachineGunAttack.h"
#include "GigatonCannonAttack.h"
#include "Customize_UI_ver2.h"
#include "PlayerUI.h"


Left_leg_weapons::Left_leg_weapons() 
{
	l_l_w_player = FindGO<Player>("player");
	m_customizeUI = FindGO<Customize_UI_ver2>("customize_ui_ver2");

	m_playerUI = FindGO<PlayerUI>("playerui");
	m_playerUI->WeaponUISetUp(4);		//UIの初期化
	m_playerUI->m_leftLeg = (this);	//自分のポインタを教える

}


Left_leg_weapons::~Left_leg_weapons() 
{
	m_playerUI->m_leftLeg = nullptr;
}

bool Left_leg_weapons::Start()
{
	return true;
}

void Left_leg_weapons::L_l_w_set() 
{
	switch (l_l_w_player->p_custom_point[1][2])
	{
	case 2:
		Left_leg_weapons_Render.Init("Assets/modelData/machine_gun_drop.tkm");
		Left_leg_weapons_Render.SetScale(scale2);
		Left_leg_weapons_Render.Update();
		set_weapons = l_l_w_player->p_custom_point[1][2];
		//武器の体力の設定
		L_l_w_HP = 700.0f;
		L_l_w_HP = 700.0f;
		break;
	case 4:
		Left_leg_weapons_Render.Init("Assets/modelData/GIgaton_cannon.tkm");
		Left_leg_weapons_Render.SetScale(0.8f);
		Left_leg_weapons_Render.Update();
		set_weapons = l_l_w_player->p_custom_point[1][2];
		//武器の体力の設定
		L_l_w_HP = 500.0f;
		L_l_w_HP = 500.0f;
		break;
	case 6:
		Left_leg_weapons_Render.Init("Assets/modelData/battleship_gun_Drop.tkm");
		Left_leg_weapons_Render.SetScale(scale2);
		Left_leg_weapons_Render.Update();
		set_weapons = l_l_w_player->p_custom_point[1][2];
		//武器の体力の設定
		L_l_w_HP = 400.0f;
		L_l_w_HP = 400.0f;
		break;

	default:
		break;
	}
}

void Left_leg_weapons::Update() 
{
	if (fast == 0) 
	{
		L_l_w_set();
	}

	fast++;


	if (l_l_w_player->game_state == 0) 
	{
		Move();

		//HPが0以下になると消える
		if (L_l_w_HP <= 0)
		{
			//プレイヤーの設定武器を空にする
			l_l_w_player->p_custom_point[1][2] = 0;
			m_customizeUI->Left_leg_weapon_set = false;
			m_customizeUI->m_leftLegWeapon = nullptr;
			DeleteGO(this);
		}

		//攻撃
		if (g_pad[0]->IsPress(enButtonLB1))
		{
			if (l_l_w_player->p_custom_point[1][2] == 2 && firing_cound % 5 == 0)
			{
				//弾にポジションと回転を教えて生成する
				m_machineGunAttack = NewGO<MachineGunAttack>(1, "machinegunattack");
				m_machineGunAttack->SetRotation(l_l_Rotation);
				m_machineGunAttack->SetLocalPosition(Vector3{0.0f,-10.0f,170.0f});
				m_machineGunAttack->SetPosition(l_l_w_position);
			}
			else if (l_l_w_player->p_custom_point[1][2] == 4 && firing_cound % 180 == 0)
			{
				//弾にポジションと回転を教えて生成する
				m_gigatonAttack = NewGO<GigatonCannonAttack>(1, "gigatoncannonattack");
				m_gigatonAttack->SetRotation(l_l_Rotation);
				m_gigatonAttack->SetLocalPosition(Vector3{0.0f,0.0f,100.0f});
				m_gigatonAttack->SetPosition(l_l_w_position);
			}
			else if (l_l_w_player->p_custom_point[1][2] == 6 && firing_cound % 180 == 0) 
			{
				battle_ship_attack = NewGO<Battle_ship_attack>(1, "battle_ship_attack");
				battle_ship_attack->SetRotation(l_l_Rotation);
				battle_ship_attack->SetLocalPosition(Vector3{ 0.0f,-37.0f,70.0f });
				battle_ship_attack->SetPosition(l_l_w_position);
			}
			firing_cound++;
		}
		else 
		{
			firing_cound = 0;
		}

		if (l_l_w_player->game_end_state == 1) 
		{
			DeleteGO(this);
		}

		Left_leg_weapons_Render.Update();
	}
}

void Left_leg_weapons::Move() 
{
	Quaternion originRotation = l_l_w_player->player_rotation;
	l_l_w_position = l_l_w_player->player_position;

	//武器によって取り付けるポジションの変更
	Vector3 lp;
	switch (l_l_w_player->p_custom_point[1][2])
	{
	case 2:	//マシンガン
		lp = { -90.0f,30.0f,0.0f };
		break;
	case 4:	//ギガトンキャノン
		lp = { -55.0f,40.0f,27.0f };
		break;
	case 6:	//戦艦砲
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

void Left_leg_weapons::Render(RenderContext& rc) 
{
	if (l_l_w_player->m_deadBakuhaPlay == true)
	{
		return;
	}
	Left_leg_weapons_Render.Draw(rc);
}