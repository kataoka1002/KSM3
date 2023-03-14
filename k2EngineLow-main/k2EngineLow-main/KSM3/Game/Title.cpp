#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title::Title() {
	title_Render.Init("Assets/sprite/title_test.dds", 1920.0f, 1080.0f);

	title_Render.SetScale(title_scale);

	title_Render.Update();
}

Title::~Title()
{
}

void Title::Update()
{
	//ƒQ[ƒ€–{•Ò‚Ö‚Ì‘JˆÚ
	if (g_pad[0]->IsTrigger(enButtonA)) {
		Game* game = NewGO<Game>(0, "game");
		DeleteGO(this);
	}
}

void Title::Render(RenderContext& rc)
{
	title_Render.Draw(rc);
}