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
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis)
	{

		// スケルトンを初期化。
		InitSkeleton(filePath);
		// アニメーションを初期化。
		InitAnimation(animationClips, numAnimationClips, enModelUpAxis);


		//モデルの初期化
		ModelInitData modelInitData;
		//影をを落とす方か落とされる方かでシェーダーを変える
		if(m_shadowDrop==true){
			// モデルの初期化
			modelInitData.m_tkmFilePath = filePath;
			modelInitData.m_fxFilePath = "Assets/shader/model.fx";
			modelInitData.m_expandConstantBuffer = &g_renderingEngine->GetLightingCB();
			modelInitData.m_expandConstantBufferSize = sizeof(g_renderingEngine->GetLightingCB());
			modelInitData.m_modelUpAxis = enModelUpAxis;

			// シャドウマップに描画するモデルを初期化
			ModelInitData shadowModelInitData;
			shadowModelInitData.m_tkmFilePath = filePath;
			shadowModelInitData.m_fxFilePath = "Assets/shader/model.fx";
			shadowModelInitData.m_psEntryPointFunc = "PSShadowMain";
			// カラーバッファーのフォーマットに変更が入ったので、こちらも変更する
			shadowModelInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32_FLOAT;
			m_shadowModel.Init(shadowModelInitData);
		}
		else {
			// 影を受ける背景モデルを初期化
			ModelInitData bgModelInitData;
			// シャドウレシーバー(影が落とされるモデル)用のシェーダーを指定する
			bgModelInitData.m_fxFilePath = "Assets/shader/shadowReciever2.fx";
			// シャドウマップを拡張SRVに設定する
			bgModelInitData.m_expandShaderResoruceView[0] = &g_renderingEngine->GetShadowTarget().GetRenderTargetTexture();
			// ライトビュープロジェクション行列を拡張定数バッファーに設定する
			bgModelInitData.m_expandConstantBuffer = (void*)&g_renderingEngine->GetLightCamera().GetViewProjectionMatrix();
			bgModelInitData.m_expandConstantBufferSize = sizeof(g_renderingEngine->GetLightCamera().GetViewProjectionMatrix());
			bgModelInitData.m_tkmFilePath = filePath;
			m_model.Init(bgModelInitData);
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

	void ModelRender::Update(bool m_syuzinkou)
	{
		//モデル側に移動回転拡大を渡す
		m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
		//影のモデルに移動回転拡大を渡す
		m_shadowModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);


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
	}
}
