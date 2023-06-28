#include "stdafx.h"
#include "Customize_area.h"
#include "Player.h"

Customize_area::Customize_area() 
{

}

Customize_area::~Customize_area() 
{

}

bool Customize_area::Start()
{
	m_player = FindGO<Player>("player");

	//ƒƒ‚ƒŠ‚ÌŠm•Û
	m_customizeAreaModel = std::make_unique<ModelRender>();
	m_customizeAreaModel->Init("Assets/modelData/Customize_area.tkm",false);
	m_customizeAreaModel->SetPosition(m_position);
	m_customizeAreaModel->SetScale(m_scale);
	m_customizeAreaModel->Update();

	return true;
}

void Customize_area::Render(RenderContext& rc) 
{
	if (m_player->GetGameState() == CUSTOMIZE_NUM) 
	{
		m_customizeAreaModel->Draw(rc);
	}
}