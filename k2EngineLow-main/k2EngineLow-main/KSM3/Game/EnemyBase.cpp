#include "stdafx.h"
#include "EnemyBase.h"
#include "Game.h"
#include "Player.h"
#include "Drop_item.h"
#include "GameCamera.h"
#include "Combo.h"
#include "Enemy_HP_UI.h"


bool EnemyBase::Start()
{

	//ゲームを探す
	m_game = FindGO<Game>("game");


	//プレイヤーを探す
	m_player = FindGO<Player>("player");


	//HPのUI作成
	m_HPUI = NewGO<Enemy_HP_UI>(1, "enemy_hp_ui");


	//足音の生成(流し続ける音源なのでインスタンスを保持させる)
	m_asiotoSE = NewGO<SoundSource>(0);
	m_asiotoSE->Init(enRunning);					//初期化
	m_asiotoSE->SetVolume(0.8f * m_game->GetBGMVol());	//音量調整
	m_asiotoSE->Play(true);							//再生
	m_asiotoSE->Stop();


	//エネミー生成エフェクトの再生
	PlayEffect(enEnemyHassei, m_enemyPosition, m_enemyRotation, { 10.0f,10.0f,10.0f });


	//パス移動ポイントの作成
	MakePoint();


	//武器生成
	WeaponSetUp();


	//ゲーム全般の設定
	GameSetUp();


	//エネミーのモデル関係の初期化
	InitEnemyModel();


	return true;

}

void EnemyBase::WeaponSetUp()
{

	//取り付ける武器の変更
	if (m_setWeapon == 1)		//ギガプラズマ
	{

	}
	else if (m_setWeapon == 2)		//マシンガン
	{

		//武器モデル設定
		m_enemyWeaponModel.Init("Assets/modelData/machine_gun_enemy.tkm");
		m_enemyWeaponModel.SetScale(2.0f);
		m_enemyWeaponModel.SetPosition(m_weaponPosition);
		m_enemyWeaponModel.SetRotation(m_weaponRotation);
		m_enemyWeaponModel.Update();

	}
	else if (m_setWeapon == 3)		 //ヘルファイヤ
	{

	}
	else if (m_setWeapon == 4)		//ギガトンキャノン
	{

		//武器モデルの設定
		m_enemyWeaponModel.Init("Assets/modelData/GIgaton_cannon.tkm");
		m_enemyWeaponModel.SetScale(1.3f);
		m_enemyWeaponModel.SetPosition(m_weaponPosition);
		m_enemyWeaponModel.SetRotation(m_weaponRotation);
		m_enemyWeaponModel.Update();

	}
	else if (m_setWeapon == 5)		//ミサイル
	{

	}
	else if (m_setWeapon == 6)		//戦艦砲
	{

		//武器モデルの設定
		m_enemyWeaponModel.Init("Assets/modelData/battleship_gun_enemy.tkm");
		m_enemyWeaponModel.SetScale({ 3.0f ,5.0f,3.0f });
		m_enemyWeaponModel.SetPosition(m_weaponPosition);
		m_enemyWeaponModel.SetRotation(m_weaponRotation);
		m_enemyWeaponModel.Update();

	}

}

void EnemyBase::Update()
{

}

void EnemyBase::NormalAction(float dist)
{

	//プレイヤーが死亡したとき用
	m_asiotoSE->SetVolume(0.8f * m_game->GetSEVol());


	//エネミーとプレイヤーの距離計算
	CalcDistance(dist);


	//武器の移動回転
	WeaponMove();


	//パス移動ポイントにロックオンしてるなら
	if (m_lockOn == true)
	{

		//パス移動
		PassMove();

	}
	//パス移動ポイントにロックオンしてないなら
	else if (m_lockOn == false)
	{

		//索敵
		PlayerSearch();


		//移動
		Move();


		//攻撃
		Attack();

	}


	//エネミー更新
	m_enemyModel.SetPosition(m_enemyPosition);
	m_enemyModel.SetRotation(m_enemyRotation);
	m_enemyModel.Update();

}

void EnemyBase::MakePoint()
{

	//ポイントの作成
	m_pointList.push_back({ RandPos(),1 });		//一番目のポイント
	m_pointList.push_back({ RandPos(),2 });		//二番目のポイント
	m_pointList.push_back({ RandPos(),3 });		//三番目のポイント
	m_pointList.push_back({ RandPos(),4 });		//四番目のポイント


	//一番目のポイントを入れる
	m_point = &m_pointList[0];

}

void EnemyBase::CalcDistance(float dist)
{

	//エネミーからプレイヤーへのベクトル
	m_toPlayer = m_player->player_position - m_enemyPosition;


	//プレイヤーとの距離を計算する
	m_distToPlayer = m_toPlayer.Length();


	//プレイヤーに向かって伸びるベクトルを正規化する
	m_toPlayerDir = m_toPlayer;
	m_toPlayerDir.Normalize();


	//プレイヤーまでの距離が遠すぎるとき
	if (m_distToPlayer > dist)
	{

		//パスポイントにロックオン
		m_lockOn = true;

	}
	else
	{

		//パスポイントロックオン解除
		m_lockOn = false;

	}

}

void EnemyBase::CalcSpeed(float speed, int dirState)
{

	if (dirState == 0)	//プレイヤー向き
	{

		//前方向の設定
		m_enemyForward = m_toPlayerDir;


		//移動速度を設定
		m_enemyMoveSpeed = m_enemyForward * speed;

	}
	else if (dirState == 1)	//プレイヤーと反対向き
	{

		//前方向の設定
		m_enemyForward = m_toPlayerDir * -1.0;		

	}
	else if (dirState == 2)	//横向き1
	{

		//外積からエネミーの横方向を取得
		m_enemyForward = Cross(m_Up, m_toPlayerDir);	
		
		
		//移動速度の設定
		m_enemyMoveSpeed = m_enemyForward * speed;

	}
	else if (dirState == 3)	//横向き2
	{

		//外積からエネミーの横方向を取得
		m_enemyForward = Cross(m_Up, m_toPlayerDir);	
		
		
		//移動速度の設定
		m_enemyMoveSpeed = m_enemyForward * speed;

	}

}

void EnemyBase::PassMove()
{

	//自分のポジションから目標とするポイントのベクトル
	Vector3 m_toPoint = m_point->m_position - m_enemyPosition;


	//ポイントまでの距離を計算
	float m_diffToPoint = m_toPoint.Length();


	//ポイントまでの方向の計算
	Vector3 m_toPointDir = m_toPoint;
	m_toPointDir.Normalize();


	//前方向の設定
	m_enemyForward = m_toPointDir;


	//距離が一定以内なら
	if (m_diffToPoint < 20.0f)
	{

		//今目的地としているポイントが配列の最後の要素なら
		if (m_point->m_num == m_pointList.size()) 
		{

			//一番最初のポイントを目的地とする
			m_point = &m_pointList[0];

		}
		else 
		{

			//配列の次の要素のポイントを目的地とする
			m_point = &m_pointList[m_point->m_num];

		}

	}


	//移動させる。
	m_enemyMoveSpeed = m_enemyForward * 200.0f;
	m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());


	//エネミーの前方向を使って、回転クォータニオンを計算する。
	m_enemyRotation.SetRotationY(atan2(m_enemyForward.x, m_enemyForward.z));

}

void EnemyBase::Move()
{

}

void EnemyBase::PlayerSearch()
{
	
}

void EnemyBase::ExecuteOnEnemyDefeated()
{

	//死亡爆破エフェ
	EnemyDead();


	//アイテムドロップの処理
	ItemDrop();


	//死んだエネミーの数を増やす
	m_game->AddDefeatedEnemyNumber();


	//殺した数を増やす
	m_player->killEnemy++;	


	//画面を揺らす
	GameCamera* m_camera = FindGO<GameCamera>("gamecamera");
	m_camera->VibFlag = true;


	//コンボの処理
	Combo* m_combo = FindGO<Combo>("combo");
	m_combo->ComboUpdate();

}

void EnemyBase::ItemDrop()
{

	//ドロップアイテムの生成
	m_dropItem = NewGO<Drop_item>(1, "drop_item");


	//ドロップアイテムの場所の決定
	m_dropItem->Drop_position = m_enemyPosition;
	m_dropItem->Drop_position.y += 50.0f;


	//エネミーがどの武器を持っていたか取得
	m_dropItem->drop_kinds = m_setWeapon;


	//作成したアイテムをコンテナにくっつける
	m_game->GetDropItemObject().push_back(m_dropItem);

}

void EnemyBase::WeaponMove()
{

	//武器がエネミーと同じ動きをするようにする(親子関係)
	Quaternion originRotation = m_enemyRotation;	//回転はエネミーと同じ
	Vector3 localPos = m_weaponLocalPos;			//親から見た位置の定義
	originRotation.Multiply(localPos);				//掛け算


	//最終的な武器の回転を決定
	m_weaponRotation = originRotation;


	//武器の位置をエネミーと同じに設定
	m_weaponPosition = m_enemyPosition;		
	
	
	//親から見た位置を足して最終的な武器の位置を決定
	m_weaponPosition += localPos;


	//更新
	m_enemyWeaponModel.SetPosition(m_weaponPosition);
	m_enemyWeaponModel.SetRotation(m_weaponRotation);
	m_enemyWeaponModel.Update();

}

void EnemyBase::Attack()
{

}

void EnemyBase::Fire(int m_weaponNum)
{

}

void EnemyBase::DustEffect()
{

	//砂ぼこりの間隔カウント
	m_sunaHassei++;


	//カウントが一定以上になると
	if (m_sunaHassei >= 10)
	{

		//砂ぼこりエフェクトの再生
		PlayEffect(enSunabokori, { m_enemyPosition.x,m_enemyPosition.y + 10.0f ,m_enemyPosition.z }, m_enemyRotation, { 4.0f,4.0f,4.0f });


		//カウントリセット
		m_sunaHassei = 0;

	}

}

void EnemyBase::AsiotoSEManage(bool play)
{

	//引数を変数に代入
	m_asiotoPlay = play;


	//フラグが立った＆足音が再生されてないとき
	if (m_asiotoPlay == true && m_asiotoSE->IsPlaying() != true)
	{

		//足音再生
		m_asiotoSE->Play(true);

	}
	//フラグが下げられたら
	else if(m_asiotoPlay == false)
	{

		//足音停止
		m_asiotoSE->Stop();

	}

}

void EnemyBase::EnemyDead()
{

}

void EnemyBase::PlayEffect(EffectName name,Vector3 pos,Quaternion rot,Vector3 scale)
{

	//エフェクトの再生
	EffectEmitter* m_effect = NewGO<EffectEmitter>(0);
	m_effect->Init(name);
	m_effect->SetPosition(pos);
	m_effect->SetRotation(rot);
	m_effect->SetScale(scale);
	m_effect->Play();

}

Vector3 EnemyBase::RandPos()
{

	Vector3 m_pos;

	//ランダムにポジションを当てはめる
	m_pos.x = rand() % 4800 - 2400;
	m_pos.y = 0.0f;
	m_pos.z = rand() % 9000;

	return m_pos;

}

void EnemyBase::Render(RenderContext& rc)
{

}

