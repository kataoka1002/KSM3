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
	b_a_player = FindGO<Player>("player");
	b_a_weapons = FindGO<Boss_Shovel>("boss_shovel");
	b_a_core_weapons = FindGO<Core_weapons>("core_weapons");
	//’eƒ‚ƒfƒ‹B
	b_a_Bullet.Init("Assets/modelData/V_P_bullet.tkm");

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
	b_a_Bullet_Fowrad = b_a_weapons->m_forward;
	firing_position.y += 100.0f;
	firing_position.x -= 600.0f;
	b_a_Bullet.SetRotation(b_a_boss->GetRotation());
	b_a_Bullet.SetPosition(firing_position);
}

void Boss_Shovel_attack::Update()
{
	if (b_a_player->GetGameState() == MAIN_GAME_NUM)
	{
		Move();
		b_a_Bullet.Update();
		if (firing_position.y <= 0.0f)
		{
			DeleteGO(this);
		}
	}
}

void Boss_Shovel_attack::Move()
{
	firing_position += b_a_Bullet_Fowrad * move_speed;
	if (firing_position.y <= b_a_core_weapons->GetPosition().y && fast_count == true)
	{
		firing_position.y += 10.0f;
	}
	else
	{
		fast_count = false;
		fall_speed += 0.1f;
	}
	firing_position.y -= fall_speed;
	move_speed -= 0.05f;

	b_a_Bullet.SetPosition(firing_position);
}

void Boss_Shovel_attack::Render(RenderContext& rc)
{
	b_a_Bullet.Draw(rc);
}