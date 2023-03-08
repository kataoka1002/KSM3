#include "stdafx.h"
#include "Result.h"
#include "Title.h"
#include "Game.h"

Result::Result() {
	result_SpriteRender.Init("Assets/sprite/gameclear.dds", 1920.0f, 1080.0f);
}

Result::~Result()
{
}

void Result::Update()
{
	//�Q�[���{�҂ւ̑J��
	if (g_pad[0]->IsTrigger(enButtonA)) {
		Title* title = NewGO<Title>(0, "title");
		DeleteGO(this);
	}
}

void Result::Render(RenderContext& rc)
{
	result_SpriteRender.Draw(rc);
}