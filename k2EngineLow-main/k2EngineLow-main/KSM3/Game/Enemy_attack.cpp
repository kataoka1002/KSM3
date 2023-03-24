#include "stdafx.h"
#include "Enemy_attack.h"
#include "Core_weapons.h"
#include "Enemy_weapons.h"
#include "Enemy.h"
#include "Player.h"
#include "sound/SoundEngine.h"

Enemy_attack::Enemy_attack() {
	e_a_enemy = FindGO<Enemy>("enemy");
	e_a_player = FindGO<Player>("player");
	e_a_enemy_weapons = FindGO<Enemy_weapons>("enemy_weapons");
	e_a_core_weapons = FindGO<Core_weapons>("core_weapons");
	e_a_Bullet.Init("Assets/modelData/V_P_bullet.tkm");
	switch (e_a_enemy_weapons->set_weapons)
	{
	case 1:
		g_soundEngine->ResistWaveFileBank(2, "Assets/audio/Taihou_kouho1.wav");
		break;
	case 2:
		g_soundEngine->ResistWaveFileBank(2, "Assets/audio/Taihou_kouho1.wav");
		break;
	default:
		break;
	}
	
	e_atack_SE = NewGO<SoundSource>(0);

	e_atack_SE->Init(2);

	e_atack_SE->SetVolume(0.2f);

	e_atack_SE->Play(false);
	
	Setup();
}

void Enemy_attack::Setup() {
	e_a_Bullet_Fowrad = e_a_enemy->enemy_forward;
	firing_position.y += 10.0f;
	e_a_Bullet.SetRotation(e_a_enemy->enemy_rotation);
	e_a_Bullet.SetPosition(firing_position);
}


Enemy_attack::~Enemy_attack() {
	e_a_enemy_weapons->atack_state = false;
}

void Enemy_attack::Update() {
	if (e_a_player->game_state == 0) {
		Move();
		e_a_Bullet.Update();
		if (firing_position.y <= 0.0f) {
			DeleteGO(this);
		}
	}
}

void Enemy_attack::Move() {
	firing_position += e_a_Bullet_Fowrad * move_speed;
	if (firing_position.y <= e_a_core_weapons->cw_position.y&&fast_count==true) {
		firing_position.y += 1.0f;
	}
	else {
		fast_count = false;
		fall_speed += 0.1f;
	}
	firing_position.y -= fall_speed;
	move_speed -= 0.05f;
	
	e_a_Bullet.SetPosition(firing_position);
}

void Enemy_attack::Render(RenderContext& rc) {
	e_a_Bullet.Draw(rc);
}