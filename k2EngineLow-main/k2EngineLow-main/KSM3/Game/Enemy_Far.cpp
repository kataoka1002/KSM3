#include "stdafx.h"
#include "Enemy_Far.h"
#include "Player.h"
#include "Game.h"
#include <time.h>
#include <stdlib.h>
#include "Battle_ship_attack.h"
#include "Drop_item.h"


Enemy_Far::Enemy_Far()
{
	m_pointList.push_back({ Vector3(0.0f,0.0f,0.0f),1 });		//一番目のポイント
	m_pointList.push_back({ Vector3(0.0f,0.0f,100.0f),2 });		//二番目のポイント
	m_pointList.push_back({ Vector3(100.0f,0.0f,200.0f),3 });	//三番目のポイント
	m_pointList.push_back({ Vector3(-100.0f,0.0f,200.0f),4 });	//四番目のポイント
	m_point = &m_pointList[0];									//一番目のポイントを入れる
}

Enemy_Far::~Enemy_Far()
{
	m_player->enemy_survival = false;	//エネミーが生きているかをプレーヤーに教える
	//エネミーがどの武器を持っていたか取得し、ドロップするアイテムを決める
	if (m_defeatState == true) {
		m_dropItem->drop_kinds = m_setWeapon;
	}
}

bool Enemy_Far::Start()
{
	m_player = FindGO<Player>("player");

	//エネミーの設定
	m_enemyModel.Init("Assets/modelData/Enemy_model_type2.tkm");
	m_enemyModel.SetScale(2.0f);
	m_enemyModel.SetRotation(m_enemyRotation);
	m_enemyModel.SetPosition(m_enemyPosition);
	//キャラクターコントローラーを初期化。
	m_enemyCharacterController.Init(
		50.0f,			//半径。
		40.0f,			//高さ。
		m_enemyPosition	//座標。
	);

	SetUp();	//武器生成

	return true;
}

void Enemy_Far::SetUp()
{
	//敵の武器の種類の確定
	m_setWeapon = 1;//ここはいったん仮で定数設定してるだけで後々ランダムにしていく予定
	//set_weapons = rand() % 2 + 1;
	if (m_setWeapon == 1) {	//ミサイル
		m_enemyWeaponModel.Init("Assets/modelData/battleship_gun_enemy.tkm");
		m_enemyWeaponModel.SetScale(2.0f);
		m_enemyWeaponModel.SetPosition(m_weaponPosition);
		m_enemyWeaponModel.SetRotation(m_weaponRotation);
		m_enemyWeaponModel.Update();
	}
	else if (m_setWeapon == 2) { //戦艦砲
		m_enemyWeaponModel.Init("Assets/modelData/machine_gun_enemy.tkm");
		m_enemyWeaponModel.SetScale(2.0f);
		m_enemyWeaponModel.SetPosition(m_weaponPosition);
		m_enemyWeaponModel.SetRotation(m_weaponRotation);
		m_enemyWeaponModel.Update();
	}
}

void Enemy_Far::Update()
{
	if (m_player->game_state == 0)
	{
		//エネミーからプレイヤーへのベクトル
		m_toPlayer = m_player->player_position - m_enemyPosition;
		//プレイヤーとの距離を計算する
		m_distToPlayer = m_toPlayer.Length();
		//プレイヤーに向かって伸びるベクトルを正規化する
		m_toPlayerDir = m_toPlayer;
		m_toPlayerDir.Normalize();


		if (m_distToPlayer > 5000.0f)
		{
			m_lockOn = true;
		}
		else
		{
			m_lockOn = false;
		}

		//ロックオンしてないならパス移動する
		if (m_lockOn == true)
		{
			PassMove();
		}
		if (m_lockOn == false)
		{
			PlayerSearch();		//索敵
			Move();				//エネミー移動
			Attack();			//攻撃
		}

		WeaponMove();		//武器の移動回転	
		ItemDrop();			//倒した時にアイテムを落とす処理


		//エネミーと武器の更新
		m_enemyModel.SetPosition(m_enemyPosition);
		m_enemyModel.SetRotation(m_enemyRotation);
		m_enemyModel.Update();
		m_enemyWeaponModel.SetPosition(m_weaponPosition);
		m_enemyWeaponModel.SetRotation(m_weaponRotation);
		m_enemyWeaponModel.Update();
	}
}

void Enemy_Far::PassMove()
{
	//自分のポジションから目標とするポイントのベクトル
	Vector3 m_toPoint = m_point->m_position - m_enemyPosition;
	//距離を計算
	float m_diffToPoint = m_toPoint.Length();
	//方向の計算
	Vector3 m_toPointDir = m_toPoint;
	m_toPointDir.Normalize();
	//前方向の設定
	m_enemyForward = m_toPointDir;

	//距離が一定以内なら目的地とするポイントを変える
	if (m_diffToPoint < 20.0f)
	{
		//今目的地としているポイントが配列の最後の要素なら
		//一番最初のポイントを目的地とする
		if (m_point->m_num == m_pointList.size()) {
			m_point = &m_pointList[0];
		}
		//そうでないなら配列の次の要素のポイントを目的地とする
		else {
			m_point = &m_pointList[m_point->m_num];
		}
	}

	//移動させる。
	m_enemyMoveSpeed = m_enemyForward * 200.0f;
	m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());

	//エネミーの前方向を使って、回転クォータニオンを計算する。
	m_enemyRotation.SetRotationY(atan2(m_enemyForward.x, m_enemyForward.z));
}

void Enemy_Far::PlayerSearch()
{
	//エネミーの前方向とtoPlayerDirとの内積を計算する
	float t = m_toPlayerDir.Dot(m_enemyForward);
	//内積の結果をacos関数に渡して、m_enemyFowradとtoPlayerDirのなす角度を求める。
	float angle = acos(t);

	//エネミーの視野にプレイヤーが入っている&距離が1500以下になる&プレイヤーの方向を向いている
	if (fabsf(angle) < Math::DegToRad(45.0f) && m_distToPlayer <= 1500.0f && m_enemyDirState == 0) {
		m_atackOK = true;
	}
	else {
		m_atackOK = false;
	}


	//エネミーの前方向を更新する
	if (m_enemyDirState == 0)
	{
		m_enemyForward = m_toPlayerDir;					//プレイヤー向き
		m_enemyMoveSpeed = m_enemyForward * 250.0f;		//移動速度を設定
	}
	else if (m_enemyDirState == 1)
	{
		m_enemyForward = m_toPlayerDir * -1.0;			//プレイヤーと反対向き
	}
	else if (m_enemyDirState == 2)
	{
		m_enemyForward = Cross(m_Up, m_toPlayerDir);	//外積からエネミーの横方向を取得
		m_enemyMoveSpeed = m_enemyForward * 250.0f;		//移動速度の設定
	}
	else if (m_enemyDirState == 3)
	{
		m_enemyForward = Cross(m_toPlayerDir, m_Up);	//外積からエネミーの横方向を取得
		m_enemyMoveSpeed = m_enemyForward * 250.0f;		//移動速度の設定
	}

	//後退してないなら回転する
	if (m_enemyEscape != true)
	{
		//エネミーの前方向を使って、回転クォータニオンを計算する。
		m_enemyRotation.SetRotationY(atan2(m_enemyForward.x, m_enemyForward.z));
	}
}

void Enemy_Far::Move()
{
	if (m_enemyDirState == 0) //プレイヤー向き
	{
		//条件を満たしている間だけプレイヤーに向かって移動する
		if (m_distToPlayer >= 3000.0f && m_distToPlayer <= 5000.0f)
		{
			//エネミーの移動
			m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());
		}

		//エネミーとプレイヤーの距離が近い時、一定確率で後退する
		if (m_distToPlayer <= 1500.0f && rand() % 150 == 1)
		{
			m_enemyDirState = 1;
			m_enemyMoveSpeed = m_enemyForward * -250.0f;	//移動速度の設定()
			m_enemyEscape = true;
		}
		//エネミーとプレイヤーの距離が近い時、一定確率で横移動する
		else if (m_distToPlayer < 2800.0f && rand() % 900 == 1)
		{
			m_enemyDirState = 2;
		}
		//エネミーとプレイヤーの距離が近い時、一定確率で横移動する
		else if (m_distToPlayer < 2800.0f && rand() % 900 == 1)
		{
			m_enemyDirState = 3;
		}
	}
	else if (m_enemyDirState == 1)	//後ろ向き
	{
		//移動させる。
		m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());
		//一定距離以上になると後退ストップ
		if (m_distToPlayer > 2800.0f || rand() % 400 == 1)
		{
			m_enemyEscape = false;
			m_enemyDirState = 0;
		}
	}
	else if (m_enemyDirState == 2)	//横向き
	{
		//移動させる。
		m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());
		//ある程度したらストップ
		if (rand() % 200 == 1)
		{
			m_enemyDirState = 0;
		}
	}
	else if (m_enemyDirState == 3)	//横向き
	{
		//移動させる。
		m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());
		//ある程度したらストップ
		if (rand() % 200 == 1)
		{
			m_enemyDirState = 0;
		}
	}
}

void Enemy_Far::Attack()
{
	if (m_atackOK == true)
	{
		//攻撃タイミングの計算
		m_attackCount++;

		//武器によっての分岐
		switch (m_setWeapon)
		{
		case 1://ミサイル
			if (m_attackCount % 180 == 0)
			{
				Fire();	//発射
				m_attackCount = 0;
			}
			break;
		case 2://戦艦砲
			if (m_attackCount % 60 == 0)
			{
				Fire();	//発射
				m_attackCount = 0;
			}
			break;
		default:
			break;
		}
	}
}

void Enemy_Far::Fire()
{
	////弾の生成
	//m_enemyAttack = NewGO<Enemy_Bullet>(1, "enemy_attack");
	//m_enemyAttack->firing_position = m_position;	//弾の位置を設定
	//m_enemyAttack->e_a_Bullet_Fowrad = m_enemy->m_enemyForward;	//弾の前方向の設定
	//m_atackState = true;

	////武器が戦艦砲なら
	//if (weponNom == 1)
	//{
	//	m_enemyAttack->e_a_aiming = m_enemy->m_enemyRotation;
	//}
}

void Enemy_Far::ItemDrop()
{
	//体力が0になったらアイテムを落とす
	if (m_enemyHP <= 0.0f)
	{
		m_dropItem = NewGO<Drop_item>(1, "drop_item");
		m_dropItem->Drop_position = m_enemyPosition;
		m_dropItem->Drop_position.y += 50.0f;
		m_defeatState = true;
		DeleteGO(this);
	}
}

void Enemy_Far::WeaponMove()
{
	//武器がエネミーと同じ動きをするようにする(親子関係)
	Quaternion originRotation = m_enemyRotation;			//回転はエネミーと同じ
	Vector3 localPosition = { 0.0f,40.0f,40.0f };			//親から見た位置の定義
	originRotation.Multiply(localPosition);					//何かしらの計算
	//最終的な武器の回転を決定
	m_weaponRotation = originRotation;

	m_weaponPosition = m_enemyPosition;		//まず,武器の位置をエネミーと同じに設定し
	m_weaponPosition += localPosition;		//それに親から見た位置を足して最終的な武器の位置を決定
}

void Enemy_Far::Render(RenderContext& rc)
{
	//モデルの描画。
	m_enemyModel.Draw(rc);
	m_enemyWeaponModel.Draw(rc);
}
