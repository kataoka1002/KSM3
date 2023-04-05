#include "stdafx.h"
#include "Test.h"

Test::Test()
{

}

Test::~Test()
{

}

bool Test::Start()
{
	nana.Normalize();

	return true;
}


void Test::Update()
{
	g_renderingEngine->SetDirectionLight(nana, col);
	g_renderingEngine->SetHemLight({ 0.5f,0.5f,0.5f }, { 0.0f,0.0f,0.0f }, { 0.5f,0.5f,0.5f });

	if (g_pad[0]->IsPress(enButtonUp))
	{
		col.x += 0.05f;
		col.y += 0.05f;
		col.z += 0.05f;
	}
	if (g_pad[0]->IsPress(enButtonDown))
	{
		col.x -= 0.05f;
		col.y -= 0.05f;
		col.z -= 0.05f;
	}
}

void Test::Draw(RenderContext& rc)
{

}