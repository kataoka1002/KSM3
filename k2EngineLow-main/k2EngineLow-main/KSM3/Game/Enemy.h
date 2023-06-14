#pragma once
#include "EnemyBase.h"


class Enemy : public EnemyBase
{
public:

	Enemy();
	~Enemy();
	void Update()					override;	//XVˆ—
	void Render(RenderContext& rc)	override;	//•`‰æˆ—
	void Move()						override;	//ˆÚ“®ˆ—
	void PlayerSearch()				override;	//õ“Gˆ—
	void Attack()					override;	//•Ší‚ğ‘I‚ñ‚ÅUŒ‚
	void Fire(int m_weaponNum)		override;	//”­Ë
	void GameSetUp()				override;		
	void EnemyDead()				override;
	void HPUnder0()					override;
	void InitEnemyModel()			override;
	void SE();


private:
	SoundSource* m_machineGunSE = nullptr;			//ƒ}ƒVƒ“ƒKƒ“SE

	bool m_atackOK = false;
	bool m_machinGunSEPlay = false;
	bool m_enemyEscape = false;
};

