#pragma once
#include "EnemyBase.h"


class Enemy : public EnemyBase
{
public:

	Enemy();
	~Enemy();
	void Update()					override;	//�X�V����
	void Render(RenderContext& rc)	override;	//�`�揈��
	void Move()						override;	//�ړ�����
	void PlayerSearch()				override;	//���G����
	void Attack()					override;	//�����I��ōU��
	void Fire(int m_weaponNum)		override;	//����
	void GameSetUp()				override;		
	void EnemyDead()				override;
	void HPUnder0()					override;
	void InitEnemyModel()			override;
	void SE();


private:
	SoundSource* m_machineGunSE = nullptr;			//�}�V���K��SE

	bool m_atackOK = false;
	bool m_machinGunSEPlay = false;
	bool m_enemyEscape = false;
};

