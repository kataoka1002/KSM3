#pragma once
#include "SceneLight.h"

namespace nsK2EngineLow {

	class K2EngineLow;
	class FontRender;

	class RenderingEngine : public Noncopyable
	{
	public:
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

		//レンダリングターゲットを作成する(初期化の前に行う)
		void MakeRenderTarget(RenderTarget& targetName, int w, int h, int mipLevel, int arraySize, DXGI_FORMAT colorFormat, DXGI_FORMAT depthStencilFormat)
		{
			targetName.Create(
				w,                      // テクスチャの幅
				h,                      // テクスチャの高さ
				mipLevel,               // Mipmapレベル
				arraySize,              // テクスチャ配列のサイズ
				colorFormat,			// カラーバッファのフォーマット
				depthStencilFormat		// デプスステンシルバッファのフォーマット
			);
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

	private:
		SceneLight m_sceneLight;
		RenderTarget offscreenRenderTarget;
		RenderContext& renderContext = g_graphicsEngine->GetRenderContext();

		std::vector<ModelRender*> ModelRenderObject;
		std::vector<SpriteRender*> SpriteRenderObject;
		std::vector<FontRender*> FontRenderObject;
	};
}
