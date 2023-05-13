#include "stdafx.h"
#include "Shoulder_weapons.h"
#include "Player.h"
#include "Enumeration.h"
#include "Battle_ship_attack.h"
#include "MachineGunAttack.h"
#include "Shoulder_UI.h"
#include "GigatonCannonAttack.h"
#include "Customize_UI_ver2.h"


Shoulder_weapons::Shoulder_weapons() 
{
	s_w_player = FindGO<Player>("player");
	shoulder_ui= FindGO<Shoulder_UI>("shoulder_ui");
	m_customizeUI = FindGO<Customize_UI_ver2>("customize_ui_ver2");
}

Shoulder_weapons::~Shoulder_weapons() 
{
	/*if (atack_state == true) {
		if (battle_ship_attack->Landing_state_BB == false) {
			DeleteGO(battle_ship_attack);
		}
	}*/
}

void Shoulder_weapons::S_w_set() 
{
	switch (s_w_player->p_custom_point[0][1])
	{
	case 2:
		//マシンガンのモデルを2つ作る
		Shoulder_weapons_Render.Init("Assets/modelData/machine_gun_drop.tkm");
		Shoulder_weapons_Render.SetScale(scale2);
		Shoulder_weapons_Render.Update();

		Shoulder_weapons_Render2.Init("Assets/modelData/machine_gun_drop.tkm");
		Shoulder_weapons_Render2.SetScale(scale2);
		Shoulder_weapons_Render2.Update();

		set_weapons = s_w_player->p_custom_point[0][1];
		break;
	case 4:
		Shoulder_weapons_Render.Init("Assets/modelData/GIgaton_shoulder.tkm");
		Shoulder_weapons_Render.SetScale(0.8f);
		Shoulder_weapons_Render.Update();
		set_weapons = s_w_player->p_custom_point[0][1];
		break;
	case 6:
		Shoulder_weapons_Render.Init("Assets/modelData/battleship_gun_shoulder.tkm");
		Shoulder_weapons_Render.SetScale(scale2);
		Shoulder_weapons_Render.Update();
		set_weapons = s_w_player->p_custom_point[0][1];
		break;
	default:
		break;
	}
}

void Shoulder_weapons::Update() 
{
	if (fast == 0) 
	{
		S_w_set();
		shoulder_ui = NewGO<Shoulder_UI>(1, "shoulder_ui");
	}
	fast++;
	if (s_w_player->game_state == 0) 
	{
		Move();
		Move2();

		//HPが0以下になると消える
		if (S_w_HP <= 0)
		{
			//プレイヤーの設定武器を空にする
			s_w_player->p_custom_point[0][1] = 0;
			m_customizeUI->Shoulder_weapon_set = false;
			m_customizeUI->m_shoulderWeapon = nullptr;
			DeleteGO(this);
		}

		//攻撃
		if (g_pad[0]->IsPress(enButtonRB1)) 
		{
			if (s_w_player->p_custom_point[0][1] == 2 && firing_cound % 5 == 0)
			{
				//弾にポジションと回転を教えて生成する
				m_machineGunAttack = NewGO<MachineGunAttack>(1, "machinegunattack");
				m_machineGunAttack->originRotation = Shoulder_Rotation;
				m_machineGunAttack->m_bulletLocalPosition = Vector3{ 0.0f,-10.0f,170.0f };
				m_machineGunAttack->m_position = s_w_position;

				m_machineGunAttack2 = NewGO<MachineGunAttack>(1, "machinegunattack");
				m_machineGunAttack2->originRotation = Shoulder_Rotation2;
				m_machineGunAttack2->m_bulletLocalPosition = Vector3{ 0.0f,-10.0f,170.0f };
				m_machineGunAttack2->m_position = s_w_position2;

				atack_state = true;
			}
			else if (s_w_player->p_custom_point[0][1] == 4 && firing_cound % 180 == 0)
			{
				//弾にポジションと回転を教えて生成する
				m_gigatonAttack = NewGO<GigatonCannonAttack>(1, "gigatoncannonattack");
				m_gigatonAttack->originRotation = Shoulder_Rotation;
				m_gigatonAttack->m_bulletLocalPosition = Vector3{ 40.0f,0.0f,100.0f };
				m_gigatonAttack->m_position = s_w_position;

				//弾にポジションと回転を教えて生成する
				m_gigatonAttack2 = NewGO<GigatonCannonAttack>(1, "gigatoncannonattack");
				m_gigatonAttack2->originRotation = Shoulder_Rotation;
				m_gigatonAttack2->m_bulletLocalPosition = Vector3{ -40.0f,0.0f,100.0f };
				m_gigatonAttack2->m_position = s_w_position;

				atack_state = true;
			}
			else if (s_w_player->p_custom_point[0][1] == 6 && firing_cound % 180 == 0) 
			{
				battle_ship_attack = NewGO<Battle_ship_attack>(1, "battle_ship_attack");
				battle_ship_attack->originRotation = Shoulder_Rotation;
				battle_ship_attack->m_bulletLocalPosition = Vector3{ 40.0f,-40.0f,70.0f };
				battle_ship_attack->firing_position = s_w_position;

				battle_ship_attack2 = NewGO<Battle_ship_attack>(1, "battle_ship_attack");
				battle_ship_attack2->originRotation = Shoulder_Rotation;
				battle_ship_attack2->m_bulletLocalPosition = Vector3{ -40.0f,-40.0f,70.0f };
				battle_ship_attack2->firing_position = s_w_position;

				atack_state = true;
			}
			firing_cound++;
		}
		else {
			firing_cound = 0;
		}
		if (s_w_player->game_end_state == 1) {
			DeleteGO(this);
		}
		s_w_player->attack_state_s = atack_state;

		//付けている武器の更新
		Shoulder_weapons_Render.Update();
		//付けている武器がマシンガンなら
		if (s_w_player->p_custom_point[0][1] == 2)
		{
			Shoulder_weapons_Render2.Update();
		}
	}
}

void Shoulder_weapons::Move() 
{
	Quaternion originRotation = s_w_player->player_rotation;
	s_w_position = s_w_player->player_position;

	//武器によって取り付けるポジションの変更
	Vector3 lp;
	switch (s_w_player->p_custom_point[0][1])
	{
	case 2:	//マシンガン
		lp = { 35.0f,120.0f,0.0f };
		break;
	case 4:	//ギガトンキャノン
		lp = { 0.0f,120.0f,0.0f };
		break;
	case 6:	//戦艦砲
		lp = { 0.0f,119.0f,0.0f };
		break;
	default:
		break;
	}
	originRotation.Multiply(lp);
	s_w_position += lp;
	Shoulder_Rotation = originRotation;
	Shoulder_weapons_Render.SetPosition(s_w_position);
	Shoulder_weapons_Render.SetRotation(Shoulder_Rotation);
}

void Shoulder_weapons::Move2()
{
	if (s_w_player->p_custom_point[0][1] == 2)
	{
		Quaternion originRotation = s_w_player->player_rotation;
		s_w_position2 = s_w_player->player_position;

		//武器によって取り付けるポジションの変更
		Vector3 lp;
		switch (s_w_player->p_custom_point[0][1])
		{
		case 2:	//マシンガン
			lp = { -35.0f,120.0f,0.0f };
			break;
		default:
			break;
		}
		originRotation.Multiply(lp);
		s_w_position2 += lp;
		Shoulder_Rotation2 = originRotation;
		Shoulder_weapons_Render2.SetPosition(s_w_position2);
		Shoulder_weapons_Render2.SetRotation(Shoulder_Rotation2);
	}
}

void Shoulder_weapons::Render(RenderContext& rc) 
{
	Shoulder_weapons_Render.Draw(rc);
	//付けている武器がマシンガンなら
	if (s_w_player->p_custom_point[0][1] == 2)
	{
		Shoulder_weapons_Render2.Draw(rc);
	}
}
