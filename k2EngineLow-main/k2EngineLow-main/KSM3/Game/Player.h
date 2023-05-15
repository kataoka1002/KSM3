#pragma once

class Left_arm_weapons;
class Customize_UI_ver2;
class Result;
class Game;

class Player:public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();									//�X�V����
	void Render(RenderContext& rc);					//�`�揈��
	void Move();									//�ړ�����
	void RunSE();									//�X�e�[�g�Ǘ�
	void pause();									//�|�[�Y���
	void MakeEfe();									//�G�t�F�N�g�Đ�
	void MachineGunSE();

	SoundSource* m_machineGunSE = nullptr;			//�}�V���K��SE
	SoundSource* m_runSE = nullptr;					//����SE
	SoundSource* m_walkSE = nullptr;				//����SE
	SoundSource* m_kettei = nullptr;
	ModelRender player_modelRender;					//���f�������_�[
	Vector3 player_position;						//���W
	CharacterController characterController;		//�L�����N�^�[�R���g���[���[
	Quaternion player_rotation;						//�N�H�[�^�j�I��
	Vector3 player_moveSpeed;						//�ړ����x

	float fsin[360], fcos[360];
	Vector3 playerFowrad = { 0.0f, 0.0f, 1.0f };	//�v���C���[�̐��ʃx�N�g��


	int game_state=0;								//�Q�[�����ǂ̏�ԉ��̊Ǘ�(0���C���Q�[��,1�|�[�Y���,2��,3�J�X�^�}�C�Y)

	Result* m_result = nullptr;
	Left_arm_weapons* p_left_arm_weapons = nullptr;
	Customize_UI_ver2* p_customize_ui_ver2 = nullptr;
	Game* m_game = nullptr;


	int game_end_state = 0;							//�Q�[���̏I������

	SpriteRender pouse_spriteRender;	//pause��ʗp�̃X�v���C�g�����_�[

	//�G�t�F�N�g�֌W
	EffectEmitter* sunabokoriEffect = nullptr;
	int effectCount = 0;

	int killEnemy = 0;	//�G���E������(10�ɂȂ�ƃE�F�[�u���i��)
						
	
						
						
	int p_custom_point[2][3] = { {0,0,0},{0,0,0} };		//[0][0]�E�r,[0][1]��,[0][2]���r,[1][0]�E��,[1][2]����
					
	
	
	bool m_cameraMove = false;	//�J�����؂�ւ������ǂ���

	float accelerator = 0;
	float brake = 0;
	float throttle = 0;
	bool attack_state_la = false;
	bool attack_state_ll = false;
	bool attack_state_rl = false;
	bool attack_state_ra = false;
	bool attack_state_s = false;
	float move_s;

	float m_playerHP = 500.0f;		//�v���C���[��HP
	float m_playerHPMax = 500.0f;		//�v���C���[��HP�̍ő�l

	bool enemy_survival = true;
	bool boss_survival = true;
};

