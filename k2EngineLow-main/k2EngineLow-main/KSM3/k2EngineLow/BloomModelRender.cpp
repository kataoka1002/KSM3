#include "k2EngineLowPreCompile.h"
#include "BloomModelRender.h"

namespace nsK2EngineLow
{
	BloomModelRender::BloomModelRender()
	{

	}

	BloomModelRender::~BloomModelRender()
	{

	}

	bool BloomModelRender::Start()
	{
		return true;
	}

	void BloomModelRender::InitModel(const char* filePath, DXGI_FORMAT colorFormat,AnimationClip* animationClips,int numAnimationClips,EnModelUpAxis enModelUpAxis)
	{
		// スケルトンを初期化。
		InitSkeleton(filePath);
		// アニメーションを初期化。
		InitAnimation(animationClips, numAnimationClips, enModelUpAxis);


		//モデルの初期化
		ModelInitData modelInitData;
		modelInitData.m_tkmFilePath = filePath;
		modelInitData.m_fxFilePath = "Assets/shader/model.fx";
		modelInitData.m_expandConstantBuffer = &g_renderingEngine->GetLightingCB();
		modelInitData.m_expandConstantBufferSize = sizeof(g_renderingEngine->GetLightingCB());
		modelInitData.m_colorBufferFormat[0] = colorFormat;
		modelInitData.m_modelUpAxis = enModelUpAxis;


		if (animationClips != nullptr) {
			modelInitData.m_skeleton = &m_skeleton;
			modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
		}
		else {
			modelInitData.m_vsEntryPointFunc = "VSMain";
		}


		m_model.Init(modelInitData);
	}

	void BloomModelRender::InitLuminance(DXGI_FORMAT colorFormat, RenderTarget&mainTargetName)
	{
		//輝度抽出スプライトの初期化
		SpriteInitData spriteInitData;
		spriteInitData.m_fxFilePath ="Assets/shader/PostEffect.fx";
		spriteInitData.m_vsEntryPointFunc = "VSMain";
		spriteInitData.m_psEntryPoinFunc = "PSSamplingLuminance";
		spriteInitData.m_width = mainTargetName.GetWidth();
		spriteInitData.m_height = mainTargetName.GetHeight();
		spriteInitData.m_textures[0] = &mainTargetName.GetRenderTargetTexture();
		spriteInitData.m_colorBufferFormat[0] = colorFormat;

		//作成した初期化情報をもとにスプライトを初期化する
		m_luminanceSprite.Init(spriteInitData);
	}

	void BloomModelRender::InitSome(RenderTarget& luminanceTargetName, RenderTarget& mainTargetName, DXGI_FORMAT colorFormat)
	{
		//ガウシアンブラーの初期化
		gaussianBlur.Init(&luminanceTargetName.GetRenderTargetTexture());

		//ボケ画像用スプライトの初期化
		SpriteInitData finalSpriteInitData;
		finalSpriteInitData.m_textures[0] = &gaussianBlur.GetBokeTexture();
		//解像度はメインターゲットの幅と高さ
		finalSpriteInitData.m_width = mainTargetName.GetWidth();
		finalSpriteInitData.m_height = mainTargetName.GetHeight();
		//ぼかした画像を通常の2Dとしてメインレンダリングターゲットに描画するため2D用のシェーダーを利用
		finalSpriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		//ただし加算合成で描画するのでアルファブレンディングモードを加算にする
		finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;
		//カラーバッファーのフォーマット設定
		finalSpriteInitData.m_colorBufferFormat[0] = colorFormat;
		//初期化情報をもとに加算合成用のスプライトを初期化する
		m_finalSprite.Init(finalSpriteInitData);
	}

	void BloomModelRender::InitSprite(RenderTarget& mainTargetName)
	{
		//テクスチャを張り付けるためのスプライトを初期化
		SpriteInitData spiteInitData;
		spiteInitData.m_textures[0] = &mainTargetName.GetRenderTargetTexture();
		spiteInitData.m_width = mainTargetName.GetWidth();
		spiteInitData.m_height = mainTargetName.GetHeight();
		spiteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		m_copyToframeBufferSprite.Init(spiteInitData);
	}

	void BloomModelRender::Update()
	{
		//モデル側に移動回転拡大を渡すのはここ
		m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

		if (m_skeleton.IsInited()) {
			m_skeleton.Update(m_model.GetWorldMatrix());
		}
		//アニメーションを進める。
		m_animation.Progress(g_gameTime->GetFrameDeltaTime() * m_animationSpeed);
	}

	void BloomModelRender::TargetSet(RenderTarget& luminanceTargetName,RenderTarget& mainTargetName)
	{
		//ターゲットを変更する
		auto& rc = g_graphicsEngine->GetRenderContext();
		rc.WaitUntilToPossibleSetRenderTarget(mainTargetName);
		rc.SetRenderTargetAndViewport(mainTargetName);
		rc.ClearRenderTargetView(mainTargetName);
		//レンダリングターゲットへの書き込み
		m_model, Draw(rc);
		rc.WaitUntilFinishDrawingToRenderTarget(mainTargetName);

		//輝度抽出用のターゲットに変更
		rc.WaitUntilToPossibleSetRenderTarget(luminanceTargetName);
		rc.SetRenderTargetAndViewport(luminanceTargetName);
		rc.ClearRenderTargetView(luminanceTargetName);
		m_luminanceSprite.Draw(rc);
		rc.WaitUntilFinishDrawingToRenderTarget(luminanceTargetName);

		//ガウシアンブラーの実行
		gaussianBlur.ExecuteOnGPU(rc, 20);

		//ボケ画像をメインレンダリングターゲットに加算合成
		rc.WaitUntilToPossibleSetRenderTarget(mainTargetName);
		rc.SetRenderTargetAndViewport(mainTargetName);

		//最終合成
		m_finalSprite.Draw(rc);
		rc.WaitUntilFinishDrawingToRenderTarget(mainTargetName);

		//メインレンダリングターゲットの絵をフレームバッファにコピー
		rc.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);
		m_copyToframeBufferSprite.Draw(rc);
	}

	void BloomModelRender::InitAnimation(AnimationClip* animationClips, int numAnimationClips, EnModelUpAxis enModelUpAxis)
	{
		m_animationClips = animationClips;
		m_numAnimationClips = numAnimationClips;
		if (m_animationClips != nullptr) {
			m_animation.Init(m_skeleton,
				m_animationClips,
				numAnimationClips);
		}
	}

	void BloomModelRender::InitSkeleton(const char* filePath)
	{
		//スケルトンのデータを読み込み。
		std::string skeletonFilePath = filePath;
		int pos = (int)skeletonFilePath.find(".tkm");
		skeletonFilePath.replace(pos, 4, ".tks");
		m_skeleton.Init(skeletonFilePath.c_str());
	}


	void BloomModelRender::Draw(RenderContext& rc)
	{

	}
}