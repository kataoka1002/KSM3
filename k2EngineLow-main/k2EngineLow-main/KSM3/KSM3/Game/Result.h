#pragma once
class Result:public IGameObject
{
public:
	Result();
	~Result();
	void Update();
	void Render(RenderContext& rc);

	SpriteRender result_SpriteRender;//リザルトのスプライトレンダー

};

