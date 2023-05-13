#include "stdafx.h"
#include "Game_UI.h"
#include "Enemy.h"
#include "Player.h"
#include <time.h>
#include <stdlib.h>
#include"Core_weapons.h"
#include"Game.h"

Game_UI::Game_UI()
{
	enemy = FindGO<Enemy>("enemy");
	u_player = FindGO<Player>("player");
	core_weapons = FindGO<Core_weapons>("core_weapons");
}

Game_UI::~Game_UI()
{

}

bool Game_UI::Start()
{
	//HPÉQÅ[ÉW
	for (int i = 0; i < 5; i++) {
		player_hp_render[0].Init("Assets/sprite/HP_Test.dds", 1000.0f, 400.0f);
		player_hp_render[1].Init("Assets/sprite/HP_2.dds", 1000.0f, 400.0f);
		player_hp_render[i].SetPosition({-400.0f, -400.0f, 0.0f});
	}

	//É{ÉXHP
	for (int B = 0; B < 5; B++) {
		boss_hp_render[0].Init("Assets/sprite/HP_Test.dds", 900.0f, 400.0f);
		boss_hp_render[B].SetPosition({ 0.0f, 400.0f, 0.0f });
	}

	//êßå¿éûä‘
	for (int t = 0; t < 5; t++) {
		Time_render[0].Init("Assets/sprite/HP_Test.dds", 500.0f, 400.0f);
		Time_render[1].Init("Assets/sprite/HP_Test.dds", 500.0f, 400.0f);
		Time_render[t].SetPosition({ -610.0f,430.0f,0.0f });
	}
	//ìGÇì|ÇµÇΩêî
	/*for (int E = 0; E < 11; E++) {
		Enemy_count_render[0].Init("Assets/sprite/enemy_count.dds", 700.0f, 500.0f);
		Enemy_count_render[1].Init("Assets/sprite/0.dds", 700.0f, 500.0f);
		Enemy_count_render[2].Init("Assets/sprite/1.dds", 700.0f, 500.0f);
		Enemy_count_render[E].SetPosition({635.0f,400.0f,0.0f});
	}*/
	//ÉRÉA
	for (int Pc = 0; Pc < 5; Pc++) {
		player_core_render[0].Init("Assets/sprite/core2.dds", 700.0f, 600.0f);
		player_core_render[Pc].SetPosition({650.0f, -250.0f, 0.0f});
	}

	return true;
}

void Game_UI::Update()
{
	if (g_pad[0]->IsTrigger(enButtonDown)) {
		core_weapons->core_HP -= 50.0f;
	}
	else if (g_pad[0]->IsTrigger(enButtonUp)) {
		core_weapons->core_HP += 50.0f;
	}

	for (int i = 0; i < 5; i++) {
		player_hp_render[i].Update();
	}

	for (int B = 0; B < 5; B++) {
		boss_hp_render[B].Update();
	}

	for (int t = 0; t < 5; t++) {
		Time_render[t].Update();
	}

	for (int E = 0; E < 11; E++) {
		Enemy_count_render[E].Update();
	}

	for (int Pc = 0; Pc < 5; Pc++) {
		player_core_render[Pc].Update();
	}
}

void Game_UI::Render(RenderContext& rc)
{

	for (int i = 0; i < 5; i++) {
		if (u_player->game_state==0) {
			if (core_weapons->core_HP == 200.0f) {
				player_hp_render[0].Draw(rc);
			}
			else if (core_weapons->core_HP == 150.0f) {
				player_hp_render[1].Draw(rc);
			}
			else if (core_weapons->core_HP == 100.0f) {
				player_hp_render[2].Draw(rc);
			}
			else if (core_weapons->core_HP == 50.0f) {
				player_hp_render[3].Draw(rc);
			}
			else if (core_weapons->core_HP == 0.0f) {
				player_hp_render[4].Draw(rc);
			}
		}
		player_hp_render[i].Update();
	}

	if (u_player->game_state == 0) {
		boss_hp_render[0].Draw(rc);
	}

	for (int t = 0; t < 5; t++) {
		if (u_player->game_state == 0) {
			m_time == 0.0f;
			m_time += g_gameTime->GetFrameDeltaTime();
			if (m_time > 5.0f)
			{
				Time_render[0].Draw(rc);
			}
			if (m_time > 10.0f)
			{
				Time_render[1].Draw(rc);
			}
		}
		/*Time_render[t].Update();*/
	}

	//for (int E = 0; E < 11; E++) {
	//	if (u_player->game_state == 0) {
	//		Game* game = FindGO<Game>("game");
	//		/*Enemy_count_render[0].Draw(rc);*/
	//		/*switch (game->m_numDefeatedEnemy) {
	//		case 0:
	//			Enemy_count_render[1].Draw(rc);
	//			break;
	//		case 1:
	//			Enemy_count_render[2].Draw(rc);
	//			break;
	//		}*/
	//	}
	//	Enemy_count_render[E].Update();
	//}

	for (int Pc = 0; Pc < 5; Pc++) {
		if (u_player->game_state == 0) {
			switch (core_weapons->set_weapons) {
			case 2:
				player_core_render[0].Draw(rc);
				break;
			}
		}
		player_core_render[Pc].Update();
	}
}

