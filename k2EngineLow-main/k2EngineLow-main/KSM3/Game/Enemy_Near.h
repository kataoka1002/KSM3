#pragma once
#define HP 200.0f

class Player;
class Battle_ship_attack;
class Drop_item;

class Enemy_Near :public IGameObject
{
public:

	//�p�X�ړ��p
	struct Point {
		Vector3 m_position;	//�|�C���g�̍��W
		int m_num;			//�|�C���g�̔ԍ�
	};

	Enemy_Near();
	~Enemy_Near();
	

	bool Start();
	void Update();					//�X�V����
	void Render(RenderContext& rc);	//�`�揈��
	void Move();					//�ړ�����
	void PlayerSearch();			//���G����
	void ItemDrop();				//�A�C�e���h���b�v
	void WeaponMove();				//����鏈��
	void SetUp();					//����Z�b�g
	void Attack();					//�����I��ōU��
	void Fire();					//����
	void PassMove();				//�p�X�ړ�


	//�p�X�ړ��ɕK�v�ȓz��
	std::vector<Point> m_pointList;
	Point* m_point;

	Player* m_player = nullptr;
	Battle_ship_attack* m_battleShipAttack;
	Drop_item* m_dropItem;

	ModelRender m_enemyModel;						//�G�l�~�[���f��
	ModelRender m_enemyWeaponModel;					//���탂�f��
	CharacterController m_enemyCharacterController;	//�G�l�~�[�L�����R��
	Quaternion m_enemyRotation;						//�G�l�~�[�N�H�[�^�j�I��
	Quaternion m_weaponRotation;					//����N�H�[�^�j�I��
	Vector3 m_enemyPosition;						//�G�l�~�[���W
	Vector3 m_weaponPosition;						//����|�W�V����
	Vector3 m_enemyMoveSpeed;						//�G�l�~�[�ړ����x
	Vector3 m_enemyForward{ 0.0f,0.0f,-1.0f };		//�G�l�~�[�̐��ʃx�N�g��
	Vector3 m_toPlayer;								//�v���C���[�ւ̃x�N�g��
	Vector3 m_toPlayerDir;							//�v���C���[�ւ̕���
	Vector3 m_Up = { 0.0f,1.0f,0.0f };				//������̐ݒ�	
	Vector3 m_enemyTargetPos = { 0.0f,0.0f,0.0f };	//�^�[�Q�b�g�̃|�W�V����
	Vector3 m_toTarget;								//�^�[�Q�b�g�ւ̕���

	bool m_defeatState = false;						//���񂾂��ǂ����t���O
	bool m_enemyEscape = false;						//��ޒ����ǂ����t���O
	bool m_attackFlag = false;
	bool m_fireFlag = false;						//�U���t���O
	bool m_dashFlag = false;						//�_�b�V�����Ă��邩�t���O
	bool m_targetFlag = false;						//�^�[�Q�b�g��ݒ肵�Ă��邩�ǂ����t���O
	bool m_lockOn = false;							//�v���C���[�����b�N�I�����Ă��邩�ǂ���
	int m_setWeapon = 0;							//����̎��
	int m_enemyDirState = 0;						//�G�l�~�[�̌���
	int m_enemyGameState = 0;
	int m_attackCount = 0;							//�U���̊Ԋu
	int m_recoilCount = 300;						//�����̎���
	float m_distToPlayer;							//�v���C���[�܂ł̋���
	float m_enemyHP = HP;							//�G�l�~�[�̗̑�
	float m_distTarget;								//�^�[�Q�b�g�܂ł̋���

};

