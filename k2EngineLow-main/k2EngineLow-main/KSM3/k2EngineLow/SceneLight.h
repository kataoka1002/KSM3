#pragma once
namespace nsK2EngineLow {

	//ディレクションライト構造体
	struct DirectionLight
	{
		Vector3 ligDirection;
		float pad0;
		Vector3 ligColor;
	};
	//ポイントライト構造体
	struct PointLight
	{
		Vector3 ligPosition;
		float pad1;
		Vector3 ligColor;
		//float pad2;
		float ligRange;
	};

	//ライト構造体
	struct Light
	{
		DirectionLight directionLight;	//ディレクションライトの配列(最大4つ)
		float pad3;
		Vector3 eyePos;						//視点の位置
		float pad4;
		Vector3 ambientLight;				//環境光
		float pad5;
		PointLight pointLight;			//ポイントライトの配列(最大10個)
	};

	class SceneLight
	{
	public:
		//初期化
		void Init()
		{
			m_light.eyePos = g_camera3D->GetPosition();
		}

		void SetDirectionLight( Vector3 direction, Vector3 color)
		{
			m_light.directionLight.ligDirection = direction;
			m_light.directionLight.ligColor = color;
		}

		void SetAmbientLight(float x, float y, float z)
		{
			m_light.ambientLight.x = x;
			m_light.ambientLight.y = y;
			m_light.ambientLight.z = z;
		}

		void SetPointLight(Vector3 position, float range, Vector3 color)
		{
			m_light.pointLight.ligPosition = position;
			m_light.pointLight.ligRange = range;
			m_light.pointLight.ligColor = color;
		}


	private:
		Light m_light;	//シーンライト
	};
}

