#pragma once

class Player;
class Customize_UI_ver2;
//�Q�[�����̃J�����𐧌䂷��B
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	/////////////////////////////////////
	//�����o�ϐ�
	/////////////////////////////////////
	Player* m_player;	//�v���C���[�B
	Customize_UI_ver2* camera_customize_ui_ver2;
	Vector3 m_toCameraPos;	//�����_���王�_�Ɍ������x�N�g���B
	int CameraState = 0;
	Vector3 target;

	int fast_count=0;
	bool trance_Finish =false;

	float x;
	float y;
};
