#include "stdafx.h"
#include "Customize_UI.h"
#include"Player.h"
#include "Left_arm_weapons.h"
#include "Drop_item.h"
#include <vector>       // ヘッダファイルインクルード
using namespace std;

Customize_UI::Customize_UI() {
	custom_player = FindGO<Player>("player");
	c_ui_drop_item = FindGO<Drop_item>("drop_item");
	custom_player->game_state = 2;
	window_open = false;

	custom_kinds = c_ui_drop_item->drop_kinds;

	//武器の設定情報の取得
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			 custom_point[i][j]= custom_player->p_custom_point[i][j];
		}
	}
	C_UI_Select_arrow.Init("Assets/sprite/C_UI_select_arrow.DDS", 33.0f, 54.0f);
	C_UI_Render.Init("Assets/sprite/custom_screen.DDS", 1920.0f, 1080.0f);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			if (custom_point[i][j]!=0) {
				switch (custom_point[i][j])
				{
				case 1:

					break;
				default:
					break;
				}
			}
		}
	}
	C_UI_Render.SetScale(scalec);

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
	
	if (window_open == false&&delete_window_open == false) {
		//セレクトアローのプログラム
			//右腕
		if (selection_position[0][0] == 1) {
			s_a_position = { -300.0f,95.0f,0.0f };
			if (g_pad[0]->IsTrigger(enButtonUp)) {
				selection_position[0][1] = 1;
				selection_position[0][0] = 0;
			}
			else if (g_pad[0]->IsTrigger(enButtonRight)) {
				selection_position[0][2] = 1;
				selection_position[0][0] = 0;
			}
			else if (g_pad[0]->IsTrigger(enButtonDown) || g_pad[0]->IsTrigger(enButtonLeft)) {
				selection_position[1][0] = 1;
				selection_position[0][0] = 0;
			}
		}
		//肩
		else if (selection_position[0][1] == 1) {
			s_a_position = { 270.0f,230.0f,0.0f };
			if (g_pad[0]->IsTrigger(enButtonRight)) {
				selection_position[0][2] = 1;
				selection_position[0][1] = 0;
			}
			else if (g_pad[0]->IsTrigger(enButtonLeft)) {
				selection_position[0][0] = 1;
				selection_position[0][1] = 0;
			}
			else if (g_pad[0]->IsTrigger(enButtonDown)) {
				selection_position[0][2] = 1;
				selection_position[0][1] = 0;
			}
		}
		//左腕
		else if (selection_position[0][2] == 1) {
			s_a_position = { 336.0f,110.0f,0.0f };
			if (g_pad[0]->IsTrigger(enButtonRight)) {
				selection_position[1][1] = 1;
				selection_position[0][2] = 0;
			}
			else if (g_pad[0]->IsTrigger(enButtonLeft)) {
				selection_position[0][0] = 1;
				selection_position[0][2] = 0;
			}
			else if (g_pad[0]->IsTrigger(enButtonDown)) {
				selection_position[1][1] = 1;
				selection_position[0][2] = 0;
			}
			else if (g_pad[0]->IsTrigger(enButtonUp)) {
				selection_position[0][1] = 1;
				selection_position[0][2] = 0;
			}
			if (g_pad[0]->IsTrigger(enButtonA)) {
				window_open = true;
				fast_push_state = 0;
			}
		}
		//右足
		else if (selection_position[1][0] == 1) {
			s_a_position = { -420.0f,-60.0f,0.0f };
			if (g_pad[0]->IsTrigger(enButtonUp)) {
				selection_position[0][0] = 1;
				selection_position[1][0] = 0;
			}
			else if (g_pad[0]->IsTrigger(enButtonRight)) {
				selection_position[1][1] = 1;
				selection_position[1][0] = 0;
			}
		}
		//左足
		else if (selection_position[1][1] == 1) {
			s_a_position = { 480.0f,-56.0f,0.0f };
			if (g_pad[0]->IsTrigger(enButtonUp)) {
				selection_position[0][2] = 1;
				selection_position[1][1] = 0;
			}
			else if (g_pad[0]->IsTrigger(enButtonLeft)) {
				selection_position[1][0] = 1;
				selection_position[1][1] = 0;
			}
		}
		//戻る
		else if (selection_position[1][2] == 1) {
			s_a_position = { 700.0f,-400.0f,0.0f };
			if (g_pad[0]->IsTrigger(enButtonUp) || g_pad[0]->IsTrigger(enButtonLeft)) {
				selection_position[1][1] = 1;
				selection_position[1][2] = 0;
			}
			if (g_pad[0]->IsTrigger(enButtonA)) {
				delete_window_open = true;
			}
		}
		if (g_pad[0]->IsTrigger(enButtonB)) {
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 3; j++) {
					selection_position[i][j] = 0;
				}
			}
			selection_position[1][2] = 1;
		}
	}

	//確認ウィンドウの表示
	if (window_open == true) {

		if (window_select == true) {
			C_UI_window.Init("Assets/sprite/change_window_yes.DDS", 512.0f, 256.0f);
			if (g_pad[0]->IsTrigger(enButtonRight)) {
				window_select = false;
			}
			if (g_pad[0]->IsTrigger(enButtonA)&&fast_push_state!=0) {
				custom_point[0][2] = custom_kinds;
				left_arm_weapons = NewGO<Left_arm_weapons>(1, "left_arm_weapons");
				left_arm_weapons->drop_weapons[custom_kinds] = 1;
				DeleteGO(this);
			}
		}
		else if (window_select == false) {
			if (g_pad[0]->IsTrigger(enButtonLeft)) {
				window_select = true;
			}
			if (g_pad[0]->IsTrigger(enButtonA) && fast_push_state != 0) {
				window_open = false;
			}
			C_UI_window.Init("Assets/sprite/change_window_no.DDS", 512.0f, 256.0f);
		}
		C_UI_window.Update();
		fast_push_state++;
	}


	else if (delete_window_open == true) {

		if (window_select == true) {
			C_UI_window.Init("Assets/sprite/back_window_yes.DDS", 512.0f, 256.0f);
			if (g_pad[0]->IsTrigger(enButtonRight)) {
				window_select = false;
			}
			if (g_pad[0]->IsTrigger(enButtonA) && fast_push_state != 0) {
				DeleteGO(this);
			}
		}
		else if (window_select == false) {
			if (g_pad[0]->IsTrigger(enButtonLeft)) {
				window_select = true;
			}
			if (g_pad[0]->IsTrigger(enButtonA) && fast_push_state != 0) {
				window_open = false;
			}
			C_UI_window.Init("Assets/sprite/back_window_no.DDS", 512.0f, 256.0f);
		}
		C_UI_window.Update();
		fast_push_state++;
	}

	C_UI_Select_arrow.SetPosition(s_a_position);
	C_UI_Select_arrow.Update();
	
}

void Customize_UI::Render(RenderContext& rc) {
	//一番最初にドロー
	C_UI_Render.Draw(rc);



	//一番最後にドロー
	C_UI_Select_arrow.Draw(rc);
	if (window_open == true|| delete_window_open == true) {
		C_UI_window.Draw(rc);
	}
}