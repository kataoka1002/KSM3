#include "stdafx.h"
#include "Game.h"
#include "BoxMove.h"

bool Game::Start()
{
	m_spriteRender.Init("Assets/modelData/utc_nomal.DDS", 100.0f, 100.0f);
	m_spriteRender.SetPosition({ 600.0f,0.0f,0.0f });

	animationClips[enAnimClip_Idle].Load("Assets/animData/idle.tka");
	animationClips[enAnimClip_Idle].SetLoopFlag(true);

	m_modelRender.Init("Assets/modelData/unityChan.tkm", animationClips, enAnimClip_Num, enModelUpAxisY);

	m_modelRender.SetPosition(0.0f, 0.0f, 0.0f);

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

	m_fontRender.SetText(L"17");
	m_fontRender.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	m_fontRender.SetScale(2.0f);
	m_fontRender.SetColor({ 1.0f,1.0f,1.0f ,1.0f });
	m_fontRender.SetShadowParam(true, 1.3f, Vector3{ 0.0f,0.0f,0.0f });

	Quaternion rot;
	rot.SetRotationDegY(180.0f);
	m_modelRender.SetRotation(rot);

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
	/*wchar_t count1[255];
	swprintf_s(count1, 255, L"X%d", 5);*/
	

	m_modelRender.PlayAnimation(enAnimClip_Idle);

	m_modelRender.Update();
	m_spriteRender.Update();
}

void Game::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
	m_spriteRender.Draw(rc);
	m_fontRender.Draw(rc);
}