#include "stdafx.h"
#include "Shoulder_weapons.h"
#include "Player.h"
#include "Battle_ship_attack.h"
#include "MachineGunAttack.h"
#include "GigatonCannonAttack.h"
#include "Customize_UI_ver2.h"
#include "PlayerUI.h"

Shoulder_weapons::Shoulder_weapons() 
{

}

Shoulder_weapons::~Shoulder_weapons() 
{
	
}

void Shoulder_weapons::SetUp()
{

	//UIの初期化
	m_playerUI->WeaponUISetUp(5);


	//自分のポインタを教える
	m_playerUI->SetShoulder(this);


	//武器の初期化
	InitWeapon();

}

void Shoulder_weapons::InitWeapon()
{

	//付いている武器によって処理の変更
	switch (m_player->GetCustomPoint(SHOULDER))
	{
	case MACHINEGUN_NUM:	//マシンガンの時

		//メモリの確保
		m_machineGunWeapon2 = std::make_unique<ModelRender>();


		//武器モデルの初期化
		m_weaponModel->Init("Assets/modelData/machine_gun_drop.tkm");


		//ローカルポジションの設定
		m_localPosition = { 35.0f,120.0f,0.0f };


		//マシンガン用のモデルの初期化
		m_machineGunWeapon2->Init("Assets/modelData/machine_gun_drop.tkm");


		//ローカルポジションの設定
		m_localPosition2 = { -35.0f,120.0f,0.0f };


		//2個目のマシンガンの大きさ設定
		m_machineGunWeapon2->SetScale(MACHINEGUN_SCALE);


		break;


	case GIGATONCANNON_NUM:	//ギガトンキャノンの時

		//武器モデルの初期化
		m_weaponModel->Init("Assets/modelData/GIgaton_shoulder.tkm");


		//ローカルポジションの設定
		m_localPosition = { 0.0f,120.0f,0.0f };

		break;


	case BATTLESHIPGUN_NUM:	//戦艦砲の時

		//武器モデルの初期化
		m_weaponModel->Init("Assets/modelData/battleship_gun_shoulder.tkm");


		//ローカルポジションの設定
		m_localPosition = { 0.0f,119.0f,0.0f };

		break;


	default:

		break;

	}


	//武器の細かい設定を行う	
	SetWeapon(m_player->GetCustomPoint(SHOULDER));

}

void Shoulder_weapons::Update() 
{

	//メインゲーム中
	if (m_player->GetGameState() == MAIN_GAME_NUM)
	{

		//動きの処理
		Move();


		//マシンガン用モデルの動きの処理
		Move2();


		//破壊されたときの処理
		DestroyEvent();


		//攻撃処理(弾の1個め)
		MakeBullet(m_player->GetCustomPoint(SHOULDER));


		//攻撃処理(弾の2個め)
		MakeBullet2(m_player->GetCustomPoint(SHOULDER));


		//プレイヤーが死亡したら
		if (m_player->GetGameEndState() == 1)
		{

			//UIの中身を空にする
			m_playerUI->SetShoulder(nullptr);


			//自分自身の削除
			DeleteGO(this);

		}

	}

}

void Shoulder_weapons::Move2()
{

	//武器がマシンガンなら
	if (m_player->GetCustomPoint(SHOULDER) == MACHINEGUN_NUM)
	{

		//ローカルポジションを教える
		Vector3 lp = m_localPosition2;


		//プレイヤーの回転量を教える
		Quaternion originRotation = m_player->GetPlayerRotation();


		//プレイヤーのポジションを教える
		m_position2 = m_player->GetPlayerPosition();


		//乗算
		originRotation.Multiply(lp);


		//ポジションにローカルポジションを足す
		m_position2 += lp;


		//最終的な回転量を教える
		m_rotation2 = originRotation;


		//更新
		m_machineGunWeapon2->SetPosition(m_position2);
		m_machineGunWeapon2->SetRotation(m_rotation2);
		m_machineGunWeapon2->Update();

	}

}

void Shoulder_weapons::MakeBullet2(int customPoint)
{

	//L1ボタンが押されたら
	if (g_pad[0]->IsPress(enButtonLB1))
	{
		//武器がマシンガンの場合
		if (m_player->GetCustomPoint(SHOULDER) == MACHINEGUN_NUM && m_firingCount2 % 5 == 0)
		{

			//弾2にポジションと回転を教えて生成する
			m_machineGunAttack2 = NewGO<MachineGunAttack>(1, "machinegunattack");
			m_machineGunAttack2->SetRotation(m_rotation);
			m_machineGunAttack2->SetPosition(m_position2);
			m_machineGunAttack2->SetLocalPosition(Vector3{ 0.0f,-10.0f,170.0f });

		}
		//武器がギガトンキャノンの場合
		else if (m_player->GetCustomPoint(SHOULDER) == GIGATONCANNON_NUM && m_firingCount2 % 180 == 0)
		{

			//弾2にポジションと回転を教えて生成する
			m_gigatonAttack2 = NewGO<GigatonCannonAttack>(1, "gigatoncannonattack");
			m_gigatonAttack2->SetRotation(m_rotation);
			m_gigatonAttack2->SetPosition(m_position);
			m_gigatonAttack2->SetLocalPosition(Vector3{ -40.0f,0.0f,100.0f });

		}
		//武器が戦艦砲の場合
		else if (m_player->GetCustomPoint(SHOULDER) == BATTLESHIPGUN_NUM && m_firingCount2 % 180 == 0)
		{

			//弾2にポジションと回転を教えて生成する
			m_battleShipAttack2 = NewGO<Battle_ship_attack>(1, "battle_ship_attack");
			m_battleShipAttack2->SetRotation(m_rotation);
			m_battleShipAttack2->SetPosition(m_position);
			m_battleShipAttack2->SetLocalPosition(Vector3{ -40.0f,-40.0f,70.0f });

		}


		//カウントアップ
		m_firingCount2++;

	}
	//L1ボタンが押されてないとき
	else
	{
		//カウントリセット
		m_firingCount2 = 0;

	}

}

void Shoulder_weapons::SetBulletLocalPosition()
{

	//武器がマシンガンの場合
	if (m_player->GetCustomPoint(SHOULDER) == MACHINEGUN_NUM)
	{

		//弾1のローカルポジションの設定
		m_machineGunAttack->SetLocalPosition(Vector3{ 0.0f,-10.0f,170.0f });

	}
	//武器がギガトンキャノンの場合
	else if (m_player->GetCustomPoint(SHOULDER) == GIGATONCANNON_NUM)
	{

		//弾1のローカルポジションの設定
		m_gigatonAttack->SetLocalPosition(Vector3{ 40.0f,0.0f,100.0f });

	}
	//武器が戦艦砲の場合
	else if (m_player->GetCustomPoint(SHOULDER) == BATTLESHIPGUN_NUM)
	{

		//弾1のローカルポジションの設定
		m_battleShipAttack->SetLocalPosition(Vector3{ 40.0f,-40.0f,70.0f });

	}

}

void Shoulder_weapons::DestroyEvent()
{

	//HPが0以下になると消える
	if (m_HP <= 0)
	{

		//プレイヤーの設定武器を空にする
		m_player->SetCustomPoint(SHOULDER, NO_WEAPON_NUM);


		//UIの設定武器を空にする
		m_customizeUI->SetIsSetShoulder(false);


		//UIの設定していたポインタを空にする
		m_customizeUI->SetShoulderWeapon(nullptr);


		//カスタマイズ画面の設定していたポインタを空にする
		m_playerUI->SetShoulder(nullptr);


		//自分自身の削除
		DeleteGO(this);

	}

}

void Shoulder_weapons::Render(RenderContext& rc) 
{

	//プレイヤー死亡時のエフェクトを発生させたら
	if (m_player->IsDeadBakuhaPlay() == true)
	{
		return;
	}


	//武器モデルの描画
	m_weaponModel->Draw(rc);


	//付けている武器がマシンガンなら
	if (m_player->GetCustomPoint(SHOULDER) == MACHINEGUN_NUM)
	{

		//2個目の武器モデルの描画
		m_machineGunWeapon2->Draw(rc);

	}

}
