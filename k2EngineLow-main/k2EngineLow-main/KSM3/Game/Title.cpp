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

	Lighting* lighting = NewGO<Lighting>(1, "lighting");

	title_Render.SetScale(title_scale);
}

Title::~Title()
{

}

bool Title::Start()
{
	//m_fade = FindGO<Fade>("fade");
	//m_fade->StartFadeIn();
	model_batt.Init("Assets/modelData/battleship_gun_Drop.tkm");
	model_batt.SetScale(scale);
	model_mac.Init("Assets/modelData/machine_gun_drop.tkm");
	model_mac.SetScale(scale);
	model_giga.Init("Assets/modelData/Giga_Plasma.tkm");
	model_giga.SetScale(scale);

	title_back.Init("Assets/modelData/title_back.tkm");
	
	return true;
}

void Title::Update()
{
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
		//if (m_isWaitFadeout)
		//{
		//	if (!m_fade->IsFade())
		//	{
				//ゲーム本編への遷移
				if (g_pad[0]->IsTrigger(enButtonA))
				{
					Game* game = NewGO<Game>(0, "game");
					//player->game_state = 0;
					//gameCamera->CameraState = 0;
					DeleteGO(this);
				}
		//	}
		//}
		//else 
		//{
		//	if (g_pad[0]->IsTrigger(enButtonA)) 
		//	{
		//		m_isWaitFadeout = true;
		//		m_fade->StartFadeOut();
		//		//SoundSource* se = NewGO<SoundSource>(0);
		//		//se->Init(1);
		//		//se->Play(false);
		//	}
		//}
	}
	//α値の変化。???
	//if (m_isWaitFadeout)
	//{
	//	m_alpha += g_gameTime->GetFrameDeltaTime() * 20.5f;
	//}
	//else
	//{
	//	m_alpha += g_gameTime->GetFrameDeltaTime() * 1.2f;
	//}	

	//title_Render.Update();
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
}