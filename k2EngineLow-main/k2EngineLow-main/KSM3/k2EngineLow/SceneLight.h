#pragma once
namespace nsK2EngineLow {

	//ディレクションライト構造体
	struct DirectionLight
	{
		Vector3 ligDirection;
		float pad;
		Vector3 ligColor;
		
	};
	//ライト構造体
	struct Light
	{
		DirectionLight directionLight[4];	//ディレクションライトの配列(最大4つ)
		Vector3 eyePos;						//視点の位置
	};

	class SceneLight
	{
	public:
		//初期化
		void Init();

		void SetDirectionLight(int lightNo, Vector3 direction, Vector3 color)
		{
			m_light.directionLight[lightNo].ligDirection = direction;
			m_light.directionLight[lightNo].ligColor = color;
		}

	private:
		Light m_light;	//シーンライト
	};
}

