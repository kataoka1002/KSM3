#include "stdafx.h"
#include "WeaponBase.h"
#include "Player.h"
#include "PlayerUI.h"
#include "Customize_UI_ver2.h"
#include "Battle_ship_attack.h"
#include "MachineGunAttack.h"
#include "GigatonCannonAttack.h"


bool WeaponBase::Start()
{

	//プレイヤーを見つける
	m_player = FindGO<Player>("player");


	//プレイヤーUIを見つける
	m_playerUI = FindGO<PlayerUI>("playerui");


	//カスタマイズUIを見つける
	m_customizeUI = FindGO<Customize_UI_ver2>("customize_ui_ver2");


	//全般のセットアップ
	SetUp();

	return true;

}

void WeaponBase::SetWeapon(int customPoint)
{

	//付いている武器によって処理を変更する
	switch (customPoint)
	{
	case 2:	//マシンガンの時


		//大きさの設定
		m_weaponModel.SetScale(MACHINEGUN_SCALE);


		//武器の体力の設定
		m_HPMax = MACHINEGUN_HP_MAX;

		break;


	case 4:	//ギガトンキャノンの時


		//大きさの設定
		m_weaponModel.SetScale(GIGATON_SCALE);


		//武器の体力の設定
		m_HPMax = GIGATON_HP_MAX;

		break;


	case 6:	//戦艦砲の時


		//大きさの設定
		m_weaponModel.SetScale(BATTLESHIP_SCALE);


		//武器の体力の設定
		m_HPMax = BATTLESHIP_HP_MAX;

		break;


	default:

		break;

	}


	//モデルの更新
	m_weaponModel.Update();


	//武器の種類を覚えさせる
	m_setWeapon = customPoint;


	//武器の体力を覚えさせる
	m_HP = m_HPMax;

}

void WeaponBase::Move()
{

	//ローカルポジションを教える
	Vector3 lp = m_localPosition;


	//プレイヤーの回転量を教える
	Quaternion originRotation = m_player->player_rotation;


	//プレイヤーのポジションを教える
	m_position = m_player->player_position;


	//乗算
	originRotation.Multiply(lp);


	//ポジションにローカルポジションを足す
	m_position += lp;


	//最終的な回転量を教える
	m_rotation = originRotation;


	//更新
	m_weaponModel.SetPosition(m_position);
	m_weaponModel.SetRotation(m_rotation);
	m_weaponModel.Update();

}

void WeaponBase::MakeBullet(int customPoint)
{
	
	//L1ボタンが押されたら
	if (g_pad[0]->IsPress(enButtonLB1))
	{

		//武器がマシンガンの場合
		if (customPoint == 2 && m_firingCount % 5 == 0)
		{

			//弾にポジションと回転を教えて生成する
			m_machineGunAttack = NewGO<MachineGunAttack>(1, "machinegunattack");
			m_machineGunAttack->SetRotation(m_rotation);
			m_machineGunAttack->SetPosition(m_position);

		}
		//武器がギガトンキャノンの場合
		else if (customPoint == 4 && m_firingCount % 180 == 0)
		{

			//弾にポジションと回転を教えて生成する
			m_gigatonAttack = NewGO<GigatonCannonAttack>(1, "gigatoncannonattack");
			m_gigatonAttack->SetRotation(m_rotation);
			m_gigatonAttack->SetPosition(m_position);

		}
		//武器が戦艦砲の場合
		else if (customPoint == 6 && m_firingCount % 180 == 0)
		{

			//弾にポジションと回転を教えて生成する
			m_battleShipAttack = NewGO<Battle_ship_attack>(1, "battle_ship_attack");
			m_battleShipAttack->SetRotation(m_rotation);
			m_battleShipAttack->SetPosition(m_position);

		}


		//弾のローカルポジションの設定
		SetBulletLocalPosition();


		//カウントアップ
		m_firingCount++;

	}
	//L1ボタンが押されてないとき
	else
	{

		//カウントリセット
		m_firingCount = 0;

	}

}
