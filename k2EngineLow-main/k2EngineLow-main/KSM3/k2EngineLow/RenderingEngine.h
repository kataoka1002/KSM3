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

		//ディレクションライトの設定
		void SetDirectionLight( Vector3 direction, Vector3 color)
		{
			m_sceneLight.SetDirectionLight( direction, color);
		}

		void SetPointLight(Vector3 position, float range, Vector3 color)
		{
			m_sceneLight.SetPointLight(position, range, color);
		}

		void SetAmbientLight(float x,float y,float z)
		{
			m_sceneLight.SetAmbientLight(x, y, z);
		}

		SceneLight& GetLightingCB()
		{
			return m_sceneLight;
		}

	private:
		SceneLight m_sceneLight;
	};
}
