#pragma once

namespace nsK2EngineLow {

	class ModelRender {
	public:
		ModelRender();
		~ModelRender();

		//������
		void Init(const char* filePath,
			bool m_shadowDrop = true,//�e(true�����Ƃ���,false�����Ƃ�����)
			AnimationClip* animationClips = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ);
		//�A�b�v�f�[�g
		void Update(bool m_syuzinkou = false);
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

		//���f���̍��W���擾
		Vector3& GetPosition()
		{
			return m_position;
		}

		//���f����X���W���擾
		float& GetPositionX()
		{
			return m_position.x;
		}

		//���f����Y���W���擾
		float& GetPositionY()
		{
			return m_position.y;
		}

		//���f����Z���W���擾
		float& GetPositionZ()
		{
			return m_position.z;
		}

		bool& GetSyuzinkou()
		{
			return syuok;
		}

		//�A�j���[�V�����̍Đ�
		void PlayAnimation(int animNo, float interpolateTime = 0.0f)//�A�j���[�V�����N���b�v�̔ԍ�,�⊮����
		{
			m_animation.Play(animNo, interpolateTime);
		}

		void OnDraw(RenderContext& rc)
		{
			m_model.Draw(rc);
		}

		void OnShadowDraw(RenderContext& rc)
		{
			m_shadowModel.Draw(rc, g_renderingEngine->GetLightCamera());
		}
		/*
		RenderTarget& GetShadowTarget()
		{
			return shadowMapTarget;
		}

		Camera& GetLightCamera()
		{
			return lightCamera;
		}*/


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
		Model m_shadowModel;

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
		
		bool syuok = false;

		//bool m_drawShadow = false;
	};
}