#include "stdafx.h"
#include "Right_arm_weapons.h"
#include "Player.h"
#include "Enumeration.h"
#include "Battle_ship_attack.h"
#include "MachineGunAttack.h"
#include "GigatonCannonAttack.h"
#include "Customize_UI_ver2.h"
#include "PlayerUI.h"

Right_arm_weapons::Right_arm_weapons() 
{
	
}

Right_arm_weapons::~Right_arm_weapons() 
{
	
}

void Right_arm_weapons::SetUp()
{
	
	//UIの初期化
	m_playerUI->WeaponUISetUp(1);		
	

	//自分のポインタを教える
	m_playerUI->m_rightArm = (this);	


	//武器の初期化
	InitWeapon();

}

void Right_arm_weapons::InitWeapon()
{

	//付いている武器によって処理の変更
	switch (m_player->p_custom_point[0][0])
	{
	case 2:	//マシンガンの時

		//武器モデルの初期化
		m_weaponModel.Init("Assets/modelData/machine_gun_drop.tkm");


		//ローカルポジションの設定
		m_localPosition = { 60.0f,100.0f,0.0f };

		break;


	case 4:	//ギガトンキャノンの時

		//武器モデルの初期化
		m_weaponModel.Init("Assets/modelData/GIgaton_cannon_Right_arm.tkm");


		//ローカルポジションの設定
		m_localPosition = { 50.0f,100.0f,30.0f };

		break;


	case 6:	//戦艦砲の時

		//武器モデルの初期化
		m_weaponModel.Init("Assets/modelData/battleship_gun_right_arm.tkm");


		//ローカルポジションの設定
		m_localPosition = { 60.0f,80.0f,-10.0f };

		break;


	default:

		break;

	}


	//武器の細かい設定を行う	
	SetWeapon(m_player->p_custom_point[0][0]);

}

void Right_arm_weapons::Update() 
{

	//メインゲーム中
	if (m_player->game_state == 0) 
	{

		//動きの処理
		Move();


		//破壊されたときの処理
		DestroyEvent();


		//攻撃処理
		MakeBullet(m_player->p_custom_point[0][0]);


		//プレイヤーが死亡したら
		if (m_player->game_end_state == 1) 
		{

			//UIの中身を空にする
			m_playerUI->m_rightArm = nullptr;


			//自分自身の削除
			DeleteGO(this);

		}

	}

}

void Right_arm_weapons::SetBulletLocalPosition()
{

	//武器がマシンガンの場合
	if (m_player->p_custom_point[0][0] == 2)
	{

		//弾のローカルポジションの設定
		m_machineGunAttack->SetLocalPosition(Vector3{ 0.0f,-10.0f,170.0f });

	}
	//武器がギガトンキャノンの場合
	else if (m_player->p_custom_point[0][0] == 4)
	{

		//弾のローカルポジションの設定
		m_gigatonAttack->SetLocalPosition(Vector3{ 0.0f,0.0f,100.0f });

	}
	//武器が戦艦砲の場合
	else if (m_player->p_custom_point[0][0] == 6)
	{

		//弾のローカルポジションの設定
		m_battleShipAttack->SetLocalPosition(Vector3{ 0.0f,-30.0f,70.0f });

	}

}

void Right_arm_weapons::DestroyEvent()
{

	//武器のHPが0以下になると
	if (m_HP <= 0)
	{

		//プレイヤーの設定武器を空にする
		m_player->p_custom_point[0][0] = 0;


		//UIの設定武器を空にする
		m_customizeUI->Right_arm_weapon_set = false;


		//UIの設定していたポインタを空にする
		m_playerUI->m_rightArm = nullptr;

		
		//カスタマイズ画面の設定していたポインタを空にする
		m_customizeUI->m_rightArmWeapon = nullptr;


		//自分自身の削除
		DeleteGO(this);

	}

}

void Right_arm_weapons::Render(RenderContext& rc) 
{

	//プレイヤー死亡時のエフェクトを発生させたら
	if (m_player->m_deadBakuhaPlay == true)
	{
		return;
	}


	//武器モデルの描画
	m_weaponModel.Draw(rc);

}