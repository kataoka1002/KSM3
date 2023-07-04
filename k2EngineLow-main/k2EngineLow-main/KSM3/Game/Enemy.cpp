#include "stdafx.h"
#include <time.h>
#include <stdlib.h>
#include "Enemy.h"
#include "Player.h"
#include "Game.h"
#include "Drop_item.h"
#include "Game.h"
#include "Enemy_Bullet.h"
#include "Enemy_HP_UI.h"
#include "GameCamera.h"
#include "Combo.h"

Enemy::Enemy() 
{

	//ステータスの初期化----------------------------------------
	
	//体力
	m_enemyHP = 200;		

	//体力の最大値
	m_enemyHPMax = 200;							

	//武器の種類
	m_setWeapon = 2;

	//武器のローカルポジション
	m_weaponLocalPos = { 0.0f,40.0f,40.0f };

	//エネミーの移動速度
	m_enemySpeed = 250.0f;

	//----------------------------------------------------------

}

Enemy::~Enemy() 
{

	//エネミーの足音の削除
	DeleteGO(m_asiotoSE);

	//HPのUIを削除
	DeleteGO(m_HPUI);

	//エネミーの死亡SEを削除
	DeleteGO(m_enemyDeadSE);

	//マシンガンのSEの削除
	DeleteGO(m_machineGunSE);

}

void Enemy::GameSetUp()
{

	//効果音の作成(流し続ける音源なのでインスタンスを保持させる)
	m_machineGunSE = NewGO<SoundSource>(0);
	m_machineGunSE->Init(enMachineGun);					//初期化
	m_machineGunSE->SetVolume(0.5f * m_game->GetSEVol());	//音量調整
	
	
	//作成したUIクラスに自分のポインタを教える
	m_HPUI->SetEnemy(this);	

}

void Enemy::InitEnemyModel()
{

	//エネミーモデルの設定
	m_enemyModel->Init("Assets/modelData/enemy_model.tkm");
	m_enemyModel->SetScale(2.0f);
	m_enemyModel->SetRotation(m_enemyRotation);
	m_enemyModel->SetPosition(m_enemyPosition);


	//キャラクターコントローラーを初期化。
	m_enemyCharacterController.Init(
		100.0f,			//半径。
		40.0f,			//高さ。
		m_enemyPosition	//座標。
	);

}

void Enemy::Update()
{

	//プレイヤーが死亡した時用の音量調整
	m_machineGunSE->SetVolume(0.5f * m_game->GetSEVol());


	//プレイヤーがメインゲーム中なら
	if (m_player->GetGameState() == MAIN_GAME_NUM)
	{

		//エネミーに共通する動き
		NormalAction(4000.0f);

		//効果音の処理
		SE();				
		
		//倒した時にアイテムを落とす処理
		HPUnder0();			
		
	}
	//プレイヤーがポーズ中またはカスタム中の時
	else if (m_player->GetGameState() == PAUSE_NUM || m_player->GetGameState() == CUSTOMIZE_NUM)
	{

		//足音停止
		AsiotoSEManage(false);

		//攻撃音停止
		m_machineGunSE->Stop();

	}
}

void Enemy::PlayerSearch() 
{

	//エネミーの前方向とtoPlayerDirとの内積を計算する
	float t = m_toPlayerDir.Dot(m_enemyForward);


	//内積の結果をacos関数に渡して、m_enemyFowradとtoPlayerDirのなす角度を求める。
	float angle = acos(t);


	//エネミーの視野にプレイヤーが入っている&距離が1500以下になる&プレイヤーの方向を向いている
	if (fabsf(angle) < Math::DegToRad(45.0f) && m_distToPlayer <= 1500.0f && m_enemyDirState == 0) 
	{

		//攻撃可能
		m_atackOK = true;		

	}
	else 
	{

		//攻撃不可
		m_atackOK = false;
		
		//効果音は流さない
		m_machinGunSEPlay = false;	

	}


	//速度計算
	CalcSpeed(m_enemySpeed, m_enemyDirState);


	//後退中じゃないなら
	if (m_enemyEscape != true) 
	{

		//エネミーの前方向を使って、回転クォータニオンを計算する。
		m_enemyRotation.SetRotationY(atan2(m_enemyForward.x, m_enemyForward.z));

	}

}

void Enemy::Move() 
{

	//プレイヤー向き
	if (m_enemyDirState == 0)
	{
		
		//条件を満たしている間
		if (m_distToPlayer >= 1500.0f && m_distToPlayer <= 4000.0f)
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
		if (m_distToPlayer <= 800.0f && rand() % 200 == 1)
		{

			//後ろ向きのステート
			m_enemyDirState = 1;


			//移動速度の設定
			m_enemyMoveSpeed = m_enemyForward * -250.0f;	


			//逃げているフラグを立てる
			m_enemyEscape = true;

		}
		//エネミーとプレイヤーの距離が近い時 & 一定確率
		else if (m_distToPlayer < 1500.0f && rand() % 900 == 1)
		{

			//横移動ステート
			m_enemyDirState = 2;

		}
		//エネミーとプレイヤーの距離が近い時 & 一定確率
		else if (m_distToPlayer < 1500.0f && rand() % 900 == 1)
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


		//一定距離以上 or 一定確率
		if (m_distToPlayer > 1400.0f || rand() % 400 == 1)
		{

			//逃げているフラグを下げる
			m_enemyEscape = false;


			//前向きのステート
			m_enemyDirState = 0;


			//足音停止
			AsiotoSEManage(false);

		}


		//足音再生
		AsiotoSEManage(true);

	}
	//横向き
	else if (m_enemyDirState == 2)	
	{

		//移動
		m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());


		//砂ぼこりの発生
		DustEffect();
		

		//足音再生
		AsiotoSEManage(true);


		//ある程度したら
		if (rand() % 200 == 1)
		{

			//前向きステート
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


		//ある程度したら
		if (rand() % 200 == 1)
		{

			//前向きステート
			m_enemyDirState = 0;


			//足音停止
			AsiotoSEManage(false);

		}

	}

}

void Enemy::Attack()
{

	//攻撃が可能になったら
	if (m_atackOK == true)
	{

		//攻撃タイミングの計算
		m_attackCount++;


		//武器によっての分岐
		switch (m_setWeapon)
		{

		case GIGAPLASMA_NUM://ギガプラズマ


			//一定のカウントになると
			if (m_attackCount % 300 == 0)
			{

				//発射
				Fire(GIGAPLASMA_NUM);


				//カウントリセット
				m_attackCount = 0;

			}
			break;


		case MACHINEGUN_NUM://マシンガン


			//一定のカウントになると
			if (m_attackCount >= 5)
			{

				//発射
				Fire(MACHINEGUN_NUM);


				//カウントリセット
				m_attackCount = 0;
				
				
				//マシンガンの効果音流す
				m_machinGunSEPlay = true;	

			}
			break;


		case HELLFIRE_NUM://ヘルファイヤ


			//一定のカウントになると
			if (m_attackCount % 60 == 0)
			{

				//発射
				Fire(HELLFIRE_NUM);
							
							
				//カウントリセット
				m_attackCount = 0;

			}
			break;


		default:
			break;

		}

	}

}

void Enemy:: Fire(int m_weaponNum)
{

	//マシンガンの時
	if (m_weaponNum == MACHINEGUN_NUM)
	{

		//弾の生成(1個目)
		Enemy_Bullet* m_enemyBullet;
		m_enemyBullet = NewGO<Enemy_Bullet>(1, "enemy_bullet");
		m_enemyBullet->SetEnemyMama(this);									//弾に自分のポインタを教える
		m_enemyBullet->SetPosition(m_enemyPosition);						//弾の位置を設定
		m_enemyBullet->SetLocalPosition({30.0f,50.0f,190.0f});		//ローカルポジション設定
		m_enemyBullet->SetRotation(m_enemyRotation);					//回転はエネミーと同じ


		//弾の生成(2個目)
		Enemy_Bullet* m_enemyBullet2;
		m_enemyBullet2 = NewGO<Enemy_Bullet>(1, "enemy_bullet");
		m_enemyBullet2->SetEnemyMama(this);									//弾に自分のポインタを教える
		m_enemyBullet2->SetPosition(m_enemyPosition);						//弾の位置を設定
		m_enemyBullet2->SetLocalPosition({-30.0f,50.0f,190.0f});	//ローカルポジション設定
		m_enemyBullet2->SetRotation(m_enemyRotation);					//回転はエネミーと同じ

	}

}

void Enemy::HPUnder0()
{

	//体力が0になったらアイテムを落とす
	if (m_enemyHP <= 0.0f)
	{

		//死亡時の処理
		ExecuteOnEnemyDefeated();


		//自分自身の削除
		DeleteGO(this);


		//リストから消す
		m_game->RemoveEnemyFromList(this);

	}

}

void Enemy::EnemyDead()
{

	//爆発エフェクトの再生
	PlayEffect(enEnemyDead, m_enemyPosition, m_enemyRotation, { 5.0f,5.0f,5.0f });


	//爆発音の設定と再生
	m_enemyDeadSE = NewGO<SoundSource>(0);			//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
	m_enemyDeadSE->Init(enEnemyDeadSE);				
	m_enemyDeadSE->SetVolume(1.5f * m_game->GetSEVol());
	m_enemyDeadSE->Play(false);

}

void Enemy::SE()
{

	//マシンガンの時
	if (m_setWeapon == MACHINEGUN_NUM)	
	{

		//攻撃中なら
		if (m_machinGunSEPlay == true && m_machineGunSE->IsPlaying() != true)
		{

			//マシンガンの効果音を再生
			m_machineGunSE->Play(true);	

		}
		//攻撃中じゃないなら
		else if (m_machinGunSEPlay == false)
		{

			//マシンガンの効果音を停止
			m_machineGunSE->Stop();		

		}

	}

}

void Enemy::Render(RenderContext& rc)
{

	//敵モデルの描画
	m_enemyModel->Draw(rc);

	//武器モデルの描画
	m_enemyWeaponModel->Draw(rc);

}
