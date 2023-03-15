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

		//�u���[���̏�����
		//m_bloom.Init(m_mainRenderingTarget);

		// �ŏI�I�ȃe�N�X�`���𒣂�t���邽�߂̃X�v���C�g��������
		m_spiteInitData.m_textures[0] = &m_mainRenderingTarget.GetRenderTargetTexture();
		m_spiteInitData.m_width = m_mainRenderingTarget.GetWidth();
		m_spiteInitData.m_height = m_mainRenderingTarget.GetHeight();
		m_spiteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		m_copyToframeBufferSprite.Init(m_spiteInitData);
	}

	bool RenderingEngine::Start()
	{
		return true;
	}

	void RenderingEngine::Execute(RenderContext& rc)
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
		// MainRenderTarget�I��


		//�u���[����K�p
		//m_bloom.Render(rc, m_mainRenderingTarget);
		

		//�X�v���C�g�ƕ�����`��
		for(auto SobjData:SpriteRenderObject){
			SobjData->OnDraw(rc);
		}
		for (auto FobjData : FontRenderObject) {
			FobjData->OnDraw(rc);
		}
		// MainRenderTarget�I��


		// frameBuffer�Z�b�g
		// ���C�������_�����O�^�[�Q�b�g�̊G���t���[���o�b�t�@�ɃR�s�[
		rc.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);
		m_copyToframeBufferSprite.Draw(rc);



		ModelRenderObject.clear();
		SpriteRenderObject.clear();
		FontRenderObject.clear();
	}
}