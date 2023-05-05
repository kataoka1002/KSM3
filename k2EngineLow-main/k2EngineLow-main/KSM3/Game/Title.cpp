#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "Fade.h"
#include "Player.h"
#include "GameCamera.h"

Title::Title()
{
	title_Render.Init("Assets/sprite/title_test.dds", 1920.0f, 1080.0f);
	//gameStart_Render.Init("Assets/sprite/title/gameStart.dds", /*1920.0f, 1080.0f*/);
	////system_Render.Init("Assets/sprite/title/system.dds", /*1920.0f, 1080.0f*/);
	////nannka_Render.Init("Assets/sprite/title/nannka.dds", /*1920.0f, 1080.0f*/);
	//yajirusi_Render.Init("Assets/sprite/title/yajirusi/dds", /*1920.0f, 1080.0f*/);

	title_Render.SetScale(title_scale);
}

Title::~Title()
{
	//DeleteGO(gameCamera);
	//DeleteGO(player);
}

bool Title::Start()
{
	//gameCamera= NewGO<GameCamera>(1, "camera");
	//gameCamera->CameraState = 2;
	//player = NewGO<Player>(1,"player");
	//player->game_state = 4;
	m_fade = FindGO<Fade>("fade");
	m_fade->StartFadeIn();
	model_batt.Init("Assets/modelData/battleship_gun_Drop.tkm");
	model_batt.SetScale(scale);
	model_mac.Init("Assets/modelData/machine_gun_drop.tkm");
	model_mac.SetScale(scale);

	title_back.Init("Assets/modelData/title_back.tkm");
	

	return true;
}

void Title::Update()
{
	model_batt.Update();
	model_mac.Update();
	title_back.SetPosition(titel_back);

	title_back.Update();
	
	if (State == 0/*&& g_pad[0]->IsTrigger(enButtonA)*/ )
	{
		if (m_isWaitFadeout)
		{
			if (!m_fade->IsFade())
			{
				//ゲーム本編への遷移
				//if (g_pad[0]->IsTrigger(enButtonA))
				//{
					Game* game = NewGO<Game>(0, "game");
					//player->game_state = 0;
					//gameCamera->CameraState = 0;
					DeleteGO(this);
				//}
			}
		}
		else 
		{
			if (g_pad[0]->IsTrigger(enButtonA)) 
			{
				m_isWaitFadeout = true;
				m_fade->StartFadeOut();
				//SoundSource* se = NewGO<SoundSource>(0);
				//se->Init(1);
				//se->Play(false);
			}
		}
	}
	//α値の変化。???
	if (m_isWaitFadeout)
	{
		m_alpha += g_gameTime->GetFrameDeltaTime() * 20.5f;
	}
	else
	{
		m_alpha += g_gameTime->GetFrameDeltaTime() * 1.2f;
	}	
	title_Render.Update();
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
	model_batt.Draw(rc);
	//model_mac.Draw(rc);
}