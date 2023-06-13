#include "stdafx.h"
#include <time.h>
#include <stdlib.h>
#include "Enemy_Near.h"
#include "Player.h"
#include "Game.h"
#include "Drop_item.h"
#include "Enemy_Bullet.h"
#include "Enemy_HP_UI.h"
#include "GameCamera.h"
#include "Combo.h"


Enemy_Near::Enemy_Near()
{

	//ステータスの初期化----------------------------------------

	//体力
	m_enemyHP = 200;

	//体力の最大値
	m_enemyHPMax = 200;

	//武器の種類
	m_setWeapon = 4;

	//武器のローカルポジション
	m_weaponLocalPos = { 0.0f,40.0f,0.0f };

	//エネミーの移動速度
	m_enemySpeed = 250.0f;

	//----------------------------------------------------------

}

Enemy_Near::~Enemy_Near()
{

	//エネミーの足音の削除
	DeleteGO(m_asiotoSE);

	//HPのUIを削除
	DeleteGO(m_HPUI);

	//エネミーの死亡SEを削除
	DeleteGO(m_enemyDeadSE);

	//キャノンのSEを削除
	DeleteGO(m_cannonSE);

}

void Enemy_Near::GameSetUp()
{

	//作成したUIクラスに自分のポインタを教える
	m_HPUI->m_enemyNear = (this);

}

void Enemy_Near::InitEnemyModel()
{
	
	//エネミーの設定
	m_enemyModel.Init("Assets/modelData/enemy_model.tkm");
	m_enemyModel.SetScale(2.0f);
	m_enemyModel.SetRotation(m_enemyRotation);
	m_enemyModel.SetPosition(m_enemyPosition);


	//キャラクターコントローラーを初期化
	m_enemyCharacterController.Init(
		50.0f,			//半径。
		40.0f,			//高さ。
		m_enemyPosition	//座標。
	);

}

void Enemy_Near::Update()
{

	//メインゲーム中
	if (m_player->game_state == 0)
	{

		//エネミーに共通する動き
		NormalAction(4000.0f);


		//倒した時にアイテムを落とす処理
		HPUnder0();

	}
	else if (m_player->game_state == 1 || m_player->game_state == 3)
	{

		//足音停止
		AsiotoSEManage(false);

	}
}

void Enemy_Near::PlayerSearch()
{

	//エネミーの前方向を更新する


	//プレイヤー向きの時
	if (m_enemyDirState == 0)
	{

		//ダッシュ中じゃないなら
		if (m_dashFlag != true)
		{
			
			//プレイヤー向き
			m_enemyForward = m_toPlayerDir;					
			
			//移動速度を設定
			m_enemyMoveSpeed = m_enemyForward * 250.0f;		 

		}

	}
	//横移動中
	else if (m_enemyDirState == 2)
	{

		//外積からエネミーの横方向を取得
		m_enemyForward = Cross(m_Up, m_toPlayerDir);	
		
		
		//移動速度の設定
		m_enemyMoveSpeed = m_enemyForward * 250.0f;		

	}
	//横移動中
	else if (m_enemyDirState == 3)
	{

		//外積からエネミーの横方向を取得
		m_enemyForward = Cross(m_toPlayerDir, m_Up);	
		
		
		//移動速度の設定
		m_enemyMoveSpeed = m_enemyForward * 250.0f;		

	}
	//攻撃中
	else if (m_enemyDirState == 4)
	{

		//攻撃

	}
	//反動中で動けない
	else if (m_enemyDirState == 5)	
	{	

		//時間経過
		m_recoilCount--;			


		//カウントが一定以下になったら
		if (m_recoilCount <= 0)
		{

			//プレイヤーの方を見るようになる(待機状態)
			m_enemyForward = m_toPlayer;

		}


		//カウントが一定以下になったら
		if (m_recoilCount <= -180)
		{
			//また戦闘状態になる
			

			//弾を撃ったかどうかフラグを下ろす
			m_attackFlag = false;	


			//ターゲットを設定しているかどうかフラグを下ろす
			m_targetFlag = false;


			//プレイヤー向きステートにする
			m_enemyDirState = 0;


			//カウントリセット
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
	
	//プレイヤー向き
	if (m_enemyDirState == 0) 
	{

		//プレイヤーに向かって移動する(通常スピード)
		if (m_distToPlayer >= 1500.0f && m_distToPlayer <= 4000.0f)
		{

			//エネミーの移動
			m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());


			//砂ぼこりの発生
			DustEffect();


			//足音再生
			AsiotoSEManage(true);

		}
		//一定距離以内 & 弾をまだ撃ってないなら
		else if (m_distToPlayer < 1500.0f && m_attackFlag == false)
		{
			//プレイヤーに向かって移動する(ダッシュ)
			
			//ターゲットを設定してないなら
			if (m_targetFlag == false)
			{

				//プレイヤーがさっきまでいた場所をターゲットの設定(1回のみ)
				m_enemyTargetPos = m_player->player_position;

				//ターゲットセットフラグを立てる
				m_targetFlag = true;

			}


			//ダッシュ中
			m_dashFlag = true;	

			
			//エネミーの移動
			m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());


			//砂ぼこりの発生
			DustEffect();


			//足音停止
			AsiotoSEManage(false);

		}	


		//ターゲットが決まったら
		if (m_targetFlag == true)	
		{

			//エネミーからターゲットまでのベクトルを求める
			m_toTarget = m_enemyTargetPos - m_enemyPosition;


			//そのベクトルの距離を求める
			m_distTarget = m_toTarget.Length();


			//そのベクトルを正規化
			m_toTarget.Normalize();

			
			//ターゲット向き
			m_enemyForward = m_toTarget;					
			
			
			//移動速度を計算(ダッシュ)
			m_enemyMoveSpeed = m_enemyForward * 700.0f;		


			//近づいたら攻撃
			if (m_distTarget <= 150.0f)
			{

				//攻撃可能フラグを立てる
				m_fireFlag = true;

				//攻撃中ステートに変更
				m_enemyDirState = 4;

			}

		}

	}
	//横向き
	else if (m_enemyDirState == 2)	
	{

		//移動させる。
		m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());


		//砂ぼこりの発生
		DustEffect();


		//足音再生
		AsiotoSEManage(true);


		//ある程度したらストップ
		if (rand() % 200 == 1)
		{

			//プレイヤー向き
			m_enemyDirState = 0;


			//足音停止
			AsiotoSEManage(false);

		}

	}
	//横向き
	else if (m_enemyDirState == 3)	
	{

		//移動させる。
		m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());


		//砂ぼこりの発生
		DustEffect();


		//足音再生
		AsiotoSEManage(true);


		//ある程度したらストップ
		if (rand() % 200 == 1)
		{

			//プレイヤー向き
			m_enemyDirState = 0;


			//足音停止
			AsiotoSEManage(false);

		}

	}
	//攻撃中
	else if (m_enemyDirState == 4)
	{
		
		//弾を撃ったら
		if (m_attackFlag == true)
		{

			//ダッシュしているフラグを下す
			m_dashFlag = false;


			//弾を撃ったら反動で動けないステート
			m_enemyDirState = 5;	

			return;
		}

	}

}

void Enemy_Near::Attack()
{

	//攻撃可能なら
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

				//発射
				Fire(4);	


				//カウントリセット
				m_attackCount = 0;


				//攻撃可能フラグを下す
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

	//ギガトンキャノンなら
	if (weaponNum == 4)
	{

		//弾の生成
		Enemy_Bullet* m_enemyBullet;
		m_enemyBullet = NewGO<Enemy_Bullet>(1, "enemy_bullet");
		m_enemyBullet->m_enemyNearMama = this;
		m_enemyBullet->m_position = m_enemyPosition;						//弾の位置を設定
		m_enemyBullet->m_bulletLocalPosition = { 0.0f,100.0f,130.0f };		//ローカルポジション設定
		m_enemyBullet->originRotation = m_enemyRotation;					//回転はエネミーと同じ


		//爆発音の設定と再生
		m_cannonSE = NewGO<SoundSource>(0);
		m_cannonSE->Init(enGigatonCannon);					//初期化
		m_cannonSE->SetVolume(2.0f * m_game->SEvol);		//音量調整
		m_cannonSE->Play(false);


		//弾を撃ったフラグを立てる
		m_attackFlag = true;	

	}

}

void Enemy_Near::HPUnder0()
{

	//体力が0になったらアイテムを落とす
	if (m_enemyHP <= 0.0f)
	{

		//死亡時の処理
		ExecuteOnEnemyDefeated();


		//自分自身の削除
		DeleteGO(this);


		//リストから消す
		m_game->RemoveEnemyNearFromList(this);

	}

}

void Enemy_Near::EnemyDead()
{

	//爆発エフェクトの再生
	PlayEffect(enEnemyDead, m_enemyPosition, m_enemyRotation, { 5.0f,5.0f,5.0f });


	//爆発音の設定と再生
	m_enemyDeadSE = NewGO<SoundSource>(0);			//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
	m_enemyDeadSE->Init(enEnemyDeadSE);				//初期化
	m_enemyDeadSE->SetVolume(1.5f * m_game->SEvol);	//音量調整
	m_enemyDeadSE->Play(false);

}

void Enemy_Near::Render(RenderContext& rc)
{

	//モデルの描画。
	m_enemyModel.Draw(rc);

	//武器モデルの描画
	m_enemyWeaponModel.Draw(rc);

}