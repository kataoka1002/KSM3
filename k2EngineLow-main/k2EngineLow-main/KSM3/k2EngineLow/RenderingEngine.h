#pragma once
#include "SceneLight.h"
#include "Bloom.h"

namespace nsK2EngineLow {

	//class K2EngineLow;
	class FontRender;
	class Bloom;

	class RenderingEngine : public Noncopyable
	{
	public:
		RenderingEngine();
		bool Start();
		void Execute(RenderContext& rc);

		//ディレクションライトの設定
		void SetDirectionLight( Vector3 direction, Vector3 color)
		{
			m_sceneLight.SetDirectionLight( direction, color);
		}

		//アンビエントライトの設定
		void SetAmbientLight(float x,float y,float z)
		{
			m_sceneLight.SetAmbientLight(x, y, z);
		}

		//ポイントライトの設定
		void SetPointLight(Vector3 position, float range, Vector3 color)
		{
			m_sceneLight.SetPointLight(position, range, color);
		}

		//スポットライトの設定
		void SetSpotLight(Vector3 position, float range, Vector3 color, Vector3 direction, float angle)
		{
			m_sceneLight.SetSpotLight(position, range, color, direction, angle);
		}

		//半球ライトの設定
		void SetHemLight(Vector3 groundColor, Vector3 skyColor, Vector3 groundNormal)
		{
			m_sceneLight.SetHemLight(groundColor, skyColor, groundNormal);
		}

		SceneLight& GetLightingCB()
		{
			return m_sceneLight;
		}

		void AddModelRenderObject(ModelRender* modelRender)
		{
			//コンテナの後ろにくっつける
			ModelRenderObject.push_back(modelRender);
		}

		void AddSpriteRenderObject(SpriteRender* spriteRender)
		{
			//コンテナの後ろにくっつける
			SpriteRenderObject.push_back(spriteRender);
		}

		void AddFontRenderObject(FontRender* fontRender)
		{
			//コンテナの後ろにくっつける
			FontRenderObject.push_back(fontRender);
		}

		RenderTarget& GetMainRenderTarget()
		{
			return m_mainRenderingTarget;
		}

		Sprite& GetFrameBufferSprite()
		{
			return m_copyToframeBufferSprite;
		}

	private:
		SceneLight m_sceneLight;
		Bloom m_bloom;

		RenderTarget m_mainRenderingTarget;
		SpriteInitData m_spiteInitData;
		Sprite m_copyToframeBufferSprite;

		std::vector<ModelRender*> ModelRenderObject;
		std::vector<SpriteRender*> SpriteRenderObject;
		std::vector<FontRender*> FontRenderObject;
	public:

	};
}
