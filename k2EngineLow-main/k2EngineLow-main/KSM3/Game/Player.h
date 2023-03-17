#pragma once

class Left_arm_weapons;



class Player:public IGameObject
{
public:
	Player();
	~Player();
	void Update();    //�X�V����
	void Render(RenderContext& rc);  //�`�揈��
	void Move();   //�ړ�����
	void ManageState();  //�X�e�[�g�Ǘ�
	void pause();//�|�[�Y���

	


	ModelRender player_modelRender;  //���f�������_�[
	Vector3 player_position;  //���W
	CharacterController characterController;  //�L�����N�^�[�R���g���[���[
	Quaternion player_rotation;  //�N�H�[�^�j�I��
	Vector3 player_moveSpeed;   //�ړ����x

	float fsin[360], fcos[360];
	Vector3 playerFowrad = { 0.0f, 0.0f, 1.0f };//�v���C���[�̐��ʃx�N�g��

	int game_state=0;//�Q�[�����ǂ̏�ԉ��̊Ǘ�

	Left_arm_weapons* p_left_arm_weapons = nullptr;
	
	
	SpriteRender pouse_spriteRender;//pause��ʗp�̃X�v���C�g�����_�[

	int game_end_state = 0;//�Q�[���̏I������

	float accelerator = 0;
	float brake = 0;
	bool attack_state_la = false;
	float move_s;

	int p_custom_point[2][3] = { {0,0,0},
						   {0,0,0} };
};

