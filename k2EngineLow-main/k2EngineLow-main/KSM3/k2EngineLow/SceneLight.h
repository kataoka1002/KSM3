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
		float pad1;
		Vector3 ligColor;
		//float pad2;
		float ligRange;
	};

	//���C�g�\����
	struct Light
	{
		DirectionLight directionLight;	//�f�B���N�V�������C�g�̔z��(�ő�4��)
		float pad3;
		Vector3 eyePos;						//���_�̈ʒu
		float pad4;
		Vector3 ambientLight;				//����
		float pad5;
		PointLight pointLight;			//�|�C���g���C�g�̔z��(�ő�10��)
	};

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


	private:
		Light m_light;	//�V�[�����C�g
	};
}

