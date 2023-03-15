#include "k2EngineLowPreCompile.h"
#include "Bloom.h"
namespace nsK2EngineLow {
	Bloom::Bloom()
	{
		
	}

	Bloom::~Bloom()
	{

	}

	void Bloom::Init(RenderTarget& renderTarget)
	{
		// luminanceRenderTarget(輝度抽出)セット
		luminanceRenderTarget.Create(
			g_graphicsEngine->GetFrameBufferWidth(),    // テクスチャの幅
			g_graphicsEngine->GetFrameBufferHeight(),   // テクスチャの高さ
			1,											// Mipmapレベル
			1,											// テクスチャ配列のサイズ
			DXGI_FORMAT_R32G32B32A32_FLOAT,				// カラーバッファのフォーマット
			DXGI_FORMAT_D32_FLOAT						// デプスステンシルバッファのフォーマット
		);


		// 輝度抽出スプライトの初期化
		luminanceSpriteInitData.m_fxFilePath = "Assets/shader/PostEffect.fx";
		luminanceSpriteInitData.m_vsEntryPointFunc = "VSMain";
		luminanceSpriteInitData.m_psEntryPoinFunc = "PSSamplingLuminance";
		luminanceSpriteInitData.m_width = g_graphicsEngine->GetFrameBufferWidth();
		luminanceSpriteInitData.m_height = g_graphicsEngine->GetFrameBufferHeight();
		luminanceSpriteInitData.m_textures[0] = &renderTarget.GetRenderTargetTexture();
		luminanceSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;
		m_luminanceSprite.Init(luminanceSpriteInitData);


		// ガウシアンブラー
		gaussianBlur[0].Init(&luminanceRenderTarget.GetRenderTargetTexture());
		gaussianBlur[1].Init(&gaussianBlur[0].GetBokeTexture());
		gaussianBlur[2].Init(&gaussianBlur[1].GetBokeTexture());
		gaussianBlur[3].Init(&gaussianBlur[2].GetBokeTexture());


		// ボケ画像用スプライトの初期化
		finalSpriteInitData.m_textures[0] = &gaussianBlur[0].GetBokeTexture();
		finalSpriteInitData.m_textures[1] = &gaussianBlur[1].GetBokeTexture();
		finalSpriteInitData.m_textures[2] = &gaussianBlur[2].GetBokeTexture();
		finalSpriteInitData.m_textures[3] = &gaussianBlur[3].GetBokeTexture();

		finalSpriteInitData.m_width = renderTarget.GetWidth();
		finalSpriteInitData.m_height = renderTarget.GetHeight();
		// ボケ画像を合成する必要があるので2D用シェーダーではなく専用シェーダーを利用する
		finalSpriteInitData.m_fxFilePath = "Assets/shader/PostEffect.fx";
		finalSpriteInitData.m_psEntryPoinFunc = "PSBloomFinal";
		// ただし加算合成で描画するのでアルファブレンディングモードを加算にする
		finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;
		finalSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;
		m_finalSprite.Init(finalSpriteInitData);
	}

	void Bloom::Update()
	{

	}

	void Bloom::Render(RenderContext& rc, RenderTarget& renderTarget)
	{
		// 輝度抽出用ターゲットに変更し使えるようになるまで待つ
		rc.WaitUntilToPossibleSetRenderTarget(luminanceRenderTarget);
		// ターゲットセット
		rc.SetRenderTargetAndViewport(luminanceRenderTarget);
		// ターゲットのクリア
		rc.ClearRenderTargetView(luminanceRenderTarget);
		//描画して終わるまで待つ
		m_luminanceSprite.Draw(rc);
		rc.WaitUntilFinishDrawingToRenderTarget(luminanceRenderTarget);
		// luminanceRenderTarget終了



		//ガウシアンブラーの実行(ぼかす)
		gaussianBlur[0].ExecuteOnGPU(rc, 10);
		gaussianBlur[1].ExecuteOnGPU(rc, 10);
		gaussianBlur[2].ExecuteOnGPU(rc, 10);
		gaussianBlur[3].ExecuteOnGPU(rc, 10);



		// MainRenderTargetセット
		rc.WaitUntilToPossibleSetRenderTarget(renderTarget);
		rc.SetRenderTargetAndViewport(renderTarget);
		//ボケ画像をメインレンダリングターゲットに加算合成(mainrenderTargetとブルームを合体)
		m_finalSprite.Draw(rc);
		// 終了待ち
		rc.WaitUntilFinishDrawingToRenderTarget(renderTarget);
	}
}
