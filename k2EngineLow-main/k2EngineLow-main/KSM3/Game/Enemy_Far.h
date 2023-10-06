#pragma once
#include "EnemyBase.h"

class Enemy_Far : public EnemyBase
{
public:
	Enemy_Far();
	~Enemy_Far();

	void Update()					override;	//�X�V����
	void Render(RenderContext& rc)	override;	//�`�揈��
	void GameSetUp()				override;
	void Move()						override;	//�ړ�����
	void PlayerSearch()				override;	//���G����
	void Attack()					override;	//�����I��ōU��
	void Fire(int m_weaponNum)		override;	//����
	void EnemyDead()				override;
	void HPUnder0()					override;
	void InitEnemyModel()			override;
	void DeleteGoThis()             override;


private:
	SoundSource* m_bisiSE = nullptr;				//����
	SoundSource* m_battleShipGunSE = nullptr;

	bool m_enemyEscape = false;						//��ޒ����ǂ����t���O
	bool m_atackOK = false;							//�U���t���O
	bool m_weponDraw = true;
	bool m_flashFinishFlag = false;
	bool m_impactPlay = false;
	bool m_defeatState = false;						//���񂾂��ǂ����t���O
	int m_flashTime = 10;
	float m_enemySize = 2.0f;
};

