#pragma once
namespace nsK2EngineLow {

	//�f�B���N�V�������C�g�\����
	struct DirectionLight
	{
		Vector3 ligDirection;
		float pad0;
		Vector3 ligColor;
	};
	//�|�C���g���C�g�\����
	struct PointLight
	{
		Vector3 ligPosition;
		float pad0;
		Vector3 ligColor;
		float ligRange;
	};
	//�X�|�b�g���C�g�\����
	struct SpotLight
	{
		Vector3 ligPosition;
		float pad0;
		Vector3 ligColor;
		float ligRange;
		Vector3 ligDirection;
		float ligAngle;
	};
	//�����C�g�\����
	struct HemLight
	{
		Vector3 groundColor;
		float pad0;
		Vector3 skyColor;
		float pad1;
		Vector3 groundNormal;
	};

	//���C�g�\����
	struct Light
	{
		DirectionLight directionLight;	//�f�B���N�V�������C�g�̔z��
		float pad0;
		Vector3 eyePos;					//���_�̈ʒu
		float pad1;
		Vector3 ambientLight;			//����
		float pad2;
		PointLight pointLight;			//�|�C���g���C�g�̔z��
		SpotLight spotLight;			//�X�|�b�g���C�g�̔z��
		HemLight hemLight;				//�������C�g�̔z��
	};

	/*struct LVP
	{
		Matrix mLVP;
	};*/

	class SceneLight
	{
	public:
		//������
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

		void SetSpotLight(Vector3 position, float range, Vector3 color, Vector3 direction, float angle)
		{
			m_light.spotLight.ligPosition = position;
			m_light.spotLight.ligRange = range;
			m_light.spotLight.ligColor = color;
			m_light.spotLight.ligDirection = direction;
			m_light.spotLight.ligAngle = angle;
		}

		void SetHemLight(Vector3 groundColor, Vector3 skyColor, Vector3 groundNormal)
		{
			m_light.hemLight.groundColor = groundColor;
			m_light.hemLight.skyColor = skyColor;
			m_light.hemLight.groundNormal = groundNormal;
		}

		/*void SetmLVP(Matrix mat)
		{
			m_lVP.mLVP = mat;
		}
		
		Matrix& GetLVP()
		{
			return m_lVP.mLVP;
		}*/
	private:
		Light m_light;	//�V�[�����C�g
		/*LVP m_lVP;*/
	};
}

