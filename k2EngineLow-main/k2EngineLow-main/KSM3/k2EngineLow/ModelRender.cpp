#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"

namespace nsK2EngineLow {

	ModelRender::ModelRender()
	{

	}

	ModelRender::~ModelRender()
	{

	}

	void ModelRender::Init(const char* filePath,
		bool m_shadowDrop,
		bool m_toonShader,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis)
	{
		// スケルトンを初期化。
		InitSkeleton(filePath);
		// アニメーションを初期化。
		InitAnimation(animationClips, numAnimationClips, enModelUpAxis);


		//モデルの初期化
		ModelInitDataFR modelInitData;
		//影をを落とす方か落とされる方かでシェーダーを変える
		if(m_shadowDrop==true){
			// モデルの初期化
			modelInitData.m_tkmFilePath = filePath;
			modelInitData.m_fxFilePath = "Assets/shader/model.fx";
			modelInitData.m_expandConstantBuffer = &g_renderingEngine->GetLightCB();
			modelInitData.m_expandConstantBufferSize = sizeof(g_renderingEngine->GetLightCB());
			modelInitData.m_modelUpAxis = enModelUpAxis;

			//輪郭線の処理
			//拡張SRVにZPrepassで作成された深度テクスチャを指定する
			modelInitData.m_expandShaderResoruceView[0] = &g_renderingEngine->GetZPrepassDepthTexture();
			//ZPrepassの初期化
			InitCommon(filePath,animationClips);
			//トゥーンシェーダーを使用するなら
			if (m_toonShader == true) {
				modelInitData.m_expandShaderResoruceView[2] = &g_renderingEngine->GetToonTexture();
				modelInitData.m_psEntryPointFunc = "PSToonMap";
			}


			// シャドウマップに描画するモデルを初期化
			ModelInitData shadowModelInitData;
			shadowModelInitData.m_tkmFilePath = filePath;
			shadowModelInitData.m_fxFilePath = "Assets/shader/model.fx";
			shadowModelInitData.m_psEntryPointFunc = "PSShadowMain";
			shadowModelInitData.m_modelUpAxis = enModelUpAxis;
			// カラーバッファーのフォーマットに変更が入ったので、こちらも変更する
			shadowModelInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32_FLOAT;

			//アニメーション有無でエントリーポイントを変える
			if (animationClips != nullptr) {
				shadowModelInitData.m_skeleton = &m_skeleton;
				shadowModelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
			}
			else {
				shadowModelInitData.m_vsEntryPointFunc = "VSMain";
			}

			m_shadowModel.Init(shadowModelInitData);
		}
		else {
			// 影を受ける背景モデルを初期化
			modelInitData.m_tkmFilePath = filePath;
			// シャドウレシーバー(影が落とされるモデル)用のシェーダーを指定する
			modelInitData.m_fxFilePath = "Assets/shader/shadowReciever.fx";
			// シャドウマップを拡張SRVに設定する
			modelInitData.m_expandShaderResoruceView[1] = &g_renderingEngine->GetShadowTarget().GetRenderTargetTexture();
			// ライトビュープロジェクション行列を拡張定数バッファーに設定する
			modelInitData.m_expandConstantBuffer = &g_renderingEngine->GetLightCB();
			modelInitData.m_expandConstantBufferSize = sizeof(g_renderingEngine->GetLightCB());
		}

		//アニメーション有無でエントリーポイントを変える
		if (animationClips != nullptr) {
			modelInitData.m_skeleton = &m_skeleton;
			modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
		}
		else {
			modelInitData.m_vsEntryPointFunc = "VSMain";
		}

		m_model.Init(modelInitData);
	}

	void ModelRender::InitCommon(const char* tkmFilePath, AnimationClip* animationClips)
	{
		// ZPrepass描画用のモデルを初期化
		ModelInitData modelInitData;
		modelInitData.m_tkmFilePath = tkmFilePath;
		modelInitData.m_fxFilePath = "Assets/shader/ZPrepass.fx";
		modelInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32_FLOAT;

		//アニメーション有無でエントリーポイントを変える
		if (animationClips != nullptr) {
			modelInitData.m_skeleton = &m_skeleton;
			modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
		}
		else {
			modelInitData.m_vsEntryPointFunc = "VSMain";
		}

		m_zprepassModel.Init(modelInitData);
	}

	void ModelRender::Update(bool m_syuzinkou)
	{
		//モデル側に移動回転拡大を渡す
		m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
		//影のモデルに移動回転拡大を渡す
		m_shadowModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
		//輪郭線に移動回転拡大を渡す
		m_zprepassModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);

		if (m_skeleton.IsInited()) {
			m_skeleton.Update(m_model.GetWorldMatrix());
		}
		//アニメーションを進める。
		m_animation.Progress(g_gameTime->GetFrameDeltaTime() * m_animationSpeed);

		//主人公ならライトカメラを追尾させる
		if (m_syuzinkou == true) {
			syuok = true;
		}
		else {
			syuok = false;
		}
	}

	void ModelRender::InitAnimation(AnimationClip* animationClips, int numAnimationClips, EnModelUpAxis enModelUpAxis)
	{
		m_animationClips = animationClips;
		m_numAnimationClips = numAnimationClips;
		if (m_animationClips != nullptr) {
			m_animation.Init(m_skeleton,
				m_animationClips,
				numAnimationClips);
		}
	}

	void ModelRender::InitSkeleton(const char* filePath)
	{
		//スケルトンのデータを読み込み。
		std::string skeletonFilePath = filePath;
		int pos = (int)skeletonFilePath.find(".tkm");
		skeletonFilePath.replace(pos, 4, ".tks");
		m_skeleton.Init(skeletonFilePath.c_str());
	}

	void ModelRender::Draw(RenderContext& rc)
	{
		g_renderingEngine->AddModelRenderObject(this);
		g_renderingEngine->Add3DModelToZPrepass(m_zprepassModel);
	}
}
