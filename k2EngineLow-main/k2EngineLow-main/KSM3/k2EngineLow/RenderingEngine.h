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

		//アンビエントライトの設定
		void SetAmbientLight(float x,float y,float z)
		{
			m_sceneLight.SetAmbientLight(x, y, z);
		}

		//ポイントライトの設定
		void SetPointLight(Vector3 position, float range, Vector3 color)
		{
			m_sceneLight.SetPointLight(position, range, color);
		}

		//スポットライトの設定
		void SetSpotLight(Vector3 position, float range, Vector3 color, Vector3 direction, float angle)
		{
			m_sceneLight.SetSpotLight(position, range, color, direction, angle);
		}

		//半球ライトの設定
		void SetHemLight(Vector3 groundColor, Vector3 skyColor, Vector3 groundNormal)
		{
			m_sceneLight.SetHemLight(groundColor, skyColor, groundNormal);
		}

		SceneLight& GetLightingCB()
		{
			return m_sceneLight;
		}

	private:
		SceneLight m_sceneLight;
	};
}
