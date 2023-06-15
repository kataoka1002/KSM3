#pragma once
#include "Game.h"

class Game;
class Player;

class AttackBase : public IGameObject
{
public:
	AttackBase(){};

	virtual ~AttackBase() {};


	bool Start();
	void Move(float deleteDir);


	//�������z�֐��ɂ��āA�h���N���X�Ŏ�������
	virtual void Update()					= 0;
	virtual void Render(RenderContext& rc)	= 0;
	virtual void DestroyWithImpactEffect()	= 0;
	virtual void SetUp()					= 0;


	/// <summary>
	/// �G�t�F�N�g���Đ�����
	/// </summary>
	/// <param name="name">�G�t�F�N�g�̖��O</param>
	/// <param name="pos">����������ꏊ</param>
	/// <param name="rot">��]��</param>
	/// <param name="scale">�X�P�[��</param>
	void PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale);
	
	
	/// <summary>
	/// �_���[�W����
	/// </summary>
	/// <param name="damage">�^����_���[�W��</param>
	void DamageEvent(float damage);


	/// <summary>
	/// �e�̏�����
	/// </summary>
	/// <param name="scale">�X�P�[��</param>
	void BulletSetUp(float scale);


	/// <summary>
	/// ��]�ʂ��Z�b�g����
	/// </summary>
	/// <param name="rot">��]��</param>
	void SetRotation(Quaternion rot)
	{
		m_originRotation = rot;
	}


	/// <summary>
	/// �|�W�V�����̐ݒ�
	/// </summary>
	/// <param name="pos">�|�W�V����</param>
	void SetPosition(Vector3 pos)
	{
		m_position = pos;
	}


	/// <summary>
	/// ���[�J���|�W�V�����̐ݒ�
	/// </summary>
	/// <param name="pos">���[�J���|�W�V����</param>
	void SetLocalPosition(Vector3 pos)
	{
		m_bulletLocalPosition = pos;
	}


	//getter�֐�-----------------------------------------------------



	//---------------------------------------------------------------

protected:

	Game* m_game = nullptr;
	Player* m_player = nullptr;

	ModelRender m_bulletModel;						//�e�̃��f��
	Vector3 m_position = Vector3::Zero;				//�|�W�V����
	Vector3 m_bulletForward = Vector3::Zero;		//�O����
	Vector3 m_bulletLocalPosition = Vector3::Zero;	//�e�̃��[�J���|�W�V����
	Quaternion m_rot;
	Quaternion m_originRotation;

	float m_bulletDamage = 0.0f;
	float m_fallSpeed = 0.0f;
	float m_moveSpeed = 0.0f;
	float m_decreaseSpeed = 0.0f;
	float m_addFallSpeed = 0.0f;
};

