#include "stdafx.h"
#include "Left_arm_weapons.h"
#include "Player.h"
#include "Enumeration.h"
#include "Battle_ship_attack.h"
#include "MachineGunAttack.h"
#include "GigatonCannonAttack.h"
#include "Customize_UI_ver2.h"
#include "PlayerUI.h"

Left_arm_weapons::Left_arm_weapons() 
{
	l_a_w_player = FindGO<Player>("player");
	m_customizeUI = FindGO<Customize_UI_ver2>("customize_ui_ver2");

	m_playerUI = FindGO<PlayerUI>("playerui");
	m_playerUI->WeaponUISetUp(3);		//UIの初期化
	m_playerUI->m_leftArm = (this);		//自分のポインタを教える
}


Left_arm_weapons::~Left_arm_weapons() 
{
	//ポインタを空にする
	m_playerUI->m_leftArm = nullptr;
}

void Left_arm_weapons::L_a_w_set() 
{
	switch (l_a_w_player->p_custom_point[0][2])
	{
	case 2:
		Left_arm_weapons_Render.Init("Assets/modelData/machine_gun_drop.tkm");
		Left_arm_weapons_Render.SetScale(scale2);
		Left_arm_weapons_Render.Update();
		set_weapons = l_a_w_player->p_custom_point[0][2];
		atack_state = true;
		//武器の体力の設定
		L_a_w_HP = 700.0f;
		L_a_w_HP = 700.0f;
		break;
	case 4:
		Left_arm_weapons_Render.Init("Assets/modelData/GIgaton_cannon_Left_arm.tkm");
		Left_arm_weapons_Render.SetScale(0.8f);
		Left_arm_weapons_Render.Update();
		set_weapons = l_a_w_player->p_custom_point[0][2];
		atack_state = true;
		//武器の体力の設定
		L_a_w_HP = 500.0f;
		L_a_w_HP = 500.0f;
		break;
	case 6:
		Left_arm_weapons_Render.Init("Assets/modelData/battleship_gun_left_arm.tkm");
		Left_arm_weapons_Render.SetScale(scale2);
		Left_arm_weapons_Render.Update();
		set_weapons = l_a_w_player->p_custom_point[0][2];
		atack_state = true;
		//武器の体力の設定
		L_a_w_HP = 400.0f;
		L_a_w_HP = 400.0f;
		break;

	default:
		break;
	}
}

void Left_arm_weapons::Update() 
{
	if (fast == 0) 
	{
		L_a_w_set();
	}

	fast++;

	if (l_a_w_player->game_state == 0) 
	{
		Move();

		//HPが0以下になると消える
		if (L_a_w_HP <= 0)
		{
			//プレイヤーの設定武器を空にする
			l_a_w_player->p_custom_point[0][2] = 0;
			m_customizeUI->Left_arm_weapon_set = false;
			m_customizeUI->m_leftArmWeapon = nullptr;
			DeleteGO(this);
		}

		//弾の生成
		if (g_pad[0]->IsPress(enButtonLB1))
		{
			if (l_a_w_player->p_custom_point[0][2] == 2 && firing_cound % 5 == 0)
			{
				//弾にポジションと回転を教えて生成する
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
		else 
		{
			firing_cound = 0;
		}

		if (l_a_w_player->game_end_state == 1) 
		{
			DeleteGO(this);
		}

		l_a_w_player->attack_state_la = atack_state;
		Left_arm_weapons_Render.Update();
	}
}

void Left_arm_weapons::Move() 
{
	Quaternion originRotation = l_a_w_player->player_rotation;
	l_a_w_position = l_a_w_player->player_position;

	//武器によって取り付けるポジションの変更
	Vector3 lp;
	switch (l_a_w_player->p_custom_point[0][2])
	{
	case 2:	//マシンガン
		lp = { -60.0f,100.0f,0.0f };
		break;
	case 4:	//ギガトンキャノン
		lp = { -50.0f,100.0f,30.0f };
		break;
	case 6:	//戦艦砲
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

void Left_arm_weapons::Render(RenderContext& rc)
{
	if (l_a_w_player->m_deadBakuhaPlay == true)
	{
		return;
	}
	Left_arm_weapons_Render.Draw(rc);
}