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

	Result* m_result = nullptr;
	Left_arm_weapons* p_left_arm_weapons = nullptr;
	Customize_UI_ver2* p_customize_ui_ver2 = nullptr;
	Game* m_game = nullptr;
	SoundSource* m_machineGunSE = nullptr;			//�}�V���K��SE
	SoundSource* m_runSE = nullptr;					//����SE
	SoundSource* m_walkSE = nullptr;				//����SE
	SoundSource* m_kettei = nullptr;

	ModelRender player_modelRender;					//���f�������_�[
	SpriteRender pouse_spriteRender;				//pause��ʗp�̃X�v���C�g�����_�[
	EffectEmitter* sunabokoriEffect = nullptr;
	CharacterController characterController;		//�L�����N�^�[�R���g���[���[
	Vector3 player_position = {0.0f,0.0f,-1000.0f};						//���W
	Vector3 player_moveSpeed;						//�ړ����x
	Vector3 playerForward = { 0.0f, 0.0f, 1.0f };	//�v���C���[�̐��ʃx�N�g��
	Quaternion player_rotation;						//�N�H�[�^�j�I��

	int game_state = 4;								//�Q�[�����ǂ̏�Ԃ��̊Ǘ�(0���C���Q�[��,1�|�[�Y���,2���U���g,3�J�X�^�}�C�Y,4�ŏ��̃V�[��,5�{�X��)
	int game_end_state = 0;							//�Q�[���̏I������
	int bossState = 0;								//�{�X�킩�ǂ���
	int effectCount = 0;							//�G�t�F�N�g�֌W
	int killEnemy = 0;								//�G���E������(10�ɂȂ�ƃE�F�[�u���i��)
	int p_custom_point[2][3] = { {0,0,0},{0,0,0} };	//[0][0]�E�r,[0][1]��,[0][2]���r,[1][0]�E��,[1][2]����
	float accelerator = 0;
	float brake = 0;
	float throttle = 0;
	float move_s;
	float m_playerHP = 500.0f;						//�v���C���[��HP
	float m_playerHPMax = 500.0f;					//�v���C���[��HP�̍ő�l
	bool attack_state_la = false;
	bool attack_state_ll = false;
	bool attack_state_rl = false;
	bool attack_state_ra = false;
	bool attack_state_s = false;
	bool m_cameraMove = false;						//�J�����؂�ւ������ǂ���
	bool enemy_survival = true;
	bool boss_survival = true;
	bool m_playerDead = false;						//�v���C���[�����񂾂��ǂ���
};

