#include "stdafx.h"
#include "Customize_UI_ver2.h"
#include"Player.h"
#include "Left_arm_weapons.h"
#include"Right_arm_weapons.h"
#include "Core_weapons.h"
#include "Drop_item.h"
#include"Customize_area.h"
#include "GameCamera.h"

Customize_UI_ver2::Customize_UI_ver2() {
	custom_player = FindGO<Player>("player");
	cui_core_weapons = FindGO<Core_weapons>("core_weapons");
	custom_player->game_state = 3;
	C_UI_2_GameCamera = FindGO<GameCamera>("gamecamera");
	C_UI_2_GameCamera->m_toCameraPos.Set(0.0f, -50.0f, -300.0f);
	//C_UI_2_GameCamera->CameraState = 3;
	cui_drop_item = FindGO<Drop_item>("drop_item");
	customize_area = NewGO<Customize_area>(1, "customize_area");
	Setup();
}

void Customize_UI_ver2::Setup() {
	
	Custom_model_Core();
	Custom_model_body();

	custom_kinds = cui_drop_item->drop_kinds;
}

Customize_UI_ver2::~Customize_UI_ver2() {
	C_UI_2_GameCamera->m_toCameraPos.Set(0.0f, 500.0f, -700.0f);

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
		if (g_pad[0]->IsTrigger(enButtonA) && fast_count != 0) {
			//適応確認
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
		if (g_pad[0]->IsTrigger(enButtonA) && fast_count != 0) {
			//適応確認
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
		if (g_pad[0]->IsTrigger(enButtonA) && fast_count != 0) {
			//適応確認
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
		if (g_pad[0]->IsTrigger(enButtonA) && fast_count != 0) {
			//適応確認
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
						break;
					case 1:
						break;
					case 2:
						cui_right_arm_weapons = NewGO<Right_arm_weapons>(2, "right_arm_weapons");
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
	custom_model_Core.Init("Assets/modelData/Versatile_Perforator.tkm");

	Quaternion originRotation = custom_model_body_rotation;
	Vector3 cw_position = custom_model_body_position;
	if (cui_core_weapons->set_weapons == 2) {
		lp = { 0.0f,70.0f,10.0f };
	}
	originRotation.Multiply(lp);
	cw_position += lp;
	Quaternion cw_Rotation = originRotation;

	custom_model_Core.SetRotation(cw_Rotation);
	custom_model_Core.SetPosition(cw_position);
	custom_model_Core.Update();
}

void Customize_UI_ver2::Render(RenderContext& rc) {
	select_sheet.Draw(rc);
	parameter_sheet.Draw(rc);
	custom_model_Core.Draw(rc);
	custom_model_body.Draw(rc);

	if (window_open == true) {
		if (confirmatino_window_open == true) {
			confirmation_window.Draw(rc);
		}
	}
}