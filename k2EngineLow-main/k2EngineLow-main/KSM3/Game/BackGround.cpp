#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{

}

BackGround::~BackGround()
{
	
}

bool BackGround::Start()
{
	//モデルを読み込む。

	modelRender.Init("Assets/modelData/stage6.tkm",false);
	modelRender.SetScale(0.8f);
	//モデルを更新する。
	modelRender.Update();
	//静的物理オブジェクトを作成。
	physicsStaticObject.CreateFromModel(modelRender.GetModel(), modelRender.GetModel().GetWorldMatrix());
	// 当たり判定を有効化する。
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	return true;
}

void BackGround::Update()
{
	//モデルの更新処理。
	modelRender.Update();
}

void BackGround::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}