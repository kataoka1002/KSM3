#pragma once
namespace nsK2EngineLow {

	//�f�B���N�V�������C�g�\����
	struct DirectionLight
	{
		Vector3 ligDirection;
		float pad;
		Vector3 ligColor;
		
	};
	//���C�g�\����
	struct Light
	{
		DirectionLight directionLight[4];	//�f�B���N�V�������C�g�̔z��(�ő�4��)
		Vector3 eyePos;						//���_�̈ʒu
	};

	class SceneLight
	{
	public:
		//������
		void Init();

		void SetDirectionLight(int lightNo, Vector3 direction, Vector3 color)
		{
			m_light.directionLight[lightNo].ligDirection = direction;
			m_light.directionLight[lightNo].ligColor = color;
		}

	private:
		Light m_light;	//�V�[�����C�g
	};
}

