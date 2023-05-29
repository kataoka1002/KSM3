#pragma once
class Game;
class Player;
class Customize_UI_ver2;
//�Q�[�����̃J�����𐧌䂷��B
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Move();
	void Update();
	/////////////////////////////////////
	//�����o�ϐ�
	/////////////////////////////////////
	Game* m_game = nullptr;
	Player* m_player = nullptr;	//�v���C���[�B
	Customize_UI_ver2* camera_customize_ui_ver2 = nullptr;
	SoundSource* m_walkSE = nullptr;				//����SE
	EffectEmitter* sunabokoriEffect = nullptr;		//���ڂ���G�t�F�N�g

	Vector3 pos = Vector3::Zero;
	Vector3 m_cameraForward = { 0.0f,0.0f,1.0f };
	Vector3 m_toCameraPos;	//�����_���王�_�Ɍ������x�N�g���B
	int CameraState = 4;	//1�o�g����,2��,3�J�X�^�}�C�Y,4�o��V�[��
	Vector3 target;
	SpringCamera m_springCamera;	//�΂˃J�����B
	int opCount = 0;
	int fast_count=0;
	bool trance_Finish =false;
	bool VibFlag = false;			//��ʂ��h��Ă��邩�ǂ���
	bool VibBigFlag = false;			//��ʂ��h��Ă��邩�ǂ���(��)
	bool VibFinalFlag = false;			//��ʂ��h��Ă��邩�ǂ���(�ŏI)
	int BGX = 0, BGY = 0;			//�ŏI�I�ȗh��̑傫��
	int effectCount = 0;
	float VIBRATION_MAX = 40.0f;	
	float VIBRATION_BIG_MAX = 160.0f;
	float VIBRATION_FINAL_MAX = 320.0f;
	float x;
	float y;
};
