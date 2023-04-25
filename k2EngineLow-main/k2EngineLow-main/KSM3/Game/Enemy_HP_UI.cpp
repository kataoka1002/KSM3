#include "stdafx.h"
#include "Enemy_HP_UI.h"
#include "Enemy.h"
#include "Player.h"
#include "Battle_ship_attack.h"
#include "Game.h"
#include "GameCamera.h"


Enemy_HP_UI::Enemy_HP_UI()
{
	game = FindGO<Game>("game");
	enemy = FindGO<Enemy>("enemy");
	player = FindGO<Player>("player");
	b_s_attack = FindGO<Battle_ship_attack>("battle_ship_attack");
}

Enemy_HP_UI::~Enemy_HP_UI()
{
	
}

bool Enemy_HP_UI::Start()
{
	hp_render.Init("Assets/sprite/HP4.dds", 800.0f, 250.0f);
    hp_render.SetPosition({ 0.0f,0.0f,0.0f });
	hp_render.SetScale({ 1.0f,1.0f,1.0f });
	return true;
}

void Enemy_HP_UI::Update()
{	
	//XV‚·‚é
	hp_render.Update();

	Enemy_HP_Position();
}

void Enemy_HP_UI::Enemy_HP_Position()
{
	//“G‚ÌHP‚ÌˆÊ’u‚ð“G‚ÌˆÊ’u‚É‡‚í‚¹‚é
	hp_position = enemy->enemy_position;
	hp_position.y += 100.0f;
	hp_position.z += 100.0f;
	hp_render.SetPosition(hp_position);
	
}

void Enemy_HP_UI::Render(RenderContext& rc)
{
	if (player->game_state == 0) {
		hp_render.Draw(rc);
	}
}