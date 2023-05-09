#include "stdafx.h"
#include "Enemy_Near.h"
#include "Player.h"
#include "Game.h"
#include <time.h>
#include <stdlib.h>
#include "Battle_ship_attack.h"
#include "Drop_item.h"
#include "Enemy_Bullet.h"


Enemy_Near::Enemy_Near()
{
	//足音の生成(流し続ける音源なのでインスタンスを保持させる)
	m_asiotoSE = NewGO<SoundSource>(0);
	m_dashSE = NewGO<SoundSource>(0);
	
	m_pointList.push_back({ Vector3(0.0f,0.0f,0.0f),1 });		//一番目のポイント
	m_pointList.push_back({ Vector3(0.0f,0.0f,100.0f),2 });		//二番目のポイント
	m_pointList.push_back({ Vector3(100.0f,0.0f,200.0f),3 });	//三番目のポイント
	m_pointList.push_back({ Vector3(-100.0f,0.0f,200.0f),4 });	//四番目のポイント
	m_point = &m_pointList[0];									//一番目のポイントを入れる
}

Enemy_Near::~Enemy_Near()
{
	//エネミーが生きているかをプレーヤーに教える
	//m_player->enemy_survival = false;	

	m_player->killEnemy++;	//殺した数を増やす

	DeleteGO(m_asiotoSE);
	DeleteGO(m_dashSE);
}

bool Enemy_Near::Start()
{
	m_player = FindGO<Player>("player");
	m_game = FindGO<Game>("game");

	//エネミーの設定
	m_enemyModel.Init("Assets/modelData/enemy_model.tkm");
	m_enemyModel.SetScale(2.0f);
	m_enemyModel.SetRotation(m_enemyRotation);
	m_enemyModel.SetPosition(m_enemyPosition);
	//キャラクターコントローラーを初期化。
	m_enemyCharacterController.Init(
		50.0f,			//半径。
		40.0f,			//高さ。
		m_enemyPosition	//座標。
	);

	//足音の設定
	m_asiotoSE->Init(enRunning);	//初期化
	m_asiotoSE->SetVolume(0.8f);	//音量調整
	m_asiotoSE->Play(true);			//再生
	m_asiotoSE->Stop();				//停止

	//足音の設定
	m_dashSE->Init(enDash);			//初期化
	m_dashSE->SetVolume(0.8f);		//音量調整
	m_dashSE->Play(true);			//再生
	m_dashSE->Stop();				//停止


	SetUp();	//武器生成

	return true;
}

void Enemy_Near::SetUp()
{
	//敵の武器の種類の確定
	m_setWeapon = 4;//ここはいったん仮で定数設定してるだけで後々ランダムにしていく予定
	//set_weapons = rand() % 1 + 1;
	if (m_setWeapon == 4) {	//ギガトンキャノン
		m_enemyWeaponModel.Init("Assets/modelData/GIgaton_cannon.tkm");
		m_enemyWeaponModel.SetScale(1.3f);
		m_enemyWeaponModel.SetPosition(m_weaponPosition);
		m_enemyWeaponModel.SetRotation(m_weaponRotation);
		m_enemyWeaponModel.Update();
	}
}

void Enemy_Near::Update()
{
	//砂ぼこりの間隔カウント
	m_sunaHassei++;

	if (m_player->game_state == 0)
	{
		//エネミーからプレイヤーへのベクトル
		m_toPlayer = m_player->player_position - m_enemyPosition;
		//プレイヤーとの距離を計算する
		m_distToPlayer = m_toPlayer.Length();
		//プレイヤーに向かって伸びるベクトルを正規化する
		m_toPlayerDir = m_toPlayer;
		m_toPlayerDir.Normalize();

		if (m_distToPlayer > 4000.0f && m_targetFlag == false)
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

void Enemy_Near::PassMove()
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

void Enemy_Near::PlayerSearch()
{
	//エネミーの前方向とtoPlayerDirとの内積を計算する
	float t = m_toPlayerDir.Dot(m_enemyForward);
	//内積の結果をacos関数に渡して、m_enemyFowradとtoPlayerDirのなす角度を求める。
	float angle = acos(t);

	//エネミーの前方向を更新する
	if (m_enemyDirState == 0)
	{
		//ダッシュ中じゃないなら
		if (m_dashFlag != true)
		{
			m_enemyForward = m_toPlayerDir;					//プレイヤー向き
			m_enemyMoveSpeed = m_enemyForward * 250.0f;		//移動速度を設定
		}
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
	else if (m_enemyDirState == 4)
	{
		//攻撃中
	}
	else if (m_enemyDirState == 5)	//反動で動けない
	{	
		//時間経過
		m_recoilCount--;			

		if (m_recoilCount <= 0)
		{
			//プレイヤーの方を見るようになる(待機状態)
			m_enemyForward = m_toPlayer;
		}

		if (m_recoilCount <= -180)
		{
			//また戦闘状態になる
			m_attackFlag = false;	
			m_targetFlag = false;
			m_enemyDirState = 0;
			m_recoilCount = 180;
		}
	}


	//ダッシュ中じゃないなら回転する
	if (m_dashFlag != true)
	{
		//エネミーの前方向を使って、回転クォータニオンを計算する。
		m_enemyRotation.SetRotationY(atan2(m_enemyForward.x, m_enemyForward.z));
	}
}

void Enemy_Near::Move()
{
	if (m_enemyDirState == 0) //プレイヤー向き
	{
		//プレイヤーに向かって移動する(通常スピード)
		if (m_distToPlayer >= 1500.0f && m_distToPlayer <= 4000.0f)
		{
			//エネミーの移動
			m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());
			//砂ぼこりの発生
			if (m_sunaHassei >= 10)
			{
				Effect();
				m_sunaHassei = 0;
			}
			//足音再生
			if (m_asiotoSE->IsPlaying() != true)
			{
				m_asiotoSE->Play(true);
			}

		}
		//プレイヤーに向かって移動する(ダッシュ)
		else if (m_distToPlayer < 1500.0f && m_attackFlag == false)
		{
			//ターゲットの設定(1回のみ)
			if (m_targetFlag == false)
			{
				m_enemyTargetPos = m_player->player_position;	//プレイヤーがさっきまでいた場所
				m_targetFlag = true;
			}

			//ダッシュ中
			m_dashFlag = true;	
			
			//エネミーの移動
			m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());
			//砂ぼこりの発生
			if (m_sunaHassei >= 10)
			{
				Effect();
				m_sunaHassei = 0;
			}
			//足音再生
			if (m_dashSE->IsPlaying() != true)
			{
				//ダッシュの効果音を流して普通の足音を消す
				m_dashSE->Play(true);
				m_asiotoSE->Stop();
			}
		}	

		//ターゲットが決まったら
		if (m_targetFlag == true)	
		{
			//ターゲットまでの距離計算
			m_toTarget = m_enemyTargetPos - m_enemyPosition;
			m_distTarget = m_toTarget.Length();
			m_toTarget.Normalize();

			m_enemyForward = m_toTarget;					//ターゲット向き
			m_enemyMoveSpeed = m_enemyForward * 700.0f;		//移動速度を計算(ダッシュ)


			//近づいたら攻撃
			if (m_distTarget <= 150.0f)
			{
				m_fireFlag = true;
				m_enemyDirState = 4;
				//足音停止
				m_dashSE->Stop();
			}
		}
	}
	else if (m_enemyDirState == 2)	//横向き
	{
		//移動させる。
		m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());
		//砂ぼこりの発生
		if (m_sunaHassei >= 10)
		{
			Effect();
			m_sunaHassei = 0;
		}
		//足音再生
		if (m_asiotoSE->IsPlaying() != true)
		{
			m_asiotoSE->Play(true);
		}


		//ある程度したらストップ
		if (rand() % 200 == 1)
		{
			m_enemyDirState = 0;
			//足音停止
			m_asiotoSE->Stop();	
		}
	}
	else if (m_enemyDirState == 3)	//横向き
	{
		//移動させる。
		m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());
		//砂ぼこりの発生
		if (m_sunaHassei >= 10)
		{
			Effect();
			m_sunaHassei = 0;
		}
		//足音再生
		if (m_asiotoSE->IsPlaying() != true)
		{
			m_asiotoSE->Play(true);
		}


		//ある程度したらストップ
		if (rand() % 200 == 1)
		{
			m_enemyDirState = 0;
			//足音停止
			m_asiotoSE->Stop();	
		}
	}
	else if (m_enemyDirState == 4)
	{
		if (m_attackFlag == true)
		{
			m_dashFlag = false;
			m_enemyDirState = 5;	//弾を撃ったら反動で動けない
			return;
		}
	}
}

void Enemy_Near::Attack()
{
	if (m_fireFlag == true)
	{
		//攻撃タイミングの計算
		m_attackCount++;

		//武器によっての分岐
		switch (m_setWeapon)
		{
		case 4://ギガトンキャノン
			if (m_attackCount >= 10)
			{
				Fire(4);	//発射
				m_attackCount = 0;
				m_fireFlag = false;
			}
			break;
		default:
			break;
		}
	}
}

void Enemy_Near::Fire(int weaponNum)
{
	if (weaponNum == 4)
	{
		//弾の生成
		Enemy_Bullet* m_enemyBullet;
		m_enemyBullet = NewGO<Enemy_Bullet>(1, "enemy_bullet");
		m_enemyBullet->m_enemyNearMama = this;
		m_enemyBullet->m_position = m_enemyPosition;						//弾の位置を設定
		m_enemyBullet->m_bulletLocalPosition = { 0.0f,50.0f,100.0f };		//ローカルポジション設定
		m_enemyBullet->originRotation = m_enemyRotation;					//回転はエネミーと同じ

		//爆発音の設定と再生
		m_cannonSE = NewGO<SoundSource>(0);
		m_cannonSE->Init(enGigatonCannon);					//初期化
		m_cannonSE->SetVolume(2.0f);			//音量調整
		m_cannonSE->Play(false);

		m_attackFlag = true;		//弾を撃ったフラグを立てる
	}
}

void Enemy_Near::ItemDrop()
{
	//体力が0になったらアイテムを落とす
	if (m_enemyHP <= 0.0f)
	{
		DeleteGO(this);
		m_dropItem = NewGO<Drop_item>(1, "drop_item");
		m_dropItem->Drop_position = m_enemyPosition;
		m_dropItem->Drop_position.y += 50.0f;
		//エネミーがどの武器を持っていたか取得し、ドロップするアイテムを決める
		m_dropItem->drop_kinds = m_setWeapon;

		//コンテナにくっつける
		m_game->m_dropItemObject.push_back(m_dropItem);
		m_game->AddDefeatedEnemyNumber();//倒した数を増やす

		m_defeatState = true;
		//DeleteGO(this);
	}
}

void Enemy_Near::WeaponMove()
{
	//武器がエネミーと同じ動きをするようにする(親子関係)
	Quaternion originRotation = m_enemyRotation;			//回転はエネミーと同じ
	Vector3 localPosition = { 0.0f,40.0f,0.0f };			//親から見た位置の定義
	originRotation.Multiply(localPosition);					//何かしらの計算
	//最終的な武器の回転を決定
	m_weaponRotation = originRotation;

	m_weaponPosition = m_enemyPosition;		//まず,武器の位置をエネミーと同じに設定し
	m_weaponPosition += localPosition;		//それに親から見た位置を足して最終的な武器の位置を決定
}

void Enemy_Near::Effect()
{
	//砂ぼこりエフェクトの初期化と再生
	sunabokoriEffect = NewGO<EffectEmitter>(0);
	sunabokoriEffect->Init(enSunabokori);
	sunabokoriEffect->SetScale({ 4.0f,4.0f,4.0f });
	sunabokoriEffect->SetRotation(m_enemyRotation);
	sunabokoriEffect->SetPosition({ m_enemyPosition.x,m_enemyPosition.y + 10.0f ,m_enemyPosition.z });
	sunabokoriEffect->Play();
}

void Enemy_Near::SE()
{

}

void Enemy_Near::Render(RenderContext& rc)
{
	//モデルの描画。
	m_enemyModel.Draw(rc);
	m_enemyWeaponModel.Draw(rc);
}