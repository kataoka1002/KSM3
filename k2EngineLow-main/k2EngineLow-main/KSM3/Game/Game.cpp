#include "stdafx.h"
#include "Game.h"

bool Game::Start()
{

	animationClips[enAnimClip_Idle].Load("Assets/animData/idle.tka");
	animationClips[enAnimClip_Idle].SetLoopFlag(true);

	m_modelRender.Init("Assets/modelData/unityChan.tkm", animationClips, enAnimClip_Num, enModelUpAxisY);

	//m_modelRender.SetPosition(0.0f, 40.0f, 0.0f);

	Quaternion rot;
	rot.SetRotationDegY(180.0f);
	m_modelRender.SetRotation(rot);

	//m_modelRender.SetScale(2.0f);

	m_modelRender.Update();
	return true;
}

Game::Game()
{



	
}

Game::~Game()
{

}

void Game::Update()
{
	m_modelRender.PlayAnimation(enAnimClip_Idle);

	m_modelRender.Update();
}

void Game::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}