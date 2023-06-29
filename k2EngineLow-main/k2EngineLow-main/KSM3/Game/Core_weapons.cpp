#include "stdafx.h"
#include "Core_weapons.h"
#include "Player.h"
#include "Core_weapons_attack.h"

Core_weapons::Core_weapons() 
{
	
}

Core_weapons::~Core_weapons() 
{
	DeleteGO(m_coreWeaponAttack);
}

bool Core_weapons::Start()
{
	//プレイヤーを探す
	m_player = FindGO<Player>("player");

	//武器のセット
	WeaponSet();

	return true;
}

void Core_weapons::WeaponSet() 
{
	//武器の種類によってモデルを変える
	if (m_setWeapon == 1) 
	{
		m_coreWeaponModel.Init("Assets/modelData/Giga_Plasma.tkm");
		m_coreWeaponModel.SetScale(m_scale);
	}
	else if (m_setWeapon == 2) 
	{
		m_coreWeaponModel.Init("Assets/modelData/Versatile_Perforator.tkm");
	}

	//更新
	m_coreWeaponModel.Update();
}

void Core_weapons::Update()
{

	//移動の処理
	Move();


	//メインゲーム中なら
	if (m_player->GetGameState() == MAIN_GAME_NUM) 
	{
		
		//弾の生成
		MakeBullet();


		//ゲームが終了したら
		if (m_player->GetGameEndState() == 1) 
		{
			DeleteGO(this);
		}

	}

}

void Core_weapons::MakeBullet()
{
	//L1を押すと
	if (g_pad[0]->IsPress(enButtonLB1))
	{

		if (m_setWeapon == 1 && m_firingCount > 60)
		{

		}
		else if (m_setWeapon == 2 && m_firingCount > 5)
		{
			//弾を生成
			m_coreWeaponAttack = NewGO<Core_weapons_attack>(1, "core_weapons_attack");
		}

		//カウントアップ
		m_firingCount++;
	}
	else
	{
		//カウントリセット
		m_firingCount = 0;
	}
}

void Core_weapons::Move() 
{
	Quaternion originRotation = m_player->GetPlayerRotation();
	m_position = m_player->GetPlayerPosition();
	Vector3 lp = m_localPosition;
	originRotation.Multiply(lp);
	m_position += lp;
	m_rotation = originRotation;
	m_coreWeaponModel.SetPosition(m_position);
	m_coreWeaponModel.SetRotation(m_rotation);
	m_coreWeaponModel.Update();
}

void Core_weapons::Render(RenderContext& rc) 
{

	if (m_player->IsDeadBakuhaPlay() == true)
	{
		return;
	}

	m_coreWeaponModel.Draw(rc);
}