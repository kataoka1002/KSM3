#include "stdafx.h"
#include "Title.h"
#include "Game.h"
//#include "Fade.h"

Title::Title() {
	title_Render.Init("Assets/sprite/title_test.dds", 1920.0f, 1080.0f);

	title_Render.SetScale(title_scale);

//	m_fade = FindGO<Fade>("fade");
//	m_fade->StartFadeIn();	
}

Title::~Title()
{
}

void Title::Update()
{
//	if (m_isWaitFadeout) {
//		if (!m_fade->IsFade())
		{
			//ƒQ[ƒ€–{•Ò‚Ö‚Ì‘JˆÚ
			if (g_pad[0]->IsTrigger(enButtonA))
			{
				Game* game = NewGO<Game>(0, "game");
				DeleteGO(this);
			}
		}
//	}
//	else {
		if (g_pad[0]->IsTrigger(enButtonA)) {
//			m_isWaitFadeout = true;
//			m_fade->StartFadeOut();
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(1);
			se->Play(false);
		}
//	}
	title_Render.Update();

}

void Title::Render(RenderContext& rc)
{
	title_Render.Draw(rc);
}