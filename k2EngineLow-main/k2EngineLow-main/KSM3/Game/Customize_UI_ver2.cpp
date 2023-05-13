#include "stdafx.h"
#include "Customize_UI_ver2.h"
#include "Player.h"
#include "Left_arm_weapons.h"
#include "Right_arm_weapons.h"
#include "Core_weapons.h"
#include "Shoulder_weapons.h"
#include "Right_leg_weapons.h"
#include "Left_leg_weapons.h"
#include "Drop_item.h"
#include "Customize_area.h"
#include "GameCamera.h"


Customize_UI_ver2::Customize_UI_ver2()
{
	//カスタマイズエリアの生成
	m_customizeArea = NewGO<Customize_area>(1, "customize_area");
}

Customize_UI_ver2::~Customize_UI_ver2()
{
	DeleteGO(m_customizeArea);
	if (m_shoulderWeapon != nullptr)
	{
		DeleteGO(m_shoulderWeapon);
	}
	if (m_rightArmWeapon != nullptr)
	{
		DeleteGO(m_rightArmWeapon);
	}
	if (m_leftArmWeapon != nullptr)
	{
		DeleteGO(m_leftArmWeapon);
	}
	if (m_rightLegWeapon != nullptr)
	{
		DeleteGO(m_rightLegWeapon);
	}
	if (m_leftLegWeapon != nullptr)
	{
		DeleteGO(m_leftLegWeapon);
	}
}

bool Customize_UI_ver2::Start()
{
	//まとめてFindGOする
	m_player = FindGO<Player>("player");
	m_coreWeapon = FindGO<Core_weapons>("core_weapons");
	m_rightArmWeapon = FindGO<Right_arm_weapons>("right_arm_weapons");
	m_leftArmWeapon = FindGO<Left_arm_weapons>("left_arm_weapons");
	m_shoulderWeapon = FindGO<Shoulder_weapons>("shoulder_weapons");
	m_rightLegWeapon = FindGO<Right_leg_weapons>("right_leg_weapons");
	m_leftLegWeapon = FindGO<Left_leg_weapons>("left_leg_weapons");
	m_gameCamera = FindGO<GameCamera>("gamecamera");
	m_dropItem = FindGO<Drop_item>("drop_item");

	//まとめて初期化する
	trance_setup();

	return true;
}

void Customize_UI_ver2::trance_setup()
{
	//変数の初期化
	selection_position = 0;
	window_count = 0;
	window_select = false;
	confirmatino_window_open = false;
	window_open = false;
	m_selectSheet.Init("Assets/sprite/select_sheet_01.DDS", 1166.0f, 175.0f);
	m_selectSheet.SetPosition(m_selectSheetPosition);
	m_selectSheet.Update();

	switch (custom_kinds)
	{
	case 0:	//装備なし
		m_parameterSheet.Init("Assets/sprite/Non_attachment_UI_parameter.DDS", 650.0f, 600.0f);
		m_parameterSheet.SetPosition(m_parameterSheetPosition);
		m_parameterSheet.Update();
		break;
	case 2:	//マシンガン
		m_parameterSheet.Init("Assets/sprite/BattleShip_gun_UI_parameter.DDS", 650.0f, 600.0f);
		m_parameterSheet.SetPosition(m_parameterSheetPosition);
		m_parameterSheet.Update();
		break;
	case 4:	//ギガトンキャノン
		m_parameterSheet.Init("Assets/sprite/BattleShip_gun_UI_parameter.DDS", 650.0f, 600.0f);
		m_parameterSheet.SetPosition(m_parameterSheetPosition);
		m_parameterSheet.Update();
		break;
	case 6:	//戦艦砲
		m_parameterSheet.Init("Assets/sprite/BattleShip_gun_UI_parameter.DDS", 650.0f, 600.0f);
		m_parameterSheet.SetPosition(m_parameterSheetPosition);
		m_parameterSheet.Update();
		break;

	default:
		break;
	}

	fast_count = 0;
	trance_sheet_color = { 0.0f,0.0f,0.0f,1.0f };
	m_selectSheetPosition = { 0.0f,650.0f,0.0f };
	m_parameterSheetPosition = { -1200.0f,38.0f,0.0f };
	custom_model_body_position = { 10500.0f,0.0f,0.0f };
	trance_state = 1;
	trance_sheet01_position = { 2880.0f,-530.0f,0.0f };
	trance_sheet02_position = { 2880.0f,-530.0f,0.0f };
	trance_sheet03_position = { -2880.0f,530.0f,0.0f };
	trance_sheet04_position = { -2880.0f,530.0f,0.0f };

	trance_sheet_count = 0;
	trance_sheet[0].Init("Assets/sprite/trance_01.DDS", 3840.0f, 2160.0f);
	trance_sheet[1].Init("Assets/sprite/trance_01.DDS", 3840.0f, 2160.0f);
	trance_sheet[2].Init("Assets/sprite/trance_02.DDS", 3840.0f, 2160.0f);
	trance_sheet[3].Init("Assets/sprite/trance_02.DDS", 3840.0f, 2160.0f);

	trance_sheet[0].SetPosition(trance_sheet01_position);
	trance_sheet[1].SetPosition(trance_sheet02_position);
	trance_sheet[2].SetPosition(trance_sheet03_position);
	trance_sheet[3].SetPosition(trance_sheet04_position);

	m_selectSheet.SetPosition(m_selectSheetPosition);
	m_parameterSheet.SetPosition(m_parameterSheetPosition);
	custom_model_body.SetPosition(custom_model_body_position);

	m_selectSheet.Update();
	m_parameterSheet.Update();
	custom_model_body.Update();
	for (int i = 0; i < 4; i++) {
		trance_sheet[i].SetMulColor(trance_sheet_color);
		trance_sheet[i].Update();
	}

}

void Customize_UI_ver2::Setup()
{
	Custom_model_Core();
	Custom_model_body();

	if (m_coreWeapon->set_weapons == 2)
	{
		//コア武器モデルの初期化
		custom_model_Core.Init("Assets/modelData/Versatile_Perforator.tkm");
	}

	//取り付けている部位によって処理を変える
	if (m_player->p_custom_point[0][0] != 0)	//右腕
	{
		Custom_model_Right_arm();
		//武器によってモデルを変える
		switch (m_rightArmWeapon->set_weapons)
		{
		case 2:	//マシンガン
			//モデルの初期化
			custom_model_Right_arm.Init("Assets/modelData/machine_gun_drop.tkm");
			//モデルの大きさの設定
			custom_model_Right_arm.SetScale(scale2);
			//ローカルポジションの設定
			raw_lp = { 60.0f,100.0f,-10.0f };

			break;
		case 4:	//ギガトンキャノン
			//モデルの初期化
			custom_model_Right_arm.Init("Assets/modelData/GIgaton_cannon.tkm");
			//モデルの大きさの設定
			custom_model_Right_arm.SetScale(1.0f);
			//ローカルポジションの設定
			raw_lp = { 60.0f,100.0f,-10.0f };

			break;
		case 6:	//戦艦砲
			//モデルの初期化
			custom_model_Right_arm.Init("Assets/modelData/battleship_gun_right_arm.tkm");
			//モデルの大きさの設定
			custom_model_Right_arm.SetScale(scale2);
			//ローカルポジションの設定
			raw_lp = { 60.0f,70.0f,-10.0f };

			break;
		default:
			break;
		}
	}
	if (m_player->p_custom_point[0][2] != 0)	//左腕
	{
		Custom_model_Left_arm();
		//武器によってモデルを変える
		switch (m_leftArmWeapon->set_weapons)
		{
		case 2:	//マシンガン
			//モデルの初期化
			custom_model_Left_arm.Init("Assets/modelData/machine_gun_drop.tkm");
			//モデルの大きさの設定
			custom_model_Left_arm.SetScale(scale2);
			//ローカルポジションの設定
			law_lp = { -60.0f,100.0f,-10.0f };

			break;
		case 4:	//ギガトンキャノン
			//モデルの初期化
			custom_model_Left_arm.Init("Assets/modelData/GIgaton_cannon.tkm");
			//モデルの大きさの設定
			custom_model_Left_arm.SetScale(1.0f);
			//ローカルポジションの設定
			law_lp = { -60.0f,100.0f,-10.0f };

			break;

		case 6:	//戦艦砲
			//モデルの初期化
			custom_model_Left_arm.Init("Assets/modelData/battleship_gun_left_arm.tkm");
			//モデルの大きさの設定
			custom_model_Left_arm.SetScale(scale2);
			//ローカルポジションの設定
			law_lp = { -60.0f,70.0f,-10.0f };


			break;
		default:
			break;
		}
	}
	if (m_player->p_custom_point[0][1] != 0)	//肩
	{
		Custom_model_Shoulder();
		//武器によってモデルを変える
		switch (m_shoulderWeapon->set_weapons)
		{
		case 2:	//マシンガン
			//モデルの初期化
			custom_model_shoulder.Init("Assets/modelData/machine_gun_drop.tkm");
			//モデルの大きさの設定
			custom_model_shoulder.SetScale(scale2);
			//ローカルポジションの設定
			sw_lp = { 0.0f,110.0f,0.0f };


			break;
		case 4:	//ギガトンキャノン
			//モデルの初期化
			custom_model_shoulder.Init("Assets/modelData/GIgaton_cannon.tkm");
			//モデルの大きさの設定
			custom_model_shoulder.SetScale(1.0f);
			//ローカルポジションの設定
			sw_lp = { 0.0f,110.0f,0.0f };


			break;

		case 6:	//戦艦砲
			//モデルの初期化
			custom_model_shoulder.Init("Assets/modelData/battleship_gun_shoulder.tkm");
			//モデルの大きさの設定
			custom_model_shoulder.SetScale(scale2);
			//ローカルポジションの設定
			sw_lp = { 0.0f,110.0f,0.0f };

			break;
		default:
			break;
		}
	}
	if (m_player->p_custom_point[1][0] != 0)	//右足
	{
		Custom_model_Right_leg();
		//武器によってモデルを変える
		switch (m_rightLegWeapon->set_weapons)
		{
		case 2:	//マシンガン
			//モデルの初期化
			custom_model_Right_leg.Init("Assets/modelData/machine_gun_drop.tkm");
			//モデルの大きさの設定
			custom_model_Right_leg.SetScale(scale2);
			//ローカルポジションの設定
			rlw_lp = { 90.0f,30.0f,0.0f };

			break;
		case 4:	//ギガトンキャノン
			//モデルの初期化
			custom_model_Right_leg.Init("Assets/modelData/GIgaton_cannon.tkm");
			//モデルの大きさの設定
			custom_model_Right_leg.SetScale(1.0f);
			//ローカルポジションの設定
			rlw_lp = { 90.0f,30.0f,0.0f };

			break;

		case 6:	//戦艦砲
			//モデルの初期化
			custom_model_Right_leg.Init("Assets/modelData/battleship_gun_right_leg01.tkm");
			//モデルの大きさの設定
			custom_model_Right_leg.SetScale(scale2);
			//ローカルポジションの設定
			rlw_lp = { 90.0f,30.0f,55.0f };


			break;
		default:
			break;
		}
	}
	if (m_player->p_custom_point[1][2] != 0)	//左足
	{
		Custom_model_Left_leg();
		//武器によってモデルを変える
		switch (m_leftLegWeapon->set_weapons)
		{
		case 2:	//マシンガン
			//モデルの初期化
			custom_model_Left_leg.Init("Assets/modelData/machine_gun_drop.tkm");
			//モデルの大きさの設定
			custom_model_Left_leg.SetScale(scale2);
			//ローカルポジションの設定
			llw_lp = { -90.0f,30.0f,0.0f };

			break;
		case 4:	//ギガトンキャノン
			//モデルの初期化
			custom_model_Left_leg.Init("Assets/modelData/GIgaton_cannon.tkm");
			//モデルの大きさの設定
			custom_model_Left_leg.SetScale(scale2);
			//ローカルポジションの設定
			llw_lp = { -90.0f,30.0f,0.0f };

			break;

		case 6:	//戦艦砲
			//モデルの初期化
			custom_model_Left_leg.Init("Assets/modelData/battleship_gun_left_leg01.tkm");
			//モデルの大きさの設定
			custom_model_Left_leg.SetScale(scale2);
			//ローカルポジションの設定
			llw_lp = { -90.0f,30.0f,55.0f };

			break;
		default:
			break;
		}
	}
}


void Customize_UI_ver2::Update()
{
	//カスタマイズ画面の時のみ実行
	if (m_player->game_state == 3)
	{
		//それぞれのモデルがnullじゃないなら,モデルの移動回転を計算している関数を実行
		Custom_model_Core();			//コア
		if (m_rightArmWeapon != nullptr)
		{
			Custom_model_Right_arm();	//右腕
		}
		if (m_leftArmWeapon != nullptr)
		{
			Custom_model_Left_arm();	//左腕
		}
		if (m_shoulderWeapon != nullptr)
		{
			Custom_model_Shoulder();	//肩
		}
		if (m_rightLegWeapon != nullptr)
		{
			Custom_model_Right_leg();	//右足
		}
		if (m_leftLegWeapon != nullptr)
		{
			Custom_model_Left_leg();	//左足
		}


		//遷移中
		if (trance_state == 1) {
			custom_model_body_rotation.AddRotationDegY(50.0f);
			trance();
		}

		//黒フェードアウト中
		if (trance_state == 3) {
			tranceOut();
		}
			
		//遷移終了
		if (trance_state == 0) {
			custom_model_body_rotation.AddRotationDegY(2.0f);
			custom_model_body.SetRotation(custom_model_body_rotation);
			//カスタム画面へ   
			Custom_UI();

			if (window_open == true)
			{
				Window();
			}

			//更新
			fast_count++;
			custom_model_body.Update();
		}
	}
}

void Customize_UI_ver2::Custom_UI()
{
	//Rボタンを押すと右に移動
	if (g_pad[0]->IsTrigger(enButtonRB1) && selection_position < 5)
	{
		selection_position++;
		fast_count = 0;
	}
	//Lボタンを押すと左に移動
	else if (g_pad[0]->IsTrigger(enButtonLB1) && selection_position >= 1)
	{
		selection_position--;
		fast_count = 0;
	}

	//カーソルを合わせている場所によって変える
	switch (selection_position)
	{
	case 0:	//肩
		if (fast_count == 0) //最初のフレームだけ実行
		{
			//どこを選択しているかのスプライト設定
			m_selectSheet.Init("Assets/sprite/select_sheet_01.DDS", 1166.0f, 175.0f);
			m_selectSheet.SetPosition(m_selectSheetPosition);
			m_selectSheet.Update();

			//取り付けている武器によってパラメーターシートを変える
			switch (custom_kinds)
			{
			case 0:
				m_parameterSheet.Init("Assets/sprite/Non_attachment_UI_parameter.DDS", 650.0f, 600.0f);
				m_parameterSheet.SetPosition(m_parameterSheetPosition);
				m_parameterSheet.Update();
				break;
			case 2:
				m_parameterSheet.Init("Assets/sprite/BattleShip_gun_UI_parameter.DDS", 650.0f, 600.0f);
				m_parameterSheet.SetPosition(m_parameterSheetPosition);
				m_parameterSheet.Update();
				break;
			case 4:
				m_parameterSheet.Init("Assets/sprite/Non_attachment_UI_parameter.DDS", 650.0f, 600.0f);
				m_parameterSheet.SetPosition(m_parameterSheetPosition);
				m_parameterSheet.Update();
				break;
			case 6:
				m_parameterSheet.Init("Assets/sprite/BattleShip_gun_UI_parameter.DDS", 650.0f, 600.0f);
				m_parameterSheet.SetPosition(m_parameterSheetPosition);
				m_parameterSheet.Update();
				break;

			default:
				break;
			}
		}
		
		break;
	case 1:	//コア
		if (fast_count == 0)
		{
			//どこを選択しているかのスプライト設定
			m_selectSheet.Init("Assets/sprite/select_sheet_02.DDS", 1166.0f, 175.0f);
			m_selectSheet.SetPosition(m_selectSheetPosition);
			m_selectSheet.Update();

			//取り付けている武器によってパラメーターシートを変える
			switch (m_player->p_custom_point[0][1])
			{
			case 0:
				m_parameterSheet.Init("Assets/sprite/Non_attachment_UI_parameter.DDS", 650.0f, 600.0f);
				m_parameterSheet.SetPosition(m_parameterSheetPosition);
				m_parameterSheet.Update();
				break;
			case 2:
				m_parameterSheet.Init("Assets/sprite/BattleShip_gun_UI_parameter.DDS", 650.0f, 600.0f);
				m_parameterSheet.SetPosition(m_parameterSheetPosition);
				m_parameterSheet.Update();
				break;
			case 4:
				m_parameterSheet.Init("Assets/sprite/Non_attachment_UI_parameter.DDS", 650.0f, 600.0f);
				m_parameterSheet.SetPosition(m_parameterSheetPosition);
				m_parameterSheet.Update();
				break;
			case 6:
				m_parameterSheet.Init("Assets/sprite/BattleShip_gun_UI_parameter.DDS", 650.0f, 600.0f);
				m_parameterSheet.SetPosition(m_parameterSheetPosition);
				m_parameterSheet.Update();
				break;

			default:
				break;
			}
		}
		if (g_pad[0]->IsTrigger(enButtonA) && m_player->p_custom_point[0][1] == 0 && window_count == 0)
		{
			//注意書きウィンドウの表示
			window_open = true;
			confirmatino_window_open = true;
			window_select = true;
			column = 0, line = 1;
		}
		break;
	case 2:	//右腕
		if (fast_count == 0)
		{
			//どこを選択しているかのスプライト設定
			m_selectSheet.Init("Assets/sprite/select_sheet_03.DDS", 1166.0f, 175.0f);
			m_selectSheet.SetPosition(m_selectSheetPosition);
			m_selectSheet.Update();

			//取り付けている武器によってパラメーターシートを変える
			switch (m_player->p_custom_point[0][0])
			{
			case 0:
				m_parameterSheet.Init("Assets/sprite/Non_attachment_UI_parameter.DDS", 650.0f, 600.0f);
				m_parameterSheet.SetPosition(m_parameterSheetPosition);
				m_parameterSheet.Update();
				break;
			case 2:
				m_parameterSheet.Init("Assets/sprite/BattleShip_gun_UI_parameter.DDS", 650.0f, 600.0f);
				m_parameterSheet.SetPosition(m_parameterSheetPosition);
				m_parameterSheet.Update();
				break;
			case 4:
				m_parameterSheet.Init("Assets/sprite/BattleShip_gun_UI_parameter.DDS", 650.0f, 600.0f);
				m_parameterSheet.SetPosition(m_parameterSheetPosition);
				m_parameterSheet.Update();
				break;
			case 6:
				m_parameterSheet.Init("Assets/sprite/BattleShip_gun_UI_parameter.DDS", 650.0f, 600.0f);
				m_parameterSheet.SetPosition(m_parameterSheetPosition);
				m_parameterSheet.Update();

			default:
				break;

			}
		}

		if (g_pad[0]->IsTrigger(enButtonA) && m_player->p_custom_point[0][0] == 0 && window_count == 0)
		{
			//注意書きウィンドウの表示
			window_open = true;
			confirmatino_window_open = true;
			window_select = true;
			column = 0, line = 0;
		}
		break;
	case 3:	//左腕
		if (fast_count == 0)
		{
			//どこを選択しているかのスプライト設定
			m_selectSheet.Init("Assets/sprite/select_sheet_04.DDS", 1166.0f, 175.0f);
			m_selectSheet.SetPosition(m_selectSheetPosition);
			m_selectSheet.Update();

			//取り付けている武器によってパラメーターシートを変える
			switch (m_player->p_custom_point[0][2])
			{
			case 0:
				m_parameterSheet.Init("Assets/sprite/Non_attachment_UI_parameter.DDS", 650.0f, 600.0f);
				m_parameterSheet.SetPosition(m_parameterSheetPosition);
				m_parameterSheet.Update();
				break;
			case 2:
				m_parameterSheet.Init("Assets/sprite/BattleShip_gun_UI_parameter.DDS", 650.0f, 600.0f);
				m_parameterSheet.SetPosition(m_parameterSheetPosition);
				m_parameterSheet.Update();
				break;
			case 4:
				m_parameterSheet.Init("Assets/sprite/Non_attachment_UI_parameter.DDS", 650.0f, 600.0f);
				m_parameterSheet.SetPosition(m_parameterSheetPosition);
				m_parameterSheet.Update();
				break;
			case 6:
				m_parameterSheet.Init("Assets/sprite/BattleShip_gun_UI_parameter.DDS", 650.0f, 600.0f);
				m_parameterSheet.SetPosition(m_parameterSheetPosition);
				m_parameterSheet.Update();
				break;

			default:
				break;
			}
		}

		if (g_pad[0]->IsTrigger(enButtonA) && m_player->p_custom_point[0][2] == 0 && window_count == 0)
		{
			//注意書きウィンドウの表示
			window_open = true;
			confirmatino_window_open = true;
			window_select = true;
			column = 0, line = 2;
		}
		break;
	case 4:	//右足 
		if (fast_count == 0)
		{
			//どこを選択しているかのスプライト設定
			m_selectSheet.Init("Assets/sprite/select_sheet_05.DDS", 1166.0f, 175.0f);
			m_selectSheet.SetPosition(m_selectSheetPosition);
			m_selectSheet.Update();

			//取り付けている武器によってパラメーターシートを変える
			switch (m_player->p_custom_point[1][0])
			{
			case 0:
				m_parameterSheet.Init("Assets/sprite/Non_attachment_UI_parameter.DDS", 650.0f, 600.0f);
				m_parameterSheet.SetPosition(m_parameterSheetPosition);
				m_parameterSheet.Update();
				break;
			case 2:
				m_parameterSheet.Init("Assets/sprite/BattleShip_gun_UI_parameter.DDS", 650.0f, 600.0f);
				m_parameterSheet.SetPosition(m_parameterSheetPosition);
				m_parameterSheet.Update();
				break;
			case 4:
				m_parameterSheet.Init("Assets/sprite/BattleShip_gun_UI_parameter.DDS", 650.0f, 600.0f);
				m_parameterSheet.SetPosition(m_parameterSheetPosition);
				m_parameterSheet.Update();
				break;
			case 6:
				m_parameterSheet.Init("Assets/sprite/BattleShip_gun_UI_parameter.DDS", 650.0f, 600.0f);
				m_parameterSheet.SetPosition(m_parameterSheetPosition);
				m_parameterSheet.Update();
				break;

			default:
				break;

			}
		}

		if (g_pad[0]->IsTrigger(enButtonA) && m_player->p_custom_point[1][0] == 0 && window_count == 0)
		{
			//注意書きウィンドウの表示
			window_open = true;
			confirmatino_window_open = true;
			window_select = true;
			column = 1, line = 0;
		}
		break;
	case 5:	//左足    
		if (fast_count == 0)
		{
			//どこを選択しているかのスプライト設定
			m_selectSheet.Init("Assets/sprite/select_sheet_06.DDS", 1166.0f, 175.0f);
			m_selectSheet.SetPosition(m_selectSheetPosition);
			m_selectSheet.Update();

			//取り付けている武器によってパラメーターシートを変える
			switch (m_player->p_custom_point[1][2])
			{
			case 0:
				m_parameterSheet.Init("Assets/sprite/Non_attachment_UI_parameter.DDS", 650.0f, 600.0f);
				m_parameterSheet.SetPosition(m_parameterSheetPosition);
				m_parameterSheet.Update();
				break;
			case 2:
				m_parameterSheet.Init("Assets/sprite/BattleShip_gun_UI_parameter.DDS", 650.0f, 600.0f);
				m_parameterSheet.SetPosition(m_parameterSheetPosition);
				m_parameterSheet.Update();
				break;
			case 4:
				m_parameterSheet.Init("Assets/sprite/BattleShip_gun_UI_parameter.DDS", 650.0f, 600.0f);
				m_parameterSheet.SetPosition(m_parameterSheetPosition);
				m_parameterSheet.Update();
				break;
			case 6:
				m_parameterSheet.Init("Assets/sprite/BattleShip_gun_UI_parameter.DDS", 650.0f, 600.0f);
				m_parameterSheet.SetPosition(m_parameterSheetPosition);
				m_parameterSheet.Update();
				break;

			default:
				break;
			}
		}

		if (g_pad[0]->IsTrigger(enButtonA) && m_player->p_custom_point[1][2] == 0 && window_count == 0)
		{
			//注意書きウィンドウの表示
			window_open = true;
			confirmatino_window_open = true;
			window_select = true;
			column = 1, line = 2;
		}
	}

	//Bボタンを押してカスタム画面終了
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		tranceOutInit();
	}
	fast_count++;

	if (window_open == true)
	{
		Window();
	}
	custom_model_body.SetRotation(custom_model_body_rotation);
	custom_model_body.Update();
}


void Customize_UI_ver2::trance()
{
	//黒フェード1回目
	if (trance_sheet_count >= 0 && trance_sheet_count <= 24)
	{
		trance_sheet01_position.x -= 160.0f;
		trance_sheet03_position.x += 160.0f;
	}
	//黒フェード2回目
	if (trance_sheet_count >= 20 && trance_sheet_count <= 44)
	{
		trance_sheet02_position.x -= 160.0f;
		trance_sheet04_position.x += 160.0f;
	}

	trance_sheet[1].SetPosition(trance_sheet02_position);
	trance_sheet[3].SetPosition(trance_sheet04_position);
	trance_sheet[0].SetPosition(trance_sheet01_position);
	trance_sheet[2].SetPosition(trance_sheet03_position);

	//黒フェード終了したらカメラ移動
	if (trance_sheet_count == 50)
	{
		m_gameCamera->trance_Finish = true;
		m_gameCamera->m_toCameraPos.Set(0.0f, -10.0f, -100.0f);
		m_gameCamera->fast_count = 0;
		m_gameCamera->target = { 10000.0f,20.0f,0.0f };
		m_gameCamera->CameraState = 3;
		m_gameCamera->m_springCamera.Refresh();
	}

	//黒フェード消滅
	if (trance_sheet_count >= 44 && trance_sheet_count <= 64)
	{
		for (int i = 0; i < 4; i++)
		{
			trance_sheet[i].SetMulColor(trance_sheet_color);
		}
		trance_sheet_color.w -= 0.05f;
	}

	//UI出現
	//上のセレクト部分
	if (trance_sheet_count >= 64 && trance_sheet_count < 71)
	{
		m_selectSheetPosition.y -= 50.0f;
		m_selectSheet.SetPosition(m_selectSheetPosition);
	}
	if (trance_sheet_count >= 71 && trance_sheet_count <= 75)
	{
		m_selectSheetPosition.y += 10.0f;
		m_selectSheet.SetPosition(m_selectSheetPosition);
	}

	//パラメータシート
	if (trance_sheet_count >= 65 && trance_sheet_count < 81)
	{
		m_parameterSheetPosition.x += 50.0f;
		m_parameterSheet.SetPosition(m_parameterSheetPosition);
	}
	if (trance_sheet_count >= 81 && trance_sheet_count < 86)
	{
		m_parameterSheetPosition.x -= 10.0f;
		m_parameterSheet.SetPosition(m_parameterSheetPosition);
	}

	//bodyの出現
	if (trance_sheet_count >= 80 && trance_sheet_count < 89)
	{
		custom_model_body_position.x -= 50.0f;

		custom_model_body.SetPosition(custom_model_body_position);
	}

	//遷移終了
	if (trance_sheet_count == 89)
	{
		trance_state = 0;
	}

	custom_model_body.Update();
	m_parameterSheet.Update();
	m_selectSheet.Update();
	trance_sheet[0].Update();
	trance_sheet[1].Update();
	trance_sheet[2].Update();
	trance_sheet[3].Update();
	trance_sheet_count++;
}

void Customize_UI_ver2::tranceOutInit()
{
	//黒フェードの初期化を行う
	trance_sheet_count = 0;
	trance_state = 3;
	trance_sheet_color = { 0.0f,0.0f,0.0f,1.0f };

	trance_sheet01_position = { 2880.0f,-530.0f,0.0f };
	trance_sheet02_position = { 2880.0f,-530.0f,0.0f };
	trance_sheet03_position = { -2880.0f,530.0f,0.0f };
	trance_sheet04_position = { -2880.0f,530.0f,0.0f };

	trance_sheet[0].SetPosition(trance_sheet01_position);
	trance_sheet[1].SetPosition(trance_sheet02_position);
	trance_sheet[2].SetPosition(trance_sheet03_position);
	trance_sheet[3].SetPosition(trance_sheet04_position);

	for (int i = 0; i < 4; i++) 
	{
		trance_sheet[i].SetMulColor(trance_sheet_color);
		trance_sheet[i].Update();
	}
}

void Customize_UI_ver2::tranceOut()
{
	//黒フェード1回目
	if (trance_sheet_count >= 0 && trance_sheet_count <= 24)
	{
		trance_sheet01_position.x -= 160.0f;
		trance_sheet03_position.x += 160.0f;
	}
	//黒フェード2回目
	if (trance_sheet_count >= 20 && trance_sheet_count <= 44)
	{
		trance_sheet02_position.x -= 160.0f;
		trance_sheet04_position.x += 160.0f;
	}

	trance_sheet[1].SetPosition(trance_sheet02_position);
	trance_sheet[3].SetPosition(trance_sheet04_position);
	trance_sheet[0].SetPosition(trance_sheet01_position);
	trance_sheet[2].SetPosition(trance_sheet03_position);

	//黒フェード終了したらカメラ移動(プレイヤーのステートはカスタム画面のまま)
	if (trance_sheet_count == 50)
	{
		//カメラの初期化
		m_gameCamera->trance_Finish = false;
		m_gameCamera->CameraState = 0;
		m_gameCamera->m_toCameraPos.Set(0.0f, 500.0f, -700.0f);
		m_gameCamera->m_springCamera.Refresh();	//ばねカメラを瞬時に移動させる
	}

	//黒フェード消滅
	if (trance_sheet_count >= 44 && trance_sheet_count <= 64)
	{
		for (int i = 0; i < 4; i++)
		{
			trance_sheet[i].SetMulColor(trance_sheet_color);
		}
		trance_sheet_color.w -= 0.05f;
	}

	//ゲーム画面に戻る
	if (trance_sheet_count >= 64)
	{
		m_player->game_state = 0;
	}

	trance_sheet[0].Update();
	trance_sheet[1].Update();
	trance_sheet[2].Update();
	trance_sheet[3].Update();
	trance_sheet_count++;
}

void Customize_UI_ver2::Window()
{
	//注意書きが表示されているときのみ実行
	if (confirmatino_window_open == true)
	{
		//カウント増加
		window_count++;

		//ACCEPT時の処理
		if (window_select == true)
		{
			//1フレーム目だけ行う
			if (window_count == 1)
			{
				//注意書きのスプライトの初期化(承認ver.)
				m_confirmationWindow.Init("Assets/sprite/confirmation_window_yes.DDS", 584.375f, 918.0f);
			}

			//右ボタンが押されたらDECLINEが選択される
			if (g_pad[0]->IsTrigger(enButtonRight))
			{
				window_count = 0;
				window_select = false;
			}

			//Aボタンが押されたら実行(最初の3フレームは反応しない)
			if (g_pad[0]->IsTrigger(enButtonA) && window_count != 1 && window_count != 2 && window_count != 3)
			{
				//プレイヤーの部位に落ちていた武器の種類を教えてやる
				m_player->p_custom_point[column][line] = custom_kinds;

				//カーソルを合わせている位置によって作り出す武器を変える
				switch (selection_position)
				{
				case 0:
					
					break;
				case 1:
					m_shoulderWeapon = NewGO<Shoulder_weapons>(2, "shoulder_weapons");
					break;
				case 2:
					m_rightArmWeapon = NewGO<Right_arm_weapons>(2, "right_arm_weapons");
					break;
				case 3:
					m_leftArmWeapon = NewGO<Left_arm_weapons>(2, "left_arm_weapons");
					break;
				case 4:
					m_rightLegWeapon = NewGO<Right_leg_weapons>(2, "right_leg_weapons");
					break;
				case 5:
					m_leftLegWeapon = NewGO<Left_leg_weapons>(2, "left_leg_weapons");
				default:
					break;

				}

				//武器取り付けを承認してカスタム画面が終わる時
				tranceOutInit();
			}
		}
		//DECLINE時の処理
		else if (window_select == false)
		{
			//1フレーム目だけ行う
			if (window_count == 1)
			{
				//注意書きのスプライトの初期化(拒否ver.)
				m_confirmationWindow.Init("Assets/sprite/confirmation_window_no.DDS", 584.375f, 918.0f);
			}

			//左ボタンが押されたらACCEPTが選択される
			if (g_pad[0]->IsTrigger(enButtonLeft))
			{
				window_select = true;
				window_count = 0;
			}

			//AまたはBボタンで注意書き表示を切る
			if (g_pad[0]->IsTrigger(enButtonA) || g_pad[0]->IsTrigger(enButtonB) && window_count != 1)
			{
				window_open = false;
				confirmatino_window_open = false;
				window_count = 0;
			}
		}

		//注意書きスプライトの更新
		m_confirmationWindow.Update();
	}
}

void Customize_UI_ver2::Custom_model_body()
{
	//ボディのモデルの初期化
	custom_model_body.Init("Assets/modelData/player.tkm");

	//回転と座標を教えて更新
	custom_model_body.SetPosition(custom_model_body_position);
	custom_model_body.SetRotation(custom_model_body_rotation);
	custom_model_body.Update();
}

void Customize_UI_ver2::Custom_model_Core()
{
	//モデルのローカルポジション設定
	cw_lp = { 0.0f,80.0f,10.0f };

	//移動の処理
	Quaternion originRotation = custom_model_body_rotation;
	Vector3 cw_position = custom_model_body_position;
	originRotation.Multiply(cw_lp);
	cw_position += cw_lp;
	Quaternion cw_Rotation = originRotation;

	//更新
	custom_model_Core.SetRotation(cw_Rotation);
	custom_model_Core.SetPosition(cw_position);
	custom_model_Core.Update();
}

void Customize_UI_ver2::Custom_model_Right_arm()
{
	right_arm_weapon_set = true;

	//付けている武器によってカスタム画面のモデルを変更する
	switch (m_rightArmWeapon->set_weapons)
	{
	case 2:	//マシンガン
		//モデルのサイズを設定	
		custom_model_Right_arm.SetScale(scale2);
		//モデルのローカルポジション設定
		raw_lp = { 60.0f,100.0f,-10.0f };

		break;
	case 4:	//ギガトンキャノン
		//モデルのサイズを設定	
		custom_model_Right_arm.SetScale(1.0f);
		//モデルのローカルポジション設定
		raw_lp = { 60.0f,100.0f,-10.0f };

		break;
	case 6:	//戦艦砲
		//モデルのサイズを設定	
		custom_model_Right_arm.SetScale(scale2);
		//モデルのローカルポジション設定
		raw_lp = { 60.0f,70.0f,-10.0f };

		break;
	default:
		break;
	}

	//移動の処理
	Quaternion originRotation = custom_model_body_rotation;
	Vector3 raw_position = custom_model_body_position;
	originRotation.Multiply(raw_lp);
	raw_position += raw_lp;
	Quaternion raw_Rotation = originRotation;

	//更新
	custom_model_Right_arm.SetRotation(raw_Rotation);
	custom_model_Right_arm.SetPosition(raw_position);
	custom_model_Right_arm.Update();
}

void Customize_UI_ver2::Custom_model_Left_arm()
{
	Left_arm_weapon_set = true;

	//付けている武器によってカスタム画面のモデルを変更する
	switch (m_leftArmWeapon->set_weapons)
	{
	case 2:	//マシンガン
		//モデルのサイズを設定	
		custom_model_Left_arm.SetScale(scale2);
		//モデルのローカルポジション設定
		law_lp = { -60.0f,100.0f,-10.0f };

		break;
	case 4:	//ギガトンキャノン
		//モデルのサイズを設定	
		custom_model_Left_arm.SetScale(1.0f);
		//モデルのローカルポジション設定
		law_lp = { -60.0f,100.0f,-10.0f };

		break;
	case 6:	//戦艦砲
		//モデルのサイズを設定	
		custom_model_Left_arm.SetScale(scale2);
		//モデルのローカルポジション設定
		law_lp = { -60.0f,70.0f,-10.0f };

		break;
	default:
		break;
	}

	//移動の処理
	Quaternion originRotation = custom_model_body_rotation;
	Vector3 law_position = custom_model_body_position;
	originRotation.Multiply(law_lp);
	law_position += law_lp;
	Quaternion law_Rotation = originRotation;

	//更新
	custom_model_Left_arm.SetRotation(law_Rotation);
	custom_model_Left_arm.SetPosition(law_position);
	custom_model_Left_arm.Update();
}

void Customize_UI_ver2::Custom_model_Shoulder()
{
	Shoulder_weapon_set = true;

	//付けている武器によってカスタム画面のモデルを変更する
	switch (m_shoulderWeapon->set_weapons)
	{
	case 2:	//マシンガン
		//モデルのサイズを設定	
		custom_model_shoulder.SetScale(scale2);
		//モデルのローカルポジション設定
		sw_lp = { 0.0f,110.0f,0.0f };

		break;
	case 4:	//ギガトンキャノン
		//モデルのサイズを設定	
		custom_model_shoulder.SetScale(1.0f);
		//モデルのローカルポジション設定
		sw_lp = { 0.0f,110.0f,0.0f };

		break;
	case 6:	//戦艦砲
		//モデルのサイズを設定	
		custom_model_shoulder.SetScale(scale2);
		//モデルのローカルポジション設定
		sw_lp = { 0.0f,110.0f,0.0f };

		break;
	default:
		break;
	}

	//移動の処理
	Quaternion originRotation = custom_model_body_rotation;
	Vector3 sw_position = custom_model_body_position;
	originRotation.Multiply(sw_lp);
	sw_position += sw_lp;
	Quaternion sw_Rotation = originRotation;

	//更新
	custom_model_shoulder.SetRotation(sw_Rotation);
	custom_model_shoulder.SetPosition(sw_position);
	custom_model_shoulder.Update();
}

void Customize_UI_ver2::Custom_model_Right_leg()
{
	Right_leg_weapon_set = true;

	//付けている武器によってカスタム画面のモデルを変更する
	switch (m_rightLegWeapon->set_weapons)
	{
	case 2:	//マシンガン
		//モデルのサイズを設定	
		custom_model_Right_leg.SetScale(scale2);
		//モデルのローカルポジション設定
		rlw_lp = { 90.0f,30.0f,0.0f };

		break;
	case 4:	//ギガトンキャノン
		//モデルのサイズを設定	
		custom_model_Right_leg.SetScale(1.0f);
		//モデルのローカルポジション設定
		rlw_lp = { 90.0f,30.0f,0.0f };

		break;
	case 6:	//戦艦砲
		//モデルのサイズを設定	
		custom_model_Right_leg.SetScale(scale2);
		//モデルのローカルポジション設定
		rlw_lp = { 90.0f,30.0f,55.0f };


		break;
	default:
		break;
	}

	//移動の処理
	Quaternion originRotation = custom_model_body_rotation;
	Vector3 rlw_position = custom_model_body_position;
	originRotation.Multiply(rlw_lp);
	rlw_position += rlw_lp;
	Quaternion rlw_Rotation = originRotation;

	//更新
	custom_model_Right_leg.SetRotation(rlw_Rotation);
	custom_model_Right_leg.SetPosition(rlw_position);
	custom_model_Right_leg.Update();
}

void Customize_UI_ver2::Custom_model_Left_leg()
{
	Left_leg_weapon_set = true;

	//付けている武器によってカスタム画面のモデルを変更する
	switch (m_leftLegWeapon->set_weapons)
	{
	case 2:	//マシンガン
		//モデルのサイズを設定			
		custom_model_Left_leg.SetScale(scale2);
		//モデルのローカルポジション設定
		llw_lp = { -90.0f,30.0f,0.0f };

		break;
	case 4:	//ギガトンキャノン
		//モデルのサイズを設定			
		custom_model_Left_leg.SetScale(1.0f);
		//モデルのローカルポジション設定
		llw_lp = { -90.0f,30.0f,0.0f };

		break;
	case 6:	//戦艦砲
		//モデルのサイズを設定	
		custom_model_Left_leg.SetScale(scale2);
		//モデルのローカルポジション設定
		llw_lp = { -90.0f,30.0f,55.0f };

		break;
	default:
		break;
	}

	//移動の処理
	Quaternion originRotation = custom_model_body_rotation;
	Vector3 llw_position = custom_model_body_position;
	originRotation.Multiply(llw_lp);
	llw_position += llw_lp;
	Quaternion llw_Rotation = originRotation;

	//更新
	custom_model_Left_leg.SetRotation(llw_Rotation);
	custom_model_Left_leg.SetPosition(llw_position);
	custom_model_Left_leg.Update();
}

void Customize_UI_ver2::Render(RenderContext& rc)
{
	//カスタマイズ画面の時のみDrawする
	if (m_player->game_state == 3)
	{
		//各部位に装備されているならDrawする
		custom_model_Core.Draw(rc);				//コア武器はずっと存在するので分岐なし
		custom_model_body.Draw(rc);				//胴体はずっと存在するので分岐なし

		if (right_arm_weapon_set == true)
		{
			custom_model_Right_arm.Draw(rc);	//右腕
		}
		if (Left_arm_weapon_set == true)
		{
			custom_model_Left_arm.Draw(rc);		//左腕
		}
		if (Shoulder_weapon_set == true)
		{
			custom_model_shoulder.Draw(rc);		//肩
		}
		if (Right_leg_weapon_set == true)
		{
			custom_model_Right_leg.Draw(rc);	//右足
		}
		if (Left_leg_weapon_set == true)
		{
			custom_model_Left_leg.Draw(rc);		//左足
		}


		//カメラがカスタム画面ステートの時のみ表示
		if (m_gameCamera->CameraState == 3)
		{
			m_selectSheet.Draw(rc);
			m_parameterSheet.Draw(rc);

			if (window_open == true)
			{
				if (confirmatino_window_open == true)
				{
					m_confirmationWindow.Draw(rc);
				}
			}
		}

		//黒フェード
		trance_sheet[0].Draw(rc);
		trance_sheet[1].Draw(rc);
		trance_sheet[2].Draw(rc);
		trance_sheet[3].Draw(rc);
	}
}