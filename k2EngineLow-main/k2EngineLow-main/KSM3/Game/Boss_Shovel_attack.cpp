#include "stdafx.h"
#include "Boss_Shovel_attack.h"
#include "Boss_Shovel.h"
#include "Boss.h"
#include "Player.h"
#include "Core_weapons.h"
#include "sound/SoundEngine.h"

Boss_Shovel_attack::Boss_Shovel_attack()
{
	m_boss = FindGO<Boss>("boss");
	m_player = FindGO<Player>("player");
	m_weapon = FindGO<Boss_Shovel>("boss_shovel");
	m_coreWeapon = FindGO<Core_weapons>("core_weapons");
	//’eƒ‚ƒfƒ‹B
	m_bulletModel.Init("Assets/modelData/V_P_bullet.tkm");

	//‰¹(‰¼)
	g_soundEngine->ResistWaveFileBank(2, "Assets/audio/Taihou_kouho1.wav");

	m_attackSE = NewGO<SoundSource>(0);
	m_attackSE->Init(2);
	m_attackSE->SetVolume(0.2f);
	m_attackSE->Play(false);
	SetUp();
}

Boss_Shovel_attack::~Boss_Shovel_attack()
{
	m_weapon->m_attackState = false;
}

void Boss_Shovel_attack::SetUp()
{
	m_bulletForward = m_weapon->m_forward;
	m_firePosition.y += 100.0f;
	m_firePosition.x -= 600.0f;
	m_bulletModel.SetRotation(m_boss->GetRotation());
	m_bulletModel.SetPosition(m_firePosition);
}

void Boss_Shovel_attack::Update()
{
	if (m_player->GetGameState() == MAIN_GAME_NUM)
	{
		Move();
		m_bulletModel.Update();
		if (m_firePosition.y <= 0.0f)
		{
			DeleteGO(this);
		}
	}
}

void Boss_Shovel_attack::Move()
{
	m_firePosition += m_bulletForward * move_speed;
	if (m_firePosition.y <= m_coreWeapon->GetPosition().y && fast_count == true)
	{
		m_firePosition.y += 10.0f;
	}
	else
	{
		fast_count = false;
		m_fallSpeed += 0.1f;
	}
	m_firePosition.y -= m_fallSpeed;
	move_speed -= 0.05f;

	m_bulletModel.SetPosition(m_firePosition);
}

void Boss_Shovel_attack::Render(RenderContext& rc)
{
	m_bulletModel.Draw(rc);
}