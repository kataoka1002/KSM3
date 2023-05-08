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


Customize_UI_ver2::Customize_UI_ver2() 
{
	//カスタムエリアの生成
	m_customizeArea = NewGO<Customize_area>(1, "customize_area");
}

Customize_UI_ver2::~Customize_UI_ver2() 
{
	//カメラの位置を元に戻す
	//m_gameCamera->m_toCameraPos.Set(0.0f, 500.0f, -700.0f);
	//DeleteGO(m_dropItem);
	DeleteGO(m_customizeArea);
	//m_player->game_state = 0;
}

bool Customize_UI_ver2::Start()
{
	//各部位のFindGOを行う
	m_player = FindGO<Player>("player");
	m_coreWeapon = FindGO<Core_weapons>("core_weapons");
	m_rightArmWeapon = FindGO<Right_arm_weapons>("right_arm_weapons");
	m_leftArmWeapon = FindGO<Left_arm_weapons>("left_arm_weapons");
	m_shoulderWeapon = FindGO<Shoulder_weapons>("shoulder_weapons");
	m_rightLegWeapon = FindGO<Right_leg_weapons>("right_leg_weapons");
	m_leftLegWeapon = FindGO<Left_leg_weapons>("left_leg_weapons");
	m_gameCamera = FindGO<GameCamera>("gamecamera");
	m_dropItem = FindGO<Drop_item>("drop_item");

	//プレイヤーのステートを変更
	//m_player->game_state = 3;

	//カメラの諸々を設定
	/*m_gameCamera->m_toCameraPos.Set(0.0f, -10.0f, -100.0f);
	m_gameCamera->fast_count = 0;
	m_gameCamera->target = custom_model_body_position;
	m_gameCamera->CameraState = 3;*/

	//武器の取り付け
	//Setup();
	return true;
}

void Customize_UI_ver2::Setup() 
{
	//コア武器とプレイヤー本体のモデルの設定
	Custom_model_Core();
	Custom_model_body();

	//各部位に武器が付いているのならモデルを設定する
	if (m_player->p_custom_point[0][0] != 0) 
	{
		Custom_model_Right_arm();	//右腕
	}
	if (m_player->p_custom_point[0][2] != 0) 
	{
		Custom_model_Left_arm();	//左腕
	}
	if (m_player->p_custom_point[0][1] != 0) 
	{
		Custom_model_Shoulder();	//肩
	}
	if (m_player->p_custom_point[1][0] != 0) 
	{
		Custom_model_Right_leg();	//右足
	}
	if (m_player->p_custom_point[1][2] != 0) 
	{
		Custom_model_Left_leg();	//左足
	}

	//拾った武器の種類を教えてやる
	//custom_kinds = m_dropItem->drop_kinds;
}

void Customize_UI_ver2::Update() 
{
	//プレイヤーのステートが３(カスタム中)だったら処理
	if (m_player->game_state == 3)
	{
		//セレクト系のUI処理
		Custom_UI();

		if (window_open == true)
		{
			Window();
		}
		
		//Bボタンでカスタム終了
		if (g_pad[0]->IsTrigger(enButtonB))
		{
			//DeleteGO(this);
		}

		//最初の1フレームを数えるための物
		fast_count++;
	}
}

void Customize_UI_ver2::Custom_UI()
{
	//Rボタンでカーソルを右に移動
	if (g_pad[0]->IsTrigger(enButtonRB1) && selection_position < 5)
	{
		selection_position++;
		fast_count = 0;
	}
	//Lボタンでカーソルを左に移動
	else if (g_pad[0]->IsTrigger(enButtonLB1) && selection_position >= 1)
	{
		selection_position--;
		fast_count = 0;
	}

	//カーソルの場所によって処理を変える
	switch (selection_position)
	{
	case 0:	//肩
		if (fast_count == 0) //カウントが0のときのみ処理する(1回のみ処理)
		{
			//どこを選択しているのかを教えるスプライト(カーソル)
			m_selectSheet.Init("Assets/sprite/select_sheet_01.DDS", 1166.0f, 175.0f);
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
			//適応確認
			window_open = true;
			confirmatino_window_open = true;
			window_select = true;
			column = 0, line = 1;
		}
		break;
	case 1:	//コア
		if (fast_count == 0)
		{
			//どこを選択しているのかを教えるスプライト(カーソル)
			m_selectSheet.Init("Assets/sprite/select_sheet_02.DDS", 1166.0f, 175.0f);
			m_selectSheet.SetPosition(m_selectSheetPosition);
			m_selectSheet.Update();

			//取り付けている武器によってパラメーターシートを変える
			switch (m_coreWeapon->set_weapons)
			{
			case 1:
				m_parameterSheet.Init("Assets/sprite/Non_attachment_UI_parameter.DDS", 650.0f, 600.0f);
				m_parameterSheet.SetPosition(m_parameterSheetPosition);
				m_parameterSheet.Update();

				break;
			case 2:
				m_parameterSheet.Init("Assets/sprite/Glare_bassinet_UI_parameter.DDS", 650.0f, 600.0f);
				m_parameterSheet.SetPosition(m_parameterSheetPosition);
				m_parameterSheet.Update();

				break;
			default:
				break;
			}
		}
		if (g_pad[0]->IsTrigger(enButtonA) && fast_count != 0)
		{
			//適応確認
		}
		break;
	case 2:	//右腕
		if (fast_count == 0)
		{
			//どこを選択しているのかを教えるスプライト(カーソル)
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
			//適応確認
			window_open = true;
			confirmatino_window_open = true;
			window_select = true;
			column = 0, line = 0;
		}
		break;
	case 3:	//左腕
		if (fast_count == 0)
		{
			//どこを選択しているのかを教えるスプライト(カーソル)
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
			//適応確認
			window_open = true;
			confirmatino_window_open = true;
			window_select = true;
			column = 0, line = 2;
		}
		break;
	case 4:	//右足
		if (fast_count == 0)
		{
			//どこを選択しているのかを教えるスプライト(カーソル)
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
			//適応確認
			window_open = true;
			confirmatino_window_open = true;
			window_select = true;
			column = 1, line = 0;
		}
		break;
	case 5:	//左足
		if (fast_count == 0)
		{
			//どこを選択しているのかを教えるスプライト(カーソル)
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
}

void Customize_UI_ver2::Window()
{
	//武器の設定確認のウィンドウを表示
	if (confirmatino_window_open == true)
	{
		//1回だけ処理する為のカウント
		window_count++;

		//ACCEPT時の処理
		if (window_select == true)
		{
			//1フレーム目にスプライトの初期化
			if (window_count == 1)
			{
				m_confirmationWindow.Init("Assets/sprite/confirmation_window_yes.DDS", 584.375f, 918.0f);
			}

			//右ボタンを押すと拒否するウィンドウに変更される
			if (g_pad[0]->IsTrigger(enButtonRight))
			{
				window_count = 0;
				window_select = false;
			}

			//決定した時の処理
			if (g_pad[0]->IsTrigger(enButtonA) && window_count != 1)
			{
				//プレイヤーの装備配列に武器の種類を教える
				m_player->p_custom_point[column][line] = custom_kinds;

				//自分がカーソルを合わせている場所によって生成する武器を変える
				switch (selection_position)
				{
				case 0:
					m_shoulderWeapon = NewGO<Shoulder_weapons>(2, "shoulder_weapons");
					break;
				case 1:

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

				//カスタム終了
				//DeleteGO(this);
				m_player->game_state = 0;
				//注意書きを消す
				confirmatino_window_open = false;
				//色々初期値に戻す
				selection_position = 0;
				fast_count = 0;
				window_count = 0;
				window_open = false;
				window_select = false;
				//どこの部位を選択しているかのスプライトも初期化しておく
				m_selectSheet.Init("Assets/sprite/select_sheet_01.DDS", 1166.0f, 175.0f);

				//ゲームカメラを元に戻す
				m_gameCamera->m_toCameraPos.Set(0.0f, 500.0f, -700.0f);
			}
		}
		//DECLINE時の処理
		else if (window_select == false)
		{
			//1フレーム目にスプライトの初期化
			if (window_count == 1)
			{
				m_confirmationWindow.Init("Assets/sprite/confirmation_window_no.DDS", 584.375f, 918.0f);
			}

			//左ボタンを押すと承認するウィンドウに変更される
			if (g_pad[0]->IsTrigger(enButtonLeft))
			{
				window_select = true;
				window_count = 0;
			}

			//AかBボタンで注意書きを消す
			if (g_pad[0]->IsTrigger(enButtonA) || g_pad[0]->IsTrigger(enButtonB) && window_count != 1)
			{
				window_open = false;
				confirmatino_window_open = false;
				window_count = 0;
			}
		}
		//注意書きの更新
		m_confirmationWindow.Update();
	}
}

void Customize_UI_ver2::Custom_model_body() 
{
	custom_model_body.Init("Assets/modelData/test_player.tkm");
	custom_model_body.SetPosition(custom_model_body_position);
	custom_model_body_rotation.SetRotationDegY(-135.0f);
	custom_model_body.SetRotation(custom_model_body_rotation);
	custom_model_body.Update();
}

void Customize_UI_ver2::Custom_model_Core() 
{
	//コアウェポンの種類でモデルを変える
	if (m_coreWeapon->set_weapons == 2) 
	{
		custom_model_Core.Init("Assets/modelData/Versatile_Perforator.tkm");
		cw_lp = { 0.0f,70.0f,10.0f };	//ローカルポジション設定
	}

	custom_model_body_rotation.SetRotationDegY(-135.0f);
	Quaternion originRotation = custom_model_body_rotation;
	Vector3 cw_position = custom_model_body_position;
	originRotation.Multiply(cw_lp);
	cw_position += cw_lp;
	Quaternion cw_Rotation = originRotation;

	custom_model_Core.SetRotation(cw_Rotation);
	custom_model_Core.SetPosition(cw_position);
	custom_model_Core.Update();
}

void Customize_UI_ver2::Custom_model_Right_arm() 
{
	right_arm_weapon_set = true;

	//付いている武器によってモデル変更(カスタム画面)
	switch (m_rightArmWeapon->set_weapons)
	{
	case 2:	//マシンガン
		//モデルの初期化
		custom_model_Right_arm.Init("Assets/modelData/machine_gun_drop.tkm");
		custom_model_Right_arm.SetScale(scale2);

		//ローカルポジションの設定
		raw_lp = { 60.0f,100.0f,-10.0f };

		break;
	case 6:	//戦艦砲
		//モデルの初期化
		custom_model_Right_arm.Init("Assets/modelData/battleship_gun_right_arm.tkm");
		custom_model_Right_arm.SetScale(scale2);

		//ローカルポジションの設定
		raw_lp = { 60.0f,70.0f,-10.0f };

		break;
	default:
		break;
	}

	//武器モデルのポジションの計算
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

	//付いている武器によってモデル変更(カスタム画面)
	switch (m_leftArmWeapon->set_weapons)
	{
	case 2:	//マシンガン
		//モデルの初期化
		custom_model_Left_arm.Init("Assets/modelData/machine_gun_drop.tkm");
		custom_model_Left_arm.SetScale(scale2);

		//ローカルポジションの設定
		law_lp = { -60.0f,100.0f,-10.0f };

		break;
	case 6:	//戦艦砲
		//モデルの初期化
		custom_model_Left_arm.Init("Assets/modelData/battleship_gun_left_arm.tkm");
		custom_model_Left_arm.SetScale(scale2);

		//ローカルポジションの設定
		law_lp = { -60.0f,70.0f,-10.0f };

		break;
	default:
		break;
	}

	//武器モデルのポジションの設定
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

	//付いている武器によってモデル変更(カスタム画面)
	switch (m_shoulderWeapon->set_weapons)
	{
	case 2:	//マシンガン
		//モデルの初期化
		custom_model_shoulder.Init("Assets/modelData/machine_gun_drop.tkm");
		custom_model_shoulder.SetScale(scale2);

		//ローカルポジションの設定
		sw_lp = { 0.0f,110.0f,0.0f };

		break;
	case 6:	//戦艦砲
		//モデルの初期化
		custom_model_shoulder.Init("Assets/modelData/battleship_gun_shoulder.tkm");
		custom_model_shoulder.SetScale(scale2);

		//ローカルポジションの設定
		sw_lp = { 0.0f,110.0f,0.0f };

		break;
	default:
		break;
	}

	//武器モデルのポジションの設定
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

	//付いている武器によってモデル変更(カスタム画面)
	switch (m_rightLegWeapon->set_weapons)
	{
	case 2:	//マシンガン
		//モデルの初期化
		custom_model_Right_leg.Init("Assets/modelData/machine_gun_drop.tkm");
		custom_model_Right_leg.SetScale(scale2);

		//ローカルポジションの設定
		rlw_lp = { 90.0f,30.0f,0.0f };

		break;
	case 6:	//戦艦砲
		//モデルの初期化
		custom_model_Right_leg.Init("Assets/modelData/battleship_gun_right_leg01.tkm");
		custom_model_Right_leg.SetScale(scale2);

		//ローカルポジションの設定
		rlw_lp = { 90.0f,30.0f,55.0f };

		break;
	default:
		break;
	}

	//武器モデルのポジションの設定
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

	//付いている武器によってモデル変更(カスタム画面)
	switch (m_leftLegWeapon->set_weapons)
	{
	case 2:	//マシンガン
		//モデルの初期化
		custom_model_Left_leg.Init("Assets/modelData/machine_gun_drop.tkm");
		custom_model_Left_leg.SetScale(scale2);

		//ローカルポジション設定
		llw_lp = { -90.0f,30.0f,0.0f };

		break;
	case 6:	//戦艦砲
		//モデルの初期化
		custom_model_Left_leg.Init("Assets/modelData/battleship_gun_left_leg01.tkm");
		custom_model_Left_leg.SetScale(scale2);
		//ローカルポジション設定
		llw_lp = { -90.0f,30.0f,55.0f };

		break;
	default:
		break;
	}

	//武器モデルのポジションの設定
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
	//プレイヤーのステートが3だったらDrawする
	if (m_player->game_state == 3)
	{
		m_selectSheet.Draw(rc);
		m_parameterSheet.Draw(rc);
		custom_model_Core.Draw(rc);
		custom_model_body.Draw(rc);

		//カスタム画面でのそれぞれの部位の武器モデルがセットされているなら表示
		if (right_arm_weapon_set == true)
		{
			custom_model_Right_arm.Draw(rc);
		}
		if (Left_arm_weapon_set == true)
		{
			custom_model_Left_arm.Draw(rc);
		}
		if (Shoulder_weapon_set == true)
		{
			custom_model_shoulder.Draw(rc);
		}
		if (Right_leg_weapon_set == true)
		{
			custom_model_Right_leg.Draw(rc);
		}
		if (Left_leg_weapon_set == true)
		{
			custom_model_Left_leg.Draw(rc);
		}

		//注意書きの表示
		if (window_open == true)
		{
			if (confirmatino_window_open == true)
			{
				m_confirmationWindow.Draw(rc);
			}
		}
	}
}