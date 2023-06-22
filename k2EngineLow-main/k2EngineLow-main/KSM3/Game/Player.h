#pragma once
#include "Game.h"

class Customize_UI_ver2;
class Result;
class Game;
class GameCamera;
class Title;

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
	void PauseSelect();
	void MakeSunabokoriEfe();						//���ڂ���G�t�F�N�g�Đ�
	void MakeEfe(EffectName name, Quaternion rot, Vector3 scale = Vector3::One, Vector3 pos = Vector3::Zero);
	void MachineGunSE();
	void PlayerDeadtoResult();
	void PlayerDead();
	void InitSprite();
	void InitModel();
	void InitSE();


	//getter�֐�----------------------------------------------------------------------


	/// <summary>
	/// ���̃Q�[���X�e�[�g��Ԃ�
	/// </summary>
	/// <returns>0:���C���Q�[��,1:�|�[�Y���,2:���U���g,3:�J�X�^�}�C�Y,4:�ŏ��̃V�[��</returns>
	int GetGameState()
	{
		return m_gameState;
	}


	/// <summary>
	/// �Q�[���̏I�������Ԃ�
	/// </summary>
	/// <returns>1�Ȃ�Q�[���I��</returns>
	int GetGameEndState()
	{
		return m_gameEndState;
	}


	/// <summary>
	/// �{�X�풆���ǂ�����Ԃ�
	/// </summary>
	/// <returns>0�F�Ⴄ , 1�F�{�X��</returns>
	int GetBossState()
	{
		return m_bossState;
	}


	/// <summary>
	/// �v���C���[�����񂾂��ǂ���
	/// </summary>
	/// <returns>false�F�����Ă��� , true�F����ł���</returns>
	bool GetPlayerDead()
	{
		return m_playerDead;
	}


	/// <summary>
	/// ��������t���Ă��镔���𒲂ׂ�
	/// </summary>
	/// <param name="line">�s</param>
	/// <param name="column">��</param>
	/// <returns>0 : �����Ȃ� </returns>
	int GetCustomPoint(int line, int column)
	{
		return m_customPoint[line][column];
	}
	int GetCustomPoint(IntPair intPair)
	{
		return m_customPoint[intPair.first][intPair.second];
	}


	/// <summary>
	/// �v���C���[�̑O������Ԃ�
	/// </summary>
	/// <returns>�v���C���[�̑O����</returns>
	Vector3 GetPlayerForward()
	{
		return m_playerForward;
	}


	/// <summary>
	/// �v���C���[��������ʒu��Ԃ�
	/// </summary>
	/// <returns>�v���C���[�̍�����ʒu</returns>
	Vector3 GetPlayerPosition()
	{
		return m_playerPosition;
	}


	/// <summary>
	/// �v���C���[�̉�]��Ԃ�
	/// </summary>
	/// <returns>�v���C���[�̉�]��</returns>
	Quaternion GetPlayerRotation()
	{
		return m_playerRotation;
	}


	/// <summary>
	/// ���S���̔��j�G�t�F�N�g���Đ��������ǂ���
	/// </summary>
	/// <returns>true�F�Đ����� , false�F�Đ����ĂȂ�</returns>
	bool IsDeadBakuhaPlay()
	{
		return m_deadBakuhaPlay;
	}


	/// <summary>
	/// �E�����G�l�~�[�̐���Ԃ�
	/// </summary>
	/// <returns></returns>
	int GetKillEnemyAmount()
	{
		return m_killEnemyAmountFont;
	}


	/// <summary>
	/// �v���C���[�̍���HP��Ԃ�
	/// </summary>
	/// <returns></returns>
	float GetPlayerHP()
	{
		return m_playerHP;
	}


	/// <summary>
	/// �v���C���[��HP�̍ő�l��Ԃ�
	/// </summary>
	/// <returns></returns>
	float GetPlayerHPMax()
	{
		return m_playerHPMax;
	}


	/// <summary>
	/// �����_���ɑI�΂ꂽ�J���[��Ԃ�
	/// </summary>
	/// <returns></returns>
	int GetRandomColor()
	{
		return m_playerColorRandom;
	}



	/// <summary>
	/// �L�����R����Ԃ�
	/// </summary>
	/// <returns></returns>
	CharacterController& GetCharacterController()
	{
		return m_characterController;
	}


	//--------------------------------------------------------------------------------


	/// <summary>
	/// �v���C���[�̃|�W�V�������Z�b�g����
	/// </summary>
	/// <param name="position">�|�W�V����</param>
	void SetPosition(Vector3 position)
	{
		m_playerPosition = position;
	}


	/// <summary>
	/// �e���ʂɕ�����Z�b�g���Ă��邩��������
	/// </summary>
	/// <param name="line">�s</param>
	/// <param name="column">��</param>
	/// <param name="weaponKind">����̎��</param>
	void SetCustomPoint(int line, int column, int weaponKind)
	{
		m_customPoint[line][column] = weaponKind;
	}
	void SetCustomPoint(IntPair intPair, int weaponKind)
	{
		m_customPoint[intPair.first][intPair.second] = weaponKind;
	}


	/// <summary>
	/// �v���C���[�̃J���[���Z�b�g����
	/// </summary>
	/// <param name="colorData">�J���[�f�[�^</param>
	void SetPlayerColorData(int colorData)
	{
		m_playerColorData = colorData;
	}


	/// <summary>
	/// �Q�[���X�e�[�g���Z�b�g����
	/// </summary>
	/// <param name="gameState">�Q�[���X�e�[�g</param>
	void SetGameState(int gameState)
	{
		m_gameState = gameState;
	}


	/// <summary>
	/// �{�X�̃X�e�[�g��ݒ肷��
	/// </summary>
	/// <param name="bossState">�{�X�̃X�e�[�g</param>
	void SetBossState(int bossState)
	{
		m_bossState = bossState;
	}


	/// <summary>
	/// �v���C���[��HP���񕜂���
	/// </summary>
	/// <param name="recoveryAmount">�񕜗�</param>
	void HealingHP(float recoveryAmount)
	{
		m_playerHP += recoveryAmount;

		m_playerHP = min(m_playerHP, m_playerHPMax);
	}


	/// <summary>
	/// �v���C���[�Ƀ_���[�W��^����֐�
	/// </summary>
	/// <param name="damage">�_���[�W��</param>
	void ApplyDamage(float damage)
	{
		m_playerHP -= damage;

		m_playerHP = max(m_playerHP, 0.0f);
	}


	/// <summary>
	/// �v���C���[�̃|�W�V����X�ɒl��������
	/// </summary>
	/// <param name="delta">������</param>
	void AddPositionX(float delta)
	{
		m_playerPosition.x += delta;
	}


	/// <summary>
	/// �v���C���[�̃|�W�V����Y�ɒl��������
	/// </summary>
	/// <param name="delta">������</param>
	void AddPositionY(float delta)
	{
		m_playerPosition.y += delta;
	}


	/// <summary>
	/// �v���C���[�̃|�W�V����Z�ɒl��������
	/// </summary>
	/// <param name="delta">������</param>
	void AddPositionZ(float delta)
	{
		m_playerPosition.z += delta;
	}


	/// <summary>
	/// �L�����R���̈ʒu��ݒ肷��
	/// </summary>
	/// <param name="position">�|�W�V����</param>
	void SetCharacterControllerPosition(Vector3 position)
	{
		m_characterController.SetPosition(position);
	}


	/// <summary>
	/// �E�����G�l�~�[�̐��𑝂₷
	/// </summary>
	void AddKillEnemyAmount()
	{
		m_killEnemyAmountFont++;
	}


private:

	Title* m_title = nullptr;
	Result* m_result = nullptr;
	Game* m_game = nullptr;
	SoundSource* m_machineGunSE = nullptr;			//�}�V���K��SE
	SoundSource* m_runSE = nullptr;					//����SE
	SoundSource* m_walkSE = nullptr;				//����SE
	SoundSource* m_kettei = nullptr;
	SoundSource* m_deadSE = nullptr;
	GameCamera* m_gameCamera = nullptr;

	std::unique_ptr<ModelRender> m_playerModel;					//���f�������_�[
	SpriteRender m_pouseSprite;				//pause��ʗp�̃X�v���C�g�����_�[
	SpriteRender m_playerDeadSprite;				//�v���C���[�����񂾂Ƃ��̃X�v���C�g�����_�[
	CharacterController m_characterController;		//�L�����N�^�[�R���g���[���[
	Vector3 m_playerPosition = {0.0f,0.0f,-1000.0f};	//���W
	Vector3 m_playerMoveSpeed;						//�ړ����x
	Vector3 m_playerForward = { 0.0f, 0.0f, 1.0f };	//�v���C���[�̐��ʃx�N�g��
	Quaternion m_playerRotation;						//�N�H�[�^�j�I��

	int m_deadCount = 0;
	int m_gameState = 4;								//�Q�[�����ǂ̏�Ԃ��̊Ǘ�(0���C���Q�[��,1�|�[�Y���,2���U���g,3�J�X�^�}�C�Y,4�ŏ��̃V�[��)
	int m_gameEndState = 0;							//�Q�[���̏I������
	int m_bossState = 0;								//�{�X�킩�ǂ���
	int m_effectCount = 0;							//�G�t�F�N�g�֌W
	int m_killEnemyAmountFont = 0;								//�G���E������(10�ɂȂ�ƃE�F�[�u���i��)
	int m_customPoint[2][3] = { {0,0,0},{0,0,0} };	//[0][0]�E�r,[0][1]��,[0][2]���r,[1][0]�E��,[1][2]����
	int m_playerColorData = 0;
	int m_playerColorRandom = 0;
	float m_accelerator = 0;
	float m_brake = 0;
	float m_throttle = 0;
	float m_move;
	float m_playerHP = 500.0f;						//�v���C���[��HP
	float m_playerHPMax = 500.0f;					//�v���C���[��HP�̍ő�l
	float m_deadSpriteColw = 0.0f;					//�v���C���[���S���̃X�v���C�g�̓����x
	bool m_cameraMove = false;						//�J�����؂�ւ������ǂ���
	bool m_playerDead = false;						//�v���C���[�����񂾂��ǂ���
	bool m_playDeadSE = false;						//���S����炵�����ǂ���
	bool m_deadBakuhaPlay = false;					//���S���̔��j�𔭐���������
};

