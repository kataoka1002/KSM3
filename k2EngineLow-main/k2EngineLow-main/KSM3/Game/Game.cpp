#include "stdafx.h"
#include "Game.h"
#include "BoxMove.h"

bool Game::Start()
{
	m_spriteRender.Init("Assets/modelData/utc_nomal.DDS", 600.0f, 600.0f);
	m_spriteRender.SetPosition({ 200.0f,0.0f,0.0f });

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
	m_modelRender.PlayAnimation(enAnimClip_Idle);

	m_modelRender.Update();
	m_spriteRender.Update();
}

void Game::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
	m_spriteRender.Draw(rc);

	//レベルで読み込んだモデルを表示させる。
	//m_levelRender.Draw(rc);
}