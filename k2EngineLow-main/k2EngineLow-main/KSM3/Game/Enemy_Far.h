#pragma once
#include "EnemyBase.h"

class Enemy_Far : public EnemyBase
{
public:
	Enemy_Far();
	~Enemy_Far();

	void Update()					override;	//更新処理
	void Render(RenderContext& rc)	override;	//描画処理
	void GameSetUp()				override;
	void Move()						override;	//移動処理
	void PlayerSearch()				override;	//索敵処理
	void Attack()					override;	//武器を選んで攻撃
	void Fire(int m_weaponNum)		override;	//発射
	void EnemyDead()				override;
	void HPUnder0()					override;
	void InitEnemyModel()			override;
	void DeleteGoThis()             override;


private:
	SoundSource* m_bisiSE = nullptr;				//足音
	SoundSource* m_battleShipGunSE = nullptr;

	bool m_enemyEscape = false;						//後退中かどうかフラグ
	bool m_atackOK = false;							//攻撃フラグ
	bool m_weponDraw = true;
	bool m_flashFinishFlag = false;
	bool m_impactPlay = false;
	bool m_defeatState = false;						//死んだかどうかフラグ
	int m_flashTime = 10;
	float m_enemySize = 2.0f;
};

