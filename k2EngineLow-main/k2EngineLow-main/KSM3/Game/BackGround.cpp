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
	//���f����ǂݍ��ށB
	modelRender.Init("Assets/modelData//stage.tkm");
	//���f�����X�V����B
	modelRender.Update();
	//�ÓI�����I�u�W�F�N�g���쐬�B
	physicsStaticObject.CreateFromModel(modelRender.GetModel(), modelRender.GetModel().GetWorldMatrix());
	// �����蔻���L��������B
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	return true;
}

void BackGround::Update()
{
	//���f���̍X�V�����B
	modelRender.Update();
}

void BackGround::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}