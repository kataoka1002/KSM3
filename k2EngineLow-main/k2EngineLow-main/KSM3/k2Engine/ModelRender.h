#pragma once

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
			const char* filePath,
			AnimationClip* animation = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ,
			bool isShadowReciever = true,
			int maxInstance = 1,
			bool isFrontCullingOnDrawShadowMap = false
		);

		//半透明描画を行うオブジェクトを初期化。
		void IniTranslucent(
			const char* filePath,
			AnimationClip* animationClips = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ,
			bool isShadowReciever = true,
			int maxInstance = 1,
			bool isFrontCullingOnDrawShadowMap = false);

		//特殊なシェーディングを行いたい場合の初期化処理
		void InitForwardRenderring(ModelInitData& initData);

		//更新処理
		void Update();

		//インスタンシングデータの更新
		void UpdateInstancingData(int instanceNo, const Vector3& pos, const Quaternion& rot, const Vector3& scale);

		//描画処理
		void Draw(RenderContext& rc);

		//アニメーション再生
		void PlayAnimation(int animNo, float interpolateTime = 0.0f)
		{
			m_animation.Play(animNo, interpolateTime);
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
			else if (m_traslucentModel.IsInited()) {
				return m_translucentModel;
			}
			//ここまで来るのはおかしい
			return m_zprepassModel;
		}

		//座標、回転、拡大を全て設定
		void SetTRS(const Vector3& pos, const Quaternion& rotation, const Vector3& scale)
		{
			SetPosition(pos);
			SetRotation(rotation);
			SetScale(scale);
		}

		//座標設定
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x,y,z });
		}
		//回転を設定
		void SetRotation(const Quaternion& rotation)
		{
			m_rotation = rotation;
		}
		//拡大率設定
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}
		void SetScale(float x, float y, float z)
		{
			SetScale({ x,y,z });
		}

		//シャドウキャスターのフラグを設定する
		void SetShadowCasterFlag(bool flag)
		{
			m_isShadowCaster = flag;
		}

		//アニメーション再生速度を設定する
		void SetAnimationSpeed(const float animationSpeed)
		{
			m_animationSpeed = animationSpeed;
		}

		//ボーンの名前からボーン番号を検索
		int FindBoneID(const wchar_t* boneName)const
		{
			return m_skeleton.FindBoneID(boneName);
		}
		//ボーン番号からボーンを取得
		Bone* GetBone(int bone)const
		{
			return m_skeleton.GetBone(boneNo);
		}
		void AddAnimationEvent(AnimationEventListener eventListener)
		{
			m_animation.AddAnimationEventListener(eventListener);
		}

		//シャドウキャスター？
		bool IsShadowCaster()const
		{
			return m_isShadowCaster;
		}

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
				return m_worldMatrixArray[instanceId];
			}
			return m_zprepassModel.GetWorldMatrix();
		}

		//インスタンスを除去
		void RemoveInstance(int instanceNo);

		//レイトレワールドに登録するかのフラグを設定する
		//頻繁に生成するモデル（弾など）をInitする前に引数falseで実行してください。
		void SetRaytracingWorld(bool flag) {
			m_isRaytracingWorld = flag;
		}
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

