#pragma once
namespace nsK2EngineLow {
	class Bloom
	{
	public:
		Bloom();
		~Bloom();
		void Init(RenderTarget& renderTarget);
		void Update();
		void Render(RenderContext& rc,RenderTarget& renderTarget);

	private:
		RenderTarget*	mainRenderingTarget;
		RenderTarget	luminanceRenderTarget;

		SpriteInitData	luminanceSpriteInitData;
		SpriteInitData	finalSpriteInitData;
		Sprite			m_luminanceSprite;
		Sprite			m_finalSprite;
		GaussianBlur	gaussianBlur[4];
	};
}
