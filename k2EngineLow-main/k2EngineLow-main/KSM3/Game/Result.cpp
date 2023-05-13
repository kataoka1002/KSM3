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
#include <map>
#include <tuple>
#include "Result_Macro.h"


Result::Result() 
{
	player = FindGO<Player>("player");
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				p_custom_point[i][j] = player->p_custom_point[i][j];
			}
		}
	boss=FindGO<Boss>("boss");
	gamecamera=FindGO<GameCamera>("gamecamera");
}

Result::~Result()
{	
	DeleteGO(gamecamera);
	DeleteGO(player);
	/*Game* game = FindGO<Game>("game");
	DeleteGO(game);
	DeleteGO(core_weapons);
	DeleteGO(drop_item);*/
}

bool Result::Start()
{
	Font_set();
	Back_set();

	return true;
}

void Result::Update()
{
	BackGround();
	
	/*Enemy_count();
	Font();
	Rank();*/

	//タイトルへの遷移(フェードあり)
	if (g_pad[0]->IsTrigger(enButtonA)&&fast_count!=1) {
		if (Neo_result_state == 0) {
			Neo_result_state = 1;
		}
		else if (Neo_result_state == 1) {
			Neo_result_state = 2;
		}
		else if (Neo_result_state == 2) {
			Title* title = NewGO<Title>(0, "title");
			DeleteGO(this);
		}
		fast_count = 0;
	}
	if (Neo_result_state == 0) {
		//タイマーの初期化
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 10; j++) {
				Time_Num[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, a[i][0]));
			}
		}
		Time_colon.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, a[1][0]));

		//timeの文字の移動(出現）
		if (fast_count <= 49) {
			Time_color.w += 0.02f;
			Time_position.x += 0.5f;
			time_Render.SetPosition(Time_position);
			time_Render.SetMulColor(Time_color);
			time_Render.Update();
		}

		//タイムの出現
		if (fast_count >= 50 && fast_count < 55) {
			for (int i = 0; i < 4; i++) {
				a[i][0] += 0.2f;
				for (int j = 0; j < 10; j++) {
					Time_Num[i][j].SetMulColor(Vector4(1.0f,1.0f,1.0f,a[i][0]));
				}
			}
			Time_colon.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, a[1][0]));
		}
		if (fast_count >= 55 && fast_count < 60) {
			for (int i = 0; i < 4; i++) {
				a[i][0] -= 0.2f;
				for (int j = 0; j < 10; j++) {
					Time_Num[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, a[i][0]));
				}
			}
			Time_colon.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, a[1][0]));
		}
		if (fast_count >= 60 && fast_count < 65) {
			for (int i = 0; i < 4; i++) {
				a[i][0] += 0.2f;
				for (int j = 0; j < 10; j++) {
					Time_Num[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, a[i][0]));
				}
			}
			Time_colon.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, a[1][0]));
		}
		if (fast_count >= 65 && fast_count < 70) {
			for (int i = 0; i < 4; i++) {
				a[i][0] -= 0.2f;
				for (int j = 0; j < 10; j++) {
					Time_Num[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, a[i][0]));
				}
			}
			Time_colon.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, a[1][0]));
		}
		if (fast_count >=70 && fast_count < 110) {
			for (int i = 0; i < 4; i++) {
				a[i][0] += 0.025f;
				for (int j = 0; j < 10; j++) {
					Time_Num[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, a[i][0]));
				}
			}
			Time_colon.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, a[1][0]));
		}
	}

	//SCORE
	if (Neo_result_state == 1) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 10; j++) {
				Score_Num[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, b[i][0]));
			}
		}
		Score_comma.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, b[1][0]));
		if (fast_count <= 10) {
			Box_Rotation.AddRotationDegY(33.0f);
			Player_rotation.AddRotationDegY(33.0f);
			Box_render.SetRotation(Box_Rotation);
			Player_modelrender.SetRotation(Player_rotation);
		}

		//Scoreの文字の移動(出現）
		if (fast_count <= 49) {
			Score_color.w += 0.02f;
			Score_position.x += 0.5f;
			Score_Render.SetPosition(Score_position);
			Score_Render.SetMulColor(Score_color);
			Score_Render.Update();
		}

		//SCOREの出現
		if (fast_count >= 50 && fast_count < 55) {
			for (int i = 0; i < 5; i++) {
				b[i][0] += 0.2f;
				for (int j = 0; j < 10; j++) {
					Score_Num[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, b[i][0]));
				}
			}
			Score_comma.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, b[1][0]));
		}
		if (fast_count >= 55 && fast_count < 60) {
			for (int i = 0; i < 5; i++) {
				b[i][0] -= 0.2f;
				for (int j = 0; j < 10; j++) {
					Score_Num[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, b[i][0]));
				}
			}
			Score_comma.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, b[1][0]));
		}
		if (fast_count >= 60 && fast_count < 65) {
			for (int i = 0; i < 5; i++) {
				b[i][0] += 0.2f;
				for (int j = 0; j < 10; j++) {
					Score_Num[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, b[i][0]));
				}
			}
			Score_comma.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, b[1][0]));
		}
		if (fast_count >= 65 && fast_count < 70) {
			for (int i = 0; i < 5; i++) {
				b[i][0] -= 0.2f;
				for (int j = 0; j < 10; j++) {
					Score_Num[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, b[i][0]));
				}
			}
			Score_comma.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, b[1][0]));
		}
		if (fast_count >= 70 && fast_count < 110) {
			for (int i = 0; i < 5; i++) {
				b[i][0] += 0.025f;
				for (int j = 0; j < 10; j++) {
					Score_Num[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, b[i][0]));
				}
			}
			Score_comma.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, b[1][0]));
		}

		
	}

	//ランク
	if (Neo_result_state == 2) {
		if (fast_count <= 10) {
			Box_Rotation.AddRotationDegY(33.0f);
			Player_rotation.AddRotationDegY(33.0f);
			Box_render.SetRotation(Box_Rotation);
			Player_modelrender.SetRotation(Player_rotation);
		}

		if (fast_count >= 30 && fast_count < 35) {
			Rank_color.w += 0.2f;
			
		}
		if (fast_count >= 30 && fast_count < 80) {
			Rank_Scale.x -= 0.02f;
			Rank_Scale.y -= 0.02f;
			Rank_sheet.SetScale(Rank_Scale);
		}
		if (fast_count >= 80 && fast_count < 100) {
			Rank_Sheet_color.w += 0.05f;
			Rank_position.x -= 2.5f;
			Rank_sheet.SetPosition(Rank_position);
			Rank_sheet.SetMulColor(Rank_Sheet_color);
		}
		if (fast_count == 1) {
			//タイムとスコアの初期化(ランク用)
			//タイム関係
			
			Rank_Time_Render.SetMulColor(Rank_Time_color);
			Rank_Time_Render.SetPosition(Rank_Time_position);
			for (int i = 0; i < 2; i++) {
				a[i][0] =0;
				for (int j = 0; j < 10; j++) {
					Time_Num[i][j].SetScale(Vector3{ 0.55f,0.55f,0.55f });
					Time_Num[i][j].SetPosition(Vector3{ (-590.0f + (50.0f * i)),13.0f,0.0f });
					Time_Num[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, a[i][0]));
				}
			}
			for (int i = 2; i < 4; i++) {
				a[i][0] = 0;
				for (int j = 0; j < 10; j++) {
					Time_Num[i][j].SetScale(Vector3{ 0.55f,0.55f,0.55f });
					Time_Num[i][j].SetPosition(Vector3{ (-590.0f + (50.0f * i+1)),13.0f,0.0f });
					Time_Num[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, a[i][0]));
				}
			}
			Time_colon.SetScale(Vector3{ 0.55f,0.55f,0.55f });
			Time_colon.SetPosition(Vector3{ -490.0f,13.0f,0.0f });
			Time_colon.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, a[1][0]));
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 10; j++) {
					Time_Num[i][j].Update();
				}
			}
			Time_colon.Update();
			Rank_Time_Render.Update();

			//SCORE関係
			Rank_Score_Render.SetMulColor(Rank_Score_color);
			Rank_Score_Render.SetPosition(Rank_Score_position);
			for (int i = 0; i < 2; i++) {
				b[i][0] = 0;
				for (int j = 0; j < 10; j++) {
					Score_Num[i][j].SetScale(Vector3{ 0.55f,0.55f,0.55f });
					Score_Num[i][j].SetPosition(Vector3{ (340.0f + (50.0f * i)),13.0f,0.0f });
					Score_Num[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, b[i][0]));
				}
			}
			for (int i = 2; i < 5; i++) {
				b[i][0] = 0;
				for (int j = 0; j < 10; j++) {
					Score_Num[i][j].SetScale(Vector3{ 0.55f,0.55f,0.55f });
					Score_Num[i][j].SetPosition(Vector3{ (340.0f + (50.0f * i + 1)),13.0f,0.0f });
					Score_Num[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, b[i][0]));
				}
			}
			Score_comma.SetScale(Vector3{ 0.55f,0.55f,0.55f });
			Score_comma.SetPosition(Vector3{ 440.0f,13.0f,0.0f });
			Score_comma.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, a[1][0]));
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 10; j++) {
					Score_Num[i][j].Update();
				}
			}
			Score_comma.Update();
			Rank_Score_Render.Update();
		}
		if (fast_count >= 80 && fast_count < 100) {

			Rank_Time_color.w += 0.05f;
			Rank_Time_position.x += 1.25f;
			Rank_Time_Render.SetMulColor(Rank_Time_color);
			Rank_Time_Render.SetPosition(Rank_Time_position);
			for (int i = 0; i < 2; i++) {
				a[i][0] +=0.05f;
				for (int j = 0; j < 10; j++) {
					Time_Num[i][j].SetPosition(Vector3{ (-590.0f + (50.0f * i)),13.0f,0.0f });
					Time_Num[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, a[i][0]));
				}
			}
			for (int i = 2; i < 4; i++) {
				a[i][0] += 0.05f;
				for (int j = 0; j < 10; j++) {
					Time_Num[i][j].SetPosition(Vector3{ (-590.0f + (50.0f * (i + 1))),13.0f,0.0f });
					Time_Num[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, a[i][0]));
				}
			}
			Rank_Time_Render.Update();
			Time_colon.SetPosition(Vector3{ -490.0f,13.0f,0.0f });
			Time_colon.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, a[1][0]));

			//SCORE
			Rank_Score_color.w += 0.05f;
			Rank_Score_position.x -= 1.25f;
			Rank_Score_Render.SetMulColor(Rank_Score_color);
			Rank_Score_Render.SetPosition(Rank_Score_position);
			for (int i = 0; i < 2; i++) {
				b[i][0] += 0.05f;
				for (int j = 0; j < 10; j++) {
					Score_Num[i][j].SetPosition(Vector3{ (340.0f + (50.0f * i)),13.0f,0.0f });
					Score_Num[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, b[i][0]));
				}
			}
			for (int i = 2; i < 5; i++) {
				b[i][0] += 0.05f;
				for (int j = 0; j < 10; j++) {
					Score_Num[i][j].SetPosition(Vector3{ (340.0f + (50.0f * (i + 1))),13.0f,0.0f });
					Score_Num[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, b[i][0]));
				}
			}
			Rank_Score_Render.Update();
			Score_comma.SetPosition(Vector3{ 440.0f,13.0f,0.0f });
			Score_comma.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, b[1][0]));
		}
		
		
	}
	fast_count++;

	//更新
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 10; j++) {
			Time_Num[i][j].Update();
		}
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			Score_Num[i][j].Update();
		}
	}
	for (int i = 1; i <= 4; i++) {
		Rank_Render[i - 1].SetScale(Rank_Scale);
		Rank_Render[i - 1].SetMulColor(Rank_color);
		Rank_Render[i - 1].Update();
	}
	Rank_sheet.Update();
	
	Box_render.Update();
	Player_modelrender.Update();
}

void Result::Font_set() {

	//タイム関連の初期化
	time_Render.Init("Assets/sprite/time.DDS", 1632.0f, 918.0f);//タイムの文字の読み込み
	Time_colon.Init("Assets/sprite/colon.DDS", 73.1f, 136.85f);//タイムの:の読み込み
	//タイムの数字の読み込み
	for (int i = 0; i < 4; i++) {
		a[i][0] = 0;
		for (int j = 0; j < 10; j++) {
			Time_Num[i][j].Init(getString(j), 86.0f, 161.0f);
		}
	}
	//ポジションの設定
	for (int i = 0; i < 10; i++) {
		Time_Num[0][i].SetPosition(Time_0_position);
		Time_Num[1][i].SetPosition(Time_1_position);
		Time_Num[2][i].SetPosition(Time_3_position);
		Time_Num[3][i].SetPosition(Time_4_position);
	}
	Time_colon.SetPosition(Time_2_position);
	//更新
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 10; j++) {
			Time_Num[i][j].Update();
		}
	}


	//SCOREの設定
	time_set[0] = minute / 10;//分10の位
	time_set[1] = minute % 10;//分1の位
	time_set[2] = sec / 10;//秒10の位
	time_set[3] = sec % 10;//秒1の位
	SCORE = (10 - minute) * 1000 + (60 - sec) * 10;//SCOREの計算
	MAX_SCORE = 10 * 1000 + 60 * 10;//マックスSCOREの計算
	//SCOREの各桁がどれだけあるかの計算
	while (SCORE >= 10000) {
		score_set[0]++;
		SCORE -= 10000;
		Total += 10000;
	}
	while (SCORE >= 1000) {
		score_set[1]++;
		SCORE -= 1000;
		Total += 1000;
	}
	while (SCORE >= 100) {
		score_set[2]++;
		SCORE -= 100;
		Total += 100;
	}
	while (SCORE >= 10) {
		score_set[3]++;
		SCORE -= 10;
		Total += 10;
	}
	while (SCORE >= 1) {
		score_set[4]++;
		SCORE -= 1;
		Total += 1;
	}

	Score_Render.Init("Assets/sprite/score.DDS", 1632.0f, 918.0f);//SCOREの文字の読み込み
	Score_comma.Init("Assets/sprite/,.DDS", 73.1f, 136.85f);//SCOREの、の読み込み
	//SCOREの数字の読み込み
	for (int i = 0; i < 5; i++) {
		b[i][0] = 0;
		for (int j = 0; j < 10; j++) {
			Score_Num[i][j].Init(getString(j), 86.0f, 161.0f);
		}
	}
	//ポジション設定
	for (int i = 0; i < 10; i++) {
		Score_Num[0][i].SetPosition(Score_0_position);
		Score_Num[1][i].SetPosition(Score_1_position);
		Score_Num[2][i].SetPosition(Score_3_position);
		Score_Num[3][i].SetPosition(Score_4_position);
		Score_Num[4][i].SetPosition(Score_5_position);
	}
	Score_comma.SetPosition(Score_2_position);
	//更新
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			Score_Num[i][j].Update();
		}
	}
	Score_comma.Update();
	Time_colon.Update();

	//ランクの設定
	Rank_Time_Render.Init("Assets/sprite/time_rank.DDS", 1632.0f, 918.0f);
	Rank_Time_Render.SetMulColor(Rank_Time_color);
	Rank_Score_Render.Init("Assets/sprite/SCORE_rank.DDS", 1632.0f, 918.0f);
	Rank_Score_Render.SetMulColor(Rank_Score_color);
	Rank_sheet.Init("Assets/sprite/Rank.DDS", 1632.0f, 918.0f);//ランクの文字の読み込み
	Rank_sheet.SetPosition(Rank_position);
	Rank_sheet.SetMulColor(Rank_Sheet_color);
	MAX_SCORE /= 4;//ランクが四段階のため
	//今回何ランクだったかの計算
	for (int i = 1; i <= 4; i++) {
		Rank_Render[i - 1].Init(getRank(i-1), 1632.0f, 918.0f);
		Rank_Render[i - 1].SetScale(Rank_Scale);
		Rank_Render[i - 1].SetMulColor(Rank_color);
		if (Total>MAX_SCORE * i) {
			Rank_set++;
		}
		Rank_Render[i - 1].Update();
	}

	Rank_Score_Render.Update();
	Rank_Time_Render.Update();
	Rank_sheet.Update();
}


void Result::Back_set() { //モデルの読み込み
	//プレイヤー
	Player_modelrender.Init("Assets/modelData/Player.tkm");
	Player_modelrender.SetPosition(Player_position);
	Player_rotation.SetRotationDegY(-135.0f);
	Player_modelrender.SetRotation(Player_rotation);
	Player_modelrender.Update();

	//背景
	Box_render.Init("Assets/modelData/Customize_area.tkm");
	Box_render.SetPosition(Box_position);
	Box_render.SetScale(Box_scale);
	Box_render.Update();

	//カメラの設定
	gamecamera->m_toCameraPos.Set(0.0f, -10.0f, -100.0f);
	gamecamera->fast_count = 0;
	gamecamera->target = { 10000.0f,20.0f,0.0f };
	gamecamera->CameraState = 3;

	//コアウェポンの設定
	custom_model_Core.Init("Assets/modelData/Versatile_Perforator.tkm");
	

	//肩
	if (p_custom_point[0][1] != 0)	
	{
		//武器によってモデルを変える
		switch (p_custom_point[0][1])
		{
		case 2:	//マシンガン
			//モデルの初期化
			custom_model_shoulder.Init("Assets/modelData/machine_gun_drop.tkm");
			//モデルの大きさの設定
			custom_model_shoulder.SetScale(scale2);



			break;
		case 4:	//ギガトンキャノン
			//モデルの初期化
			custom_model_shoulder.Init("Assets/modelData/GIgaton_cannon.tkm");
			//モデルの大きさの設定
			custom_model_shoulder.SetScale(1.0f);



			break;

		case 6:	//戦艦砲
			//モデルの初期化
			custom_model_shoulder.Init("Assets/modelData/battleship_gun_shoulder.tkm");
			//モデルの大きさの設定
			custom_model_shoulder.SetScale(scale2);


			break;
		default:
			break;
		}
		
	}

	//右腕
	if (p_custom_point[0][0] != 0)	
	{
		//武器によってモデルを変える
		switch (p_custom_point[0][0])
		{
		case 2:	//マシンガン
			//モデルの初期化
			custom_model_Right_arm.Init("Assets/modelData/machine_gun_drop.tkm");
			//モデルの大きさの設定
			custom_model_Right_arm.SetScale(scale2);
			

			break;
		case 4:	//ギガトンキャノン
			//モデルの初期化
			custom_model_Right_arm.Init("Assets/modelData/GIgaton_cannon.tkm");
			

			break;
		case 6:	//戦艦砲
			//モデルの初期化
			custom_model_Right_arm.Init("Assets/modelData/battleship_gun_right_arm.tkm");
			

			break;
		default:
			break;
		}
		custom_model_Right_arm.Update();
	}

	//右足
	if (p_custom_point[1][0] != 0)	
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
		switch (p_custom_point[1][0])
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

	//左腕
	if (p_custom_point[0][2] != 0)	
	{
		switch (p_custom_point[0][2]) {
		case 2:	//マシンガン
			//モデルの初期化
			custom_model_Left_arm.Init("Assets/modelData/machine_gun_drop.tkm");
			//モデルの大きさの設定
			custom_model_Left_arm.SetScale(scale2);
			

			break;
		case 4:	//ギガトンキャノン
			//モデルの初期化
			custom_model_Left_arm.Init("Assets/modelData/GIgaton_cannon.tkm");
			//モデルの大きさの設定
			custom_model_Left_arm.SetScale(1.0f);
			

			break;

		case 6:	//戦艦砲
			//モデルの初期化
			custom_model_Left_arm.Init("Assets/modelData/battleship_gun_left_arm.tkm");
			//モデルの大きさの設定
			custom_model_Left_arm.SetScale(scale2);
			


			break;
		default:
			break;
		}
		custom_model_Left_arm.Update();
	}

	//左足
	if (p_custom_point[1][2] != 0)	
	{
		//武器によってモデルを変える
		switch (p_custom_point[1][2])
		{
		case 2:	//マシンガン
			//モデルの初期化
			custom_model_Left_leg.Init("Assets/modelData/machine_gun_drop.tkm");
			//モデルの大きさの設定
			custom_model_Left_leg.SetScale(scale2);
			

			break;
		case 4:	//ギガトンキャノン
			//モデルの初期化
			custom_model_Left_leg.Init("Assets/modelData/GIgaton_cannon.tkm");
			//モデルの大きさの設定
			custom_model_Left_leg.SetScale(1.0f);
			

			break;

		case 6:	//戦艦砲
			//モデルの初期化
			custom_model_Left_leg.Init("Assets/modelData/battleship_gun_left_leg01.tkm");
			//モデルの大きさの設定
			custom_model_Left_leg.SetScale(scale2);
			

			break;
		default:
			break;
		}
		custom_model_Left_leg.Update();
	}
}
void Result::BackGround()
{
	//コアウェポンの動き
	cw_lp = { 0.0f,80.0f,10.0f };
	Quaternion originRotation = Player_rotation;
	Vector3 cw_position = Player_position;


	originRotation.Multiply(cw_lp);
	cw_position += cw_lp;
	Quaternion cw_Rotation = originRotation;

	custom_model_Core.SetRotation(cw_Rotation);
	custom_model_Core.SetPosition(cw_position);
	custom_model_Core.Update();
		
	//肩
	if (p_custom_point[0][1] != 0)
	{
		//移動の処理
		Quaternion originRotation = Player_rotation;
		Vector3 sw_position = Player_position;
		originRotation.Multiply(sw_lp);
		sw_position += sw_lp;
		Quaternion sw_Rotation = originRotation;

		//更新
		custom_model_shoulder.SetRotation(sw_Rotation);
		custom_model_shoulder.SetPosition(sw_position);

		//武器によってモデルを変える
		switch (p_custom_point[0][1])
		{
		case 2:	//マシンガン
			
			//モデルの大きさの設定
			custom_model_shoulder.SetScale(scale2);
			//ローカルポジションの設定
			sw_lp = { 0.0f,110.0f,0.0f };


			break;
		case 4:	//ギガトンキャノン
			
			//モデルの大きさの設定
			custom_model_shoulder.SetScale(1.0f);
			//ローカルポジションの設定
			sw_lp = { 0.0f,110.0f,0.0f };


			break;

		case 6:	//戦艦砲
			
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
		
	//右腕
	if (p_custom_point[0][0] != 0)
	{
		//移動の処理
		Quaternion originRotation = Player_rotation;
		Vector3 raw_position = Player_position;
		originRotation.Multiply(raw_lp);
		raw_position += raw_lp;
		Quaternion raw_Rotation = originRotation;

		//更新
		custom_model_Right_arm.SetRotation(raw_Rotation);
		custom_model_Right_arm.SetPosition(raw_position);

		//武器によってモデルを変える
		switch (p_custom_point[0][0])
		{
		case 2:	//マシンガン
			//モデルの大きさの設定
			custom_model_Right_arm.SetScale(scale2);
			//ローカルポジションの設定
			raw_lp = { 60.0f,100.0f,-10.0f };

			break;
		case 4:	//ギガトンキャノン
			
			//モデルの大きさの設定
			custom_model_Right_arm.SetScale(1.0f);
			//ローカルポジションの設定
			raw_lp = { 60.0f,100.0f,-10.0f };

			break;
		case 6:	//戦艦砲
			
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
		
	//右足
	if (p_custom_point[1][0] != 0)
	{
		//移動の処理
		Quaternion originRotation = Player_rotation;
		Vector3 rlw_position = Player_position;
		originRotation.Multiply(rlw_lp);
		rlw_position += rlw_lp;
		Quaternion rlw_Rotation = originRotation;

		//更新
		custom_model_Right_leg.SetRotation(rlw_Rotation);
		custom_model_Right_leg.SetPosition(rlw_position);

		//武器によってモデルを変える
		switch (p_custom_point[1][0])
		{
		case 2:	//マシンガン
			//モデルの大きさの設定
			custom_model_Right_leg.SetScale(scale2);
			//ローカルポジションの設定
			rlw_lp = { 90.0f,30.0f,0.0f };

			break;
		case 4:	//ギガトンキャノン
			//モデルの大きさの設定
			custom_model_Right_leg.SetScale(1.0f);
			//ローカルポジションの設定
			rlw_lp = { 90.0f,30.0f,0.0f };

			break;

		case 6:	//戦艦砲
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
	
	//左腕
	if (p_custom_point[0][2] != 0)
	{

		//移動の処理
		Quaternion originRotation = Player_rotation;
		Vector3 law_position = Player_position;
		originRotation.Multiply(law_lp);
		law_position += law_lp;
		Quaternion law_Rotation = originRotation;

		//更新
		custom_model_Left_arm.SetRotation(law_Rotation);
		custom_model_Left_arm.SetPosition(law_position);
		switch (p_custom_point[0][2]) {
		case 2:	//マシンガン
			//モデルの大きさの設定
			custom_model_Left_arm.SetScale(scale2);
			//ローカルポジションの設定
			law_lp = { -60.0f,100.0f,-10.0f };

			break;
		case 4:	//ギガトンキャノン
			//モデルの大きさの設定
			custom_model_Left_arm.SetScale(1.0f);
			//ローカルポジションの設定
			law_lp = { -60.0f,100.0f,-10.0f };

			break;

		case 6:	//戦艦砲
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

	//左足
	if (p_custom_point[1][2] != 0)
	{
		//移動の処理
		Quaternion originRotation = Player_rotation;
		Vector3 llw_position = Player_position;
		originRotation.Multiply(llw_lp);
		llw_position += llw_lp;
		Quaternion llw_Rotation = originRotation;

		//更新
		custom_model_Left_leg.SetRotation(llw_Rotation);
		custom_model_Left_leg.SetPosition(llw_position);

		//武器によってモデルを変える
		switch (p_custom_point[1][2])
		{
		case 2:	//マシンガン

			//モデルの大きさの設定
			custom_model_Left_leg.SetScale(scale2);
			//ローカルポジションの設定
			llw_lp = { -90.0f,30.0f,0.0f };

			break;
		case 4:	//ギガトンキャノン
			//モデルの大きさの設定
			custom_model_Left_leg.SetScale(1.0f);
			//ローカルポジションの設定
			llw_lp = { -90.0f,30.0f,0.0f };

			break;

		case 6:	//戦艦砲

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


void Result::Enemy_count()
{

}




void Result::Render(RenderContext& rc)
{	
	//各部位に装備されているならDrawする
	custom_model_Core.Draw(rc);				//コア武器はずっと存在するので分岐なし
	Player_modelrender.Draw(rc);				//胴体はずっと存在するので分岐なし
	if (p_custom_point[0][0] !=0)
	{
		custom_model_Right_arm.Draw(rc);	//右腕
	}
	if (p_custom_point[0][2] != 0)
	{
		custom_model_Left_arm.Draw(rc);		//左腕
	}
	if (p_custom_point[0][1] != 0)
	{
		custom_model_shoulder.Draw(rc);		//肩
	}
	if (p_custom_point[1][0] != 0)
	{
		custom_model_Right_leg.Draw(rc);	//右足
	}
	if (p_custom_point[1][2] != 0)
	{
		custom_model_Left_leg.Draw(rc);		//左足
	}

	Box_render.Draw(rc);

	if (Neo_result_state == 0) {
		time_Render.Draw(rc);
		for (int i = 0; i < 4; i++) {
			Time_Num[i][time_set[i]].Draw(rc);
		}
		Time_colon.Draw(rc);
	}
	if (Neo_result_state == 1) {
		Score_Render.Draw(rc);
		for (int i = 0; i < 5; i++) {
			Score_Num[i][score_set[i]].Draw(rc);
		}
		Score_comma.Draw(rc);
	}
	if (Neo_result_state == 2) {
		Rank_Render[Rank_set].Draw(rc);
		Rank_sheet.Draw(rc);

		Rank_Time_Render.Draw(rc);
		for (int i = 0; i < 4; i++) {
			Time_Num[i][time_set[i]].Draw(rc);
		}
		Time_colon.Draw(rc);

		Rank_Score_Render.Draw(rc);
		for (int i = 0; i < 5; i++) {
			Score_Num[i][score_set[i]].Draw(rc);
		}
		Score_comma.Draw(rc);
	}
}