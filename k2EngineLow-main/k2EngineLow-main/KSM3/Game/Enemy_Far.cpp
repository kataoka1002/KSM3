#include "stdafx.h"
#include "Enemy_Far.h"
#include "Player.h"
#include "Game.h"
#include <time.h>
#include <stdlib.h>
#include "Battle_ship_attack.h"
#include "Drop_item.h"
#include "Enemy_Bullet.h"
#include "Enemy_HP_UI.h"
#include "GameCamera.h"
#include "Combo.h"


Enemy_Far::Enemy_Far()
{
	//足音の生成(流し続ける音源なのでインスタンスを保持させる)
	m_asiotoSE = NewGO<SoundSource>(0);

	m_pointList.push_back({ RandPos(),1 });		//一番目のポイント
	m_pointList.push_back({ RandPos(),2 });		//二番目のポイント
	m_pointList.push_back({ RandPos(),3 });		//三番目のポイント
	m_pointList.push_back({ RandPos(),4 });		//四番目のポイント
	m_point = &m_pointList[0];					//一番目のポイントを入れる
}

Enemy_Far::~Enemy_Far()
{
	//エネミーが生きているかをプレーヤーに教える
	//m_player->enemy_survival = false;	

	
	DeleteGO(m_bisiSE);
	DeleteGO(m_asiotoSE);
	DeleteGO(m_HPUI);
}

bool Enemy_Far::Start()
{
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");

	//HPのUI作成
	m_HPUI = NewGO<Enemy_HP_UI>(1, "enemy_hp_ui");
	m_HPUI->m_enemyFar = (this);	//作成したUIクラスに自分のポインタを教える

	//エネミーの設定
	m_enemyModel.Init("Assets/modelData/Enemy_model_type2.tkm");
	m_enemyModel.SetScale(m_enemySize);
	m_enemyModel.SetRotation(m_enemyRotation);
	m_enemyModel.SetPosition(m_enemyPosition);
	//キャラクターコントローラーを初期化。
	m_enemyCharacterController.Init(
		200.0f,			//半径。
		70.0f,			//高さ。
		m_enemyPosition	//座標。
	);

	//足音の設定
	m_asiotoSE->Init(enRunning);					//初期化
	m_asiotoSE->SetVolume(0.8f * m_game->SEvol);	//音量調整
	m_asiotoSE->Play(true);							//再生
	m_asiotoSE->Stop();

	//エネミー生成エフェクトの設定と再生
	EffectEmitter*enemyHassei = NewGO<EffectEmitter>(0);
	enemyHassei->Init(enEnemyHassei);
	enemyHassei->SetScale({ 15.0f,15.0f,15.0f });
	enemyHassei->SetRotation(m_enemyRotation);
	enemyHassei->SetPosition({ m_enemyPosition.x,m_enemyPosition.y ,m_enemyPosition.z });
	enemyHassei->Play();


	//武器生成
	SetUp();	

	return true;
}

void Enemy_Far::SetUp()
{
	//敵の武器の種類の確定
	m_setWeapon = 6;//ここはいったん仮で定数設定してるだけで後々ランダムにしていく予定
	//set_weapons = rand() % 2 + 1;
	if (m_setWeapon == 5) {	//ミサイル
		
	}
	else if (m_setWeapon == 6) { //戦艦砲
		//武器モデルの設定
		m_enemyWeaponModel.Init("Assets/modelData/battleship_gun_enemy.tkm");
		m_enemyWeaponModel.SetScale({ 3.0f ,5.0f,3.0f });
		m_enemyWeaponModel.SetPosition(m_weaponPosition);
		m_enemyWeaponModel.SetRotation(m_weaponRotation);
		m_enemyWeaponModel.Update();
	}
}

void Enemy_Far::Update()
{
	//プレイヤーが死亡したとき用
	m_asiotoSE->SetVolume(0.8f * m_game->SEvol);	//音量調整

	if (m_player->game_state == 0)
	{
		if (m_defeatState == true)
		{
			//砂ぼこりの発生カウント
			m_sunaHassei++;

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

			//SE();				//効果音の処理
			WeaponMove();		//武器の移動回転	
			//体力が0になったら死亡フラグを立たせる
			if (m_enemyHP <= 0.0f)
			{
				m_defeatState = false;
				if (m_impactPlay == false)
				{
					EffectEmitter* impact = NewGO<EffectEmitter>(0);
					impact->Init(enImpact);
					impact->SetScale({ 10.0f,10.0f,10.0f });
					impact->SetRotation(m_enemyRotation);
					impact->SetPosition({ m_enemyPosition.x,m_enemyPosition.y ,m_enemyPosition.z });
					impact->Play();

					m_bisiSE = NewGO<SoundSource>(0);
					m_bisiSE->Init(enBisi);						//初期化
					m_bisiSE->SetVolume(3.8f * m_game->SEvol);	//音量調整
					m_bisiSE->Play(false);						//再生

					m_impactPlay = true;
				}
				m_enemyModel.PlayFlash();	//モデルを白くさせる
			}

			//エネミーと武器の更新
			m_enemyModel.SetPosition(m_enemyPosition);
			m_enemyModel.SetRotation(m_enemyRotation);
			m_enemyModel.Update();
			m_enemyWeaponModel.SetPosition(m_weaponPosition);
			m_enemyWeaponModel.SetRotation(m_weaponRotation);
			m_enemyWeaponModel.Update();

		}
		else if (m_defeatState == false)	//死んだら
		{
			if (m_flashFinishFlag == false)	//まだ固まっているとき
			{
				if (m_flashTime < 0)
				{
					ItemDrop();			//死亡演出
					m_flashFinishFlag = true;
				}

				m_flashTime--;
				return;
			}

			

			m_enemySize -= 0.15f;
			
			if (m_enemySize <= 0.0f)
			{
				DeleteGO(this);
				//リストから消す
				m_game->RemoveEnemyFarFromList(this);
			}
			m_enemyModel.SetScale(m_enemySize);
			m_enemyModel.Update();
		}
	}
	else if (m_player->game_state == 1 || m_player->game_state == 3)
	{
		//足音停止
		m_asiotoSE->Stop();
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

	//エネミーの視野にプレイヤーが入っている&距離が3000以下になる&プレイヤーの方向を向いている
	if (fabsf(angle) < Math::DegToRad(45.0f) && m_distToPlayer <= 3000.0f && m_enemyDirState == 0) {
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
		else
		{
			//足音停止
			m_asiotoSE->Stop();			
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
		//足音再生
		if (m_asiotoSE->IsPlaying() != true)
		{
			m_asiotoSE->Play(true);
		}

		//一定距離以上になると後退ストップ
		if (m_distToPlayer > 2800.0f || rand() % 300 == 1)
		{
			m_enemyEscape = false;
			m_enemyDirState = 0;
			//足音停止
			m_asiotoSE->Stop();	
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
		case 5://ミサイル
			if (m_attackCount % 180 == 0)
			{
				Fire(5);	//発射
				m_attackCount = 0;
			}
			break;
		case 6://戦艦砲
			if (m_attackCount >= 120)
			{
				Fire(6);	//発射
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
	if (m_weaponNum == 6)	//戦艦砲なら
	{
		//弾の生成
		Enemy_Bullet* m_enemyBullet;
		m_enemyBullet = NewGO<Enemy_Bullet>(1, "enemy_bullet");
		m_enemyBullet->m_enemyFarMama = this;
		m_enemyBullet->m_position = m_enemyPosition;						//弾の位置を設定
		m_enemyBullet->m_bulletLocalPosition = { 105.0f,140.0f,290.0f };	//ローカルポジション設定
		m_enemyBullet->m_bulletFowrad = m_enemyForward;						//弾の前方向の設定		
		m_enemyBullet->originRotation = m_enemyRotation;					//回転はエネミーと同じ

		//弾の生成
		Enemy_Bullet* m_enemyBullet2;
		m_enemyBullet2 = NewGO<Enemy_Bullet>(1, "enemy_bullet");
		m_enemyBullet2->m_enemyFarMama = this;
		m_enemyBullet2->m_position = m_enemyPosition;						//弾の位置を設定
		m_enemyBullet2->m_bulletLocalPosition = { -105.0f,140.0f,290.0f };	//ローカルポジション設定
		m_enemyBullet2->originRotation = m_enemyRotation;					//回転はエネミーと同じ

		//弾の生成
		Enemy_Bullet* m_enemyBullet3;
		m_enemyBullet3 = NewGO<Enemy_Bullet>(1, "enemy_bullet");
		m_enemyBullet3->m_enemyFarMama = this;
		m_enemyBullet3->m_position = m_enemyPosition;						//弾の位置を設定
		m_enemyBullet3->m_bulletLocalPosition = { 0.0f,140.0f,290.0f };		//ローカルポジション設定
		m_enemyBullet3->originRotation = m_enemyRotation;					//回転はエネミーと同じ

		//発射音の設定と再生
		m_battleShipGunSE = NewGO<SoundSource>(0);	//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
		m_battleShipGunSE->Init(enButtleShipGun);	//初期化
		m_battleShipGunSE->SetVolume(1.0f * m_game->SEvol);			//音量調整
		m_battleShipGunSE->Play(false);
	}
}

void Enemy_Far::ItemDrop()
{
	//死亡爆破エフェ
	EnemyDead();

	m_dropItem = NewGO<Drop_item>(1, "drop_item");
	m_dropItem->Drop_position = m_enemyPosition;
	m_dropItem->Drop_position.y += 50.0f;
	//エネミーがどの武器を持っていたか取得し、ドロップするアイテムを決める
	m_dropItem->drop_kinds = m_setWeapon;


	//コンテナにくっつける
	m_game->m_dropItemObject.push_back(m_dropItem);
	m_game->AddDefeatedEnemyNumber();


	m_player->killEnemy++;	//殺した数を増やす

	//画面を揺らす
	GameCamera* m_camera = FindGO<GameCamera>("gamecamera");
	m_camera->VibFlag = true;

	//コンボの処理
	Combo* m_combo = FindGO<Combo>("combo");
	m_combo->ComboUpdate();

	//リストから消す
	m_game->RemoveEnemyFarFromList(this);
}

void Enemy_Far::WeaponMove()
{
	//武器がエネミーと同じ動きをするようにする(親子関係)
	Quaternion originRotation = m_enemyRotation;			//回転はエネミーと同じ
	Vector3 localPosition = { 0.0f,120.0f,150.0f };			//親から見た位置の定義
	originRotation.Multiply(localPosition);					//何かしらの計算
	//最終的な武器の回転を決定
	m_weaponRotation = originRotation;

	m_weaponPosition = m_enemyPosition;		//まず,武器の位置をエネミーと同じに設定し
	m_weaponPosition += localPosition;		//それに親から見た位置を足して最終的な武器の位置を決定
}

void Enemy_Far::Damage()
{
	//m_battleShipAttack = FindGO<Battle_ship_attack>("buttle_ship_attack");
	/*Vector3 diff = m_battleShipAttack->firing_position - m_enemyPosition;
	if (diff.Length() <= 100.0f)
	{
		m_enemyHP -= 50.0f;
		DeleteGO(m_battleShipAttack);
	}*/
}

void Enemy_Far::Effect()
{
	//砂ぼこりエフェクトの初期化と再生
	sunabokoriEffect = NewGO<EffectEmitter>(0);
	sunabokoriEffect->Init(enSunabokori);
	sunabokoriEffect->SetScale({ 6.0f,6.0f,4.0f });
	sunabokoriEffect->SetRotation(m_enemyRotation);
	sunabokoriEffect->SetPosition({ m_enemyPosition.x,m_enemyPosition.y + 10.0f ,m_enemyPosition.z });
	sunabokoriEffect->Play();
}

void Enemy_Far::EnemyDead()
{
	//爆発エフェクトの設定と再生
	enemyDeadEffect = NewGO<EffectEmitter>(0);
	enemyDeadEffect->Init(enEnemyDead);
	enemyDeadEffect->SetScale({ 5.0f,5.0f,5.0f });
	enemyDeadEffect->SetRotation(m_enemyRotation);
	enemyDeadEffect->SetPosition({ m_enemyPosition.x,m_enemyPosition.y ,m_enemyPosition.z });
	enemyDeadEffect->Play();

	//爆発エフェクトの初期化と再生
	enemyDeadEffect2 = NewGO<EffectEmitter>(0);
	enemyDeadEffect2->Init(enTyakudan);
	enemyDeadEffect2->SetScale({ 15.7f,15.7f,15.7f });
	enemyDeadEffect2->SetPosition(m_enemyPosition);
	enemyDeadEffect2->Play();

	//爆発音の設定と再生
	m_enemyDeadSE = NewGO<SoundSource>(0);	//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
	m_enemyDeadSE->Init(enEnemyDeadSE);		//初期化
	m_enemyDeadSE->SetVolume(1.5f * m_game->SEvol);			//音量調整
	m_enemyDeadSE->Play(false);
}

void Enemy_Far::SE()
{

}

Vector3 Enemy_Far::RandPos()
{
	Vector3 m_pos;

	//ランダムにポジションを当てはめる
	m_pos.x = rand() % 4800 - 2400;
	m_pos.y = 0.0f;
	m_pos.z = rand() % 9000;

	return m_pos;
}

void Enemy_Far::Render(RenderContext& rc)
{
	//モデルの描画。
	m_enemyModel.Draw(rc);
	//生きている間だけ武器表示
	if (m_defeatState == true)
	{
		m_enemyWeaponModel.Draw(rc);
	}
}
