#pragma once
class Result:public IGameObject
{
public:
	Result();
	~Result();
	void Update();
	void Render(RenderContext& rc);

	SpriteRender result_SpriteRender;//���U���g�̃X�v���C�g�����_�[

};

