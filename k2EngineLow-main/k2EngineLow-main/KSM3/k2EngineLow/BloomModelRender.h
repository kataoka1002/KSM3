#pragma once


namespace nsK2EngineLow {
	class BloomModelRender
	{
	public:
		BloomModelRender();
		~BloomModelRender();
		//���f���p�̏������֐�
		void InitModel(const char* filePath,
			DXGI_FORMAT colorFormat,
			AnimationClip* animationClips = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ
			);
		//�P�x���o�p�X�v���C�g�̏������֐�
		void InitLuminance(
			DXGI_FORMAT colorFormat,
			RenderTarget& mainTargetName
		);
		//�F�X���������邽�߂̊֐�
		void InitSome(RenderTarget&luminanceTargetName,
			RenderTarget& mainTargetName,
			DXGI_FORMAT colorFormat
		);
		void InitSprite(RenderTarget& mainTargetName);
		void Update();
		bool Start();
		void Draw(RenderContext& rc);



		void TargetSet(RenderTarget& luminanceTargetName,RenderTarget& mainTargetName);

		//���W�ݒ�
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x, y, z });
		}

		//��]�ݒ�
		void SetRotation(const Quaternion& rotation)
		{
			m_rotation = rotation;
		}

		//�g��ݒ�
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

		//���W�g���]�S�Ă�ݒ�
		void SetTRS(const Vector3& pos, const Quaternion& rotation, const Vector3& scale)
		{
			SetPosition(pos);
			SetRotation(rotation);
			SetScale(scale);
		}

		//���f�����擾
		Model& GetModel()
		{
			return m_model;
		}

		//�A�j���[�V�����̍Đ�
		void PlayAnimation(int animNo, float interpolateTime = 0.0f)//�A�j���[�V�����N���b�v�̔ԍ�,�⊮����
		{
			m_animation.Play(animNo, interpolateTime);
		}

	private:
		//�A�j���[�V�����̏�����
		void InitAnimation(AnimationClip* animationClips,	//�A�j���[�V�����N���b�v
			int numAnimationClips,							//�A�j���[�V�����N���b�v�̐�
			EnModelUpAxis enModelUpAxis);					//���f���̏����

		//�X�P���g���̏�����
		void InitSkeleton(const char* filePath);


	private:
		//���f��
		Model m_model;

		//�X�v���C�g
		Sprite m_luminanceSprite;
		Sprite m_finalSprite;
		Sprite m_copyToframeBufferSprite;

		//�A�j���[�V����
		Animation m_animation;
		AnimationClip* m_animationClips;
		int m_numAnimationClips = 0;
		Skeleton m_skeleton;
		float m_animationSpeed = 1.0f;

		//���W��]�傫��
		Vector3 m_position = Vector3::Zero;
		Quaternion m_rotation = { 0.0f,0.0f,0.0f,1.0f };
		Vector3 m_scale = Vector3::One;

		//�K�E�V�A���u���[
		GaussianBlur gaussianBlur;
	};
}

