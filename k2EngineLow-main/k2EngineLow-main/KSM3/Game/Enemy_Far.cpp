#include "stdafx.h"
#include <time.h>
#include <stdlib.h>
#include "Enemy_Far.h"
#include "Player.h"
#include "Game.h"
#include "Drop_item.h"
#include "Enemy_Bullet.h"
#include "Enemy_HP_UI.h"
#include "GameCamera.h"
#include "Combo.h"


Enemy_Far::Enemy_Far()
{

	//ステータスの初期化----------------------------------------

	//体力
	m_enemyHP = 200;

	//体力の最大値
	m_enemyHPMax = 200;

	//武器の種類
	m_setWeapon = 6;

	//武器のローカルポジション
	m_weaponLocalPos = { 0.0f,120.0f,150.0f };

	//エネミーの移動速度
	m_enemySpeed = 200.0f;

	//----------------------------------------------------------

}

Enemy_Far::~Enemy_Far()
{

	//エネミーの足音の削除
	DeleteGO(m_asiotoSE);

	//HPのUIを削除
	DeleteGO(m_HPUI);

	//エネミーの死亡SEを削除
	DeleteGO(m_enemyDeadSE);

	//ビシ音を削除
	DeleteGO(m_bisiSE);

	//戦艦砲SEの削除
	DeleteGO(m_battleShipGunSE);

}

void Enemy_Far::GameSetUp()
{

	//作成したUIクラスに自分のポインタを教える
	m_HPUI->SetEnemyFar(this);	

}

void Enemy_Far::InitEnemyModel()
{

	//エネミーの設定
	m_enemyModel->Init("Assets/modelData/Enemy_model_type2.tkm");
	m_enemyModel->SetScale(m_enemySize);
	m_enemyModel->SetRotation(m_enemyRotation);
	m_enemyModel->SetPosition(m_enemyPosition);


	//キャラクターコントローラーを初期化。
	m_enemyCharacterController.Init(
		200.0f,			//半径。
		70.0f,			//高さ。
		m_enemyPosition	//座標。
	);

}

void Enemy_Far::Update()
{
	//世界が止まっているとき
	if (m_game->IsStopWorld() != false)
	{
		if (m_deleteGoThisFlag == true)
		{
			ToPushButton();
		}

		return;
	}

	//メインゲーム中
	if (m_player->GetGameState() == MAIN_GAME_NUM)
	{

		//生きている間
		if (m_defeatState == false)
		{

			//エネミーに共通する動き
			NormalAction(5000.0f);


			//体力が0になった時の処理
			HPUnder0();

		}
		//死んだら
		else if (m_defeatState == true)	
		{
			
			//まだ固まっているとき
			if (m_flashFinishFlag == false)	
			{

				//一定時間経過したら
				if (m_flashTime < 0)
				{

					//死亡時の処理
					ExecuteOnEnemyDefeated();


					//衝撃発生が終わったフラグを立てる
					m_flashFinishFlag = true;

				}


				//時間計測
				m_flashTime--;

				return;
			}

			
			//サイズを小さくしていく
			m_enemySize -= 0.15f;
			

			//サイズが0以下になると
			if (m_enemySize <= 0.0f)
			{

				//自分自身の削除
				DeleteGO(this);


				//リストから消す
				m_game->RemoveEnemyFarFromList(this);

			}


			//モデルサイズの更新
			m_enemyModel->SetScale(m_enemySize);
			m_enemyModel->Update();

		}
	}
	else if (m_player->GetGameState() == PAUSE_NUM || m_player->GetGameState() == CUSTOMIZE_NUM)
	{

		//足音停止
		AsiotoSEManage(false);

	}
}


void Enemy_Far::PlayerSearch()
{

	//エネミーの前方向とtoPlayerDirとの内積を計算する
	float t = m_toPlayerDir.Dot(m_enemyForward);


	//内積の結果をacos関数に渡して、m_enemyFowradとtoPlayerDirのなす角度を求める。
	float angle = acos(t);


	//エネミーの視野にプレイヤーが入っている&距離が3000以下になる & プレイヤーの方向を向いている
	if (fabsf(angle) < Math::DegToRad(45.0f) && m_distToPlayer <= 3000.0f && m_enemyDirState == 0) 
	{

		//攻撃可能
		m_atackOK = true;

	}
	else 
	{

		//攻撃不可
		m_atackOK = false;

	}


	//速度計算
	CalcSpeed(m_enemySpeed, m_enemyDirState);


	//後退してないなら
	if (m_enemyEscape != true)
	{

		//エネミーの前方向を使って、回転クォータニオンを計算する。
		m_enemyRotation.SetRotationY(atan2(m_enemyForward.x, m_enemyForward.z));

	}

}

void Enemy_Far::Move()
{
	
	//プレイヤー向き
	if (m_enemyDirState == 0) 
	{

		//条件を満たしている間だけプレイヤーに向かって移動する
		if (m_distToPlayer >= 3000.0f && m_distToPlayer <= 5000.0f)
		{

			//エネミーの移動
			m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());


			//砂ぼこりの発生
			DustEffect();


			//足音再生
			AsiotoSEManage(true);

		}
		else
		{

			//足音停止
			AsiotoSEManage(false);

		}


		//エネミーとプレイヤーの距離が近い時 & 一定確率
		if (m_distToPlayer <= 1500.0f && rand() % 150 == 1)
		{

			//後退ステート
			m_enemyDirState = 1;
			

			//移動速度の設定
			m_enemyMoveSpeed = m_enemyForward * -250.0f;	


			//後退中フラグを立てる
			m_enemyEscape = true;

		}
		//エネミーとプレイヤーの距離が近い時 & 一定確率
		else if (m_distToPlayer < 2800.0f && rand() % 900 == 1)
		{
			
			//横移動ステート
			m_enemyDirState = 2;

		}
		//エネミーとプレイヤーの距離が近い時 & 一定確率
		else if (m_distToPlayer < 2800.0f && rand() % 900 == 1)
		{

			//横移動ステート
			m_enemyDirState = 3;

		}

	}
	//後ろ向き
	else if (m_enemyDirState == 1)	
	{

		//移動させる。
		m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());


		//足音再生
		AsiotoSEManage(true);


		//一定距離以上 or 一定確率
		if (m_distToPlayer > 2800.0f || rand() % 300 == 1)
		{
			
			//後退ストップ
			m_enemyEscape = false;


			//前向きステートに変更
			m_enemyDirState = 0;


			//足音停止
			AsiotoSEManage(false);

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

			//前向きステートに変更
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

			//前向きステートに戻す
			m_enemyDirState = 0;


			//足音停止
			AsiotoSEManage(false);

		}

	}

}

void Enemy_Far::Attack()
{
	//攻撃が可能なら
	if (m_atackOK == true)
	{

		//攻撃タイミングの計算
		m_attackCount++;


		//武器によっての分岐
		switch (m_setWeapon)
		{
		case MISSILE_NUM://ミサイル


			//一定のカウントになると
			if (m_attackCount % 180 == 0)
			{

				//発射
				Fire(MISSILE_NUM);


				//カウントリセット
				m_attackCount = 0;

			}

			break;


		case BATTLESHIPGUN_NUM://戦艦砲


			//一定のカウントになると
			if (m_attackCount >= 120)
			{

				//発射
				Fire(BATTLESHIPGUN_NUM);
							
							
				//カウントリセット
				m_attackCount = 0;

			}

			break;


		default:
			break;

		}

	}

}

void Enemy_Far::Fire(int m_weaponNum)
{
	
	//戦艦砲なら
	if (m_weaponNum == BATTLESHIPGUN_NUM)
	{

		//弾の生成
		Enemy_Bullet* m_enemyBullet;
		m_enemyBullet = NewGO<Enemy_Bullet>(1, "enemy_bullet");
		m_enemyBullet->SetEnemyFarMama(this);
		m_enemyBullet->SetPosition(m_enemyPosition);						//弾の位置を設定
		m_enemyBullet->SetLocalPosition({105.0f,140.0f,290.0f});	//ローカルポジション設定
		//m_enemyBullet->m_bulletFowrad = m_enemyForward;						//弾の前方向の設定		
		m_enemyBullet->SetRotation(m_enemyRotation);					//回転はエネミーと同じ


		//弾の生成
		Enemy_Bullet* m_enemyBullet2;
		m_enemyBullet2 = NewGO<Enemy_Bullet>(1, "enemy_bullet");
		m_enemyBullet2->SetEnemyFarMama(this);
		m_enemyBullet2->SetPosition(m_enemyPosition);						//弾の位置を設定
		m_enemyBullet2->SetLocalPosition({-105.0f,140.0f,290.0f});	//ローカルポジション設定
		m_enemyBullet2->SetRotation(m_enemyRotation);					//回転はエネミーと同じ


		//弾の生成
		Enemy_Bullet* m_enemyBullet3;
		m_enemyBullet3 = NewGO<Enemy_Bullet>(1, "enemy_bullet");
		m_enemyBullet3->SetEnemyFarMama(this);
		m_enemyBullet3->SetPosition(m_enemyPosition);						//弾の位置を設定
		m_enemyBullet3->SetLocalPosition({0.0f,140.0f,290.0f});		//ローカルポジション設定
		m_enemyBullet3->SetRotation(m_enemyRotation);					//回転はエネミーと同じ


		//発射音の設定と再生
		m_battleShipGunSE = NewGO<SoundSource>(0);	//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
		m_battleShipGunSE->Init(enButtleShipGun);	//初期化
		m_battleShipGunSE->SetVolume(1.0f * m_game->GetSEVol());			//音量調整
		m_battleShipGunSE->Play(false);

	}
}

void Enemy_Far::HPUnder0()
{

	//HPが0以下になると
	if (m_enemyHP <= 0.0f)
	{

		//死亡フラグを立てる
		m_defeatState = true;


		//衝撃がまだ発生してないなら
		if (m_impactPlay == false)
		{

			//衝撃エフェクトの再生
			PlayEffect(enImpact, m_enemyPosition, m_enemyRotation, { 10.0f,10.0f,10.0f });


			//衝撃のSEを再生
			m_bisiSE = NewGO<SoundSource>(0);
			m_bisiSE->Init(enBisi);								//初期化
			m_bisiSE->SetVolume(3.8f * m_game->GetSEVol());		//音量調整
			m_bisiSE->Play(false);								//再生


			//衝撃発生フラグを立てる
			m_impactPlay = true;

		}
		
		//モデルを白くさせる
		//m_enemyModel->PlayFlash();

	}

}

void Enemy_Far::EnemyDead()
{

	//爆発エフェクトの再生
	PlayEffect(enEnemyDead, m_enemyPosition, m_enemyRotation, { 5.0f,5.0f,5.0f });


	//別の爆発エフェクトの再生
	PlayEffect(enTyakudan, m_enemyPosition, m_enemyRotation, { 15.7f,15.7f,15.7f });


	//爆発音の設定と再生
	m_enemyDeadSE = NewGO<SoundSource>(0);	//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
	m_enemyDeadSE->Init(enEnemyDeadSE);		//初期化
	m_enemyDeadSE->SetVolume(1.5f * m_game->GetSEVol());			//音量調整
	m_enemyDeadSE->Play(false);

}

void Enemy_Far::DeleteGoThis()
{
	//自分自身の削除
	DeleteGO(this);

	//リストから消す
	m_game->RemoveEnemyFarFromList(this);
}


void Enemy_Far::Render(RenderContext& rc)
{

	//モデルの描画。
	m_enemyModel->Draw(rc);

	//生きている間
	if (m_defeatState == false)
	{
		//武器表示
		m_enemyWeaponModel->Draw(rc);
	}

}
