#pragma once
#include "Game.h"
#include "GameCamera.h"

class Game;
class Player;
class Drop_item;
class GameCamera;
class Combo;
class Enemy_HP_UI;


class EnemyBase : public IGameObject, Noncopyable
{
public:

	//�R���X�g���N�^
	EnemyBase(){}


	//�f�X�g���N�^�̓o�[�`�����ɂ��Ă���
	virtual ~EnemyBase(){}


	bool Start();
	void CalcDistance(float dist);				//�����̓v���C���[�����b�N�I������܂ł̋���
	void CalcSpeed(float speed,int dirState);	//�ړ����x�v�Z
	void NormalAction(float dist);				//�����̓v���C���[�����b�N�I������܂ł̋���
	void MakePoint();							//�p�X�ړ��p�̃|�C���g�𐶐�
	Vector3 RandPos();							//�����_���ȃ|�W�V������ݒ肷��
	void DustEffect();							//���ڂ���G�t�F�N�g
	void ExecuteOnEnemyDefeated();				//���S���̏���
	void ItemDrop();							//�A�C�e���h���b�v
	void WeaponSetUp();							//����Z�b�g
	void WeaponMove();							//����鏈��
	void PassMove();							//�p�X�ړ�
	void PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale);
	void AsiotoSEManage(bool play);
	void PushButton();
	void ToPushButton();

	//�������z�֐��ɂ��āA�h���N���X�Ŏ�������B
	virtual void GameSetUp()				= 0;	//�Q�[���S�ʂ̏�����
	virtual void Update()					= 0;	//�X�V����
	virtual void Render(RenderContext& rc)	= 0;	//�`�揈��
	virtual void Move()						= 0;	//�ړ�����
	virtual void PlayerSearch()				= 0;	//���G����
	virtual void Attack()					= 0;	//�����I��ōU��
	virtual void Fire(int m_weaponNum)		= 0;	//����
	virtual void EnemyDead()				= 0;
	virtual void HPUnder0()					= 0;
	virtual void InitEnemyModel()			= 0;
	virtual void DeleteGoThis()             = 0;


	//getter�֐�-------------------------------------------------------------
	
	/// <summary>
	/// ��]�ʂ�Ԃ�
	/// </summary>
	/// <returns></returns>
	Quaternion GetRot() const
	{
		return m_enemyRotation;
	}

	/// <summary>
	/// �O������Ԃ�
	/// </summary>
	/// <returns></returns>
	Vector3 GetForward() const
	{
		return m_enemyForward;
	}

	
	/// <summary>
	/// �|�W�V������Ԃ�
	/// </summary>
	/// <returns></returns>
	Vector3 GetPos() const
	{
		return m_enemyPosition;
	}

	
	/// <summary>
	/// ���t���Ă��镐��̎�ނ�Ԃ�
	/// </summary>
	/// <returns></returns>
	int GetWeponKind() const
	{		
		return m_setWeapon;
	}
	

	/// <summary>
	/// ���݂�HP��Ԃ�
	/// </summary>
	/// <returns></returns>
	float GetHP() const
	{
		return m_enemyHP;
	}
	

	/// <summary>
	/// HP�̍ő�l��Ԃ�
	/// </summary>
	/// <returns></returns>
	float GetMaxHP() const
	{
		return m_enemyHPMax;
	}

	
	/// <summary>
	/// �X�s�[�h��Ԃ�
	/// </summary>
	/// <returns></returns>
	float GetSpeed() const
	{
		return m_enemySpeed;
	}

	//-------------------------------------------------------------------------


	//setter�֐�---------------------------------------------------------------

	/// <summary>
	/// �_���[�W����
	/// </summary>
	/// <param name="damage">�_���[�W��</param>
	void ApplyDamage(float damage)
	{

		//����HP����_���[�W��������
		m_enemyHP -= damage;


		//0.0f�ȉ��ɂȂ�Ȃ��悤�ɂ���
		m_enemyHP = max(m_enemyHP, 0.0f);

	}

	/// <summary>
	/// �|�W�V�������Z�b�g
	/// </summary>
	/// <param name="pos">�V�����|�W�V����</param>
	void SetPosition(Vector3 pos)
	{

		//�V�����|�W�V�������Z�b�g
		m_enemyPosition = pos;

	}

	//-------------------------------------------------------------------------


//�h���N���X����A�N�Z�X�ł���悤��protected�ɂ��Ă���
protected:

	/// <summary>
	/// �p�X�ړ��p�̍\����
	/// </summary>
	struct Point 
	{
		Vector3 m_position;	//�|�C���g�̍��W
		int m_num;			//�|�C���g�̔ԍ�
	};
	//�p�X�ړ��ɕK�v�ȓz��
	std::vector<Point> m_pointList;
	Point* m_point = nullptr;


	Game* m_game = nullptr;
	Player* m_player = nullptr;
	GameCamera* m_gameCamera = nullptr;
	Drop_item* m_dropItem = nullptr;
	Enemy_HP_UI* m_HPUI = nullptr;
	SoundSource* m_enemyDeadSE = nullptr;			//���񂾂Ƃ��̔��jSE
	SoundSource* m_asiotoSE = nullptr;				//����


	std::unique_ptr<ModelRender> m_enemyModel;						//�G�l�~�[���f��
	std::unique_ptr<ModelRender> m_enemyWeaponModel;					//���탂�f��
	CharacterController m_enemyCharacterController;	//�G�l�~�[�L�����R��
	Quaternion m_weaponRotation;					//����N�H�[�^�j�I��
	Vector3 m_weaponPosition = Vector3::Zero;		//����|�W�V����
	Vector3 m_weaponLocalPos = Vector3::Zero;		//���탍�[�J���|�W�V����
	Vector3 m_toPlayer = Vector3::Zero;				//�v���C���[�ւ̃x�N�g��
	Vector3 m_toPlayerDir = Vector3::Zero;			//�v���C���[�ւ̕���
	Vector3 m_enemyMoveSpeed = Vector3::Zero;		//�G�l�~�[�ړ����x
	Vector3 m_Up = { 0.0f,1.0f,0.0f };				//������̐ݒ�	


	bool m_lockOn = false;							//�G�l�~�[���p�X�̃|�C���g�����b�N�I�����Ă��邩�ǂ���
	bool m_running = false;							//�����Ă��邩�ǂ���
	bool m_asiotoPlay = false;						//�������Ȃ��Ă��邩�ǂ���
	int m_enemyDirState = 0;						//�G�l�~�[�̌���
	int m_attackCount = 0;							//�U���̊Ԋu
	int m_sunaHassei = 0;							//���ڂ��肪��������Ԋu
	float m_distToPlayer = 0;						//�v���C���[�܂ł̋���


	//��������A�h���N���X�O���炢������ϐ�
	Quaternion m_enemyRotation;						//�G�l�~�[�N�H�[�^�j�I��
	Vector3 m_enemyForward = Vector3::Zero;			//�G�l�~�[�̐��ʃx�N�g��
	Vector3 m_enemyPosition = Vector3::Zero;		//�G�l�~�[���W
	int m_setWeapon = 0;							//����̎��
	float m_enemyHP = 0;							//�G�l�~�[�̗̑�
	float m_enemyHPMax = 0;							//�G�l�~�[�̗̑͂̍ő�l
	float m_enemySpeed = 0;							//�G�l�~�[�̈ړ����x
	int m_pushTimer = 300;							//��������܂ł̎���
	bool m_deleteGoThisFlag = false;				//������钼�O���ǂ���
};

