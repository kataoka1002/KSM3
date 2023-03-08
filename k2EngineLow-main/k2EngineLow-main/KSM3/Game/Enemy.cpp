#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include"Game.h"

#include <time.h>
#include <stdlib.h>

void Enemy::Init(Vector3 initPos)
{
	m_position = initPos;
	m_rotation.SetRotationY(Math::PI);
	// メンバ変数のm_playerにアドレスを記憶しておく。、
	m_player = FindGO<Player>("Player");
}

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

bool Enemy::Start()
{
	//モデルを読み込む
	m_modelRender.Init("Assets/modelData/enemy_model.tkm");
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale({ 1.0f, 1.0f, 1.0f });
	//キャラクターコントローラーを初期化。
	m_charaCon.Init(
		50.0f,			//半径。
		-40.0f,			//高さ。
		m_position		//座標。
	);
	//乱数を初期化。
	srand((unsigned)time(NULL));

	return true;
}
 
void Enemy::Update()
{
	//追跡処理
	Chase();
	//プレイヤーに向かって視点移動
	SearchPlayer();
	//ステートの遷移処理。
	ManageState();
	//モデルの更新
	m_modelRender.Update();
}

 void Enemy::SearchPlayer()
{
	//エネミーからプレイヤーが入ってきたら追いかける
	Vector3 toPlayer = m_player->m_position - m_position;

	    //プレイヤーとの距離を計算する
		float distToPlayer = toPlayer.Length();
		   //プレイヤーに向かって伸びるベクトルを正規化する
			Vector3 toPlayerDir = toPlayer;
			toPlayerDir.Normalize();
			//エネミーの前方方向とtoPlayerDirとの内積を計算する
			float t = toPlayerDir.Dot(m_forward);
			//内積の結果をacos関数に渡して、m_enemyFowradとtoPlayerDirのなす角度を求める。
			float angle = acos(t);

				//敵キャラの前方方向を更新する
				m_forward = toPlayerDir;
		// 敵の前方方向を使って、回転クォータニオンを計算する。
		m_rotation.SetRotationY(atan2(m_forward.x, m_forward.z));
		m_modelRender.SetPosition(m_position);
		m_modelRender.SetRotation(m_rotation);
		m_modelRender.Update();
}

void Enemy::Chase()
{
	//追跡ステートでないなら、追跡処理はしない。
	if (m_enemyState != EnemyState_Chase)
	{
		return;
	}

	//エネミーからプレイヤーに向かうベクトルを計算する
	Vector3 toPlayer = m_player->m_position - m_position;
	//ベクトルを正規化する。
	toPlayer.Normalize();
	//移動速度を設定する。
	m_moveSpeed = toPlayer * 100.0f;
	//エネミーを移動させる
	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	if (m_charaCon.IsOnGround()) {
		//地面についた。
		m_moveSpeed.y = 0.0f;
	}
	Vector3 modelPosition = m_position;
	//ちょっとだけモデルの座標を挙げる。
	modelPosition.y += 2.5f;
	m_modelRender.SetPosition(modelPosition);
}

void Enemy::ProcessCommonStateTransition()
{
	//各タイマーを初期化
	//待機時間と追跡時間を制限するため
	m_idleTimer = 0.0f;
	m_chaseTimer = 0.0f;
	//エネミーからプレイヤーに向かうベクトルを計算する
	Vector3 toPlayer = m_player->m_position - m_position;
	//ベクトルを正規化する。
	toPlayer.Normalize();

	int ram = rand() % 100;
	if (ram<50)
	{
		//追跡ステートに遷移する。
		m_enemyState = EnemyState_Chase;
		return;
	}
	else
	{
		//待機ステートに遷移する。
		m_enemyState = EnemyState_Idle;
		return;
	}
}

void Enemy::ProcessIdleStateTransition()
{
	m_idleTimer += g_gameTime->GetFrameDeltaTime();
	//待機時間がある程度経過したら
	if (m_idleTimer >= 2.0f)
	{
		//他のステートに遷移する。
		ProcessCommonStateTransition();
	}
}

void Enemy::ProcessChaseStateTransition()
{
	m_chaseTimer += g_gameTime->GetFrameDeltaTime();
	//追跡時間がある程度経過したら
	if (m_chaseTimer >= 2.0f)
	{
		//他のステートに遷移する。
		ProcessCommonStateTransition();
	}
}

void Enemy::ManageState()
{
	switch (m_enemyState)
	{
		//待機ステートの時
	case Enemy::EnemyState_Idle:
		//待機ステートのステート遷移処理。
		ProcessIdleStateTransition();
		break;
		//追跡ステートの時
	case Enemy::EnemyState_Chase:
		//追跡ステートのステート遷移処理。
		ProcessChaseStateTransition();
		break;
	}
}

void Enemy::Render(RenderContext& rc)
{
	//モデルの描画。
	m_modelRender.Draw(rc);
}