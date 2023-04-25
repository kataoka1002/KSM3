#include "stdafx.h"
#include "Customize_UI_ver2.h"
#include"Player.h"

#include "Left_arm_weapons.h"
#include"Right_arm_weapons.h"
#include "Core_weapons.h"
#include "Shoulder_weapons.h"
#include "Right_leg_weapons.h"
#include "Left_leg_weapons.h"

#include "Drop_item.h"

#include"Customize_area.h"
#include "GameCamera.h"



Customize_UI_ver2::Customize_UI_ver2() {
	custom_player = FindGO<Player>("player");
	cui_core_weapons = FindGO<Core_weapons>("core_weapons");
	cui_right_arm_weapons = FindGO<Right_arm_weapons>("right_arm_weapons");
	cui_left_arm_weapons = FindGO<Left_arm_weapons>("left_arm_weapons");
	cui_shoulder_weapons = FindGO<Shoulder_weapons>("shoulder_weapons");
	cui_right_leg_weapons = FindGO<Right_leg_weapons>("right_leg_weapons");
	cui_left_leg_weapons = FindGO<Left_leg_weapons>("left_leg_weapons");

	custom_player->game_state = 3;
	C_UI_2_GameCamera = FindGO<GameCamera>("gamecamera");
	C_UI_2_GameCamera->m_toCameraPos.Set(0.0f, -10.0f, -100.0f);
	C_UI_2_GameCamera->fast_count=0;
	C_UI_2_GameCamera->target = custom_model_body_position;
	C_UI_2_GameCamera->CameraState =3;
	cui_drop_item = FindGO<Drop_item>("drop_item");
	customize_area = NewGO<Customize_area>(1, "customize_area");
	Setup();
}

void Customize_UI_ver2::Setup() {
	
	Custom_model_Core();
	Custom_model_body();

	if (custom_player->p_custom_point[0][0] != 0) {
		Custom_model_Right_arm();
	}
	if (custom_player->p_custom_point[0][2] != 0) {
		Custom_model_Left_arm();
	}
	if (custom_player->p_custom_point[0][1] != 0) {
		Custom_model_Shoulder();
	}
	if (custom_player->p_custom_point[1][0] != 0) {
		Custom_model_Right_leg();
	}
	if (custom_player->p_custom_point[1][2] != 0) {
		Custom_model_Left_leg();
	}

	custom_kinds = cui_drop_item->drop_kinds;
}

Customize_UI_ver2::~Customize_UI_ver2() {
	C_UI_2_GameCamera->m_toCameraPos.Set(0.0f, 500.0f, -700.0f);
	//DeleteGO(cui_drop_item);
	DeleteGO(customize_area);
	custom_player->game_state = 0;
}

void Customize_UI_ver2::Update() {
	
	if (g_pad[0]->IsTrigger(enButtonRB1) && selection_position < 5) {
		selection_position++;
		fast_count = 0;
	}
	else if (g_pad[0]->IsTrigger(enButtonLB1) && selection_position >=1) {
		selection_position--;
		fast_count = 0;
	}

	switch (selection_position)
	{
	case 0:
		if (fast_count == 0) {
			//表示指示
			//どこを選択しているのか
			select_sheet.Init("Assets/sprite/select_sheet_01.DDS", 1166.0f, 175.0f);
			select_sheet.SetPosition(select_sheet_position);
			select_sheet.Update();
			//パラメーターシート
			switch (custom_player->p_custom_point[0][1])
			{
			case 0:
				parameter_sheet.Init("Assets/sprite/Non_attachment_UI_parameter.DDS",650.0f,600.0f);
				parameter_sheet.SetPosition(parameter_sheet_position);
				parameter_sheet.Update();
				break;
			case 1:
				parameter_sheet.Init("Assets/sprite/BattleShip_gun_UI_parameter.DDS", 650.0f, 600.0f);
				parameter_sheet.SetPosition(parameter_sheet_position);
				parameter_sheet.Update();
				//Custom_model_Shoulder;
				break;
			default:
				break;
			}
		}
		if (g_pad[0]->IsTrigger(enButtonA) && custom_player->p_custom_point[0][1] == 0 && window_count == 0) {
			//適応確認
			window_open = true;
			confirmatino_window_open = true;
			window_select = true;
			column = 0, line = 1;
		}
		break;
	case 1:
		if (fast_count == 0) {
			//表示指示
			select_sheet.Init("Assets/sprite/select_sheet_02.DDS", 1166.0f, 175.0f);
			select_sheet.SetPosition(select_sheet_position);
			select_sheet.Update();
			switch (cui_core_weapons->set_weapons)
			{
			case 1:
				parameter_sheet.Init("Assets/sprite/Non_attachment_UI_parameter.DDS", 650.0f, 600.0f);
				parameter_sheet.SetPosition(parameter_sheet_position);
				parameter_sheet.Update();
				
				break;
			case 2:
				parameter_sheet.Init("Assets/sprite/Glare_bassinet_UI_parameter.DDS", 650.0f, 600.0f);
				parameter_sheet.SetPosition(parameter_sheet_position);
				parameter_sheet.Update();
				
				break;
			default:
				break;
			}
		}
		if (g_pad[0]->IsTrigger(enButtonA) && fast_count != 0) {
			//適応確認
		}
		break;
	case 2:
		if (fast_count == 0) {
			//表示指示
			select_sheet.Init("Assets/sprite/select_sheet_03.DDS", 1166.0f, 175.0f);
			select_sheet.SetPosition(select_sheet_position);
			select_sheet.Update();
			switch (custom_player->p_custom_point[0][0])
			{
			case 0:
				parameter_sheet.Init("Assets/sprite/Non_attachment_UI_parameter.DDS", 650.0f, 600.0f);
				parameter_sheet.SetPosition(parameter_sheet_position);
				parameter_sheet.Update();
				break;
			case 1:
				parameter_sheet.Init("Assets/sprite/BattleShip_gun_UI_parameter.DDS", 650.0f, 600.0f);
				parameter_sheet.SetPosition(parameter_sheet_position);
				parameter_sheet.Update();
				//Custom_model_Shoulder;
				break;
			default:
				break;
			}
		}

		if (g_pad[0]->IsTrigger(enButtonA)&& custom_player->p_custom_point[0][0]==0&&window_count==0) {
			//適応確認
			window_open = true;
			confirmatino_window_open = true;
			window_select = true;
			column = 0,line=0;
		}
		break;
	case 3:
		if (fast_count == 0) {
			//表示指示
			select_sheet.Init("Assets/sprite/select_sheet_04.DDS", 1166.0f, 175.0f);
			select_sheet.SetPosition(select_sheet_position);
			select_sheet.Update();
			switch (custom_player->p_custom_point[0][2])
			{
			case 0:
				parameter_sheet.Init("Assets/sprite/Non_attachment_UI_parameter.DDS", 650.0f, 600.0f);
				parameter_sheet.SetPosition(parameter_sheet_position);
				parameter_sheet.Update();
				break;
			case 1:
				parameter_sheet.Init("Assets/sprite/BattleShip_gun_UI_parameter.DDS", 650.0f, 600.0f);
				parameter_sheet.SetPosition(parameter_sheet_position);
				parameter_sheet.Update();
				//Custom_model_Shoulder;
				break;
			default:
				break;
			}
		}
		if (g_pad[0]->IsTrigger(enButtonA) && custom_player->p_custom_point[0][2] == 0 && window_count == 0) {
			//適応確認
			window_open = true;
			confirmatino_window_open = true;
			window_select = true;
			column = 0, line = 2;
		}
		break;
	case 4:
		if (fast_count == 0) {
			//表示指示
			select_sheet.Init("Assets/sprite/select_sheet_05.DDS", 1166.0f, 175.0f);
			select_sheet.SetPosition(select_sheet_position);
			select_sheet.Update();
			switch (custom_player->p_custom_point[1][0])
			{
			case 0:
				parameter_sheet.Init("Assets/sprite/Non_attachment_UI_parameter.DDS", 650.0f, 600.0f);
				parameter_sheet.SetPosition(parameter_sheet_position);
				parameter_sheet.Update();
				break;
			case 1:
				parameter_sheet.Init("Assets/sprite/BattleShip_gun_UI_parameter.DDS", 650.0f, 600.0f);
				parameter_sheet.SetPosition(parameter_sheet_position);
				parameter_sheet.Update();
				//Custom_model_Shoulder;
				break;
			default:
				break;
			}
		}
		if (g_pad[0]->IsTrigger(enButtonA) && custom_player->p_custom_point[1][0] == 0 && window_count == 0) {
			//適応確認
			window_open = true;
			confirmatino_window_open = true;
			window_select = true;
			column = 1, line = 0;
		}
		break;
	case 5:
		if (fast_count == 0) {
			//表示指示
			select_sheet.Init("Assets/sprite/select_sheet_06.DDS", 1166.0f, 175.0f);
			select_sheet.SetPosition(select_sheet_position);
			select_sheet.Update();
			switch (custom_player->p_custom_point[1][2])
			{
			case 0:
				parameter_sheet.Init("Assets/sprite/Non_attachment_UI_parameter.DDS", 650.0f, 600.0f);
				parameter_sheet.SetPosition(parameter_sheet_position);
				parameter_sheet.Update();
				break;
			case 1:
				parameter_sheet.Init("Assets/sprite/BattleShip_gun_UI_parameter.DDS", 650.0f, 600.0f);
				parameter_sheet.SetPosition(parameter_sheet_position);
				parameter_sheet.Update();
				//Custom_model_Shoulder;
				break;
			default:
				break;
			}
		}
		if (g_pad[0]->IsTrigger(enButtonA) && custom_player->p_custom_point[1][2] == 0 && window_count == 0) {
			//適応確認
			window_open = true;
			confirmatino_window_open = true;
			window_select = true;
			column = 1, line = 2;
		}
		break;
	default:
		break;
	}
	if (g_pad[0]->IsTrigger(enButtonB)) {
		DeleteGO(this);
	}
	fast_count++;

	if (window_open == true) {
		Window();
	}
}

void Customize_UI_ver2::Window() {
	if (window_open == true) {
		//武器の設定確認のウィンドウ
		if (confirmatino_window_open == true) {
			window_count++;
			//ACCEPT時の処理
			if (window_select == true) {
				//ウィンドウの表示処理
				if (window_count == 1) {
					confirmation_window.Init("Assets/sprite/confirmation_window_yes.DDS", 584.375f, 918.0f);
				}
				//セレクトが変わったときの処理
				if (g_pad[0]->IsTrigger(enButtonRight)) {
					window_count = 0;
					window_select = false;
				}
				//決定した時の処理
				if (g_pad[0]->IsTrigger(enButtonA) && window_count != 1 && window_open == true) {
					custom_player->p_custom_point[column][line] = custom_kinds;
					switch (selection_position)
					{
					case 0:
						cui_shoulder_weapons = NewGO<Shoulder_weapons>(2, "shoulder_weapons");
						break;
					case 1:
						
						break;
					case 2:
						cui_right_arm_weapons = NewGO<Right_arm_weapons>(2, "right_arm_weapons");
						break;
					case 3:
						cui_left_arm_weapons = NewGO<Left_arm_weapons>(2, "left_arm_weapons");
						break;
					case 4:
						cui_right_leg_weapons = NewGO<Right_leg_weapons>(2, "right_leg_weapons");
						break;
					case 5:
						cui_left_leg_weapons = NewGO<Left_leg_weapons>(2, "left_leg_weapons");
					default:
						break;
					}
					
					DeleteGO(this);
				}
			}
			//DECLINE時の処理
			else if (window_select == false) {
				if (window_count == 1) {
					confirmation_window.Init("Assets/sprite/confirmation_window_no.DDS", 584.375f, 918.0f);
				}
				if (g_pad[0]->IsTrigger(enButtonLeft)) {
					window_select = true;
					window_count = 0;
				}
				if (g_pad[0]->IsTrigger(enButtonA) || g_pad[0]->IsTrigger(enButtonB) && window_count != 1) {
					window_open = false;
					window_count = 0;
				}
			}
			confirmation_window.Update();
		}
	}
}

void Customize_UI_ver2::Custom_model_body() {
	custom_model_body.Init("Assets/modelData/test_player.tkm");
	custom_model_body.SetPosition(custom_model_body_position);
	custom_model_body_rotation.SetRotationDegY(-135.0f);
	custom_model_body.SetRotation(custom_model_body_rotation);
	custom_model_body.Update();
}

void Customize_UI_ver2::Custom_model_Core() {
	
	custom_model_body_rotation.SetRotationDegY(-135.0f);
	Quaternion originRotation = custom_model_body_rotation;
	Vector3 cw_position = custom_model_body_position;
	if (cui_core_weapons->set_weapons == 2) {
		custom_model_Core.Init("Assets/modelData/Versatile_Perforator.tkm");
		cw_lp = { 0.0f,70.0f,10.0f };
	}
	originRotation.Multiply(cw_lp);
	cw_position += cw_lp;
	Quaternion cw_Rotation = originRotation;

	custom_model_Core.SetRotation(cw_Rotation);
	custom_model_Core.SetPosition(cw_position);
	custom_model_Core.Update();
}

void Customize_UI_ver2::Custom_model_Right_arm() {
	right_arm_weapon_set = true;

	Quaternion originRotation = custom_model_body_rotation;
	Vector3 raw_position = custom_model_body_position;
	switch (cui_right_arm_weapons->set_weapons)
	{
	case 1:
		custom_model_Right_arm.Init("Assets/modelData/battleship_gun_right_arm.tkm");
		raw_lp = { 60.0f,70.0f,-10.0f };
		
		custom_model_Right_arm.SetScale(scale2);
	default:
		break;
	}
	originRotation.Multiply(raw_lp);
	raw_position += raw_lp;
	Quaternion raw_Rotation = originRotation;

	custom_model_Right_arm.SetRotation(raw_Rotation);
	custom_model_Right_arm.SetPosition(raw_position);
	custom_model_Right_arm.Update();
}

void Customize_UI_ver2::Custom_model_Left_arm() {
	Left_arm_weapon_set = true;

	Quaternion originRotation = custom_model_body_rotation;
	Vector3 law_position = custom_model_body_position;
	switch (cui_left_arm_weapons->set_weapons)
	{
	case 1:
		custom_model_Left_arm.Init("Assets/modelData/battleship_gun_left_arm.tkm");
		law_lp = { -60.0f,70.0f,-10.0f };

		custom_model_Left_arm.SetScale(scale2);
	default:
		break;
	}
	originRotation.Multiply(law_lp);
	law_position += law_lp;
	Quaternion law_Rotation = originRotation;

	custom_model_Left_arm.SetRotation(law_Rotation);
	custom_model_Left_arm.SetPosition(law_position);
	custom_model_Left_arm.Update();
}

void Customize_UI_ver2::Custom_model_Shoulder() {
	Shoulder_weapon_set = true;

	Quaternion originRotation = custom_model_body_rotation;
	Vector3 sw_position = custom_model_body_position;
	switch (cui_shoulder_weapons->set_weapons)
	{
	case 1:
		custom_model_shoulder.Init("Assets/modelData/battleship_gun_shoulder.tkm");
		sw_lp = { 0.0f,110.0f,0.0f };

		custom_model_shoulder.SetScale(scale2);
	default:
		break;
	}
	originRotation.Multiply(sw_lp);
	sw_position += sw_lp;
	Quaternion sw_Rotation = originRotation;

	custom_model_shoulder.SetRotation(sw_Rotation);
	custom_model_shoulder.SetPosition(sw_position);
	custom_model_shoulder.Update();
}

void Customize_UI_ver2::Custom_model_Right_leg() {
	Right_leg_weapon_set = true;

	Quaternion originRotation = custom_model_body_rotation;
	Vector3 rlw_position = custom_model_body_position;
	switch (cui_right_leg_weapons->set_weapons)
	{
	case 1:
		custom_model_Right_leg.Init("Assets/modelData/battleship_gun_right_leg01.tkm");
		rlw_lp = { 90.0f,30.0f,55.0f };

		custom_model_Right_leg.SetScale(scale2);
	default:
		break;
	}
	originRotation.Multiply(rlw_lp);
	rlw_position += rlw_lp;
	Quaternion rlw_Rotation = originRotation;

	custom_model_Right_leg.SetRotation(rlw_Rotation);
	custom_model_Right_leg.SetPosition(rlw_position);
	custom_model_Right_leg.Update();
}

void Customize_UI_ver2::Custom_model_Left_leg() {
	Left_leg_weapon_set = true;

	Quaternion originRotation = custom_model_body_rotation;
	Vector3 llw_position = custom_model_body_position;
	switch (cui_left_leg_weapons->set_weapons)
	{
	case 1:
		custom_model_Left_leg.Init("Assets/modelData/battleship_gun_left_leg01.tkm");
		llw_lp = { -90.0f,30.0f,55.0f };

		custom_model_Left_leg.SetScale(scale2);
	default:
		break;
	}
	originRotation.Multiply(llw_lp);
	llw_position += llw_lp;
	Quaternion llw_Rotation = originRotation;

	custom_model_Left_leg.SetRotation(llw_Rotation);
	custom_model_Left_leg.SetPosition(llw_position);
	custom_model_Left_leg.Update();
}

void Customize_UI_ver2::Render(RenderContext& rc) {
	select_sheet.Draw(rc);
	parameter_sheet.Draw(rc);
	custom_model_Core.Draw(rc);
	custom_model_body.Draw(rc);

	if (right_arm_weapon_set == true) {
		custom_model_Right_arm.Draw(rc);
	}
	if (Left_arm_weapon_set == true) {
		custom_model_Left_arm.Draw(rc);
	}
	if (Shoulder_weapon_set == true) {
		custom_model_shoulder.Draw(rc);
	}
	if (Right_leg_weapon_set == true) {
		custom_model_Right_leg.Draw(rc);
	}
	if (Left_leg_weapon_set == true) {
		custom_model_Left_leg.Draw(rc);
	}

	if (window_open == true) {
		if (confirmatino_window_open == true) {
			confirmation_window.Draw(rc);
		}
	}
}