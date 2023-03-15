#pragma once
#include "SceneLight.h"
#include "Bloom.h"

namespace nsK2EngineLow {

	//class K2EngineLow;
	class FontRender;
	class Bloom;

	class RenderingEngine : public Noncopyable
	{
	public:
		RenderingEngine();
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

		RenderTarget& GetMainRenderTarget()
		{
			return m_mainRenderingTarget;
		}

		Sprite& GetFrameBufferSprite()
		{
			return m_copyToframeBufferSprite;
		}

	private:
		SceneLight m_sceneLight;
		Bloom m_bloom;

		RenderTarget m_mainRenderingTarget;
		SpriteInitData m_spiteInitData;
		Sprite m_copyToframeBufferSprite;

		std::vector<ModelRender*> ModelRenderObject;
		std::vector<SpriteRender*> SpriteRenderObject;
		std::vector<FontRender*> FontRenderObject;
	public:

	};
}
