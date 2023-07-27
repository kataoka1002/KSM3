#pragma once
class Game;
class Player;
class Customize_UI_ver2;
//�Q�[�����̃J�����𐧌䂷��B
class GameCamera : public IGameObject, Noncopyable
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void OPMove();
	void Update();
	void ManageVibration();
	void CalcRotation();

	/// <summary>
	/// ��ʗh��̏������s��
	/// </summary>
	/// <param name="decline">������</param>
	/// <param name="maxVib">�h��̍ő�l</param>
	/// <param name="flag">true�F�h��Ă��� , false�F�h��Ă��Ȃ�</param>
	/// <param name="vibration">�h��̑傫��</param>
	void PlayVibration(int decline, int maxVib, bool& flag, int& vibration);


	/// <summary>
	/// �h��Ă��邩�ǂ����̃t���O���Z�b�g����
	/// </summary>
	/// <param name="flag">true�F�h��Ă��� , false�F�h��Ă��Ȃ�</param>
	void SetVibFlag(bool flag)
	{
		m_vibFlag = flag;
	}


	/// <summary>
	/// �h��Ă��邩�ǂ����̃t���O���Z�b�g����
	/// </summary>
	/// <param name="flag">true�F�h��Ă��� , false�F�h��Ă��Ȃ�</param>
	void SetBigVibFlag(bool flag)
	{
		m_bigVibFlag = flag;
	}


	/// <summary>
	/// �h��Ă��邩�ǂ����̃t���O���Z�b�g����
	/// </summary>
	/// <param name="flag">true�F�h��Ă��� , false�F�h��Ă��Ȃ�</param>
	void SetFinalVibFlag(bool flag)
	{
		m_finalVibFlag = flag;
	}


	/// <summary>
	/// �����_���猩���J�����̃|�W�V�������Z�b�g����
	/// </summary>
	/// <param name="pos">�|�W�V����</param>
	void SetToCameraPos(Vector3 pos)
	{
		m_toCameraPos.Set(pos);
	}


	/// <summary>
	/// �^�[�Q�b�g���Z�b�g����
	/// </summary>
	/// <param name="target">�^�[�Q�b�g</param>
	void SetTarget(Vector3 target)
	{
		m_target = target;
	}


	/// <summary>
	/// �X�e�[�g�̐ݒ�
	/// </summary>
	/// <param name="state">�X�e�[�g</param>
	void SetCameraState(int state)
	{
		m_cameraState = state;
	}


	/// <summary>
	/// �J�����̃|�W�V������Ԃ�
	/// </summary>
	/// <returns>�J�����̃|�W�V����</returns>
	Vector3 GetCameraPos() const
	{
		return m_position;
	}


	/// <summary>
	/// �J�����̑O������Ԃ�
	/// </summary>
	/// <returns>�J�����̑O����</returns>
	Vector3 GetCameraForward() const
	{
		return m_cameraForward;
	}


	/// <summary>
	/// �΂˃J������Ԃ�
	/// </summary>
	/// <returns>�΂˃J����</returns>
	const SpringCamera& GetSpringCamera() const
	{
		return m_springCamera;
	}


	/// <summary>
	/// �΂˃J�������u�Ԉړ�������
	/// </summary>
	void SpringCameraRefresh()
	{
		m_springCamera.Refresh();
	}


	/// <summary>
	/// �J�����X�e�[�g��Ԃ�
	/// </summary>
	/// <returns>�X�e�[�g</returns>
	int GetCameraState() const
	{
		return m_cameraState;
	}

private:
	/////////////////////////////////////
	//�����o�ϐ�
	/////////////////////////////////////
	Game* m_game = nullptr;
	Player* m_player = nullptr;						
	SoundSource* m_walkSE = nullptr;				//����SE
	EffectEmitter* m_sunabokoriEffect = nullptr;	//���ڂ���G�t�F�N�g

	Vector3 m_position = Vector3::Zero;
	Vector3 m_cameraForward = { 0.0f,0.0f,1.0f };
	Vector3 m_toCameraPos = Vector3::Zero;			//�����_���王�_�Ɍ������x�N�g��
	Vector3 m_target = Vector3::Zero;
	SpringCamera m_springCamera;					//�΂˃J����

	int m_cameraState = 4;			//1�o�g����,2��,3�J�X�^�}�C�Y,4�o��V�[��
	int m_opCount = 0;
	int BGX = 0, BGY = 0;			//�ŏI�I�ȗh��̑傫��
	int m_effectCount = 0;
	bool m_vibFlag = false;			//��ʂ��h��Ă��邩�ǂ���
	bool m_bigVibFlag = false;		//��ʂ��h��Ă��邩�ǂ���(��)
	bool m_finalVibFlag = false;	//��ʂ��h��Ă��邩�ǂ���(�ŏI)
	float m_stickPowerX = 0;
	float m_stickPowerY = 0;
};
