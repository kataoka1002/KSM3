#include "k2EngineLowPreCompile.h"
#include "BloomModelRender.h"

namespace nsK2EngineLow
{
	BloomModelRender::BloomModelRender()
	{

	}

	BloomModelRender::~BloomModelRender()
	{

	}

	bool BloomModelRender::Start()
	{
		return true;
	}

	void BloomModelRender::InitModel(const char* filePath, DXGI_FORMAT colorFormat,AnimationClip* animationClips,int numAnimationClips,EnModelUpAxis enModelUpAxis)
	{
		// �X�P���g�����������B
		InitSkeleton(filePath);
		// �A�j���[�V�������������B
		InitAnimation(animationClips, numAnimationClips, enModelUpAxis);


		//���f���̏�����
		ModelInitData modelInitData;
		modelInitData.m_tkmFilePath = filePath;
		modelInitData.m_fxFilePath = "Assets/shader/model.fx";
		modelInitData.m_expandConstantBuffer = &g_renderingEngine->GetLightingCB();
		modelInitData.m_expandConstantBufferSize = sizeof(g_renderingEngine->GetLightingCB());
		modelInitData.m_colorBufferFormat[0] = colorFormat;
		modelInitData.m_modelUpAxis = enModelUpAxis;


		if (animationClips != nullptr) {
			modelInitData.m_skeleton = &m_skeleton;
			modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
		}
		else {
			modelInitData.m_vsEntryPointFunc = "VSMain";
		}


		m_model.Init(modelInitData);
	}

	void BloomModelRender::InitLuminance(DXGI_FORMAT colorFormat, RenderTarget&mainTargetName)
	{
		//�P�x���o�X�v���C�g�̏�����
		SpriteInitData spriteInitData;
		spriteInitData.m_fxFilePath ="Assets/shader/PostEffect.fx";
		spriteInitData.m_vsEntryPointFunc = "VSMain";
		spriteInitData.m_psEntryPoinFunc = "PSSamplingLuminance";
		spriteInitData.m_width = mainTargetName.GetWidth();
		spriteInitData.m_height = mainTargetName.GetHeight();
		spriteInitData.m_textures[0] = &mainTargetName.GetRenderTargetTexture();
		spriteInitData.m_colorBufferFormat[0] = colorFormat;

		//�쐬�����������������ƂɃX�v���C�g������������
		m_luminanceSprite.Init(spriteInitData);
	}

	void BloomModelRender::InitSome(RenderTarget& luminanceTargetName, RenderTarget& mainTargetName, DXGI_FORMAT colorFormat)
	{
		//�K�E�V�A���u���[�̏�����
		gaussianBlur.Init(&luminanceTargetName.GetRenderTargetTexture());

		//�{�P�摜�p�X�v���C�g�̏�����
		SpriteInitData finalSpriteInitData;
		finalSpriteInitData.m_textures[0] = &gaussianBlur.GetBokeTexture();
		//�𑜓x�̓��C���^�[�Q�b�g�̕��ƍ���
		finalSpriteInitData.m_width = mainTargetName.GetWidth();
		finalSpriteInitData.m_height = mainTargetName.GetHeight();
		//�ڂ������摜��ʏ��2D�Ƃ��ă��C�������_�����O�^�[�Q�b�g�ɕ`�悷�邽��2D�p�̃V�F�[�_�[�𗘗p
		finalSpriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		//���������Z�����ŕ`�悷��̂ŃA���t�@�u�����f�B���O���[�h�����Z�ɂ���
		finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;
		//�J���[�o�b�t�@�[�̃t�H�[�}�b�g�ݒ�
		finalSpriteInitData.m_colorBufferFormat[0] = colorFormat;
		//�������������Ƃɉ��Z�����p�̃X�v���C�g������������
		m_finalSprite.Init(finalSpriteInitData);
	}

	void BloomModelRender::InitSprite(RenderTarget& mainTargetName)
	{
		//�e�N�X�`���𒣂�t���邽�߂̃X�v���C�g��������
		SpriteInitData spiteInitData;
		spiteInitData.m_textures[0] = &mainTargetName.GetRenderTargetTexture();
		spiteInitData.m_width = mainTargetName.GetWidth();
		spiteInitData.m_height = mainTargetName.GetHeight();
		spiteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		m_copyToframeBufferSprite.Init(spiteInitData);
	}

	void BloomModelRender::Update()
	{
		//���f�����Ɉړ���]�g���n���̂͂���
		m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

		if (m_skeleton.IsInited()) {
			m_skeleton.Update(m_model.GetWorldMatrix());
		}
		//�A�j���[�V������i�߂�B
		m_animation.Progress(g_gameTime->GetFrameDeltaTime() * m_animationSpeed);
	}

	void BloomModelRender::TargetSet(RenderTarget& luminanceTargetName,RenderTarget& mainTargetName)
	{
		//�^�[�Q�b�g��ύX����
		auto& rc = g_graphicsEngine->GetRenderContext();
		rc.WaitUntilToPossibleSetRenderTarget(mainTargetName);
		rc.SetRenderTargetAndViewport(mainTargetName);
		rc.ClearRenderTargetView(mainTargetName);
		//�����_�����O�^�[�Q�b�g�ւ̏�������
		m_model, Draw(rc);
		rc.WaitUntilFinishDrawingToRenderTarget(mainTargetName);

		//�P�x���o�p�̃^�[�Q�b�g�ɕύX
		rc.WaitUntilToPossibleSetRenderTarget(luminanceTargetName);
		rc.SetRenderTargetAndViewport(luminanceTargetName);
		rc.ClearRenderTargetView(luminanceTargetName);
		m_luminanceSprite.Draw(rc);
		rc.WaitUntilFinishDrawingToRenderTarget(luminanceTargetName);

		//�K�E�V�A���u���[�̎��s
		gaussianBlur.ExecuteOnGPU(rc, 20);

		//�{�P�摜�����C�������_�����O�^�[�Q�b�g�ɉ��Z����
		rc.WaitUntilToPossibleSetRenderTarget(mainTargetName);
		rc.SetRenderTargetAndViewport(mainTargetName);

		//�ŏI����
		m_finalSprite.Draw(rc);
		rc.WaitUntilFinishDrawingToRenderTarget(mainTargetName);

		//���C�������_�����O�^�[�Q�b�g�̊G���t���[���o�b�t�@�ɃR�s�[
		rc.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);
		m_copyToframeBufferSprite.Draw(rc);
	}

	void BloomModelRender::InitAnimation(AnimationClip* animationClips, int numAnimationClips, EnModelUpAxis enModelUpAxis)
	{
		m_animationClips = animationClips;
		m_numAnimationClips = numAnimationClips;
		if (m_animationClips != nullptr) {
			m_animation.Init(m_skeleton,
				m_animationClips,
				numAnimationClips);
		}
	}

	void BloomModelRender::InitSkeleton(const char* filePath)
	{
		//�X�P���g���̃f�[�^��ǂݍ��݁B
		std::string skeletonFilePath = filePath;
		int pos = (int)skeletonFilePath.find(".tkm");
		skeletonFilePath.replace(pos, 4, ".tks");
		m_skeleton.Init(skeletonFilePath.c_str());
	}


	void BloomModelRender::Draw(RenderContext& rc)
	{

	}
}