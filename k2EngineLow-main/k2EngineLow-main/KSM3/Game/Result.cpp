#include "stdafx.h"
#include "Result.h"
#include "Title.h"
#include "Game.h"
#include "Player.h"
#include "Boss.h"
#include <time.h>
#include <stdlib.h>
#include "Fade.h"
#include "Core_weapons.h"
#include "Shoulder_weapons.h"
#include "Right_arm_weapons.h"
#include "Right_leg_weapons.h"
#include "Left_arm_weapons.h"
#include "Left_leg_weapons.h"
#include "Drop_item.h"
#include "GameCamera.h"


Result::Result() 
{
	Game* game = FindGO<Game>("game");
	player = FindGO<Player>("player");
	boss=FindGO<Boss>("boss");
	core_weapons=FindGO<Core_weapons>("core_weapons");
	shoulder_weapons=FindGO<Shoulder_weapons>("shoulder_weapons");
	right_arm_weapons=FindGO<Right_arm_weapons>("right_arm_weapons");
	right_leg_weapons=FindGO<Right_leg_weapons>("right_leg_weapons");
	left_arm_weapons=FindGO<Left_arm_weapons>("left_arm_weapons");
	left_leg_weapons=FindGO<Left_leg_weapons>("left_leg_weapons");
	gamecamera=FindGO<GameCamera>("gamecamera");
}

Result::~Result()
{	
	Game* game = FindGO<Game>("game");
	DeleteGO(game);
	DeleteGO(core_weapons);
	DeleteGO(drop_item);
}

bool Result::Start()
{
	    //ゲームのステートを取得
		/*m_fade = FindGO<Fade>("fade");
		m_fade->StartFadeIn();*/

	    //result_SpriteRender.Init("Assets/sprite/gameclear.dds", 1920.0f, 1080.0f);
		
		



		//テキスト
		for (int M = 0; M < 5; M++) {
			//リザルト
			Mozi_render[0].Init("Assets/sprite/result.dds", 500.0f, 300.0f);
			Mozi_render[0].SetPosition({ -50.0f, 350.0f, 0.0f });
			Mozi_render[0].SetScale({ 2.0f,2.0f,2.0f });
			//敵を倒した数
			Mozi_render[1].Init("Assets/sprite/mozi1.dds", 500.0f, 300.0f);
			Mozi_render[1].SetPosition({-520.0f,250.0f,0.0f});
			Mozi_render[1].SetScale({1.3f,1.3f,1.3f});
			//装備した数
			Mozi_render[2].Init("Assets/sprite/mozi2.dds", 500.0f, 300.0f);
			Mozi_render[2].SetPosition({-515.0f,50.0f,0.0f});
			Mozi_render[2].SetScale({1.3f,1.3f,1.3f});
			//BOSSを倒した時間
			Mozi_render[3].Init("Assets/sprite/mozi3.dds", 500.0f, 300.0f);
			Mozi_render[3].SetPosition({-490.0f,-200.0f,0.0f});
			Mozi_render[3].SetScale({1.3f,1.3f,1.3f});
			//トータルスコア
			Mozi_render[4].Init("Assets/sprite/total_score.dds", 500.0f, 300.0f);
			Mozi_render[4].SetPosition({380.0f,50.0f,0.0f});
			Mozi_render[4].SetScale({1.4f,1.4f,1.4f});
			//Aボタンでゲーム終了
			Mozi_render[5].Init("Assets/sprite/game_end.dds", 500.0f, 300.0f);
			Mozi_render[5].SetPosition({ 0.0f, -400.0f, 0.0f });
			Mozi_render[5].SetScale({ 1.4f,1.4f,1.4f });
		}

		//数値
		//敵を倒した数
		Enemy_count_render[0].Init("Assets/sprite/0.dds", 500.0f, 300.0f);
		Enemy_count_render[1].Init("Assets/sprite/1.dds", 500.0f, 300.0f);
		Enemy_count_render[2].Init("Assets/sprite/2.dds", 500.0f, 300.0f);
		Enemy_count_render[3].Init("Assets/sprite/3.dds", 500.0f, 300.0f);
		Enemy_count_render[4].Init("Assets/sprite/4.dds", 500.0f, 300.0f);
		Enemy_count_render[5].Init("Assets/sprite/5.dds", 500.0f, 300.0f);
		Enemy_count_render[6].Init("Assets/sprite/6.dds", 500.0f, 300.0f);
		Enemy_count_render[7].Init("Assets/sprite/7.dds", 500.0f, 300.0f);
		Enemy_count_render[8].Init("Assets/sprite/8.dds", 500.0f, 300.0f);
		Enemy_count_render[9].Init("Assets/sprite/9.dds", 500.0f, 300.0f);
		Enemy_count_render[10].Init("Assets/sprite/10.dds", 500.0f, 300.0f);
		Enemy_count_render[11].Init("Assets/sprite/11.dds", 500.0f, 300.0f);
		Enemy_count_render[12].Init("Assets/sprite/12.dds", 500.0f, 300.0f);
		Enemy_count_render[13].Init("Assets/sprite/13.dds", 500.0f, 300.0f);
		Enemy_count_render[14].Init("Assets/sprite/14.dds", 500.0f, 300.0f);
		Enemy_count_render[15].Init("Assets/sprite/15.dds", 500.0f, 300.0f);
		Enemy_count_render[16].Init("Assets/sprite/16.dds", 500.0f, 300.0f);
		Enemy_count_render[17].Init("Assets/sprite/17.dds", 500.0f, 300.0f);
		Enemy_count_render[18].Init("Assets/sprite/18.dds", 500.0f, 300.0f);
		Enemy_count_render[19].Init("Assets/sprite/19.dds", 500.0f, 300.0f);
		Enemy_count_render[20].Init("Assets/sprite/20.dds", 500.0f, 300.0f);
		Enemy_count_render[21].Init("Assets/sprite/21.dds", 500.0f, 300.0f);
		Enemy_count_render[22].Init("Assets/sprite/22.dds", 500.0f, 300.0f);
		Enemy_count_render[23].Init("Assets/sprite/23.dds", 500.0f, 300.0f);
		Enemy_count_render[24].Init("Assets/sprite/24.dds", 500.0f, 300.0f);
		Enemy_count_render[25].Init("Assets/sprite/25.dds", 500.0f, 300.0f);
		Enemy_count_render[26].Init("Assets/sprite/26.dds", 500.0f, 300.0f);
		Enemy_count_render[27].Init("Assets/sprite/27.dds", 500.0f, 300.0f);
		Enemy_count_render[28].Init("Assets/sprite/28.dds", 500.0f, 300.0f);
		Enemy_count_render[29].Init("Assets/sprite/29.dds", 500.0f, 300.0f);
		Enemy_count_render[30].Init("Assets/sprite/30.dds", 500.0f, 300.0f);

		for (int E = 0; E < 31; E++) {
			Enemy_count_render[E].SetPosition({ -600.0f,150.0f,0.0f });
			Enemy_count_render[E].SetScale({ 1.5f,1.5f,1.5f });
		}

		//武器をセットした数
		Weapon_set_render[0].Init("Assets/sprite/0.dds", 500.0f, 300.0f);
		Weapon_set_render[1].Init("Assets/sprite/1.dds", 500.0f, 300.0f);
		Weapon_set_render[2].Init("Assets/sprite/2.dds", 500.0f, 300.0f);
		Weapon_set_render[3].Init("Assets/sprite/3.dds", 500.0f, 300.0f);
		Weapon_set_render[4].Init("Assets/sprite/4.dds", 500.0f, 300.0f);
		Weapon_set_render[5].Init("Assets/sprite/5.dds", 500.0f, 300.0f);

		for (int Ws = 0; Ws < 6; Ws++) {
			Weapon_set_render[Ws].SetPosition({ -600.0f,-50.0f,0.0f });
			Weapon_set_render[Ws].SetScale({ 1.5f,1.5f,1.5f });
		}

		//ランク
		for (int R = 0; R < 5; R++) {
			rank_render[0].Init("Assets/sprite/D_p2.dds", 1000.0f, 800.0f);
			rank_render[1].Init("Assets/sprite/C_p2.dds", 1000.0f, 800.0f);
			rank_render[2].Init("Assets/sprite/B_p2.dds", 1000.0f, 800.0f);
			rank_render[3].Init("Assets/sprite/A.dds", 1000.0f, 800.0f);
			rank_render[4].Init("Assets/sprite/S.dds", 1000.0f, 800.0f); 
			rank_render[R].SetPosition({ 0.0f, 0.0f, 0.0f });
		}

	return true;
}

void Result::Update()
{
	BackGround();
	Set_count();
	Enemy_count();
	Font();
	Rank();

	//タイトルへの遷移(フェードあり)
	/*if (m_isWaitFadeout)
	{
		if (!m_fade->IsFade()){
			Title* title = NewGO<Title>(0, "title");				
			DeleteGO(this);
		}
	}
	else
	{
		if (draw_time >= 8.0f) {
			if (g_pad[0]->IsTrigger(enButtonA)) {
				m_isWaitFadeout = true;
				m_fade->StartFadeOut();
			}
		}
	}*/
	//(フェードなし)
	if (result_state == 0) {
		if (draw_time >= 8.0f) {
			if (g_pad[0]->IsTrigger(enButtonA)) {
				Title* title = NewGO<Title>(0, "title");
				DeleteGO(this);
			}

			if (g_pad[0]->IsTrigger(enButtonB)) {
				//スコア表示OFF
				result_state = 1;
			}
		}
	}
	else if(result_state==1){
		Score_OFF();
	}
	//custom_model_Core.Update();

	for (int M = 0; M < 6; M++) {
		Mozi_render[M].Update();
	}

	for (int E = 0; E < 31; E++) {
		Enemy_count_render[E].Update();
	}

	for (int Ws = 0; Ws < 6; Ws++) {
		Weapon_set_render[Ws].Update();
	}

	for (int R = 0; R < 5; R++) {
		rank_render[R].Update();
	}
}

void Result::Score_OFF()
{
    //gamecamera->x = g_pad[0]->GetRStickXF();
	if (g_pad[0]->IsTrigger(enButtonB)) {
			//スコア表示ON
			result_state = 0;
	}
		
}

void Result::BackGround()
{
		//背景
	if (player->game_state == 2) {
		
		Player_modelrender.Init("Assets/modelData/Player.tkm");
		Player_modelrender.SetPosition(Player_position);
		Player_rotation.SetRotationDegY(-180.0f);
		Player_modelrender.SetRotation(Player_rotation);
		Player_modelrender.Update();

		Box_render.Init("Assets/modelData/Customize_area.tkm");
		Box_render.SetPosition(Box_position);
		Box_render.SetScale(Box_scale);
		Box_render.Update();

		gamecamera->m_toCameraPos.Set(0.0f, -10.0f, -100.0f);
		gamecamera->fast_count = 0;
		gamecamera->target = { 10000.0f,20.0f,0.0f };
		gamecamera->CameraState = 3;

		if (core_weapons->set_weapons == 2) {
			custom_model_Core.Init("Assets/modelData/Versatile_Perforator.tkm");
			cw_lp = { 0.0f,80.0f,10.0f };
			custom_model_body_rotation.SetRotationDegY(-180.0f);
			Quaternion originRotation = custom_model_body_rotation;
			Vector3 cw_position = Player_position;


			originRotation.Multiply(cw_lp);
			cw_position += cw_lp;
			Quaternion cw_Rotation = originRotation;

			custom_model_Core.SetRotation(cw_Rotation);
			custom_model_Core.SetPosition(cw_position);
			custom_model_Core.Update();
		}

		if (player->p_custom_point[0][1] != 0)	//肩
		{
			//移動の処理
			Quaternion originRotation = custom_model_body_rotation;
			Vector3 sw_position = Player_position;
			originRotation.Multiply(sw_lp);
			sw_position += sw_lp;
			Quaternion sw_Rotation = originRotation;

			//更新
			custom_model_shoulder.SetRotation(sw_Rotation);
			custom_model_shoulder.SetPosition(sw_position);
			
			//武器によってモデルを変える
			switch (shoulder_weapons->set_weapons)
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
			custom_model_shoulder.Update();
		}

		if (player->p_custom_point[0][0] != 0)	//右腕
		{
			//移動の処理
			Quaternion originRotation = custom_model_body_rotation;
			Vector3 raw_position = Player_position;
			originRotation.Multiply(raw_lp);
			raw_position += raw_lp;
			Quaternion raw_Rotation = originRotation;

			//更新
			custom_model_Right_arm.SetRotation(raw_Rotation);
			custom_model_Right_arm.SetPosition(raw_position);
			
			//武器によってモデルを変える
			switch (right_arm_weapons->set_weapons)
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
		custom_model_Right_arm.Update();
		}

		if (player->p_custom_point[1][0] != 0)	//右足
		{
			//移動の処理
			Quaternion originRotation = custom_model_body_rotation;
			Vector3 rlw_position = Player_position;
			originRotation.Multiply(rlw_lp);
			rlw_position += rlw_lp;
			Quaternion rlw_Rotation = originRotation;

			//更新
			custom_model_Right_leg.SetRotation(rlw_Rotation);
			custom_model_Right_leg.SetPosition(rlw_position);
			
			//武器によってモデルを変える
			switch (right_leg_weapons->set_weapons)
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
		custom_model_Right_leg.Update();
		}

		if (player->p_custom_point[0][2] != 0)	//左腕
		{

			//移動の処理
			Quaternion originRotation = custom_model_body_rotation;
			Vector3 law_position = Player_position;
			originRotation.Multiply(law_lp);
			law_position += law_lp;
			Quaternion law_Rotation = originRotation;

			//更新
			custom_model_Left_arm.SetRotation(law_Rotation);
			custom_model_Left_arm.SetPosition(law_position);
			switch (player->p_custom_point[0][2]) {
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
			custom_model_Left_arm.Update();
		}

		if (player->p_custom_point[1][2] != 0)	//左足
		{
			//移動の処理
			Quaternion originRotation = custom_model_body_rotation;
			Vector3 llw_position = Player_position;
			originRotation.Multiply(llw_lp);
			llw_position += llw_lp;
			Quaternion llw_Rotation = originRotation;

			//更新
			custom_model_Left_leg.SetRotation(llw_Rotation);
			custom_model_Left_leg.SetPosition(llw_position);
			
			//武器によってモデルを変える
			switch (left_leg_weapons->set_weapons)
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
				custom_model_Left_leg.SetScale(1.0f);
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
			custom_model_Left_leg.Update();
		}

		
	}
}

void Result::Set_count()
{

		player = FindGO<Player>("player");
		//1箇所装備していたら
		if (/*右腕*/player->p_custom_point[0][0] || /*右足*/player->p_custom_point[1][0] || /*肩*/player->p_custom_point[0][1] || /*左腕*/player->p_custom_point[0][2] || /*左足*/player->p_custom_point[1][2])
		{
			set = 1;
		}
		//2箇所装備していたら
		if (player->p_custom_point[0][0] && player->p_custom_point[1][0] || player->p_custom_point[0][0] && player->p_custom_point[0][1] || player->p_custom_point[0][0] && player->p_custom_point[0][2] || player->p_custom_point[0][0] && player->p_custom_point[1][2] ||
			player->p_custom_point[1][0] && player->p_custom_point[0][1] || player->p_custom_point[1][0] && player->p_custom_point[0][2] || player->p_custom_point[1][0] && player->p_custom_point[1][2] ||
			player->p_custom_point[0][1] && player->p_custom_point[0][2] || player->p_custom_point[0][1] && player->p_custom_point[1][2] ||
			player->p_custom_point[0][2] && player->p_custom_point[1][2])
		{
			set = 2;
		}
		//3箇所装備していたら
		if (player->p_custom_point[0][0] && player->p_custom_point[1][0] && player->p_custom_point[0][2] || player->p_custom_point[0][0] && player->p_custom_point[1][0] && player->p_custom_point[1][2] || player->p_custom_point[0][0] && player->p_custom_point[0][2] && player->p_custom_point[1][2] ||
			player->p_custom_point[0][1] && player->p_custom_point[0][0] && player->p_custom_point[0][2] || player->p_custom_point[0][1] && player->p_custom_point[1][0] && player->p_custom_point[1][2] || player->p_custom_point[0][1] && player->p_custom_point[0][0] && player->p_custom_point[1][0] ||
			player->p_custom_point[0][1] && player->p_custom_point[0][2] && player->p_custom_point[1][2] || player->p_custom_point[0][1] && player->p_custom_point[0][0] && player->p_custom_point[1][2] || player->p_custom_point[0][1] && player->p_custom_point[0][2] && player->p_custom_point[1][0])
		{
			set = 3;
		}
		//4箇所装備していたら
		if (player->p_custom_point[0][1] && player->p_custom_point[0][0] && player->p_custom_point[0][2] && player->p_custom_point[1][0] || player->p_custom_point[0][1] && player->p_custom_point[0][0] && player->p_custom_point[0][2] && player->p_custom_point[1][2] || player->p_custom_point[0][1] && player->p_custom_point[0][2] && player->p_custom_point[1][0] && player->p_custom_point[1][2] ||
			player->p_custom_point[0][1] && player->p_custom_point[1][2] && player->p_custom_point[0][2] && player->p_custom_point[1][0] || player->p_custom_point[1][0] && player->p_custom_point[0][0] && player->p_custom_point[0][2] && player->p_custom_point[1][2])
		{
			set = 4;
		}
		//5箇所装備していたら
		if (player->p_custom_point[0][1] && player->p_custom_point[0][0] && player->p_custom_point[0][2] && player->p_custom_point[1][0] && player->p_custom_point[1][2])
		{
			set = 5;
		}
	    //装備した箇所に応じてスコア変動
		switch (set) {
		case 0:
			set_score = 0;
			break;
		case 1:
			set_score = 1000;
			break;
		case 2:
			set_score = 750;
			break;
		case 3:
			set_score = 500;
			break;
		case 4:
			set_score = 250;
			break;
		case 5:
			set_score = 100;
			break;
		}
	
}

void Result::Enemy_count()
{
	Game* game = FindGO<Game>("game");

	    //倒した敵の数に応じてスコア変動
		switch (game->m_numDefeatedEnemy) {
		case 1:
			enemy_count = 1;
			enemy_count_score = 1000;
			break;
		case 2:
			enemy_count = 2;
			enemy_count_score = 2000;
			break;
		case 3:
			enemy_count = 3;
			enemy_count_score = 3000;
			break;
		case 4:
			enemy_count = 4;
			enemy_count_score = 4000;
			break;
		case 5:
			enemy_count = 5;
			enemy_count_score = 5000;
			break;
		case 6:
			enemy_count = 6;
			enemy_count_score = 6000;
			break;
		case 7:
			enemy_count = 7;
			enemy_count_score = 7000;
			break;
		case 8:
			enemy_count = 8;
			enemy_count_score = 8000;
			break;
		case 9:
			enemy_count = 9;
			enemy_count_score = 9000;
			break;
		case 10:
			enemy_count = 10;
			enemy_count_score = 10000;
			break;
		case 11:
			enemy_count = 11;
			enemy_count_score = 11000;
			break;
		case 12:
			enemy_count = 12;
			enemy_count_score = 12000;
			break;
		case 13:
			enemy_count = 13;
			enemy_count_score = 13000;
			break;
		case 14:
			enemy_count = 14;
			enemy_count_score = 14000;
			break;
		case 15:
			enemy_count = 15;
			enemy_count_score = 15000;
			break;
		case 16:
			enemy_count = 16;
			enemy_count_score = 16000;
			break;
		case 17:
			enemy_count = 17;
			enemy_count_score = 17000;
			break;
		case 18:
			enemy_count = 18;
			enemy_count_score = 18000;
			break;
		case 19:
			enemy_count = 19;
			enemy_count_score = 19000;
			break;
		case 20:
			enemy_count = 20;
			enemy_count_score = 20000;
			break;
		case 21:
			enemy_count = 21;
			enemy_count_score = 21000;
			break;
		case 22:
			enemy_count = 22;
			enemy_count_score = 22000;
			break;
		case 23:
			enemy_count = 23;
			enemy_count_score = 23000;
			break;
		case 24:
			enemy_count = 24;
			enemy_count_score = 24000;
			break;
		case 25:
			enemy_count = 25;
			enemy_count_score = 25000;
			break;
		case 26:
			enemy_count = 26;
			enemy_count_score = 26000;
			break;
		case 27:
			enemy_count = 27;
			enemy_count_score = 27000;
			break;
		case 28:
			enemy_count = 28;
			enemy_count_score = 28000;
			break;
		case 29:
			enemy_count = 29;
			enemy_count_score = 29000;
			break;
		case 30:
			enemy_count = 30;
			enemy_count_score = 30000;
			break;
		}
}

void Result::Rank()
{
	Game* game = FindGO<Game>("game");
	//トータルスコアを計算
	total_score = set_score+enemy_count_score + game->time_score;

	//トータルスコアによってランクを変える
	if (total_score > 500) {
		//ランクD
		rank = 0;
	}
	if (total_score > 1000) {
		//ランクC
		rank = 1;
	}
	if (total_score > 3500){
		//ランクB
		rank = 2;
	}
	if (total_score > 5000){
		//ランクA
		rank = 3;
	}
	if (total_score > 10000) {
		//ランクS
		rank = 4;
	}
}

void Result::Font()
{
	draw_time += g_gameTime->GetFrameDeltaTime();

	if (draw_time >= 8.0f) {
		wchar_t score[256];
		swprintf_s(score, 256, L" %06d", int(total_score));
		//表示するテキストを設定。
		Score_font.SetText(score);
		Score_font.SetPosition({ 350.0f,0.0f,0.0f });
		Score_font.SetScale(1.5f);
		Score_font.SetColor(g_vec4Black);
	}

	if (draw_time >= 7.0f) {
		Game* game = FindGO<Game>("game");
		wchar_t text[256];
		int minute = (int)game->boss_time / 60;
		int sec = (int)game->boss_time % 60;
		swprintf_s(text, 256, L"%02d:%02d", minute, sec);
		//表示するテキストを設定。
		Boss_time_font.SetText(text);
		Boss_time_font.SetPosition({ -800.0f, -300.0f, 0.0f });
		Boss_time_font.SetScale(1.5f);
		Boss_time_font.SetColor(g_vec4Black);
	}
	
}

void Result::Render(RenderContext& rc)
{	
	

	//result_SpriteRender.Draw(rc);
	
		if (player->game_state == 2) {
			Player_modelrender.Draw(rc);
			custom_model_Core.Draw(rc);
			custom_model_shoulder.Draw(rc);
			custom_model_Right_arm.Draw(rc);
			custom_model_Right_leg.Draw(rc);
			custom_model_Left_arm.Draw(rc);
			custom_model_Left_leg.Draw(rc);
			Box_render.Draw(rc);
		}
	if (result_state == 0) {
		draw_time += g_gameTime->GetFrameDeltaTime();
		if (player->boss_survival == false) {

			for (int F = 0; F < 5; F++) {
				font_render[F].Draw(rc);
			}

			Score_font.Draw(rc);
			Boss_time_font.Draw(rc);

			for (int M = 0; M < 6; M++) {
				if (draw_time >= 0.0f) {
					Mozi_render[0].Draw(rc);
				}
				if (draw_time >= 2.0f) {
					Mozi_render[1].Draw(rc);
				}
				if (draw_time >= 4.0f) {
					Mozi_render[2].Draw(rc);
				}
				if (draw_time >= 6.0f) {
					Mozi_render[3].Draw(rc);
				}
				if (draw_time >= 8.0f) {
					Mozi_render[4].Draw(rc);
					Mozi_render[5].Draw(rc);
				}
			}

			for (int E = 0; E < 31; E++) {
				if (draw_time >= 3.0f) {
					Game* game = FindGO<Game>("game");
					switch (game->m_numDefeatedEnemy) {
					case 0:
						Enemy_count_render[0].Draw(rc);
						break;
					case 1:
						Enemy_count_render[1].Draw(rc);
						break;
					case 2:
						Enemy_count_render[2].Draw(rc);
						break;
					case 3:
						Enemy_count_render[3].Draw(rc);
						break;
					case 4:
						Enemy_count_render[4].Draw(rc);
						break;
					case 5:
						Enemy_count_render[5].Draw(rc);
						break;
					case 6:
						Enemy_count_render[6].Draw(rc);
						break;
					case 7:
						Enemy_count_render[7].Draw(rc);
						break;
					case 8:
						Enemy_count_render[8].Draw(rc);
						break;
					case 9:
						Enemy_count_render[9].Draw(rc);
						break;
					case 10:
						Enemy_count_render[10].Draw(rc);
						break;
					case 11:
						Enemy_count_render[11].Draw(rc);
						break;
					case 12:
						Enemy_count_render[12].Draw(rc);
						break;
					case 13:
						Enemy_count_render[13].Draw(rc);
						break;
					case 14:
						Enemy_count_render[14].Draw(rc);
						break;
					case 15:
						Enemy_count_render[15].Draw(rc);
						break;
					case 16:
						Enemy_count_render[16].Draw(rc);
						break;
					case 17:
						Enemy_count_render[17].Draw(rc);
						break;
					case 18:
						Enemy_count_render[18].Draw(rc);
						break;
					case 19:
						Enemy_count_render[19].Draw(rc);
						break;
					case 20:
						Enemy_count_render[20].Draw(rc);
						break;
					case 21:
						Enemy_count_render[21].Draw(rc);
						break;
					case 22:
						Enemy_count_render[22].Draw(rc);
						break;
					case 23:
						Enemy_count_render[23].Draw(rc);
						break;
					case 24:
						Enemy_count_render[24].Draw(rc);
						break;
					case 25:
						Enemy_count_render[25].Draw(rc);
						break;
					case 26:
						Enemy_count_render[26].Draw(rc);
						break;
					case 27:
						Enemy_count_render[27].Draw(rc);
						break;
					case 28:
						Enemy_count_render[28].Draw(rc);
						break;
					case 29:
						Enemy_count_render[29].Draw(rc);
						break;
					case 30:
						Enemy_count_render[30].Draw(rc);
						break;
					}
				}
				Enemy_count_render[E].Update();
			}

			for (int Ws = 0; Ws < 6; Ws++) {
				if (draw_time >= 5.0f) {
					switch (set) {
					case 0:
						Weapon_set_render[0].Draw(rc);
						break;
					case 1:
						Weapon_set_render[1].Draw(rc);
						break;
					case 2:
						Weapon_set_render[2].Draw(rc);
						break;
					case 3:
						Weapon_set_render[3].Draw(rc);
						break;
					case 4:
						Weapon_set_render[4].Draw(rc);
						break;
					case 5:
						Weapon_set_render[5].Draw(rc);
						break;
					}
				}
				Weapon_set_render[Ws].Update();
			}

			for (int R = 0; R < 5; R++) {
				if (draw_time >= 8.0f) {
					switch (rank) {
					case 0:
						rank_render[0].Draw(rc);
						break;
					case 1:
						rank_render[1].Draw(rc);
						break;

					case 2:
						rank_render[2].Draw(rc);
						break;
					case 3:
						rank_render[3].Draw(rc);
						break;
					case 4:
						rank_render[4].Draw(rc);
						break;
					}
				}
				rank_render[R].Update();
			}
		}
	}
}