#pragma once

namespace nsK2EngineLow {
	class RenderingEngine;

	//�X�L�����f�������_�[
	class ModelRender
	{
	public:
		ModelRender();
		~ModelRender();

		//������
		void Init(
			const char* filePath,
			AnimationClip* animation = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ,
			bool isShadowReciever = true,
			int maxInstance = 1,
			bool isFrontCullingOnDrawShadowMap = false
		);

		//�������`����s���I�u�W�F�N�g���������B
		void IniTranslucent(
			const char* filePath,
			AnimationClip* animationClips = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ,
			bool isShadowReciever = true,
			int maxInstance = 1,
			bool isFrontCullingOnDrawShadowMap = false);

		//����ȃV�F�[�f�B���O���s�������ꍇ�̏���������
		void InitForwardRenderring(ModelInitData& initData);

		//�X�V����
		void Update();

		//�C���X�^���V���O�f�[�^�̍X�V
		void UpdateInstancingData(int instanceNo, const Vector3& pos, const Quaternion& rot, const Vector3& scale);

		//�`�揈��
		void Draw(RenderContext& rc);

		//�A�j���[�V�����Đ�
		void PlayAnimation(int animNo, float interpolateTime = 0.0f)
		{
			m_animation.Play(animNo, interpolateTime);
		};

		//�A�j���[�V�����Đ����H
		bool IsPlayingAnimation()const
		{
			return m_animation.IsPlaying();
		}

		//���f�����擾
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
			//�����܂ŗ���̂͂�������
			return m_zprepassModel;
		}

		//���W�A��]�A�g���S�Đݒ�
		void SetTRS(const Vector3& pos, const Quaternion& rotation, const Vector3& scale)
		{
			SetPosition(pos);
			SetRotation(rotation);
			SetScale(scale);
		}

		//���W�ݒ�
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x,y,z });
		}
		//��]��ݒ�
		void SetRotation(const Quaternion& rotation)
		{
			m_rotation = rotation;
		}
		//�g�嗦�ݒ�
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}
		void SetScale(float x, float y, float z)
		{
			SetScale({ x,y,z });
		}

		//�V���h�E�L���X�^�[�̃t���O��ݒ肷��
		void SetShadowCasterFlag(bool flag)
		{
			m_isShadowCaster = flag;
		}

		//�A�j���[�V�����Đ����x��ݒ肷��
		void SetAnimationSpeed(const float animationSpeed)
		{
			m_animationSpeed = animationSpeed;
		}

		//�{�[���̖��O����{�[���ԍ�������
		int FindBoneID(const wchar_t* boneName)const
		{
			return m_skeleton.FindBoneID(boneName);
		}
		//�{�[���ԍ�����{�[�����擾
		Bone* GetBone(int bone)const
		{
			return m_skeleton.GetBone(boneNo);
		}
		void AddAnimationEvent(AnimationEventListener eventListener)
		{
			m_animation.AddAnimationEventListener(eventListener);
		}

		//�V���h�E�L���X�^�[�H
		bool IsShadowCaster()const
		{
			return m_isShadowCaster;
		}

		//�C���X�^���X�����擾
		int GetNumInstance()const
		{
			return m_numInstance;
		}

		//�C���X�^���V���O�`����s��
		bool IsInstancingDraw()const
		{
			return m_isEnableInstancingDraw;
		}

		//���[���h�s����擾
		const Matrix& GetWorldMatrix(int instanceId) const
		{
			if (IsInstancingDraw()) {
				return m_worldMatrixArray[instanceId];
			}
			return m_zprepassModel.GetWorldMatrix();
		}

		//�C���X�^���X������
		void RemoveInstance(int instanceNo);

		//���C�g�����[���h�ɓo�^���邩�̃t���O��ݒ肷��
		//�p�ɂɐ������郂�f���i�e�Ȃǁj��Init����O�Ɉ���false�Ŏ��s���Ă��������B
		void SetRaytracingWorld(bool flag) {
			m_isRaytracingWorld = flag;
		}
	public:
		static const int NUM_SHADOW_LIGHT = 1;
	private:
		AnimationClip* m_animationClips = nullptr;
		int							m_numAnimationClips = 0;			// �A�j���[�V�����N���b�v�̐��B
		Vector3 					m_position = Vector3::Zero;			// ���W�B
		Quaternion	 				m_rotation = Quaternion::Identity;	// ��]�B
		Vector3						m_scale = Vector3::One;				// �g�嗦�B
		EnModelUpAxis				m_enFbxUpAxis = enModelUpAxisZ;		// FBX�̏�����B
		Animation					m_animation;						// �A�j���[�V�����B
		ComputeAnimationVertexBuffer m_computeAnimationVertexBuffer;	// �A�j���[�V�����ςݒ��_�o�b�t�@�̌v�Z�����B
		Model* m_addRaytracingWorldModel = nullptr;// ���C�g�����[���h�ɓo�^�������f���B				
		Model						m_zprepassModel;					// ZPrepass�ŕ`�悳��郂�f��
		Model						m_forwardRenderModel;				// �t�H���[�h�����_�����O�̕`��p�X�ŕ`�悳��郂�f��
		Model						m_translucentModel;					// ���������f���B
		Model						m_renderToGBufferModel;				// RenderToGBuffer�ŕ`�悳��郂�f��
		Model						m_shadowModels[MAX_DIRECTIONAL_LIGHT][NUM_SHADOW_MAP];	// �V���h�E�}�b�v�ɕ`�悷�郂�f��
		ConstantBuffer				m_drawShadowMapCameraParamCB[MAX_DIRECTIONAL_LIGHT][NUM_SHADOW_MAP];		// �V���h�E�}�b�v�쐬���ɕK�v�ȃJ�����p�����[�^�p�̒萔�o�b�t�@�B
		bool						m_isUpdateAnimation = true;			// �A�j���[�V�������X�V����H
		Skeleton					m_skeleton;							// ���B
		bool						m_isShadowCaster = true;			// �V���h�E�L���X�^�[�t���O
		float						m_animationSpeed = 1.0f;
		int							m_numInstance = 0;					// �C���X�^���X�̐��B
		int							m_maxInstance = 1;					// �ő�C���X�^���X���B
		bool						m_isEnableInstancingDraw = false;	// �C���X�^���V���O�`�悪�L���H
		bool						m_isRaytracingWorld = true;			//���C�g�����[���h�ɓo�^����H
		std::unique_ptr<Matrix[]>	m_worldMatrixArray;					// ���[���h�s��̔z��B
		StructuredBuffer			m_worldMatrixArraySB;				// ���[���h�s��̔z��̃X�g���N�`���[�h�o�b�t�@�B
		std::vector< GemometryData > m_geometryDatas;					// �W�I���g�����B
		std::unique_ptr<int[]>		m_instanceNoToWorldMatrixArrayIndexTable;	// �C���X�^���X�ԍ����烏�[���h�s��̔z��̃C���f�b�N�X�ɕϊ�����e�[�u���B

	};
}

