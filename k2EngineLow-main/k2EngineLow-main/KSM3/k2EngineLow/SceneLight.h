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
		float pad0;
		Vector3 ligColor;
		float ligRange;
	};
	//スポットライト構造体
	struct SpotLight
	{
		Vector3 ligPosition;
		float pad0;
		Vector3 ligColor;
		float ligRange;
		Vector3 ligDirection;
		float ligAngle;
	};
	//環境ライト構造体
	struct HemLight
	{
		Vector3 groundColor;
		float pad0;
		Vector3 skyColor;
		float pad1;
		Vector3 groundNormal;
	};

	//ライト構造体
	struct Light
	{
		DirectionLight directionLight;	//ディレクションライトの配列
		float pad0;
		Vector3 eyePos;					//視点の位置
		float pad1;
		Vector3 ambientLight;			//環境光
		float pad2;
		PointLight pointLight[10];			//ポイントライトの配列
		SpotLight spotLight[10];			//スポットライトの配列
		HemLight hemLight;				//半球ライトの配列
		float pad3;
		Matrix m_LVP;					//ライトビュースクリーン配列
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

		void SetPointLight(int num, Vector3 position, float range, Vector3 color)
		{
			m_light.pointLight[num].ligPosition = position;
			m_light.pointLight[num].ligRange = range;
			m_light.pointLight[num].ligColor = color;
		}

		void SetSpotLight(int num,Vector3 position, float range, Vector3 color, Vector3 direction, float angle)
		{
			m_light.spotLight[num].ligPosition = position;
			m_light.spotLight[num].ligRange = range;
			m_light.spotLight[num].ligColor = color;
			m_light.spotLight[num].ligDirection = direction;
			m_light.spotLight[num].ligAngle = angle;
		}

		void SetHemLight(Vector3 groundColor, Vector3 skyColor, Vector3 groundNormal)
		{
			m_light.hemLight.groundColor = groundColor;
			m_light.hemLight.skyColor = skyColor;
			m_light.hemLight.groundNormal = groundNormal;
		}

		void SetLVP(Matrix mat)
		{
			m_light.m_LVP = mat;
		}

		Light& GetLight()
		{
			return m_light;
		}

	private:
		Light m_light;	//シーンライト
	};
}

