#include "stdafx.h"
#include "Customize_UI.h"
#include"Player.h"
#include "Left_arm_weapons.h"
#include"Right_arm_weapons.h"
#include "Drop_item.h"
#include <vector>       // ヘッダファイルインクルード
using namespace std;

Customize_UI::Customize_UI() {
	custom_player = FindGO<Player>("player");
	c_ui_drop_item = FindGO<Drop_item>("drop_item");
	custom_player->game_state = 2;
	m_isWindowOpen = false;

	m_customKinds = c_ui_drop_item->drop_kinds;

	//武器の設定情報の取得
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			 custom_point[i][j]= custom_player->p_custom_point[i][j];
		}
	}
	C_UI_Select_arrow.Init("Assets/sprite/C_UI_select_arrow.DDS", 33.0f, 54.0f);
	C_UI_Render.Init("Assets/sprite/custom_screen.DDS", 1920.0f, 1080.0f);
	custom_point[1][2] = m_customKinds;


	switch (custom_point[0][0])
	{
	case 0:
		slot_1_RA.Init("Assets/sprite/air_slot.DDS", 140.0f, 115.0f);
		break;
	case 1:
		slot_1_RA.Init("Assets/sprite/BattleShip_gun_icon.DDS", 140.0f, 115.0f);
		break;
	default:
		break;
	}

	switch (custom_point[0][1])
	{
	case 0:
		slot_2_SD.Init("Assets/sprite/air_slot.DDS", 140.0f, 115.0f);
		break;
	case 1:
		slot_2_SD.Init("Assets/sprite/BattleShip_gun_icon.DDS", 140.0f, 115.0f);
		break;
	default:
		break;
	}

	switch (custom_point[0][2])
	{
	case 0:
		slot_3_LA.Init("Assets/sprite/air_slot.DDS", 140.0f, 115.0f);
		break;
	case 1:
		slot_3_LA.Init("Assets/sprite/BattleShip_gun_icon.DDS", 140.0f, 115.0f);
		break;
	default:
		break;
	}

	switch (custom_point[1][0])
	{
	case 0:
		slot_4_RL.Init("Assets/sprite/air_slot.DDS", 140.0f, 115.0f);
		break;
	case 1:
		slot_4_RL.Init("Assets/sprite/BattleShip_gun_icon.DDS", 140.0f, 115.0f);
		break;
	default:
		break;
	}

	switch (custom_point[1][1])
	{
	case 0:
		slot_5_LL.Init("Assets/sprite/air_slot.DDS", 140.0f, 115.0f);
		break;
	case 1:
		slot_5_LL.Init("Assets/sprite/BattleShip_gun_icon.DDS", 140.0f, 115.0f);
		break;
	default:
		break;
	}

	switch (custom_point[1][2]){
	    case 0:
			slot_6_CI.Init("Assets/sprite/air_slot.DDS", 140.0f, 115.0f);
			break;
		case 1:
			slot_6_CI.Init("Assets/sprite/BattleShip_gun_icon.DDS", 140.0f, 115.0f);
			break;
		default:
			break;
	}

	slot_1_RA.SetPosition(slot_1_position);
	slot_2_SD.SetPosition(slot_2_position);
	slot_3_LA.SetPosition(slot_3_position);
	slot_4_RL.SetPosition(slot_4_position);
	slot_5_LL.SetPosition(slot_5_position);
	slot_6_CI.SetPosition(slot_6_position);

	slot_1_RA.SetScale(scalec);
	slot_2_SD.SetScale(scalec);
	slot_3_LA.SetScale(scalec);
	slot_4_RL.SetScale(scalec);
	slot_5_LL.SetScale(scalec);
	slot_6_CI.SetScale(scalec);

	C_UI_Render.SetScale(scalec);

	slot_1_RA.Update();
	slot_2_SD.Update();
	slot_3_LA.Update();
	slot_4_RL.Update();
	slot_5_LL.Update();
	slot_6_CI.Update();

	C_UI_Render.Update();
}

Customize_UI::~Customize_UI() {
	custom_player->game_state = 0;
	//武器の設定情報の更新
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			custom_player->p_custom_point[i][j] = custom_point[i][j];
		}
	}
	DeleteGO(c_ui_drop_item);
}

void Customize_UI::Update() {
	Custom_UI();
}

void Customize_UI::Custom_UI() {
	
	if (m_isWindowOpen == false&&delete_window_open == false&& error_window_open == false) {
		//セレクトアローのプログラム
			//右腕
		if (m_selectPosition[0][0] == 1) {
			s_a_position = { -300.0f,95.0f,0.0f };
			if (g_pad[0]->IsTrigger(enButtonUp)) {
				m_selectPosition[0][1] = 1;
				m_selectPosition[0][0] = 0;
			}
			else if (g_pad[0]->IsTrigger(enButtonRight)) {
				m_selectPosition[0][2] = 1;
				m_selectPosition[0][0] = 0;
			}
			else if (g_pad[0]->IsTrigger(enButtonDown) || g_pad[0]->IsTrigger(enButtonLeft)) {
				m_selectPosition[1][0] = 1;
				m_selectPosition[0][0] = 0;
			}
			if (g_pad[0]->IsTrigger(enButtonA)) {
				if (custom_point[0][0] == 0) {
					change_slot_x = 0, change_slot_y = 0;
					m_isWindowOpen = true;
					fast_push_state = 0;
				}
				else {
					error_window_open = true;
					fast_push_state = 0;
				}
			}
		}
		//肩
		else if (m_selectPosition[0][1] == 1) {
			s_a_position = { 270.0f,230.0f,0.0f };
			if (g_pad[0]->IsTrigger(enButtonRight)) {
				m_selectPosition[0][2] = 1;
				m_selectPosition[0][1] = 0;
			}
			else if (g_pad[0]->IsTrigger(enButtonLeft)) {
				m_selectPosition[0][0] = 1;
				m_selectPosition[0][1] = 0;
			}
			else if (g_pad[0]->IsTrigger(enButtonDown)) {
				m_selectPosition[0][2] = 1;
				m_selectPosition[0][1] = 0;
			}
		}
		//左腕
		else if (m_selectPosition[0][2] == 1) {
			s_a_position = { 336.0f,110.0f,0.0f };
			if (g_pad[0]->IsTrigger(enButtonRight)) {
				m_selectPosition[1][1] = 1;
				m_selectPosition[0][2] = 0;
			}
			else if (g_pad[0]->IsTrigger(enButtonLeft)) {
				m_selectPosition[0][0] = 1;
				m_selectPosition[0][2] = 0;
			}
			else if (g_pad[0]->IsTrigger(enButtonDown)) {
				m_selectPosition[1][1] = 1;
				m_selectPosition[0][2] = 0;
			}
			else if (g_pad[0]->IsTrigger(enButtonUp)) {
				m_selectPosition[0][1] = 1;
				m_selectPosition[0][2] = 0;
			}
			if (g_pad[0]->IsTrigger(enButtonA)) {
				if (custom_point[0][2] == 0) {
					change_slot_x = 0, change_slot_y = 2;
					m_isWindowOpen = true;
					fast_push_state = 0;
				}
				else {
					error_window_open = true;
					fast_push_state = 0;
				}
			}
		}
		//右足
		else if (m_selectPosition[1][0] == 1) {
			s_a_position = { -420.0f,-60.0f,0.0f };
			if (g_pad[0]->IsTrigger(enButtonUp)) {
				m_selectPosition[0][0] = 1;
				m_selectPosition[1][0] = 0;
			}
			else if (g_pad[0]->IsTrigger(enButtonRight)) {
				m_selectPosition[1][1] = 1;
				m_selectPosition[1][0] = 0;
			}
		}
		//左足
		else if (m_selectPosition[1][1] == 1) {
			s_a_position = { 480.0f,-56.0f,0.0f };
			if (g_pad[0]->IsTrigger(enButtonUp)) {
				m_selectPosition[0][2] = 1;
				m_selectPosition[1][1] = 0;
			}
			else if (g_pad[0]->IsTrigger(enButtonLeft)) {
				m_selectPosition[1][0] = 1;
				m_selectPosition[1][1] = 0;
			}
		}
		//戻る
		else if (m_selectPosition[1][2] == 1) {
			s_a_position = { 700.0f,-400.0f,0.0f };
			if (g_pad[0]->IsTrigger(enButtonUp) || g_pad[0]->IsTrigger(enButtonLeft)) {
				m_selectPosition[1][1] = 1;
				m_selectPosition[1][2] = 0;
			}
			if (g_pad[0]->IsTrigger(enButtonA)) {
				fast_push_state = 0;
				delete_window_open = true;
			}
		}
		if (g_pad[0]->IsTrigger(enButtonB)) {
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 3; j++) {
					m_selectPosition[i][j] = 0;
				}
			}
			m_selectPosition[1][2] = 1;
		}
	}

	//確認ウィンドウの表示
	if (m_isWindowOpen == true) {
		fast_push_state++;
		if (m_windowSelect == true) {
			if(fast_push_state==1)
			C_UI_window.Init("Assets/sprite/change_window_yes.DDS", 512.0f, 256.0f);
			if (g_pad[0]->IsTrigger(enButtonRight)) {
				fast_push_state = 0;
				m_windowSelect = false;
			}
			if (g_pad[0]->IsTrigger(enButtonA)&&fast_push_state!=1) {
				custom_point[change_slot_x][change_slot_y] = m_customKinds;
				if (change_slot_x == 0) {
					if (change_slot_y == 0) {
						right_arm_weapons = NewGO<Right_arm_weapons>(2, "right_arm_weapons");
						//right_arm_weapons->set_weapons[custom_kinds] = 1;
					}
					else if (change_slot_y==2) {
						left_arm_weapons = NewGO<Left_arm_weapons>(2, "left_arm_weapons");
						//left_arm_weapons->set_weapons[custom_kinds] = 1;
					}
				}
				
				DeleteGO(this);
			}
		}
		else if (m_windowSelect == false) {
			if(fast_push_state==1)
			C_UI_window.Init("Assets/sprite/change_window_no.DDS", 512.0f, 256.0f);
			if (g_pad[0]->IsTrigger(enButtonLeft)) {
				m_windowSelect = true;
				fast_push_state = 0;
			}
			if (g_pad[0]->IsTrigger(enButtonA) && fast_push_state != 1) {
				m_isWindowOpen = false;
			}
			
		}
		C_UI_window.Update();
		
	}


	else if (delete_window_open == true) {
		fast_push_state++;
		if (m_windowSelect == true) {
			if(fast_push_state==1)
			C_UI_window.Init("Assets/sprite/back_window_yes.DDS", 512.0f, 256.0f);
			if (g_pad[0]->IsTrigger(enButtonRight)) {
				m_windowSelect = false;
				fast_push_state = 0;
			}
			if (g_pad[0]->IsTrigger(enButtonA) && fast_push_state != 1) {
				DeleteGO(this);
			}
		}
		else if (m_windowSelect == false) {
			if (fast_push_state == 0)
				C_UI_window.Init("Assets/sprite/back_window_no.DDS", 512.0f, 256.0f);
			if (g_pad[0]->IsTrigger(enButtonLeft)) {
				m_windowSelect = true;
				fast_push_state = 0;
			}
			if (g_pad[0]->IsTrigger(enButtonA) && fast_push_state != 1) {
				delete_window_open = false;
			}
			
		}
		C_UI_window.Update();
		
	}

	else if (error_window_open == true) {
		
		if (g_pad[0]->IsTrigger(enButtonA) && fast_push_state != 0) {
			error_window_open = false;
		}
		if (fast_push_state == 0) {
			C_UI_window.Init("Assets/sprite/error_window.DDS", 512.0f, 256.0f);
			C_UI_window.Update();
		}
		fast_push_state++;
	}

	C_UI_Select_arrow.SetPosition(s_a_position);
	C_UI_Select_arrow.Update();
	
}

void Customize_UI::Render(RenderContext& rc) {
	//一番最初にドロー
	C_UI_Render.Draw(rc);

	slot_1_RA.Draw(rc);
	slot_2_SD.Draw(rc);
	slot_3_LA.Draw(rc);
	slot_4_RL.Draw(rc);
	slot_5_LL.Draw(rc);
	slot_6_CI.Draw(rc);

	//一番最後にドロー
	C_UI_Select_arrow.Draw(rc);
	if (m_isWindowOpen == true || error_window_open == true || delete_window_open == true) {
		C_UI_window.Draw(rc);
	}
}