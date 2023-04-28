#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow {

	RenderingEngine::RenderingEngine()
	{
		// MainRenderTargetセット
		m_mainRenderingTarget.Create(
			g_graphicsEngine->GetFrameBufferWidth(),    // テクスチャの幅
			g_graphicsEngine->GetFrameBufferHeight(),   // テクスチャの高さ
			1,											// Mipmapレベル
			1,											// テクスチャ配列のサイズ
			DXGI_FORMAT_R32G32B32A32_FLOAT,				// カラーバッファのフォーマット
			DXGI_FORMAT_D32_FLOAT						// デプスステンシルバッファのフォーマット
		);

		// ブルームの初期化
		//m_bloom.Init(m_mainRenderingTarget);

		// シャドウの為の初期化
		InitShadowMap();

		// ZPrepassターゲット作成
		InitZPrepassRenderTarget();

		// トゥーンマップのテクスチャの初期化
		InitToonMap();

		// 最終的なテクスチャを張り付けるためのスプライトを初期化
		InitFinalSprite();
	}

	bool RenderingEngine::Start()
	{
		return true;
	}

	void RenderingEngine::InitShadowMap()
	{
		//ライトカメラの上方向の設定
		lightCamera.SetUp(0, 1, 0);
		SetLVP(lightCamera.GetViewProjectionMatrix());

		//シャドウマップ用のターゲットの作成
		shadowMapTarget.Create(
			1024,	//解像度
			1024,
			1,
			1,
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_D32_FLOAT,
			clearColor
		);
	}

	void RenderingEngine::InitFinalSprite()
	{
		m_spiteInitData.m_textures[0] = &m_mainRenderingTarget.GetRenderTargetTexture();
		m_spiteInitData.m_width = m_mainRenderingTarget.GetWidth();
		m_spiteInitData.m_height = m_mainRenderingTarget.GetHeight();
		m_spiteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		m_copyToframeBufferSprite.Init(m_spiteInitData);
	}

	void RenderingEngine::InitZPrepassRenderTarget()
	{
		m_zprepassRenderTarget.Create(
			g_graphicsEngine->GetFrameBufferWidth(),
			g_graphicsEngine->GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R32G32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);
	}

	void RenderingEngine::InitToonMap()
	{
		//トゥーンシェーダーのテクスチャを用意
		const wchar_t* shaderTex = L"Assets/shader/texture/shader.DDS";
		m_toonTexture.InitFromDDSFile(shaderTex);
	}

	void RenderingEngine::Execute(RenderContext& rc)
	{
		// ZPrepass
		ZPrepass(rc);

		// シャドウの描画
		ShadowDraw(rc);

		// モデルの描画
		ModelDraw(rc);

		// 画像と文字の描画
		SpriteFontDraw(rc);

		//ブルームを適用(ON.OFF変更可)
		//m_bloom.Render(rc, m_mainRenderingTarget);

		//ここでエフェクトドロー。
		EffectEngine::GetInstance()->Draw();


		// メインレンダリングターゲットの絵をフレームバッファにコピー
		CopyMainRenderTargetToFrameBuffer(rc);


		// クリア
		ModelRenderObject.clear();
		SpriteRenderObject.clear();
		FontRenderObject.clear();
		m_zprepassModelsObject.clear();
	}

	void RenderingEngine::ShadowDraw(RenderContext& rc)
	{
		//ターゲットをシャドウマップに変更
		rc.WaitUntilFinishDrawingToRenderTarget(shadowMapTarget);
		rc.SetRenderTargetAndViewport(shadowMapTarget);
		rc.ClearRenderTargetView(shadowMapTarget);

		// まとめて影モデルレンダーを描画
		for (auto MobjData : ModelRenderObject)
		{
			//主人公ならライトカメラを更新
			if (MobjData->GetSyuzinkou() == true) {
				//ライトカメラの更新
				lightCamera.SetPosition(MobjData->GetPositionX() + 600.0f, MobjData->GetPositionY() + 800.0f, MobjData->GetPositionZ());
				lightCamera.SetTarget(MobjData->GetPositionX(), MobjData->GetPositionY(), MobjData->GetPositionZ());
				lightCamera.Update();
			}
			//ライトビューセット
			SetLVP(lightCamera.GetViewProjectionMatrix());
			//影モデルの描画
			MobjData->OnShadowDraw(rc);
			rc.WaitUntilFinishDrawingToRenderTarget(shadowMapTarget);
		}
	}

	void RenderingEngine::ModelDraw(RenderContext& rc)
	{
		// メインのターゲットが使えるようになるまで待つ
		rc.WaitUntilToPossibleSetRenderTarget(m_mainRenderingTarget);
		// ターゲットセット
		rc.SetRenderTargetAndViewport(m_mainRenderingTarget);
		// ターゲットのクリア
		rc.ClearRenderTargetView(m_mainRenderingTarget);

		// まとめてモデルレンダーを描画
		for (auto MobjData : ModelRenderObject) {
			MobjData->OnDraw(rc);
		}

		// 描画されるまで待つ
		rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderingTarget);
	}

	void RenderingEngine::SpriteFontDraw(RenderContext& rc)
	{
		// スプライトと文字を描画
		for (auto SobjData : SpriteRenderObject) {
			SobjData->OnDraw(rc);
		}
		for (auto FobjData : FontRenderObject) {
			FobjData->OnDraw(rc);
		}
	}

	void RenderingEngine::ZPrepass(RenderContext& rc)
	{
		// まず、レンダリングターゲットとして設定できるようになるまで待つ
		rc.WaitUntilToPossibleSetRenderTarget(m_zprepassRenderTarget);
		// レンダリングターゲットを設定
		rc.SetRenderTargetAndViewport(m_zprepassRenderTarget);
		// レンダリングターゲットをクリア
		rc.ClearRenderTargetView(m_zprepassRenderTarget);

		for (auto& model : m_zprepassModelsObject)
		{
			model->Draw(rc);
		}

		rc.WaitUntilFinishDrawingToRenderTarget(m_zprepassRenderTarget);
	}

	void RenderingEngine::CopyMainRenderTargetToFrameBuffer(RenderContext& rc)
	{
		// フレームバッファにセット
		rc.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);
		m_copyToframeBufferSprite.Draw(rc);
	}
}