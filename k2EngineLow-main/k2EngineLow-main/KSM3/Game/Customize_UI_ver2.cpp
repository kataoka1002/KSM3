#include "stdafx.h"
#include <map>
#include "Customize_UI_ver2.h"
#include "Player.h"
#include "Left_arm_weapons.h"
#include "Right_arm_weapons.h"
#include "Core_weapons.h"
#include "Shoulder_weapons.h"
#include "Right_leg_weapons.h"
#include "Left_leg_weapons.h"
#include "Drop_item.h"
#include "GameCamera.h"
#include "Game.h"
#include "Player_custom_Macro.h"


namespace 
{
	//装備なしあり
	const int NO_EQUIPMENT = 0;
	const int WITH_EQUIPMENT = 1;

	//ヒロイモノにカーソルが当てられている
	const int PARAMETER_SHEET_FIND = 0;

	//各部位にカーソルが当てられている
	const int PARAMETER_SHEET_SHOULDER = 1;
	const int PARAMETER_SHEET_RIGHT_ARM = 2;
	const int PARAMETER_SHEET_LEFT_ARM = 3;
	const int PARAMETER_SHEET_RIGHT_LEG = 4;
	const int PARAMETER_SHEET_LEFT_LEG = 5;

	//武器の大きさ
	const float MCHINEGUN_SCALE = 2.0f;
	const float GIGATONCANNON_SCALE = 0.8f;
	const float BATTLESHIPGUN_SCALE = 2.0f;

	const bool ACCEPT = true;
	const bool REJECT = false;

	//フェードのステート
	const int NOT_FADE = 0;
	const int FADE_IN = 1;
	const int FADE_OUT = 2;

	//トランスシートの数
	const int TRANCE_SHEET_AMOUNT = 4;
	
	//トランスシートのポジションの初期値
	const Vector3 TRANCE_SHEET_POSITION_01 = { 2880.0f, -530.0f, 0.0f };
	const Vector3 TRANCE_SHEET_POSITION_02 = { 2880.0f, -530.0f, 0.0f };
	const Vector3 TRANCE_SHEET_POSITION_03 = { -2880.0f, 530.0f, 0.0f };
	const Vector3 TRANCE_SHEET_POSITION_04 = { -2880.0f, 530.0f, 0.0f };

	//トランスシートのカラーの初期値
	const Vector4 TRANCE_SHEET_COLOR = { 0.0f, 0.0f, 0.0f, 1.0f };

	//カスタムモデルのポジションの初期値
	const Vector3 CUSTOM_MODEL_POSITION = { 10590.0f, 0.0f, 0.0f };

	//パラメーターシートのポジションの初期値
	const Vector3 PARAMETER_SHEET_POSITION = { -1200.0f, 38.0f, 0.0f };

	//セレクトシートのポジションの初期値
	const Vector3 SELECT_SHEET_POSITION = { 0.0f, 650.0f, 0.0f };
}


Customize_UI_ver2::Customize_UI_ver2()
{
	
}

Customize_UI_ver2::~Customize_UI_ver2()
{
	//各部位に武器を取り付けていたら削除
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
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");
	m_coreWeapon = FindGO<Core_weapons>("core_weapons");	//コア武器はGame.cppでNewGOしている
	m_gameCamera = FindGO<GameCamera>("gamecamera");


	//メモリの確保
	m_bodyModel = std::make_unique<ModelRender>();
	m_coreModel = std::make_unique<ModelRender>();
	m_shoulderModel = std::make_unique<ModelRender>();
	m_shoulderModel2 = std::make_unique<ModelRender>();//肩のマシンガン用のモデル
	m_rightArmModel = std::make_unique<ModelRender>();
	m_rightLegModel = std::make_unique<ModelRender>();
	m_leftArmModel = std::make_unique<ModelRender>();
	m_leftLegModel = std::make_unique<ModelRender>();


	//マシンガンモデルの初期化
	m_shoulderModel2->Init("Assets/modelData/machine_gun_drop.tkm");


	//ボディのモデルの初期化
	m_bodyModel->Init(getPlayer_custom_color(m_player->GetRandomColor()));


	//トランスシートの初期化
	InitTranceSheet();


	//まとめて初期化する
	TranceSetUp();


	return true;
}

void Customize_UI_ver2::InitTranceSheet()
{

	m_tranceSheet[0].Init("Assets/sprite/trance_01.DDS", 3840.0f, 2160.0f);
	m_tranceSheet[1].Init("Assets/sprite/trance_01.DDS", 3840.0f, 2160.0f);
	m_tranceSheet[2].Init("Assets/sprite/trance_02.DDS", 3840.0f, 2160.0f);
	m_tranceSheet[3].Init("Assets/sprite/trance_02.DDS", 3840.0f, 2160.0f);

}

void Customize_UI_ver2::TranceSetUp()
{

	//カーソルをヒロイモノに当てる
	m_selectPosition = PARAMETER_SHEET_FIND;


	//注意書きの非表示
	m_isConformatinoWindowOpen = false;


	//ヒロイモノでセレクトシートを初期化
	m_selectSheet.Init("Assets/sprite/select_sheet_01.DDS", 1166.0f, 175.0f);


	//セレクトシートのポジションの初期化
	m_selectSheetPosition = SELECT_SHEET_POSITION;
	m_selectSheet.SetPosition(m_selectSheetPosition);
	m_selectSheet.Update();


	//パラメーターシートを初期化
	InitParameter(NON, PARAMETER_SHEET_FIND);
	
	//トランスシートの初期化
	InitTrance();


	//パラメーターシートのポジションを初期化
	m_parameterSheetPosition = PARAMETER_SHEET_POSITION;
	m_parameterSheet.SetPosition(m_parameterSheetPosition);
	m_parameterSheet.Update();


	//カスタムモデルのポジションを初期化
	m_customModelPosition = CUSTOM_MODEL_POSITION;
	m_bodyModel->SetPosition(m_customModelPosition);
	m_bodyModel->Update();


	//ステートをフェードIN中にする
	m_tranceState = FADE_IN;


	//どこにカスタムするかはまだ選択されてない
	m_customParts = NON;


	//回復はできない
	m_isRecovery = false;

}

void Customize_UI_ver2::InitTrance()
{

	//カウントの初期化
	m_tranceSheetCount = 0;


	//ポジションの初期化
	m_tranceSheetPosition01 = TRANCE_SHEET_POSITION_01;
	m_tranceSheetPosition02 = TRANCE_SHEET_POSITION_02;
	m_tranceSheetPosition03 = TRANCE_SHEET_POSITION_03;
	m_tranceSheetPosition04 = TRANCE_SHEET_POSITION_04;

	m_tranceSheet[0].SetPosition(m_tranceSheetPosition01);
	m_tranceSheet[1].SetPosition(m_tranceSheetPosition02);
	m_tranceSheet[2].SetPosition(m_tranceSheetPosition03);
	m_tranceSheet[3].SetPosition(m_tranceSheetPosition04);


	//カラーの初期化
	m_tranceSheetColor = TRANCE_SHEET_COLOR;


	//更新
	for (int i = 0; i < TRANCE_SHEET_AMOUNT; i++)
	{
		m_tranceSheet[i].SetMulColor(m_tranceSheetColor);
		m_tranceSheet[i].Update();
	}

}

void Customize_UI_ver2::SetUp()
{

	if (m_coreWeapon->GetSetWeapon() == 2)
	{
		//コア武器モデルの初期化
		m_coreModel->Init("Assets/modelData/Versatile_Perforator.tkm");
	}


	//取り付けている部位によって処理を変える
	if (m_player->GetCustomPoint(RIGHT_ARM) != NO_EQUIPMENT)	//右腕
	{
		//武器によってモデルを変える
		switch (m_rightArmWeapon->GetWeaponKind())
		{
		case MACHINEGUN_NUM:	//マシンガン
			
			m_rightArmModel->Init("Assets/modelData/machine_gun_drop.tkm");

			break;
		case GIGATONCANNON_NUM:	//ギガトンキャノン
			
			m_rightArmModel->Init("Assets/modelData/GIgaton_cannon_Right_arm.tkm");

			break;
		case BATTLESHIPGUN_NUM:	//戦艦砲
			
			m_rightArmModel->Init("Assets/modelData/battleship_gun_right_arm.tkm");

			break;
		default:
			break;
		}
	}
	if (m_player->GetCustomPoint(LEFT_ARM) != NO_EQUIPMENT)	//左腕
	{
		//武器によってモデルを変える
		switch (m_leftArmWeapon->GetWeaponKind())
		{
		case MACHINEGUN_NUM:	//マシンガン
			
			m_leftArmModel->Init("Assets/modelData/machine_gun_drop.tkm");

			break;
		case GIGATONCANNON_NUM:	//ギガトンキャノン
			
			m_leftArmModel->Init("Assets/modelData/GIgaton_cannon_Left_arm.tkm");

			break;
		case BATTLESHIPGUN_NUM:	//戦艦砲
			
			m_leftArmModel->Init("Assets/modelData/battleship_gun_left_arm.tkm");

			break;
		default:
			break;
		}
	}
	if (m_player->GetCustomPoint(SHOULDER) != NO_EQUIPMENT)	//肩
	{
		//武器によってモデルを変える
		switch (m_shoulderWeapon->GetWeaponKind())
		{
		case MACHINEGUN_NUM:	//マシンガン
			
			m_shoulderModel->Init("Assets/modelData/machine_gun_drop.tkm");

			break;
		case GIGATONCANNON_NUM:	//ギガトンキャノン
			
			m_shoulderModel->Init("Assets/modelData/GIgaton_shoulder.tkm");

			break;
		case BATTLESHIPGUN_NUM:	//戦艦砲
			
			m_shoulderModel->Init("Assets/modelData/battleship_gun_shoulder.tkm");

			break;
		default:
			break;
		}
	}
	if (m_player->GetCustomPoint(RIGHT_LEG) != NO_EQUIPMENT)	//右足
	{
		//武器によってモデルを変える
		switch (m_rightLegWeapon->GetWeaponKind())
		{
		case MACHINEGUN_NUM:	//マシンガン
			
			m_rightLegModel->Init("Assets/modelData/machine_gun_drop.tkm");

			break;
		case GIGATONCANNON_NUM:	//ギガトンキャノン
			
			m_rightLegModel->Init("Assets/modelData/GIgaton_cannon.tkm");

			break;
		case BATTLESHIPGUN_NUM:	//戦艦砲
			
			m_rightLegModel->Init("Assets/modelData/battleship_gun_Drop.tkm");

			break;
		default:
			break;
		}
	}
	if (m_player->GetCustomPoint(LEFT_LEG) != NO_EQUIPMENT)	//左足
	{
		//武器によってモデルを変える
		switch (m_leftLegWeapon->GetWeaponKind())
		{
		case MACHINEGUN_NUM:	//マシンガン
			
			m_leftLegModel->Init("Assets/modelData/machine_gun_drop.tkm");

			break;
		case GIGATONCANNON_NUM:	//ギガトンキャノン
			
			m_leftLegModel->Init("Assets/modelData/GIgaton_cannon.tkm");

			break;
		case BATTLESHIPGUN_NUM:	//戦艦砲
			
			m_leftLegModel->Init("Assets/modelData/battleship_gun_Drop.tkm");

			break;
		default:
			break;
		}
	}
}

void Customize_UI_ver2::Update()
{

	//カスタマイズ画面の時のみ実行
	if (m_player->GetGameState() != CUSTOMIZE_NUM)
	{
		return;
	}


	//モデル全ての処理
	ExecuteModel();


	//遷移じゃないとき
	if (m_tranceState == NOT_FADE)
	{

		//メインのカスタム画面の処理
		ExecuteCustom();


		//注意書き表示中の処理
		ExecuteConformatinoWindow();


		//Bボタンを押してカスタム画面終了(注意書きが表示されているときは無効)
		if (g_pad[0]->IsTrigger(enButtonB) && m_isConformatinoWindowOpen == false)
		{
			InitTranceOut();
		}


	}
	//遷移中(IN)
	else if (m_tranceState == FADE_IN)
	{
		TranceIn();
	}
	//遷移中(OUT)
	else if (m_tranceState == FADE_OUT)
	{
		TranceOut();
	}

}

void Customize_UI_ver2::ExecuteModel()
{

	//本体
	ExecuteBody();


	//コア
	ExecuteCore();


	//各部位のモデルがnullじゃないなら,モデルの移動回転を計算している関数を実行
	if (m_rightArmWeapon != nullptr)
	{
		//右腕
		ExecuteBodyParts(m_rightArmWeapon, m_rightArmSet, m_rightArmModel, RIGHT_ARM_NUM);
	}
	if (m_leftArmWeapon != nullptr)
	{
		//左腕
		ExecuteBodyParts(m_leftArmWeapon, m_leftArmSet, m_leftArmModel, LEFT_ARM_NUM);
	}
	if (m_shoulderWeapon != nullptr)
	{
		//肩
		ExecuteBodyParts(m_shoulderWeapon, m_shoulderSet, m_shoulderModel, SHOULDER_NUM);
		ExecuteBodyParts(m_shoulderWeapon, m_shoulderSet, m_shoulderModel2, SHOULDER_NUM, true);
	}
	if (m_rightLegWeapon != nullptr)
	{
		//右足
		ExecuteBodyParts(m_rightLegWeapon, m_rightLegSet, m_rightLegModel, RIGHT_LEG_NUM);
	}
	if (m_leftLegWeapon != nullptr)
	{
		//左足
		ExecuteBodyParts(m_leftLegWeapon, m_leftLegSet, m_leftLegModel, LEFT_LEG_NUM);
	}

}

void Customize_UI_ver2::ExecuteCustom()
{

	//注意書きが表示されてないときのみ実行
	if (m_isConformatinoWindowOpen == true)
	{
		return;
	}


	//Rボタンを押すと
	if (g_pad[0]->IsTrigger(enButtonRB1) && m_selectPosition < PARAMETER_SHEET_LEFT_LEG)
	{
		//右に移動
		m_selectPosition++;


		//シートの処理
		InitSelectSheet(m_selectPosition);


		//効果音再生
		PlaySE(enSentakuIdouSE, 2.0f);
	}
	//Lボタンを押すと
	else if (g_pad[0]->IsTrigger(enButtonLB1) && m_selectPosition > PARAMETER_SHEET_FIND)
	{
		//左に移動
		m_selectPosition--;


		//シートの処理
		InitSelectSheet(m_selectPosition);


		//効果音再生
		PlaySE(enSentakuIdouSE, 2.0f);
	}


	//Aボタンを押したら
	if (g_pad[0]->IsTrigger(enButtonA))
	{

		//カスタム画面でAボタンを押したときの処理
		ExecuteAButtonActionOnCustom();

	}

}

void Customize_UI_ver2::ExecuteAButtonActionOnCustom()
{

	//注意書きは表示されない方で初期化
	m_canGoToConformation = false;


	//カーソルを合わせている場所によって変える
	switch (m_selectPosition)
	{
	case PARAMETER_SHEET_FIND:	//拾い物

		//回復可能にする
		m_isRecovery = true;

		//注意書きを表示
		m_canGoToConformation = true;

		break;

	case PARAMETER_SHEET_SHOULDER:	//肩

		//装備のチェックを行う
		CheckEquipment(SHOULDER);

		break;

	case PARAMETER_SHEET_RIGHT_ARM:	//右腕

		//装備のチェックを行う
		CheckEquipment(RIGHT_ARM);

		break;

	case PARAMETER_SHEET_LEFT_ARM:	//左腕

		//装備のチェックを行う
		CheckEquipment(LEFT_ARM);

		break;

	case PARAMETER_SHEET_RIGHT_LEG:	//右足 

		//装備のチェックを行う
		CheckEquipment(RIGHT_LEG);

		break;

	case PARAMETER_SHEET_LEFT_LEG:	//左足    

		//装備のチェックを行う
		CheckEquipment(LEFT_LEG);

		break;

	default:
		break;
	}


	//注意書き表示に行けるなら
	if (m_canGoToConformation == true)
	{

		//注意書きウィンドウの表示
		m_isConformatinoWindowOpen = true;


		//ACCEPTの状態で表示する
		m_selectedWindow = ACCEPT;
		InitConfirmationWindow(ACCEPT);


		//決定音再生
		PlaySE(enKetteiSE, 2.0f);

	}


	//Aボタンを押したフラグを下ろす
	g_pad[0]->SetTriggerFlagFalse(enButtonA);

}

void Customize_UI_ver2::CheckEquipment(IntPair parts)
{

	//装備が空かどうか確認
	if (m_player->GetCustomPoint(parts) == NO_EQUIPMENT)
	{

		//どこに装備するかを教える
		m_customParts = parts;


		//注意書きを表示
		m_canGoToConformation = true;

	}

}

void Customize_UI_ver2::InitSelectSheet(int selectPosition)
{
	//カーソルを合わせている場所によって変える
	switch (m_selectPosition)
	{
	case PARAMETER_SHEET_FIND:	//拾い物

		//初期化
		m_selectSheet.Init("Assets/sprite/select_sheet_01.DDS", 1166.0f, 175.0f);

		//パラメーターシートの変更処理
		InitParameter(NON, PARAMETER_SHEET_FIND);

		break;
	case PARAMETER_SHEET_SHOULDER:	//肩

		//初期化
		m_selectSheet.Init("Assets/sprite/select_sheet_02.DDS", 1166.0f, 175.0f);

		//パラメーターシートの変更処理
		InitParameter(SHOULDER, PARAMETER_SHEET_SHOULDER);

		break;
	case PARAMETER_SHEET_RIGHT_ARM:	//右腕

		//初期化
		m_selectSheet.Init("Assets/sprite/select_sheet_03.DDS", 1166.0f, 175.0f);

		//パラメーターシートの変更処理
		InitParameter(RIGHT_ARM, PARAMETER_SHEET_RIGHT_ARM);

		break;
	case PARAMETER_SHEET_LEFT_ARM:	//左腕

		//初期化
		m_selectSheet.Init("Assets/sprite/select_sheet_04.DDS", 1166.0f, 175.0f);

		//パラメーターシートの変更処理
		InitParameter(LEFT_ARM, PARAMETER_SHEET_LEFT_ARM);

		break;
	case PARAMETER_SHEET_RIGHT_LEG:	//右足 

		//初期化
		m_selectSheet.Init("Assets/sprite/select_sheet_05.DDS", 1166.0f, 175.0f);

		//パラメーターシートの変更処理
		InitParameter(RIGHT_LEG, PARAMETER_SHEET_RIGHT_LEG);

		break;
	case PARAMETER_SHEET_LEFT_LEG:	//左足    

		//初期化
		m_selectSheet.Init("Assets/sprite/select_sheet_06.DDS", 1166.0f, 175.0f);

		//パラメーターシートの変更処理
		InitParameter(LEFT_LEG, PARAMETER_SHEET_LEFT_LEG);

	}


	//更新
	m_selectSheet.SetPosition(m_selectSheetPosition);
	m_selectSheet.Update();

}

void Customize_UI_ver2::InitParameter(IntPair point, int cursor)
{

	//武器の種類
	int weaponNum;


	//カーソルの位置が「ヒロイモノ」の場合
	if (cursor == PARAMETER_SHEET_FIND)
	{

		//拾った武器の種類を保存
		weaponNum = m_customKinds;

	}
	//各部位の場合
	else
	{

		//プレイヤーが今付けている武器の種類を保存
		weaponNum = m_player->GetCustomPoint(point);

	}


	switch (weaponNum)
	{
	case NO_WEAPON_NUM:		//装備なし

		m_parameterSheet.Init("Assets/sprite/Non_attachment_UI_parameter.DDS", 650.0f, 600.0f);
		break;

	case MACHINEGUN_NUM:	//マシンガン

		m_parameterSheet.Init("Assets/sprite/machine_gun_UI_parameter.DDS", 650.0f, 600.0f);
		break;

	case GIGATONCANNON_NUM:	//ギガトンキャノン

		m_parameterSheet.Init("Assets/sprite/GigaTon_cannon_UI_parameter.DDS", 650.0f, 600.0f);
		break;

	case BATTLESHIPGUN_NUM:	//戦艦砲

		m_parameterSheet.Init("Assets/sprite/BattleShip_gun_UI_parameter.DDS", 650.0f, 600.0f);
		break;

	default:
		break;
	}


	//パラメーターシートの更新
	m_parameterSheet.SetPosition(m_parameterSheetPosition);
	m_parameterSheet.Update();

}


void Customize_UI_ver2::ExecuteConformatinoWindow()
{

	//注意書きが表示されているときのみ実行
	if (m_isConformatinoWindowOpen != true)
	{
		return;
	}


	//ACCEPT時の処理
	if (m_selectedWindow == ACCEPT)
	{

		ExecuteAccept();
		
	}
	//REJECT時の処理
	else if (m_selectedWindow == REJECT)
	{

		ExecuteReject();

	}

}

void Customize_UI_ver2::ExecuteAccept()
{

	//右ボタンが押されたら
	if (g_pad[0]->IsTrigger(enButtonRight) || g_pad[0]->IsTrigger(enButtonRB1))
	{

		//REJECTが選択される
		m_selectedWindow = REJECT;


		//拒否ウィンドウへ
		InitConfirmationWindow(REJECT);

	}


	//Aボタンが押されたら
	if (g_pad[0]->IsTrigger(enButtonA))
	{

		//カーソルを合わせている位置によって作り出す武器を変える
		switch (m_selectPosition)
		{
		case PARAMETER_SHEET_FIND:

			//体力回復
			m_player->HealingHP(300.0f);
			break;

		case PARAMETER_SHEET_SHOULDER:

			//武器を装備してないなら
			if (m_shoulderWeapon == nullptr)
			{
				//武器の生成
				m_shoulderWeapon = NewGO<Shoulder_weapons>(2, "shoulder_weapons");

				//部位に武器の種類を教える
				m_shoulderWeapon->SetWeaponKind(m_customKinds);
			}
			break;

		case PARAMETER_SHEET_RIGHT_ARM:

			//武器を装備してないなら
			if (m_rightArmWeapon == nullptr)
			{
				//武器の生成
				m_rightArmWeapon = NewGO<Right_arm_weapons>(2, "right_arm_weapons");

				//部位に武器の種類を教える
				m_rightArmWeapon->SetWeaponKind(m_customKinds);
			}
			break;

		case PARAMETER_SHEET_LEFT_ARM:

			//武器を装備してないなら
			if (m_leftArmWeapon == nullptr)
			{
				//武器の生成
				m_leftArmWeapon = NewGO<Left_arm_weapons>(2, "left_arm_weapons");

				//部位に武器の種類を教える
				m_leftArmWeapon->SetWeaponKind(m_customKinds);
			}
			break;

		case PARAMETER_SHEET_RIGHT_LEG:

			//武器を装備してないなら
			if (m_rightLegWeapon == nullptr)
			{
				//武器の生成
				m_rightLegWeapon = NewGO<Right_leg_weapons>(2, "right_leg_weapons");

				//部位に武器の種類を教える
				m_rightLegWeapon->SetWeaponKind(m_customKinds);
			}
			break;

		case PARAMETER_SHEET_LEFT_LEG:

			//武器を装備してないなら
			if (m_leftLegWeapon == nullptr)
			{
				//武器の生成
				m_leftLegWeapon = NewGO<Left_leg_weapons>(2, "left_leg_weapons");

				//部位に武器の種類を教える
				m_leftLegWeapon->SetWeaponKind(m_customKinds);
			}
			break;

		default:
			break;

		}


		//回復が選択されてないなら
		if (m_isRecovery != true)
		{

			//プレイヤーの部位に落ちていた武器の種類を教えてやる
			m_player->SetCustomPoint(m_customParts, m_customKinds);


			//モデル更新
			SetUp();	

		}


		//武器取り付けを承認してカスタム画面が終わる時
		InitTranceOut();


		//決定音再生
		PlaySE(enSoutyakuSE, 2.0f);


		//Aボタンを押したフラグを下ろす
		g_pad[0]->SetTriggerFlagFalse(enButtonA);

	}

}

void Customize_UI_ver2::ExecuteReject()
{

	//左ボタンが押されたら
	if (g_pad[0]->IsTrigger(enButtonLeft) || g_pad[0]->IsTrigger(enButtonLB1))
	{

		//ACCEPTが選択される
		m_selectedWindow = ACCEPT;


		//賛成ウィンドウへ
		InitConfirmationWindow(ACCEPT);

	}


	//Aボタンが押されたら
	if (g_pad[0]->IsTrigger(enButtonA))
	{

		//注意書き表示を切る
		m_isConformatinoWindowOpen = false;


		//キャンセル音の再生
		PlaySE(enCancelSE, 2.0f);

	}

}

void Customize_UI_ver2::InitConfirmationWindow(bool isApproval)
{

	//承認する方なら
	if (isApproval == ACCEPT)
	{
		//注意書きのスプライトの初期化(承認ver.)
		m_confirmationWindow.Init("Assets/sprite/confirmation_window_yes.DDS", 584.375f, 918.0f);
	}
	//拒否する方なら
	else
	{
		//注意書きのスプライトの初期化(拒否ver.)
		m_confirmationWindow.Init("Assets/sprite/confirmation_window_no.DDS", 584.375f, 918.0f);
	}


	//更新
	m_confirmationWindow.Update();

}

void Customize_UI_ver2::ExecuteBody()
{

	//少しづつ回転させる
	m_customModelRotation.AddRotationDegY(2.0f);


	//更新
	m_bodyModel->SetRotation(m_customModelRotation);
	m_bodyModel->Update();

}

void Customize_UI_ver2::ExecuteCore()
{

	//モデルのローカルポジション設定
	m_coreLocalPosition = { 0.0f,80.0f,10.0f };


	//追尾移動の処理
	CalcWeaponTracking(m_coreLocalPosition, m_coreModel);

}

template <class T>
void Customize_UI_ver2::ExecuteBodyParts(T* parts, bool& isWeaponSet, std::unique_ptr<ModelRender>& model, int siteNum, bool isShoulder2)
{

	Vector3 localPos;


	//武器をセットしているフラグを立てる
	isWeaponSet = true;


	//付けている武器によってカスタム画面のモデルを変更する
	switch (parts->GetWeaponKind())
	{
	case MACHINEGUN_NUM:	//マシンガン

		//モデルのサイズを設定			
		model->SetScale(MCHINEGUN_SCALE);


		//部位によってローカルポジションを変える
		if (siteNum == RIGHT_ARM_NUM)
		{
			localPos = { 60.0f,100.0f,0.0f };
		}
		else if (siteNum == RIGHT_LEG_NUM)
		{
			localPos = { 90.0f,30.0f,0.0f };
		}
		else if (siteNum == LEFT_ARM_NUM)
		{
			localPos = { -60.0f,100.0f,0.0f };
		}
		else if (siteNum == LEFT_LEG_NUM)
		{
			localPos = { -90.0f,30.0f,0.0f };
		}
		else if (siteNum == SHOULDER_NUM)
		{

			//マシンガンの2個目じゃないなら
			if (isShoulder2 == false)
			{
				localPos = { 35.0f,119.0f,0.0f };
			}
			//2個目なら
			else
			{
				localPos = { -35.0f, 119.0f, 0.0f };
			}

		}

		break;


	case GIGATONCANNON_NUM:	//ギガトンキャノン

		//モデルのサイズを設定			
		model->SetScale(GIGATONCANNON_SCALE);


		//部位によってローカルポジションを変える
		if (siteNum == RIGHT_ARM_NUM)
		{
			localPos = { 50.0f,100.0f,30.0f };
		}
		else if (siteNum == RIGHT_LEG_NUM)
		{
			localPos = { 55.0f,40.0f,27.0f };
		}
		else if (siteNum == LEFT_ARM_NUM)
		{
			localPos = { -50.0f,100.0f,30.0f };
		}
		else if (siteNum == LEFT_LEG_NUM)
		{
			localPos = { -55.0f,40.0f,27.0f };
		}
		else if (siteNum == SHOULDER_NUM)
		{
			localPos = { 0.0f,120.0f,0.0f };
		}

		break;


	case BATTLESHIPGUN_NUM:	//戦艦砲

		//モデルのサイズを設定	
		model->SetScale(BATTLESHIPGUN_SCALE);


		//部位によってローカルポジションを変える
		if (siteNum == RIGHT_ARM_NUM)
		{
			localPos = { 60.0f,80.0f,-10.0f };
		}
		else if (siteNum == RIGHT_LEG_NUM)
		{
			localPos = { 60.0f,40.0f,40.0f };
		}
		else if (siteNum == LEFT_ARM_NUM)
		{
			localPos = { -60.0f,80.0f,-10.0f };
		}
		else if (siteNum == LEFT_LEG_NUM)
		{
			localPos = { -60.0f,40.0f,40.0f };
		}
		else if (siteNum == SHOULDER_NUM)
		{
			localPos = { 0.0f,119.0f,0.0f };
		}

		break;

	default:
		break;

	}


	//追尾移動の処理
	CalcWeaponTracking(localPos, model);

}

void Customize_UI_ver2::CalcWeaponTracking(Vector3 localPos, std::unique_ptr<ModelRender>& model)
{

	//本体モデルの回転を渡す
	Quaternion weaponRotation = m_customModelRotation;


	//本体モデルの回転に合わせたローカルポジションを計算
	weaponRotation.Multiply(localPos);


	//本体モデルのポジションを渡す
	Vector3 weaponPosition = m_customModelPosition;


	//本体モデルのポジションに計算したローカルポジションを足す
	weaponPosition += localPos;


	//更新
	model->SetRotation(weaponRotation);
	model->SetPosition(weaponPosition);
	model->Update();

}

void Customize_UI_ver2::TranceIn()
{

	//黒フェード1回目
	if (m_tranceSheetCount >= 0 && m_tranceSheetCount <= 24)
	{
		m_tranceSheetPosition01.x -= 160.0f;
		m_tranceSheetPosition03.x += 160.0f;
	}
	//黒フェード2回目
	if (m_tranceSheetCount >= 20 && m_tranceSheetCount <= 44)
	{
		m_tranceSheetPosition02.x -= 160.0f;
		m_tranceSheetPosition04.x += 160.0f;
	}


	//黒フェード終了したら
	if (m_tranceSheetCount == 50)
	{
		//カメラ移動
		m_gameCamera->SetToCameraPos({ 0.0f, -10.0f, -100.0f });
		m_gameCamera->SetTarget({ 10000.0f,20.0f,0.0f });
		m_gameCamera->SetCameraState(3);
		m_gameCamera->GetSpringCamera().Refresh();
	}


	//黒フェード消滅
	if (m_tranceSheetCount >= 44 && m_tranceSheetCount <= 64)
	{
		for (int i = 0; i < TRANCE_SHEET_AMOUNT; i++)
		{
			m_tranceSheet[i].SetMulColor(m_tranceSheetColor);
		}
		m_tranceSheetColor.w -= 0.05f;
	}


	//UI出現
	//上のセレクト部分
	if (m_tranceSheetCount >= 64 && m_tranceSheetCount < 71)
	{
		m_selectSheetPosition.y -= 50.0f;
	}
	if (m_tranceSheetCount >= 71 && m_tranceSheetCount <= 75)
	{
		m_selectSheetPosition.y += 10.0f;
	}

	//パラメータシート
	if (m_tranceSheetCount >= 65 && m_tranceSheetCount < 81)
	{
		m_parameterSheetPosition.x += 50.0f;
	}
	if (m_tranceSheetCount >= 81 && m_tranceSheetCount < 86)
	{
		m_parameterSheetPosition.x -= 10.0f;
	}

	//bodyの出現
	if (m_tranceSheetCount >= 80 && m_tranceSheetCount < 89)
	{
		m_customModelPosition.x -= 60.0f;
	}

	//遷移終了
	if (m_tranceSheetCount == 89)
	{
		m_tranceState = NOT_FADE;
	}


	//更新
	m_bodyModel->SetPosition(m_customModelPosition);
	m_bodyModel->Update();

	m_parameterSheet.SetPosition(m_parameterSheetPosition);
	m_parameterSheet.Update();

	m_selectSheet.SetPosition(m_selectSheetPosition);
	m_selectSheet.Update();

	m_tranceSheet[0].SetPosition(m_tranceSheetPosition01);
	m_tranceSheet[1].SetPosition(m_tranceSheetPosition02);
	m_tranceSheet[2].SetPosition(m_tranceSheetPosition03);
	m_tranceSheet[3].SetPosition(m_tranceSheetPosition04);

	m_tranceSheet[0].Update();
	m_tranceSheet[1].Update();
	m_tranceSheet[2].Update();
	m_tranceSheet[3].Update();


	//カウントアップ
	m_tranceSheetCount++;

}

void Customize_UI_ver2::InitTranceOut()
{

	//フェードアウトへ
	m_tranceState = FADE_OUT;


	//トランスシートの初期化
	InitTrance();
	
}

void Customize_UI_ver2::TranceOut()
{
	//黒フェード1回目
	if (m_tranceSheetCount >= 0 && m_tranceSheetCount <= 24)
	{
		m_tranceSheetPosition01.x -= 160.0f;
		m_tranceSheetPosition03.x += 160.0f;
	}
	//黒フェード2回目
	if (m_tranceSheetCount >= 20 && m_tranceSheetCount <= 44)
	{
		m_tranceSheetPosition02.x -= 160.0f;
		m_tranceSheetPosition04.x += 160.0f;
	}


	//黒フェード終了したら
	if (m_tranceSheetCount == 50)
	{
		//カメラ移動(プレイヤーのステートはカスタム画面のまま)
		m_gameCamera->SetCameraState(0);
		m_gameCamera->SetToCameraPos({ 0.0f, 500.0f, -700.0f });
		m_gameCamera->GetSpringCamera().Refresh();	
	}

	//黒フェード消滅
	if (m_tranceSheetCount >= 44 && m_tranceSheetCount <= 64)
	{
		for (int i = 0; i < 4; i++)
		{
			m_tranceSheet[i].SetMulColor(m_tranceSheetColor);
		}
		m_tranceSheetColor.w -= 0.05f;
	}

	//ゲーム画面に戻る
	if (m_tranceSheetCount >= 64)
	{
		m_player->SetGameState(0);
	}

	//更新
	m_tranceSheet[0].SetPosition(m_tranceSheetPosition01);
	m_tranceSheet[1].SetPosition(m_tranceSheetPosition02);
	m_tranceSheet[2].SetPosition(m_tranceSheetPosition03);
	m_tranceSheet[3].SetPosition(m_tranceSheetPosition04);

	m_tranceSheet[0].Update();
	m_tranceSheet[1].Update();
	m_tranceSheet[2].Update();
	m_tranceSheet[3].Update();

	//カウントアップ
	m_tranceSheetCount++;
}

void Customize_UI_ver2::PlaySE(SoundName name, float vol)
{
	SoundSource* m_SE = NewGO<SoundSource>(0);			//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
	m_SE->Init(name);									//初期化
	m_SE->SetVolume(vol * m_game->GetSEVol());			//音量調整
	m_SE->Play(false);
}

void Customize_UI_ver2::Render(RenderContext& rc)
{

	//カスタマイズ画面の時のみDrawする
	if (m_player->GetGameState() != CUSTOMIZE_NUM)
	{
		return;
	}


	//カメラがカスタム画面ステートの時
	if (m_gameCamera->GetCameraState() == 3)
	{

		//コア武器はずっと存在するので分岐なし
		m_coreModel->Draw(rc);


		//胴体はずっと存在するので分岐なし
		m_bodyModel->Draw(rc);


		//各部位に装備されているならDrawする
		if (m_rightArmSet == true)
		{
			//右腕
			m_rightArmModel->Draw(rc);
		}
		if (m_leftArmSet == true)
		{
			//左腕
			m_leftArmModel->Draw(rc);
		}
		if (m_shoulderSet == true)
		{
			//肩
			m_shoulderModel->Draw(rc);


			//付けている武器がマシンガンなら
			if (m_shoulderWeapon->GetWeaponKind() == MACHINEGUN_NUM)
			{
				//2個目のマシンガンをDraw
				m_shoulderModel2->Draw(rc);
			}

		}
		if (m_rightLegSet == true)
		{
			//右足
			m_rightLegModel->Draw(rc);
		}
		if (m_leftLegSet == true)
		{
			//左足
			m_leftLegModel->Draw(rc);
		}


		//セレクトシートの描画
		m_selectSheet.Draw(rc);


		//パラメーターシートの描画
		m_parameterSheet.Draw(rc);


		//注意書きを表示するなら
		if (m_isConformatinoWindowOpen == true)
		{
			//注意書きを描画
			m_confirmationWindow.Draw(rc);
		}
	}


	//黒フェード
	m_tranceSheet[0].Draw(rc);
	m_tranceSheet[1].Draw(rc);
	m_tranceSheet[2].Draw(rc);
	m_tranceSheet[3].Draw(rc);

}