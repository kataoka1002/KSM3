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
	//メモリの確保
	m_groundModel = std::make_unique<ModelRender>();


	//モデルを読み込む。
	m_groundModel->Init("Assets/modelData/stage8.tkm",false);
	m_groundModel->SetScale(0.8f);
	//モデルを更新する。
	m_groundModel->Update();
	//静的物理オブジェクトを作成。
	m_physicsStaticObject.CreateFromModel(m_groundModel->GetModel(), m_groundModel->GetModel().GetWorldMatrix());
	// 当たり判定を有効化する。
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	return true;
}

void BackGround::Update()
{
	//モデルの更新処理。
	m_groundModel->Update();
}

void BackGround::Render(RenderContext& rc)
{
	m_groundModel->Draw(rc);
}