#pragma once
#include "SceneLight.h"

namespace nsK2EngineLow {

	class K2EngineLow;
	class FontRender;

	class RenderingEngine : public Noncopyable
	{
	public:
		bool Start();
		void Execute(RenderContext& rc);

		//�f�B���N�V�������C�g�̐ݒ�
		void SetDirectionLight( Vector3 direction, Vector3 color)
		{
			m_sceneLight.SetDirectionLight( direction, color);
		}

		//�A���r�G���g���C�g�̐ݒ�
		void SetAmbientLight(float x,float y,float z)
		{
			m_sceneLight.SetAmbientLight(x, y, z);
		}

		//�|�C���g���C�g�̐ݒ�
		void SetPointLight(Vector3 position, float range, Vector3 color)
		{
			m_sceneLight.SetPointLight(position, range, color);
		}

		//�X�|�b�g���C�g�̐ݒ�
		void SetSpotLight(Vector3 position, float range, Vector3 color, Vector3 direction, float angle)
		{
			m_sceneLight.SetSpotLight(position, range, color, direction, angle);
		}

		//�������C�g�̐ݒ�
		void SetHemLight(Vector3 groundColor, Vector3 skyColor, Vector3 groundNormal)
		{
			m_sceneLight.SetHemLight(groundColor, skyColor, groundNormal);
		}

		SceneLight& GetLightingCB()
		{
			return m_sceneLight;
		}

		//�����_�����O�^�[�Q�b�g���쐬����(�������̑O�ɍs��)
		void MakeRenderTarget(RenderTarget& targetName, int w, int h, int mipLevel, int arraySize, DXGI_FORMAT colorFormat, DXGI_FORMAT depthStencilFormat)
		{
			targetName.Create(
				w,                      // �e�N�X�`���̕�
				h,                      // �e�N�X�`���̍���
				mipLevel,               // Mipmap���x��
				arraySize,              // �e�N�X�`���z��̃T�C�Y
				colorFormat,			// �J���[�o�b�t�@�̃t�H�[�}�b�g
				depthStencilFormat		// �f�v�X�X�e���V���o�b�t�@�̃t�H�[�}�b�g
			);
		}

		void AddModelRenderObject(ModelRender* modelRender)
		{
			//�R���e�i�̌��ɂ�������
			ModelRenderObject.push_back(modelRender);
		}

		void AddSpriteRenderObject(SpriteRender* spriteRender)
		{
			//�R���e�i�̌��ɂ�������
			SpriteRenderObject.push_back(spriteRender);
		}

		void AddFontRenderObject(FontRender* fontRender)
		{
			//�R���e�i�̌��ɂ�������
			FontRenderObject.push_back(fontRender);
		}

	private:
		SceneLight m_sceneLight;
		RenderTarget offscreenRenderTarget;
		RenderContext& renderContext = g_graphicsEngine->GetRenderContext();

		std::vector<ModelRender*> ModelRenderObject;
		std::vector<SpriteRender*> SpriteRenderObject;
		std::vector<FontRender*> FontRenderObject;
	};
}
