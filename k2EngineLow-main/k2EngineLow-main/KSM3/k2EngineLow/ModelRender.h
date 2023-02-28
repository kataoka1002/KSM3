#pragma once

namespace nsK2EngineLow {
	class ModelRender {
	public:
		ModelRender();
		~ModelRender();

		//������
		void Init(const char* filePath, 
			AnimationClip* animationClips = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ);
		//�A�b�v�f�[�g
		void Update();
		//�`�揈��
		void Draw(RenderContext& rc);

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

	public:
		
		
	private:
		//���f��
		Model m_model;
		//�A�j���[�V����
		Animation m_animation;
		AnimationClip* m_animationClips;
		int m_numAnimationClips = 0;
		Skeleton m_skeleton;
		float m_animationSpeed = 1.0f;
		//���W��]�傫��
		Vector3 m_position = { 0.0f,0.0f,0.0f };
		Quaternion m_rotation = { 0.0f,0.0f,0.0f,1.0f };
		Vector3 m_scale = Vector3::One;
		
	};


}