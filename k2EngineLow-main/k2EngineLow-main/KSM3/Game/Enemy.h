#pragma once
#include "EnemyBase.h"


class Enemy : public EnemyBase
{
public:

	Enemy();
	~Enemy();
	void Update()					override;	//XV
	void Render(RenderContext& rc)	override;	//`æ
	void Move()						override;	//Ú®
	void PlayerSearch()				override;	//õG
	void Attack()					override;	//íðIñÅU
	void Fire(int m_weaponNum)		override;	//­Ë
	void GameSetUp()				override;		
	void EnemyDead()				override;
	void HPUnder0()					override;
	void InitEnemyModel()			override;
	void SE();

	SoundSource* m_machineGunSE = nullptr;			//}VKSE

	bool m_atackOK = false;
	bool m_machinGunSEPlay = false;
	bool m_enemyEscape = false;
};

