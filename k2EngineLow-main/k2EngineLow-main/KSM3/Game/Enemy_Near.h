#pragma once
#include "EnemyBase.h"

class Enemy_Near : public EnemyBase
{
public:

	Enemy_Near();
	~Enemy_Near();
	

	void GameSetUp()				override;
	void Update()					override;	//�X�V����
	void Render(RenderContext& rc)	override;	//�`�揈��
	void Move()						override;	//�ړ�����
	void PlayerSearch()				override;	//���G����
	void Attack()					override;	//�����I��ōU��
	void Fire(int weaponNum)		override;	//����
	void EnemyDead()				override;
	void HPUnder0()					override;
	void InitEnemyModel()			override;
	void DeleteGoThis()             override;

private:
	SoundSource* m_cannonSE = nullptr;				//�M�K�g���L���m��SE

	Vector3 m_enemyTargetPos = { 0.0f,0.0f,0.0f };	//�^�[�Q�b�g�̃|�W�V����
	Vector3 m_toTarget = Vector3::Zero;				//�^�[�Q�b�g�ւ̕���

	bool m_attackFlag = false;						//�e�����������ǂ����t���O
	bool m_fireFlag = false;						//�U���t���O
	bool m_dashFlag = false;						//�_�b�V�����Ă��邩�t���O
	bool m_targetFlag = false;						//�^�[�Q�b�g��ݒ肵�Ă��邩�ǂ����t���O
	int m_recoilCount = 300;						//�����̎���
	float m_distToPlayer = 0;						//�v���C���[�܂ł̋���
	float m_distTarget = 0;							//�^�[�Q�b�g�܂ł̋���

};

