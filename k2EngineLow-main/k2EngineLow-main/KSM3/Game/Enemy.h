#pragma once
//�N���X�錾�B
class Player;

class Enemy:public IGameObject
{
public:
	//�G�l�~�[�X�e�[�g�B
	enum EnemyState {
		EnemyState_Chase,
		EnemyState_Idle,
	};
public:
	Enemy();
	~Enemy();
	void Init(Vector3 initPos);
	bool Start();
	void Update();
	void Render(RenderContext& rc);


	//�ǐՏ���
	void Chase();
	//�v���C���[�Ɍ������Ď��_�ړ�
	void SearchPlayer();
	//�e�X�e�[�g�̑J�ڏ����B
	void ManageState();
	//���ʂ̃X�e�[�g�J�ڏ����B
	void ProcessCommonStateTransition();
	//�ҋ@����
	void ProcessIdleStateTransition();
	//�ǐՏ���
	void ProcessChaseStateTransition();

	ModelRender m_modelRender;	//���f�������_�[
	EnemyState m_enemyState;
	Vector3 m_position;		//���W
	Vector3 m_moveSpeed;	//�ړ����x
	CharacterController	m_charaCon;	   //�L�����R���B
	Quaternion m_rotation;	//��]
	Player* m_player = nullptr;		//�v���C���[�B
	Vector3	m_forward = { 0.0f, 0.0f, -1.0f };		//�G�l�~�[�̐��ʃx�N�g���B
	float	m_chaseTimer = 0.0f;	//�ǐՃ^�C�}�[
	float	m_idleTimer = 0.0f;	   //�ҋ@�^�C�}�[
};

