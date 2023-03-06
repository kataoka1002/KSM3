#include "stdafx.h"
#include "Game.h"
#include "BoxMove.h"

bool Game::Start()
{
	m_spriteRender.Init("Assets/modelData/utc_nomal.DDS", 100.0f, 100.0f);
	m_spriteRender.SetPosition({ -600.0f,300.0f,0.0f });

	animationClips[enAnimClip_Idle].Load("Assets/animData/idle.tka");
	animationClips[enAnimClip_Idle].SetLoopFlag(true);

	m_modelRender.Init("Assets/modelData/unityChan.tkm", animationClips, enAnimClip_Num, enModelUpAxisY);
	m_modelRender.SetPosition(-50.0f, 0.0f, 0.0f);

	m_modelRender2.Init("Assets/modelData/sample/testBackGround.tkm");
	m_modelRender2.SetPosition(0.0f, -20.0f, 20.0f);
	m_modelRender2.Update();

	m_modelRender3.Init("Assets/modelData/sample/light.tkm");
	m_modelRender3.Update();

	m_levelRender.Init("Assets/level/sample.tkl",
		[&](LevelObjectData2& objData)
		{
			//名前がBox_Moveだったら。
			if (objData.EqualObjectName(L"Box_Move") == true) {

				auto box = NewGO<BoxMove>(0);
				//配置座標、スケール、回転を取得する。
				box->m_position = objData.position;
				box->m_scale = objData.scale;
				box->m_rotation = objData.rotation;
				//後で削除するために、ボックスをプッシュしておく。
				m_boxmoves.push_back(box);

				//trueにすると、レベルの方でモデルが読み込まれない。
				return true;
			}
		});

	/*Vector3 nana = g_vec3Naname;
	nana.Normalize();
	g_renderingEngine->SetDirectionLight(nana, g_vec3One);*/

	/*Quaternion rot;
	rot.SetRotationDegX(90.0f);
	m_modelRender2.SetRotation(rot);*/
	m_modelRender.SetScale(1.0f);
	m_modelRender.Update();

	return true;
}

Game::Game()
{
	
}

Game::~Game()
{
	//プッシュしたボックスを削除していく。
	for (auto box : m_boxmoves)
	{
		DeleteGO(box);
	}
}

void Game::Update()
{
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"%d秒経過!!", int(m_timer));
	//表示するテキストを設定。
	m_fontRender.SetText(wcsbuf);
	//フォントの位置を設定。
	m_fontRender.SetPosition(Vector3(-800.0f, 0.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender.SetScale(2.0f);
	//フォントの色を設定。
	m_fontRender.SetColor({ 1.0f,0.0f,0.0f,1.0f });
	m_timer += g_gameTime->GetFrameDeltaTime();

	m_modelRender.PlayAnimation(enAnimClip_Idle);

	g_renderingEngine->SetPointLight( ptPosition, 150.0, g_vec3Right);
	g_renderingEngine->SetAmbientLight(0.3f, 0.3f, 0.3f);

	if (g_pad[0]->IsPress(enButtonRight)) {
		ptPosition.x += 1.0;
	}
	if (g_pad[0]->IsPress(enButtonLeft)) {
		ptPosition.x -= 1.0;
	}
	if (g_pad[0]->IsPress(enButtonUp)) {
		ptPosition.z += 1.0;
	}
	if (g_pad[0]->IsPress(enButtonDown)) {
		ptPosition.z -= 1.0;
	}
	
	
	m_modelRender.Update();
	m_modelRender2.Update();
	m_modelRender3.SetPosition(ptPosition);
	m_modelRender3.Update();
	m_spriteRender.Update();
}

void Game::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
	m_modelRender2.Draw(rc);
	m_modelRender3.Draw(rc);
	m_spriteRender.Draw(rc);

	m_fontRender.Draw(rc);
}