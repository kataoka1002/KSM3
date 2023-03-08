#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title::Title() {
	title_Render.Init("Assets/sprite/MAIN_MENU.dds", 1920.0f, 1080.0f);
}

Title::~Title()
{
}

void Title::Update()
{
	//�Q�[���{�҂ւ̑J��
	if (g_pad[0]->IsTrigger(enButtonA)) {
		Game* game = NewGO<Game>(0, "game");
		DeleteGO(this);
	}
}

void Title::Render(RenderContext& rc)
{
	title_Render.Draw(rc);
}