#include "stdafx.h"
#include "Enemy_weapons.h"
#include "Player.h"
#include "Enemy.h"

Enemy_weapons::Enemy_weapons() {
	e_w_player = FindGO<Player>("player");
	e_w_enemy = FindGO<Enemy>("enemy");
}

Enemy_weapons::~Enemy_weapons() {

}

void Enemy_weapons::Setup() {
	//“G‚Ì•Ší‚ÌŽí—Þ‚ÌŠm’è
	set_weapons = 1;

	if (set_weapons == 1) {
		Enemy_weapons_Render.Init("Assets/modelData/battleship_gun_enemy.tkm");
		Enemy_weapons_Render.Update();
	}
}

void Enemy_weapons::Update() {
	if (fast == 0) {
		Setup();
	}
	fast++;
	if (game_state == 0) {
		Move();
	}
	if (e_w_player->game_end_state == 1) {
		DeleteGO(this);
	}
	Enemy_weapons_Render.Update();
}

void Enemy_weapons::Move() {
	Quaternion originRotation = e_w_enemy->enemy_rotation;
	e_w_position = e_w_enemy->enemy_position;
	Vector3 lp = e_w_localposition;
	originRotation.Multiply(lp);
	e_w_position += lp;
	e_w_Rotation = originRotation;
	Enemy_weapons_Render.SetPosition(e_w_position);
	Enemy_weapons_Render.SetRotation(e_w_Rotation);
}

void Enemy_weapons::Render(RenderContext& rc) {
	Enemy_weapons_Render.Draw(rc);
}