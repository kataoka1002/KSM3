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

		// �X�P���g�����������B
		InitSkeleton(filePath);
		// �A�j���[�V�������������B
		InitAnimation(animationClips, numAnimationClips, enModelUpAxis);


		//���f���̏�����
		ModelInitData modelInitData;
		//�e���𗎂Ƃ��������Ƃ��������ŃV�F�[�_�[��ς���
		if(m_shadowDrop==true){
			// ���f���̏�����
			modelInitData.m_tkmFilePath = filePath;
			modelInitData.m_fxFilePath = "Assets/shader/model.fx";
			modelInitData.m_expandConstantBuffer = &g_renderingEngine->GetLightingCB();
			modelInitData.m_expandConstantBufferSize = sizeof(g_renderingEngine->GetLightingCB());
			modelInitData.m_modelUpAxis = enModelUpAxis;

			// �V���h�E�}�b�v�ɕ`�悷�郂�f����������
			ModelInitData shadowModelInitData;
			shadowModelInitData.m_tkmFilePath = filePath;
			shadowModelInitData.m_fxFilePath = "Assets/shader/model.fx";
			shadowModelInitData.m_psEntryPointFunc = "PSShadowMain";
			// �J���[�o�b�t�@�[�̃t�H�[�}�b�g�ɕύX���������̂ŁA��������ύX����
			shadowModelInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32_FLOAT;
			m_shadowModel.Init(shadowModelInitData);
		}
		else {
			// �e���󂯂�w�i���f����������
			ModelInitData bgModelInitData;
			// �V���h�E���V�[�o�[(�e�����Ƃ���郂�f��)�p�̃V�F�[�_�[���w�肷��
			bgModelInitData.m_fxFilePath = "Assets/shader/shadowReciever2.fx";
			// �V���h�E�}�b�v���g��SRV�ɐݒ肷��
			bgModelInitData.m_expandShaderResoruceView[0] = &g_renderingEngine->GetShadowTarget().GetRenderTargetTexture();
			// ���C�g�r���[�v���W�F�N�V�����s����g���萔�o�b�t�@�[�ɐݒ肷��
			bgModelInitData.m_expandConstantBuffer = (void*)&g_renderingEngine->GetLightCamera().GetViewProjectionMatrix();
			bgModelInitData.m_expandConstantBufferSize = sizeof(g_renderingEngine->GetLightCamera().GetViewProjectionMatrix());
			bgModelInitData.m_tkmFilePath = filePath;
			m_model.Init(bgModelInitData);
		}



		//�A�j���[�V�����L���ŃG���g���[�|�C���g��ς���
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
		//���f�����Ɉړ���]�g���n��
		m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
		//�e�̃��f���Ɉړ���]�g���n��
		m_shadowModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);


		if (m_skeleton.IsInited()) {
			m_skeleton.Update(m_model.GetWorldMatrix());
		}
		//�A�j���[�V������i�߂�B
		m_animation.Progress(g_gameTime->GetFrameDeltaTime() * m_animationSpeed);

		//��l���Ȃ烉�C�g�J������ǔ�������
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
		//�X�P���g���̃f�[�^��ǂݍ��݁B
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
