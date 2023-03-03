#pragma once
#include "SceneLight.h"

namespace nsK2EngineLow {

	class K2EngineLow;

	class RenderingEngine : public Noncopyable
	{
	public:

		RenderingEngine()
		{
		}
		~RenderingEngine()
		{
		}

		//�f�B���N�V�������C�g�̐ݒ�
		void SetDirectionLight(int lightNo, Vector3 direction, Vector3 color)
		{
			m_sceneLight.SetDirectionLight(lightNo, direction, color);
		}

		SceneLight& GetLightingCB()
		{
			return m_sceneLight;
		}

	private:
		SceneLight m_sceneLight;
	};
}
