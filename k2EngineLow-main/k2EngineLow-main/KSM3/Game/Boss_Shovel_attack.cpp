#include "stdafx.h"
#include "Boss_Shovel_attack.h"
#include "Boss_Shovel.h"
#include "Boss.h"
#include "Player.h"
#include "Core_weapons.h"
#include "sound/SoundEngine.h"

Boss_Shovel_attack::Boss_Shovel_attack()
{
	b_a_boss = FindGO<Boss>("boss");
	m_player = FindGO<Player>("player");
	b_a_weapons = FindGO<Boss_Shovel>("boss_shovel");
	b_a_core_weapons = FindGO<Core_weapons>("core_weapons");
	//’eƒ‚ƒfƒ‹B
	m_bulletModel.Init("Assets/modelData/V_P_bullet.tkm");

	//‰¹(‰¼)
	g_soundEngine->ResistWaveFileBank(2, "Assets/audio/Taihou_kouho1.wav");

	b_attack_SE = NewGO<SoundSource>(0);
	b_attack_SE->Init(2);
	b_attack_SE->SetVolume(0.2f);
	b_attack_SE->Play(false);
	SetUp();
}

Boss_Shovel_attack::~Boss_Shovel_attack()
{
	b_a_weapons->m_attackState = false;
}

void Boss_Shovel_attack::SetUp()
{
	m_bulletForward = b_a_weapons->m_forward;
	m_firePosition.y += 100.0f;
	m_firePosition.x -= 600.0f;
	m_bulletModel.SetRotation(b_a_boss->GetRotation());
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
	if (m_firePosition.y <= b_a_core_weapons->GetPosition().y && fast_count == true)
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