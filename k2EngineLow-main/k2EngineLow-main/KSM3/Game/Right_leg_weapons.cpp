#include "stdafx.h"
#include "Right_leg_weapons.h"
#include "Player.h"
#include "Enumeration.h"
#include "Battle_ship_attack.h"
#include "MachineGunAttack.h"
#include "GigatonCannonAttack.h"
#include "Customize_UI_ver2.h"
#include "PlayerUI.h"

Right_leg_weapons::Right_leg_weapons() 
{

}

Right_leg_weapons::~Right_leg_weapons() 
{
	
}

void Right_leg_weapons::SetUp()
{
	
	//UIの初期化
	m_playerUI->WeaponUISetUp(2);		
	

	//自分のポインタを教える
	m_playerUI->SetRightLeg(this);	


	//武器の初期化
	InitWeapon();

}

void Right_leg_weapons::InitWeapon()
{

	//付いている武器によって処理の変更
	switch (m_player->GetCustomPoint(RIGHT_LEG))
	{
	case MACHINEGUN_NUM:	//マシンガンの時

		//武器モデルの初期化
		m_weaponModel->Init("Assets/modelData/machine_gun_drop.tkm");


		//ローカルポジションの設定
		m_localPosition = { 90.0f,30.0f,0.0f };

		break;


	case GIGATONCANNON_NUM:	//ギガトンキャノンの時

		//武器モデルの初期化
		m_weaponModel->Init("Assets/modelData/GIgaton_cannon.tkm");


		//ローカルポジションの設定
		m_localPosition = { 55.0f,40.0f,27.0f };

		break;


	case BATTLESHIPGUN_NUM:	//戦艦砲の時

		//武器モデルの初期化
		m_weaponModel->Init("Assets/modelData/battleship_gun_Drop.tkm");


		//ローカルポジションの設定
		m_localPosition = { 60.0f,40.0f,40.0f };

		break;


	default:

		break;

	}


	//武器の細かい設定を行う	
	SetWeapon(m_player->GetCustomPoint(RIGHT_LEG));


}

void Right_leg_weapons::Update() 
{

	//メインゲーム中
	if (m_player->GetGameState() == MAIN_GAME_NUM)
	{

		//動きの処理
		Move();


		//破壊されたときの処理
		DestroyEvent();


		//攻撃処理
		MakeBullet(m_player->GetCustomPoint(RIGHT_LEG));


		//プレイヤーが死亡したら
		if (m_player->GetGameEndState() == 1)
		{

			//UIの中身を空にする
			m_playerUI->SetRightLeg(nullptr);


			//自分自身の削除
			DeleteGO(this);

		}

	}

}

void Right_leg_weapons::SetBulletLocalPosition()
{


	//武器がマシンガンの場合
	if (m_player->GetCustomPoint(RIGHT_LEG) == MACHINEGUN_NUM)
	{

		//弾のローカルポジションの設定
		m_machineGunAttack->SetLocalPosition(Vector3{ 0.0f,-10.0f,170.0f });

	}
	//武器がギガトンキャノンの場合
	else if (m_player->GetCustomPoint(RIGHT_LEG) == GIGATONCANNON_NUM)
	{

		//弾のローカルポジションの設定
		m_gigatonAttack->SetLocalPosition(Vector3{ 0.0f,0.0f,100.0f });

	}
	//武器が戦艦砲の場合
	else if (m_player->GetCustomPoint(RIGHT_LEG) == BATTLESHIPGUN_NUM)
	{

		//弾のローカルポジションの設定
		m_battleShipAttack->SetLocalPosition(Vector3{ 0.0f,-37.0f,70.0f });

	}

}

void Right_leg_weapons::DestroyEvent()
{
	//HPが0以下になると消える
	if (m_HP <= 0)
	{

		//プレイヤーの設定武器を空にする
		m_player->SetCustomPoint(RIGHT_LEG, NO_WEAPON_NUM);
		
		
		//UIの設定武器を空にする
		m_customizeUI->Right_leg_weapon_set = false;
		
		
		//UIの設定していたポインタを空にする
		m_customizeUI->m_rightLegWeapon = nullptr;


		//UIの中身を空にする
		m_playerUI->SetRightLeg(nullptr);


		//自分自身の削除
		DeleteGO(this);

	}

}

void Right_leg_weapons::Render(RenderContext& rc) 
{

	//プレイヤー死亡時のエフェクトを発生させたら
	if (m_player->IsDeadBakuhaPlay() == true)
	{
		return;
	}


	//武器モデルの描画
	m_weaponModel->Draw(rc);

}