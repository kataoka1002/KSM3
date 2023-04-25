#pragma once
#include "SceneLight.h"
#include "Bloom.h"

namespace nsK2EngineLow {

	class FontRender;
	class Bloom;
	class ModelRender;
	class SpriteRender;

	class RenderingEngine : public Noncopyable
	{
	public:
		RenderingEngine();
		bool Start();
		void InitShadowMap();
		void InitZPrepassRenderTarget();
		void InitFinalSprite();
		void InitToonMap();
		void Execute(RenderContext& rc);
		void ZPrepass(RenderContext& rc);
		void ShadowDraw(RenderContext& rc);
		void ModelDraw(RenderContext& rc);
		void SpriteFontDraw(RenderContext& rc);
		void CopyMainRenderTargetToFrameBuffer(RenderContext& rc);


		//ディレクションライトの設定
		void SetDirectionLight( Vector3 direction, Vector3 color)
		{
			m_sceneLight.SetDirectionLight(direction, color);
		}

		//アンビエントライトの設定
		void SetAmbientLight(float x,float y,float z)
		{
			m_sceneLight.SetAmbientLight(x, y, z);
		}

		//ポイントライトの設定
		void SetPointLight(int num,Vector3 position, float range, Vector3 color)
		{
			m_sceneLight.SetPointLight(num,position, range, color);
		}

		//スポットライトの設定
		void SetSpotLight(int num,Vector3 position, float range, Vector3 color, Vector3 direction, float angle)
		{
			m_sceneLight.SetSpotLight(num,position, range, color, direction, angle);
		}

		//半球ライトの設定
		void SetHemLight(Vector3 groundColor, Vector3 skyColor, Vector3 groundNormal)
		{
			m_sceneLight.SetHemLight(groundColor, skyColor, groundNormal);
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

		//ライトビュースクリーンの設定
		void SetLVP(Matrix mat)
		{
			m_sceneLight.SetLVP(mat);
		}

		//ZPrepassで作成された深度テクスチャを取得
		Texture& GetZPrepassDepthTexture()
		{
			return m_zprepassRenderTarget.GetRenderTargetTexture();
		}

		//ZPrepassの描画パスにモデルを追加
		void Add3DModelToZPrepass(Model& model)
		{
			m_zprepassModelsObject.push_back(&model);
		}

		//取得系の関数
		SceneLight& GetLightingCB()
		{
			return m_sceneLight;
		}

		Light& GetLightCB()
		{
			return m_sceneLight.GetLight();
		}

		RenderTarget& GetMainRenderTarget()
		{
			return m_mainRenderingTarget;
		}

		Sprite& GetFrameBufferSprite()
		{
			return m_copyToframeBufferSprite;
		}

		RenderTarget& GetShadowTarget()
		{
			return shadowMapTarget;
		}

		Camera& GetLightCamera()
		{
			return lightCamera;
		}

		Texture& GetToonTexture()
		{
			return m_toonTexture;
		}

		
	private:

		SceneLight m_sceneLight;
		Bloom m_bloom;

		RenderTarget m_mainRenderingTarget;
		RenderTarget m_zprepassRenderTarget;
		SpriteInitData m_spiteInitData;
		Sprite m_copyToframeBufferSprite;

		//シャドウ用
		RenderTarget shadowMapTarget;
		Camera lightCamera;
		float clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };	//カラーバッファーは真っ白
		
		//トゥーンシェーダーのテクスチャ
		Texture m_toonTexture;

		std::vector<ModelRender*>	ModelRenderObject;
		std::vector<SpriteRender*>	SpriteRenderObject;
		std::vector<FontRender*>	FontRenderObject;
		std::vector<Model* >		m_zprepassModelsObject;	// ZPrepassの描画パスで描画されるモデルのリスト
	public:

	};
}
