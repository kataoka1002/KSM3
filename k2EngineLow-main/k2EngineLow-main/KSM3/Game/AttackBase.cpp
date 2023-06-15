#include "stdafx.h"
#include "AttackBase.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy_Far.h"
#include "Enemy_Near.h"
#include "Boss.h"
#include "Boss_Drill.h"

bool AttackBase::Start()
{

	//ゲームを探す
	m_game = FindGO<Game>("game");


	//プレイヤーを探す
	m_player = FindGO<Player>("player");


	//全般のセットアップ
	SetUp();

	return true;

}

void AttackBase::BulletSetUp(float scale)
{

	//弾のモデルの初期化
	m_bulletModel.Init("Assets/modelData/battleship_gun_bullet.tkm");
	m_bulletModel.SetScale(scale);


	//エネミーから見て正しい位置に弾を設定
	m_originRotation.Multiply(m_bulletLocalPosition);	//掛け算


	//最終的な弾の回転を決定
	m_rot = m_originRotation;


	//それに親から見た位置を足して最終的な武器の位置を決定
	m_position += m_bulletLocalPosition;				


	//前方向はプレイヤーと一緒
	m_bulletForward = m_player->playerForward;


	//更新
	m_bulletModel.SetRotation(m_rot);
	m_bulletModel.SetPosition(m_position);
	m_bulletModel.Update();

}

void AttackBase::Move(float deleteDir)
{

	//ポジションに、前方向に速さを掛けた値を足す
	m_position += m_bulletForward * m_moveSpeed;


	//弾からプレイヤーまでのベクトルを求める
	Vector3 m_toPlayer = m_player->player_position - m_position;


	//少しづつ下に落とす
	m_position.y -= m_fallSpeed;


	//スピードを少しづつ遅くする
	m_moveSpeed -= m_decreaseSpeed;


	//落ちるスピードを少しづつ速くする
	m_fallSpeed += m_addFallSpeed;



	//弾からプレイヤーまでの距離を求める
	float m_dirToPlayer = m_toPlayer.Length();


	//一定距離以上なら
	if (m_dirToPlayer >= deleteDir)
	{

		//弾を消す処理
		DestroyWithImpactEffect();

	}
	//地面に着いたら
	else if (m_position.y <= 0.0f)
	{

		//弾を消す処理
		DestroyWithImpactEffect();

	}


	//バレットの更新
	m_bulletModel.SetPosition(m_position);
	m_bulletModel.Update();

}

void AttackBase::PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale)
{

	//エフェクトの再生
	EffectEmitter* m_effect = NewGO<EffectEmitter>(0);
	m_effect->Init(name);
	m_effect->SetPosition(pos);
	m_effect->SetRotation(rot);
	m_effect->SetScale(scale);
	m_effect->Play();

}

void AttackBase::DamageEvent(float damage)
{

	//エネミーの数だけ繰り返す
	for (auto enemy : m_game->GetEnemyObject())
	{

		//弾とエネミーの距離を測る
		Vector3 diff = m_position - enemy->GetPos();


		//一定距離以下なら
		if (diff.Length() <= 300.0f)
		{

			//ダメージを与える
			enemy->ApplyDamage(damage);


			//弾が消えるときの処理
			DestroyWithImpactEffect();

		}

	}


	//エネミーFarの数だけ繰り返す
	for (auto enemyFar : m_game->GetEnemyFarObject())
	{

		//弾とエネミーの距離を測る
		Vector3 diff = m_position - enemyFar->GetPos();


		//一定距離以下なら
		if (diff.Length() <= 400.0f)
		{

			//ダメージを与える
			enemyFar->ApplyDamage(damage);


			//弾が消えるときの処理
			DestroyWithImpactEffect();

		}

	}


	//エネミーNearの数だけ繰り返す
	for (auto enemyNear : m_game->GetEnemyNearObject())
	{

		//弾とエネミーの距離を測る
		Vector3 diff = Vector3{ m_position.x,m_position.y + 20.0f,m_position.z } - enemyNear->GetPos();


		//一定距離以下なら
		if (diff.Length() <= 400.0f)
		{

			//ダメージを与える
			enemyNear->ApplyDamage(damage);


			//弾が消えるときの処理
			DestroyWithImpactEffect();

		}

	}


	//ボスがヌルじゃいないとき
	if (m_game->GetBoss() != nullptr)
	{

		//弾とボスの距離を測る
		Vector3 diff = m_position - m_game->GetBoss()->boss_position;


		//一定距離以下なら
		if (diff.Length() <= 400.0f)
		{

			//ダメージを与える
			m_game->GetBoss()->boss_HP -= damage;


			//弾が消えるときの処理
			DestroyWithImpactEffect();

		}

	}


	//ボスがヌルじゃないとき
	if (m_game->GetBoss() != nullptr)
	{

		//ドリルがヌルじゃないとき
		if (m_game->GetBoss()->b_boss_drill != nullptr)
		{

			//弾とドリルの距離を測る
			Vector3 diff = m_position - m_game->GetBoss()->b_boss_drill->b_w_position;


			//一定距離以下なら
			if (diff.Length() <= 400.0f)
			{

				//ダメージを与える
				m_game->GetBoss()->b_boss_drill->drill_HP -= damage;


				//弾が消えるときの処理
				DestroyWithImpactEffect();

			}

		}

	}

}