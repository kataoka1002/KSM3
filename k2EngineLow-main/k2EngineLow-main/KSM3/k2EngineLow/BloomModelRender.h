#pragma once


namespace nsK2EngineLow {
	class BloomModelRender
	{
	public:
		BloomModelRender();
		~BloomModelRender();
		//モデル用の初期化関数
		void InitModel(const char* filePath,
			DXGI_FORMAT colorFormat,
			AnimationClip* animationClips = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ
			);
		//輝度抽出用スプライトの初期化関数
		void InitLuminance(
			DXGI_FORMAT colorFormat,
			RenderTarget& mainTargetName
		);
		//色々初期化するための関数
		void InitSome(RenderTarget&luminanceTargetName,
			RenderTarget& mainTargetName,
			DXGI_FORMAT colorFormat
		);
		void InitSprite(RenderTarget& mainTargetName);
		void Update();
		bool Start();
		void Draw(RenderContext& rc);



		void TargetSet(RenderTarget& luminanceTargetName,RenderTarget& mainTargetName);

		//座標設定
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x, y, z });
		}

		//回転設定
		void SetRotation(const Quaternion& rotation)
		{
			m_rotation = rotation;
		}

		//拡大設定
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}
		void SetScale(float x, float y, float z)
		{
			SetScale({ x, y, z });
		}
		void SetScale(float xyz)
		{
			SetScale({ xyz,xyz,xyz });
		}

		//座標拡大回転全てを設定
		void SetTRS(const Vector3& pos, const Quaternion& rotation, const Vector3& scale)
		{
			SetPosition(pos);
			SetRotation(rotation);
			SetScale(scale);
		}

		//モデルを取得
		Model& GetModel()
		{
			return m_model;
		}

		//アニメーションの再生
		void PlayAnimation(int animNo, float interpolateTime = 0.0f)//アニメーションクリップの番号,補完時間
		{
			m_animation.Play(animNo, interpolateTime);
		}

	private:
		//アニメーションの初期化
		void InitAnimation(AnimationClip* animationClips,	//アニメーションクリップ
			int numAnimationClips,							//アニメーションクリップの数
			EnModelUpAxis enModelUpAxis);					//モデルの上向き

		//スケルトンの初期化
		void InitSkeleton(const char* filePath);


	private:
		//モデル
		Model m_model;

		//スプライト
		Sprite m_luminanceSprite;
		Sprite m_finalSprite;
		Sprite m_copyToframeBufferSprite;

		//アニメーション
		Animation m_animation;
		AnimationClip* m_animationClips;
		int m_numAnimationClips = 0;
		Skeleton m_skeleton;
		float m_animationSpeed = 1.0f;

		//座標回転大きさ
		Vector3 m_position = Vector3::Zero;
		Quaternion m_rotation = { 0.0f,0.0f,0.0f,1.0f };
		Vector3 m_scale = Vector3::One;

		//ガウシアンブラー
		GaussianBlur gaussianBlur;
	};
}

