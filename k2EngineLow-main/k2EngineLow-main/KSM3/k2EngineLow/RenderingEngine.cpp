#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow {

	RenderingEngine::RenderingEngine()
	{
		// MainRenderTarget�Z�b�g
		m_mainRenderingTarget.Create(
			g_graphicsEngine->GetFrameBufferWidth(),    // �e�N�X�`���̕�
			g_graphicsEngine->GetFrameBufferHeight(),   // �e�N�X�`���̍���
			1,											// Mipmap���x��
			1,											// �e�N�X�`���z��̃T�C�Y
			DXGI_FORMAT_R32G32B32A32_FLOAT,				// �J���[�o�b�t�@�̃t�H�[�}�b�g
			DXGI_FORMAT_D32_FLOAT						// �f�v�X�X�e���V���o�b�t�@�̃t�H�[�}�b�g
		);

		// �u���[���̏�����
		//m_bloom.Init(m_mainRenderingTarget);

		// �V���h�E�ׂ̈̏�����
		InitShadowMap();

		// ZPrepass�^�[�Q�b�g�쐬
		InitZPrepassRenderTarget();

		// �g�D�[���}�b�v�̃e�N�X�`���̏�����
		InitToonMap();

		// �ŏI�I�ȃe�N�X�`���𒣂�t���邽�߂̃X�v���C�g��������
		InitFinalSprite();
	}

	bool RenderingEngine::Start()
	{
		return true;
	}

	void RenderingEngine::InitShadowMap()
	{
		//���C�g�J�����̏�����̐ݒ�
		lightCamera.SetUp(0, 1, 0);
		SetLVP(lightCamera.GetViewProjectionMatrix());

		//�V���h�E�}�b�v�p�̃^�[�Q�b�g�̍쐬
		shadowMapTarget.Create(
			1024,	//�𑜓x
			1024,
			1,
			1,
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_D32_FLOAT,
			clearColor
		);
	}

	void RenderingEngine::InitFinalSprite()
	{
		m_spiteInitData.m_textures[0] = &m_mainRenderingTarget.GetRenderTargetTexture();
		m_spiteInitData.m_width = m_mainRenderingTarget.GetWidth();
		m_spiteInitData.m_height = m_mainRenderingTarget.GetHeight();
		m_spiteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		m_copyToframeBufferSprite.Init(m_spiteInitData);
	}

	void RenderingEngine::InitZPrepassRenderTarget()
	{
		m_zprepassRenderTarget.Create(
			g_graphicsEngine->GetFrameBufferWidth(),
			g_graphicsEngine->GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R32G32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);
	}

	void RenderingEngine::InitToonMap()
	{
		//�g�D�[���V�F�[�_�[�̃e�N�X�`����p��
		const wchar_t* shaderTex = L"Assets/shader/texture/shader.DDS";
		m_toonTexture.InitFromDDSFile(shaderTex);
	}

	void RenderingEngine::Execute(RenderContext& rc)
	{
		// ZPrepass
		ZPrepass(rc);

		// �V���h�E�̕`��
		ShadowDraw(rc);

		// ���f���̕`��
		ModelDraw(rc);

		// �摜�ƕ����̕`��
		SpriteFontDraw(rc);

		//�u���[����K�p(ON.OFF�ύX��)
		//m_bloom.Render(rc, m_mainRenderingTarget);

		//�����ŃG�t�F�N�g�h���[�B
		EffectEngine::GetInstance()->Draw();


		// ���C�������_�����O�^�[�Q�b�g�̊G���t���[���o�b�t�@�ɃR�s�[
		CopyMainRenderTargetToFrameBuffer(rc);


		// �N���A
		ModelRenderObject.clear();
		SpriteRenderObject.clear();
		FontRenderObject.clear();
		m_zprepassModelsObject.clear();
	}

	void RenderingEngine::ShadowDraw(RenderContext& rc)
	{
		//�^�[�Q�b�g���V���h�E�}�b�v�ɕύX
		rc.WaitUntilFinishDrawingToRenderTarget(shadowMapTarget);
		rc.SetRenderTargetAndViewport(shadowMapTarget);
		rc.ClearRenderTargetView(shadowMapTarget);

		// �܂Ƃ߂ĉe���f�������_�[��`��
		for (auto MobjData : ModelRenderObject)
		{
			//��l���Ȃ烉�C�g�J�������X�V
			if (MobjData->GetSyuzinkou() == true) {
				//���C�g�J�����̍X�V
				lightCamera.SetPosition(MobjData->GetPositionX() + 600.0f, MobjData->GetPositionY() + 800.0f, MobjData->GetPositionZ());
				lightCamera.SetTarget(MobjData->GetPositionX(), MobjData->GetPositionY(), MobjData->GetPositionZ());
				lightCamera.Update();
			}
			//���C�g�r���[�Z�b�g
			SetLVP(lightCamera.GetViewProjectionMatrix());
			//�e���f���̕`��
			MobjData->OnShadowDraw(rc);
			rc.WaitUntilFinishDrawingToRenderTarget(shadowMapTarget);
		}
	}

	void RenderingEngine::ModelDraw(RenderContext& rc)
	{
		// ���C���̃^�[�Q�b�g���g����悤�ɂȂ�܂ő҂�
		rc.WaitUntilToPossibleSetRenderTarget(m_mainRenderingTarget);
		// �^�[�Q�b�g�Z�b�g
		rc.SetRenderTargetAndViewport(m_mainRenderingTarget);
		// �^�[�Q�b�g�̃N���A
		rc.ClearRenderTargetView(m_mainRenderingTarget);

		// �܂Ƃ߂ă��f�������_�[��`��
		for (auto MobjData : ModelRenderObject) {
			MobjData->OnDraw(rc);
		}

		// �`�悳���܂ő҂�
		rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderingTarget);
	}

	void RenderingEngine::SpriteFontDraw(RenderContext& rc)
	{
		// �X�v���C�g�ƕ�����`��
		for (auto SobjData : SpriteRenderObject) {
			SobjData->OnDraw(rc);
		}
		for (auto FobjData : FontRenderObject) {
			FobjData->OnDraw(rc);
		}
	}

	void RenderingEngine::ZPrepass(RenderContext& rc)
	{
		// �܂��A�����_�����O�^�[�Q�b�g�Ƃ��Đݒ�ł���悤�ɂȂ�܂ő҂�
		rc.WaitUntilToPossibleSetRenderTarget(m_zprepassRenderTarget);
		// �����_�����O�^�[�Q�b�g��ݒ�
		rc.SetRenderTargetAndViewport(m_zprepassRenderTarget);
		// �����_�����O�^�[�Q�b�g���N���A
		rc.ClearRenderTargetView(m_zprepassRenderTarget);

		for (auto& model : m_zprepassModelsObject)
		{
			model->Draw(rc);
		}

		rc.WaitUntilFinishDrawingToRenderTarget(m_zprepassRenderTarget);
	}

	void RenderingEngine::CopyMainRenderTargetToFrameBuffer(RenderContext& rc)
	{
		// �t���[���o�b�t�@�ɃZ�b�g
		rc.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);
		m_copyToframeBufferSprite.Draw(rc);
	}
}