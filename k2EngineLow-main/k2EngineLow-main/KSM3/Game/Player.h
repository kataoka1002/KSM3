#pragma once

class Left_arm_weapons;

class Customize_UI_ver2;



class Player:public IGameObject
{
public:
	Player();
	~Player();
	void Update();									//�X�V����
	void Render(RenderContext& rc);					//�`�揈��
	void Move();									//�ړ�����
	void ManageState();								//�X�e�[�g�Ǘ�
	void pause();									//�|�[�Y���
	void MakeEfe();									//�G�t�F�N�g�Đ�
	


	ModelRender player_modelRender;					//���f�������_�[
	Vector3 player_position;						//���W
	CharacterController characterController;		//�L�����N�^�[�R���g���[���[
	Quaternion player_rotation;						//�N�H�[�^�j�I��
	Vector3 player_moveSpeed;						//�ړ����x

	float fsin[360], fcos[360];
	Vector3 playerFowrad = { 0.0f, 0.0f, 1.0f };	//�v���C���[�̐��ʃx�N�g��


	int game_state=0;								//�Q�[�����ǂ̏�ԉ��̊Ǘ�(0���C���Q�[��,1�|�[�Y���,2��,3�J�X�^�}�C�Y)


	Left_arm_weapons* p_left_arm_weapons = nullptr;
	Customize_UI_ver2* p_customize_ui_ver2;
	
	
	SpriteRender pouse_spriteRender;				//pause��ʗp�̃X�v���C�g�����_�[

	int game_end_state = 0;							//�Q�[���̏I������

	//�G�t�F�N�g�֌W
	EffectEmitter* sunabokoriEffect = nullptr;
	int effectCount = 0;

		
	int p_custom_point[2][3] = { {0,0,0},{0,0,0} }; //[0][0]�E�r,[0][1]��,[0][2]���r,[1][0]�E��,[1][2]����
	 

	float accelerator = 0;
	float brake = 0;
	bool attack_state_la = false;
	bool attack_state_ll = false;
	bool attack_state_rl = false;
	bool attack_state_ra = false;
	bool attack_state_s = false;
	float move_s;

	


	bool enemy_survival = true;
	bool boss_survival = true;
};

