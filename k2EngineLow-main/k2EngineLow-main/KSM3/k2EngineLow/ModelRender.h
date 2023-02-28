#pragma once

#include "geometry/AABB.h"

namespace nsK2EngineLow {
	class RenderingEngine;

	//スキンモデルレンダー
	class ModelRender
	{
	public:
		ModelRender();
		~ModelRender();

		//初期化
		void Init(
			const char* filePath,							//ファイルパス
			AnimationClip* animation = nullptr,				//アニメーションクリップ
			int numAnimationClips = 0,						//アニメーションクリップの数
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ,	//モデルの上方向
			bool isShadowReciever = true,					//シャドウレシーバーフラグtrueなら影が落ちる
			int maxInstance = 1,							//インスタンスの最大数。この引数を１より大きくするとインスタンシング描画が行われます。
			bool isFrontCullingOnDrawShadowMap = false		//シャドウマップを描画する際にフロントカリングを行う？
		);

		////半透明描画を行うオブジェクトを初期化。
		//void IniTranslucent(
		//	const char* filePath,								//ファイルパス
		//	AnimationClip* animationClips = nullptr,			//アニメーションクリップ
		//	int numAnimationClips = 0,							//アニメーションクリップの数
		//	EnModelUpAxis enModelUpAxis = enModelUpAxisZ,		//モデルの上方向
		//	bool isShadowReciever = true,						//trueなら影が落ちる
		//	int maxInstance = 1,								//インスタンスの最大数。この引数を１より大きくするとインスタンシング描画が行われます。
		//	bool isFrontCullingOnDrawShadowMap = false);		//シャドウマップを描画する際にフロントカリングを行う？

		////特殊なシェーディングを行いたい場合の初期化処理
		//void InitForwardRendering(ModelInitData& initData);//モデルデータ

		//更新処理
		void Update();

		//インスタンシングデータの更新
		void UpdateInstancingData(
			int instanceNo,			//インスタンス番号
			const Vector3& pos,		//座標
			const Quaternion& rot,	//回転
			const Vector3& scale);	//拡大率

		//描画処理
		void Draw(RenderContext& rc);

		//アニメーション再生
		void PlayAnimation(int animNo, float interpolateTime = 0.0f)//アニメーションクリップの番号
		{
			m_animation.Play(animNo,		//アニメーションクリップの番号
				interpolateTime);			//補完時間(単位：秒)
		};

		//アニメーション再生中？
		bool IsPlayingAnimation()const
		{
			return m_animation.IsPlaying();
		}

		//モデルを取得
		Model& GetModel()
		{
			if (m_renderToGBufferModel.IsInited()) {
				return m_renderToGBufferModel;
			}
			else if (m_forwardRenderModel.IsInited()) {
				return m_forwardRenderModel;
			}
			else if (m_translucentModel.IsInited()) {
				return m_translucentModel;
			}
			//ここまで来るのはおかしい
			return m_zprepassModel;
		}

		//座標、回転、拡大を全て設定
		void SetTRS(const Vector3& pos, const Quaternion& rotation, const Vector3& scale)
		{
			SetPosition(pos);			//座標
			SetRotation(rotation);		//回転
			SetScale(scale);			//拡大
		}

		//座標設定
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;		//座標
		}
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x,y,z });	//x座標、y座標、z座標
		}
		//回転を設定
		void SetRotation(const Quaternion& rotation)
		{
			m_rotation = rotation;	//回転
		}
		//拡大率設定
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;		//拡大率
		}
		void SetScale(float x, float y, float z)
		{
			SetScale({ x,y,z });
		}

		////シャドウキャスターのフラグを設定する
		//void SetShadowCasterFlag(bool flag)
		//{
		//	m_isShadowCaster = flag;
		//}

		//アニメーション再生速度を設定する
		void SetAnimationSpeed(const float animationSpeed)
		{
			m_animationSpeed = animationSpeed;	//数値の分だけ倍にする
		}

		//ボーンの名前からボーン番号を検索
		//int FindBoneID(const wchar_t* boneName)const
		//{
		//	return m_skeleton.FindBoneID(boneName);	//ボーンの名前
		//}
		//ボーン番号からボーンを取得
		//Bone* GetBone(int boneNo)const
		//{
		//	return m_skeleton.GetBone(boneNo);		//ボーンの番号
		//}
		//void AddAnimationEvent(AnimationEventListener eventListener)
		//{
		//	m_animation.AddAnimationEventListener(eventListener);
		//}

		//シャドウキャスター？
		//bool IsShadowCaster()const
		//{
		//	return m_isShadowCaster;
		//}

		//インスタンス数を取得
		int GetNumInstance()const
		{
			return m_numInstance;
		}

		//インスタンシング描画を行う
		bool IsInstancingDraw()const
		{
			return m_isEnableInstancingDraw;
		}

		//ワールド行列を取得
		const Matrix& GetWorldMatrix(int instanceId) const
		{
			if (IsInstancingDraw()) {
				return m_worldMatrixArray[instanceId];	//インスタンスID
			}
			return m_zprepassModel.GetWorldMatrix();	//インスタンシング描画が無効の場合は無視される
		}

		//インスタンスを除去
		void RemoveInstance(int instanceNo);	//インスタンス番号

		////レイトレワールドに登録するかのフラグを設定する
		////頻繁に生成するモデル（弾など）をInitする前に引数falseで実行してください。
		//void SetRaytracingWorld(bool flag) {
		//	m_isRaytracingWorld = flag;
		//}
	private:
		//スケルトンの初期化
		void InitSkeleton(const char* filePath);

		//アニメーションの初期化
		void InitAnimation(AnimationClip* animationClips,   //アニメーションクリップ
			int numAnimationClips,							//アニメーションクリップの数
			EnModelUpAxis enModelUpAxis);					//モデルの上向き

		////頂点計算パスから呼び出される処理
		//void OnCompteVertex(RenderContext& rc);

		////シャドウマップへの描画パスから呼ばれる処理
		//void OnRenderShadowMap(
		//	RenderContext& rc,					//レンダリングコンテキスト
		//	int ligNo,							//ライト番号
		//	int shadowMapNo,					//シャドウマップ番号
		//	const Matrix& lvpMatrix)override;	//ライトビュープロジェクション行列

		////ZPrepassから呼ばれる処理
		//void OnZPrepass(RenderContext& rc)override;

		///// G-Buffer描画パスから呼ばれる処理。
		//void OnRenderToGBuffer(RenderContext& rc) override;

		///// フォワードレンダーパスから呼ばれる処理。
		//void OnForwardRender(RenderContext& rc) override;

		///// 半透明オブジェクト描画パスから呼ばれる処理。
		//void OnTlanslucentRender(RenderContext& rc) override;

		///// 各種モデルのワールド行列を更新する。
		//void UpdateWorldMatrixInModes();

	private:

		//レンダリングエンジンで発生したイベントを受け取ったときに呼ばれる処理
		void OnRecievedEventFromRenderingEngine(RenderingEngine::EnEvent enEvent);

		//シャドウマップ描画用のモデルを初期化
		void InitModelOnShadowMap(
			RenderingEngine& renderingEngine,		//レンダリングエンジン
			const char* tkmFilePath,				//tkmファイルパス
			EnModelUpAxis modelUpAxis,				//モデルの上軸
			bool isFrontCullingOnDrawShadowMap
		);

		//ZPrepass描画用のモデルを初期化。
		void InitModelOnZprepass(
			RenderingEngine& renderingEngine,
			const char* tkmFilePath,
			EnModelUpAxis modelUpAxis
		);

		//インスタンシング描画用の初期化処理を実行
		void InitInstancingDraw(int maxInstance);	//最大インスタンス数

		//アニメーション済み頂点バッファの計算処理を初期化
		void InitComputeAnimatoinVertexBuffer(
			const char* tkmFilePath,			//tkmファイルのファイルパス
			EnModelUpAxis enModelUpAxis);		//モデルの上軸

		//GBuffer描画用のモデルを初期化
		void InitModelOnRenderGBuffer(
			RenderingEngine& renderingEngine,	//レンダリングエンジン
			const char* tkmFilePath,			//tkmファイルパス
			EnModelUpAxis enModelUpAxis,		//モデルの上軸
			bool isShadowReciever);

		//半透明オブジェクト描画パスで使用されるモデルを初期化
		void InitModelOnTranslucent(
			RenderingEngine& renderingEngine,
			const char* tkmFilePath,
			EnModelUpAxis enModelUpAxis,
			bool isShadowReciever
		);

		//各種モデルの頂点シェーダーのエントリーポイントを設定。
		void SetupVertexShaderEntryPointFunc(ModelInitData& modelInitData);

		//モデルを内包するバウンディングボリュームを初期化。
		void InitBoundingVolume();		//AABBを構築します

		//幾何学情報を初期化
		void InitGeometryDatas(int maxInstance);	//インスタンス数

	public:
		static const int NUM_SHADOW_LIGHT = 1;
	private:
		AnimationClip* m_animationClips = nullptr;
		int							m_numAnimationClips = 0;			// アニメーションクリップの数。
		Vector3 					m_position = Vector3::Zero;			// 座標。
		Quaternion	 				m_rotation = Quaternion::Identity;	// 回転。
		Vector3						m_scale = Vector3::One;				// 拡大率。
		EnModelUpAxis				m_enFbxUpAxis = enModelUpAxisZ;		// FBXの上方向。
		Animation					m_animation;						// アニメーション。
		ComputeAnimationVertexBuffer m_computeAnimationVertexBuffer;	// アニメーション済み頂点バッファの計算処理。
		Model* m_addRaytracingWorldModel = nullptr;// レイトレワールドに登録したモデル。				
		Model						m_zprepassModel;					// ZPrepassで描画されるモデル
		Model						m_forwardRenderModel;				// フォワードレンダリングの描画パスで描画されるモデル
		Model						m_translucentModel;					// 半透明モデル。
		Model						m_renderToGBufferModel;				// RenderToGBufferで描画されるモデル
		Model						m_shadowModels[MAX_DIRECTIONAL_LIGHT][NUM_SHADOW_MAP];	// シャドウマップに描画するモデル
		ConstantBuffer				m_drawShadowMapCameraParamCB[MAX_DIRECTIONAL_LIGHT][NUM_SHADOW_MAP];		// シャドウマップ作成時に必要なカメラパラメータ用の定数バッファ。
		bool						m_isUpdateAnimation = true;			// アニメーションを更新する？
		Skeleton					m_skeleton;							// 骨。
		bool						m_isShadowCaster = true;			// シャドウキャスターフラグ
		float						m_animationSpeed = 1.0f;
		int							m_numInstance = 0;					// インスタンスの数。
		int							m_maxInstance = 1;					// 最大インスタンス数。
		bool						m_isEnableInstancingDraw = false;	// インスタンシング描画が有効？
		bool						m_isRaytracingWorld = true;			//レイトレワールドに登録する？
		std::unique_ptr<Matrix[]>	m_worldMatrixArray;					// ワールド行列の配列。
		StructuredBuffer			m_worldMatrixArraySB;				// ワールド行列の配列のストラクチャードバッファ。
		std::vector< GemometryData > m_geometryDatas;					// ジオメトリ情報。
		std::unique_ptr<int[]>		m_instanceNoToWorldMatrixArrayIndexTable;	// インスタンス番号からワールド行列の配列のインデックスに変換するテーブル。

	};
}

