#include "stdafx.h"
#include "Title.h"
#include "Game.h"
//#include "Fade.h"
#include "Lighting.h"

Title::Title()
{
	//title_Render.Init("Assets/sprite/title_test.dds", 1920.0f, 1080.0f);
	//gameStart_Render.Init("Assets/sprite/title/gameStart.dds", /*1920.0f, 1080.0f*/);
	////system_Render.Init("Assets/sprite/title/system.dds", /*1920.0f, 1080.0f*/);
	////nannka_Render.Init("Assets/sprite/title/nannka.dds", /*1920.0f, 1080.0f*/);
	//yajirusi_Render.Init("Assets/sprite/title/yajirusi/dds", /*1920.0f, 1080.0f*/);
	SetUp();
	Lighting* lighting = NewGO<Lighting>(1, "lighting");
	title_Render.SetScale(title_scale);
}

Title::~Title()
{

}

bool Title::Start() {
	return true;
}
void Title::SetUp()
{
	//m_fade = FindGO<Fade>("fade");
	//m_fade->StartFadeIn();
	//モデルの読み込み
	model_batt.Init("Assets/modelData/battleship_gun_Drop.tkm");
	model_batt.SetScale(scale);
	model_mac.Init("Assets/modelData/machine_gun_drop.tkm");
	model_mac.SetScale(scale);
	model_giga.Init("Assets/modelData/Giga_Plasma.tkm");
	model_giga.SetScale(scale);

	title_back.Init("Assets/modelData/title_back.tkm");
	
	//画像の読み込み
	MAIN_MENU_Render.Init("Assets/sprite/MAIN_MENU.DDS", 1632.0f, 918.0f);
	Title_Render.Init("Assets/sprite/title.DDS", 1632.0f, 918.0f);
	Press_Render.Init("Assets/sprite/Press_any_button.DDS", 1632.0f, 918.0f);
	Whiteout.Init("Assets/sprite/whiteout.DDS", 1632.0f, 918.0f);
	Side_line_Render.Init("Assets/sprite/side_line.DDS", 1632.0f, 918.0f);
	OK_BACK_Render.Init("Assets/sprite/OK_BACK.DDS", 1632.0f, 918.0f);
	Main_menu_foundation_Render.Init("Assets/sprite/brack_back.DDS", 1632.0f, 918.0f);
	Select_point_Render.Init("Assets/sprite/select_point.DDS", 1632.0f, 918.0f);
	Select_point_pow_Render.Init("Assets/sprite/select_point_pow.DDS", 1632.0f, 918.0f);
	Loading_Render.Init("Assets/sprite/NOW_LOADING.DDS", 1632.0f, 918.0f);

	Option_Render.Init("Assets/sprite/OPTION.DDS", 1632.0f, 918.0f);
	Sound_Render.Init("Assets/sprite/SOUND.DDS", 1632.0f, 918.0f);
	BGM_Sound_ber.Init("Assets/sprite/gage.DDS", 400.0f, 50.0f);
	BGM_Sound_ber.SetPivot(BGM_ber_pivot);
	BGM_Sound_ber.SetPosition(BGM_ber_position);
	SE_Sound_ber.Init("Assets/sprite/gage.DDS", 400.0f, 50.0f);
	SE_Sound_ber.SetPivot(SE_ber_pivot);
	SE_Sound_ber.SetPosition(SE_ber_position);

	CONTROLES_Render.Init("Assets/sprite/CONTROLES.DDS", 1632.0f, 918.0f);

	Menu_trance[0].Init("Assets/sprite/MENU_contents_TRANCE.DDS", 430.0f, 100.0f);
	for (int i = 1; i < 9; i++) {
		Menu_trance[i].Init("Assets/sprite/MENU_TITLE_TRANCE.DDS", 670.0f, 63.0f);
	}

	Menu_trance[0].SetPosition(Menu_trance_position0);
	Menu_trance[1].SetPosition(Menu_trance_position1);
	Menu_trance[2].SetPosition(Menu_trance_position2);
	Menu_trance[3].SetPosition(Menu_trance_position3);
	Menu_trance[4].SetPosition(Menu_trance_position4);
	Menu_trance[5].SetPosition(Menu_trance_position5);
	Menu_trance[6].SetPosition(Menu_trance_position6);
	Menu_trance[7].SetPosition(Menu_trance_position7);
	Menu_trance[8].SetPosition(Menu_trance_position8);

	Menu_trance[0].SetPivot(Menu_trance_pivot0);
	Menu_trance[1].SetPivot(Menu_trance_pivot1);
	Menu_trance[2].SetPivot(Menu_trance_pivot2);
	Menu_trance[3].SetPivot(Menu_trance_pivot3);
	Menu_trance[4].SetPivot(Menu_trance_pivot4);
	Menu_trance[5].SetPivot(Menu_trance_pivot5);
	Menu_trance[6].SetPivot(Menu_trance_pivot6);
	Menu_trance[7].SetPivot(Menu_trance_pivot7);
	Menu_trance[8].SetPivot(Menu_trance_pivot8);

	for (int i = 0; i < 9;i++ ) {
		Menu_trance[i].SetScale(Trance_sheet_scale);
		Menu_trance[i].Update();
	}
	BGM_Sound_ber.Update();
	SE_Sound_ber.Update();
	Loading_Render.SetMulColor(Loading_color);
	Loading_Render.Update();

}

void Title::Update()
{
	if (title_state == 0|| title_state == 1) {
		Title_Move();
	}
	if (title_state >= 2) {
		Menu();
	}

	if (pattern == 0)//迫ってくるbattをその場で眼だけで追う。
	{
		model_position.x += 0.6f;
		model_batt.SetPosition(model_position);

		y_Rot.SetRotationDegY(120.0f);
		x_Rot.SetRotationDegX(-25.0f);
		m_Rot = x_Rot * y_Rot;
		model_batt.SetRotation(m_Rot);

		target = model_position;
		target.x += 50.0f;
		g_camera3D->SetTarget(target);
		pos = { 0.0f,-50.0f,-00.0f };
		g_camera3D->SetPosition(pos);
	}
	else if (pattern == 1)//上前からmacを後ろまで追っていく感じ。
	{
		model_mac.SetPosition(model_position);

		y_Rot.SetRotationDegY(100.0f);
		model_mac.SetRotation(y_Rot);

		pos.x -= 1.2f;
		target.x -= 1.20f;
		g_camera3D->SetTarget(target);
		g_camera3D->SetPosition(pos);
	}
	else if (pattern == 2)//ローアングルからgigaを見上げる感じで。
	{
		model_position.z -= 0.5f;
		//model_batt.SetPosition(model_position);
		//model_mac.SetPosition(model_position);
		model_giga.SetPosition(model_position);

		y_Rot.SetRotationDegY(180.0f);
		x_Rot.SetRotationDegX(-15.0f);
		m_Rot = x_Rot * y_Rot;
		//model_batt.SetRotation(m_Rot);
		//model_mac.SetRotation(m_Rot);
		model_giga.SetRotation(m_Rot);

		g_camera3D->SetTarget(model_position);
		pos = { 0.0f,-50.0f,-00.0f };
		g_camera3D->SetPosition(pos);
	}

	model_batt.Update();
	model_mac.Update();
	model_giga.Update();
	title_back.SetPosition(titel_back);

	title_back.Update();

	m_timer += g_gameTime->GetFrameDeltaTime();
	switch (time)
	{
	case 0:
		if (m_timer >=10.0f)
		{
			time = 1;
			model_position = { -300.0f,00.0f,200.0f };
			target = { -300.0f,-50.0f,500.0f };
			pos = { 600.0f,100.0f,100.0f };
			pattern = 1;
			m_timer = 0.0f;
		}
		break;
	case 1:
		if (m_timer >= 10.0f)
		{
			time = 2;
			model_position = { 0.0f,00.0f,200.0f };
			pattern = 2;
			m_timer = 0.0f;
		}
		break;
	case 2:
		if (m_timer >= 10.0f)
		{
			time = 0;
			model_position= { -300.0f,50.0f,200.0f };
			pattern = 0;
			m_timer = 0.0f;
		}
		break;
	}
	
	if (State == 0/*&& g_pad[0]->IsTrigger(enButtonA)*/ )
	{
		
		//ゲーム本編への遷移
		//if (g_pad[0]->IsTrigger(enButtonA))
		//{
		//	Game* game = NewGO<Game>(0, "game");
		//	//player->game_state = 0;
		//	//gameCamera->CameraState = 0;
		//	DeleteGO(this);
		//}
	
	}
	
}

void Title::Title_Move() {
	Whiteout.SetMulColor(whiteout_color);
	if (Press_count % 100 == 0) {
		Press_direction *= -1;
	}
	Press_Render_coler.w -= 0.01*Press_direction;
	Press_Render.SetMulColor(Press_Render_coler);

	if (g_pad[0]->IsTrigger(enButtonA)) {
		
		title_state = 1;
	}
	if (title_state == 1) {
		whiteout_color.w += 0.1;
		if (whiteout_count == 9) {
			title_state = 2;
		}
		whiteout_count++;
		Whiteout.SetMulColor(whiteout_color);
	}
	

	Press_count++;
	Press_Render.Update();
	Whiteout.Update();
}

void Title::Menu() {
	//遷移
	if (title_state == 2) {
		whiteout_color.w -= 0.1;
		if (whiteout_count == 18) {
			title_state = 3;
			select_point = 0;
			fast_count = 0;
		}
		whiteout_count++;
	}

	if (Select_point_pow_count % 100 == 0) {
		Select_point_pow_direction *= -1;
	}
	Select_point_pow_color.w -= 0.02 * Select_point_pow_direction;
	Select_point_pow_Render.SetMulColor(Select_point_pow_color);
	Select_point_pow_count++;

	//メインメニュー
	if (title_state == 3) {
		if (fast_count >= 1 && fast_count < 11) {
			Trance_sheet_scale.x += 0.085f;
		}
		else if (fast_count >= 11 && fast_count < 21) {
			Trance_sheet_scale.x -= 0.085f;
		}


		if (select_point >= 0 &&select_point<=1&& g_pad[0]->IsTrigger(enButtonDown)) {
			select_point++;
		}
		if (select_point <= 2 && select_point >= 1 && g_pad[0]->IsTrigger(enButtonUp)) {
			select_point--;
		}
		if (g_pad[0]->IsTrigger(enButtonA) && fast_count != 1&&select_point==0) {
			title_state = 4;
		}
		if (g_pad[0]->IsTrigger(enButtonA) && fast_count != 1 && select_point== 1) {
			
			select_point = 0;
			fast_count = 0;
			title_state = 5;
			
		}
		if (g_pad[0]->IsTrigger(enButtonB)) {
			title_state = 0;
			whiteout_count = 0;
			select_point = 0;
			fast_count = 0;
		}
		fast_count++;


		for (int i = 0; i < 9; i++) {
			Menu_trance[i].SetScale(Trance_sheet_scale);
		}
		Menu_trance[0].Update();
		Menu_trance[9].Update();
		for (int i = 1; i < 4; i++) {
			Menu_trance[i].Update();
		}
	}
	if (title_state == 4) {
		Loading_color.w += 0.1;
		Loading_Render.SetMulColor(Loading_color);
		Loading_Render.Update();
		if (Loading_color.w >= 1.1f) 
		{
			//ゲームを始めると同時に音量のデータも送る
			Game* game = NewGO<Game>(0, "game");
			game->SEvol = BGM_volume;
			game->BGMvol = SE_volume;
			DeleteGO(this);
		}
	}

	if (title_state == 5) {
		if (fast_count >= 1 && fast_count < 11) {
			Trance_sheet_scale.x += 0.085f;
		}
		else if (fast_count >= 11 && fast_count < 21) {
			Trance_sheet_scale.x -= 0.085f;
		}

		if (select_point >= 0 && select_point <= 0 && g_pad[0]->IsTrigger(enButtonDown)) {
			select_point++;
		}
		if (select_point <= 1 && select_point >= 1 && g_pad[0]->IsTrigger(enButtonUp)) {
			select_point--;
		}
		if (g_pad[0]->IsTrigger(enButtonA) && fast_count != 1&& select_point==0) {
			title_state = 6;
			select_point = 0;
			fast_count = 0;
		}
		if (g_pad[0]->IsTrigger(enButtonA) && fast_count != 1 && select_point == 1) {
			title_state = 7;
			select_point = 0;
			fast_count = 0;
		}
		if (g_pad[0]->IsTrigger(enButtonB)) {
			title_state = 3;
			select_point = 0;
			fast_count = 0;
		}
		fast_count++;

		for (int i = 0; i < 9; i++) {
			Menu_trance[i].SetScale(Trance_sheet_scale);
		}
		Menu_trance[0].Update();
		Menu_trance[9].Update();
		for (int i = 1; i < 3; i++) {
			Menu_trance[i].Update();
		}
	}

	if (title_state == 6) {
		if (fast_count >= 1 && fast_count < 11) {
			Trance_sheet_scale.x += 0.085f;
		}
		else if (fast_count >= 11 && fast_count < 21) {
			Trance_sheet_scale.x -= 0.085f;
		}

		if (select_point >= 0 && select_point <= 0 && g_pad[0]->IsTrigger(enButtonDown) && sound_set_state == 0) {
			select_point++;
		}
		if (select_point <= 1 && select_point >= 1 && g_pad[0]->IsTrigger(enButtonUp) && sound_set_state == 0) {
			select_point--;
		}
		if (g_pad[0]->IsTrigger(enButtonA) && fast_count != 1 && select_point == 0&&sound_set_state==0) {
			sound_set_state = 1;
		}
		if (g_pad[0]->IsTrigger(enButtonA) && fast_count != 1 && select_point == 1 && sound_set_state == 0) {
			sound_set_state = 2;
		}

		if (g_pad[0]->IsTrigger(enButtonB)) {
			title_state = 5;
			select_point = 0;
			fast_count = 0;
		}

		if (g_pad[0]->IsPress(enButtonRight) && sound_set_state == 1) {
			BGM_volume += 0.01;
			BGM_ber_scale.x += 0.0085;
			if (BGM_volume >= 1.0f) {
				BGM_volume = 1.0f;
				BGM_ber_scale.x = 0.85f;
			}
		}
		else if (g_pad[0]->IsPress(enButtonLeft) && sound_set_state == 1) {
			BGM_volume -= 0.01;
			BGM_ber_scale.x -= 0.0085;
			if (BGM_volume <= 0.0f) {
				BGM_volume = 0.0f;
				BGM_ber_scale.x = 0.0f;
			}
		}

		if (g_pad[0]->IsPress(enButtonRight) && sound_set_state == 2) {
			SE_volume += 0.01;
			SE_ber_scale.x += 0.0085;
			if (SE_volume >= 1.0f) {
				SE_volume = 1.0f;
				SE_ber_scale.x = 0.85f;
			}
		}
		else if (g_pad[0]->IsPress(enButtonLeft) && sound_set_state == 2) {
			SE_volume -= 0.01;
			SE_ber_scale.x -= 0.0085;
			if (SE_volume <= 0.0f) {
				SE_volume = 0.0f;
				SE_ber_scale.x = 0.0f;
			}
		}

		if (g_pad[0]->IsTrigger(enButtonB) && fast_count != 1 && select_point == 0 && sound_set_state == 1) {
			sound_set_state = 0;
		}
		if (g_pad[0]->IsTrigger(enButtonB) && fast_count != 1 && select_point == 2 && sound_set_state == 2) {
			sound_set_state = 0;
		}
		fast_count++;

		BGM_Sound_ber.SetScale(BGM_ber_scale);
		SE_Sound_ber.SetScale(SE_ber_scale);

		BGM_Sound_ber.Update();
		SE_Sound_ber.Update();

		for (int i = 0; i < 9; i++) {
			Menu_trance[i].SetScale(Trance_sheet_scale);
		}
		Menu_trance[0].Update();
		Menu_trance[9].Update();
		for (int i = 1; i < 3; i++) {
			Menu_trance[i].Update();
		}
	}

	if (title_state == 7) {
		if (fast_count >= 1 && fast_count < 11) {
			Trance_sheet_scale.x += 0.085f;
		}
		else if (fast_count >= 11 && fast_count < 21) {
			Trance_sheet_scale.x -= 0.085f;
		}

		if (select_point >= 0 && select_point <= 6 && g_pad[0]->IsTrigger(enButtonDown)) {
			select_point++;
		}
		if (select_point <= 7 && select_point >= 1 && g_pad[0]->IsTrigger(enButtonUp)) {
			select_point--;
		}
		
		if (g_pad[0]->IsTrigger(enButtonB)) {
			title_state = 5;
			select_point = 0;
			fast_count = 0;
		}
		for (int i = 0; i < 9; i++) {
			Menu_trance[i].SetScale(Trance_sheet_scale);
		}
		fast_count++;
		Menu_trance[0].Update();
		Menu_trance[9].Update();
		for (int i = 1; i < 9; i++) {
			Menu_trance[i].Update();
		}
	}

	//セレクトポイントの処理
	if (title_state >= 3) {
		switch (select_point)
		{
		case 0:
			Select_position = { 0.0f,0.0f,0.0f };
			Select_point_Render.SetPosition(Select_position);
			Select_point_pow_Render.SetPosition(Select_position);
			break;
		case 1:
			Select_position = { 0.0f,-67.5f,0.0f };
			Select_point_Render.SetPosition(Select_position);
			Select_point_pow_Render.SetPosition(Select_position);
			break;
		case 2:
			Select_position = { 0.0f,-135.0f,0.0f };
			Select_point_Render.SetPosition(Select_position);
			Select_point_pow_Render.SetPosition(Select_position);
			break;
		case 3:
			Select_position = { 0.0f,-202.5f,0.0f };
			Select_point_Render.SetPosition(Select_position);
			Select_point_pow_Render.SetPosition(Select_position);
			break;
		case 4:
			Select_position = { 0.0f,-270.0f,0.0f };
			Select_point_Render.SetPosition(Select_position);
			Select_point_pow_Render.SetPosition(Select_position);
			break;
		case 5:
			Select_position = { 0.0f,-337.5f,0.0f };
			Select_point_Render.SetPosition(Select_position);
			Select_point_pow_Render.SetPosition(Select_position);
			break;
		case 6:
			Select_position = { 0.0f,-405.0f,0.0f };
			Select_point_Render.SetPosition(Select_position);
			Select_point_pow_Render.SetPosition(Select_position);
			break;
		default:
			break;
		}
	}

	Select_point_Render.Update();
	Select_point_pow_Render.Update();
	Main_menu_foundation_Render.SetMulColor(Main_menu_foundation_Render_color);
	Whiteout.SetMulColor(whiteout_color);
	Main_menu_foundation_Render.Update();
	Whiteout.Update();
}

void Title::S()
{
	if (State == 0 && g_pad[0]->IsTrigger(enButtonDown))
	{
		State = 1;
	}

	if (State == 1 && g_pad[0]->IsTrigger(enButtonUp))
	{
		State = 0;
	}
	else if (State == 1 && g_pad[0]->IsTrigger(enButtonDown))
	{
		State = 2;
	}

	if (State == 2 && g_pad[0]->IsTrigger(enButtonUp))
	{
		State = 1;
	}

	//矢印の置き場所。
	if (State == 0)
	{
		gameStart_Render.SetPosition({ -280.0f,10.0f,0.0f });
	}
	if (State == 1)
	{
		system_Render.SetPosition({ -280.0f,-120.0f,0.0f });
	}
	if (State == 2)
	{
		nannka_Render.SetPosition({ -280.0f,-250.0f,0.0f });
	}
}

void Title::Render(RenderContext& rc)
{
	//title_Render.Draw(rc);
	//gameStart_Render.Draw(rc);
	///system_Render.Draw(rc);
	///nannka_Render.Draw(rc);
	//yajirusi_Render.Draw(rc);
	//player->player_modelRender.Draw(rc);
	title_back.Draw(rc);
	if (pattern == 0)
	{
		model_batt.Draw(rc);
	}
	else if (pattern == 1)
	{
		model_mac.Draw(rc);
	}
	else if (pattern == 2)
	{
		model_giga.Draw(rc);
	}

	//画像のドロー
	if (title_state == 0||title_state==1) {
		Title_Render.Draw(rc);
		Press_Render.Draw(rc);
	}
	if (title_state >= 3) {
		
		Main_menu_foundation_Render.Draw(rc);
		Side_line_Render.Draw(rc);
		OK_BACK_Render.Draw(rc);
		Select_point_Render.Draw(rc);
		Select_point_pow_Render.Draw(rc);
	}
	if (title_state == 3) {
		MAIN_MENU_Render.Draw(rc);
	}

	if (title_state == 4) {
		Loading_Render.Draw(rc);
	}

	if (title_state == 5) {
		Option_Render.Draw(rc);
	}
	if (title_state == 6) {
		Sound_Render.Draw(rc);
		BGM_Sound_ber.Draw(rc);
		SE_Sound_ber.Draw(rc);
	}
	if (title_state == 7) {
		CONTROLES_Render.Draw(rc);
	}
	
	/*for(int i = 0; i < 9; i++) {
		Menu_trance[i].Draw(rc);
	}*/

	Whiteout.Draw(rc);
}