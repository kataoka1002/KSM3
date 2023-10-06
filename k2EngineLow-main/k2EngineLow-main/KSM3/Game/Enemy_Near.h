#pragma once
#include "EnemyBase.h"

class Enemy_Near : public EnemyBase
{
public:

	Enemy_Near();
	~Enemy_Near();
	

	void GameSetUp()				override;
	void Update()					override;	//更新処理
	void Render(RenderContext& rc)	override;	//描画処理
	void Move()						override;	//移動処理
	void PlayerSearch()				override;	//索敵処理
	void Attack()					override;	//武器を選んで攻撃
	void Fire(int weaponNum)		override;	//発射
	void EnemyDead()				override;
	void HPUnder0()					override;
	void InitEnemyModel()			override;
	void DeleteGoThis()             override;

private:
	SoundSource* m_cannonSE = nullptr;				//ギガトンキャノンSE

	Vector3 m_enemyTargetPos = { 0.0f,0.0f,0.0f };	//ターゲットのポジション
	Vector3 m_toTarget = Vector3::Zero;				//ターゲットへの方向

	bool m_attackFlag = false;						//弾を撃ったかどうかフラグ
	bool m_fireFlag = false;						//攻撃フラグ
	bool m_dashFlag = false;						//ダッシュしているかフラグ
	bool m_targetFlag = false;						//ターゲットを設定しているかどうかフラグ
	int m_recoilCount = 300;						//反動の時間
	float m_distToPlayer = 0;						//プレイヤーまでの距離
	float m_distTarget = 0;							//ターゲットまでの距離

};

