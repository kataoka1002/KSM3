#include "stdafx.h"
#include "Enemy_weapons.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy_attack.h"

Enemy_weapons::Enemy_weapons() {
	e_w_player = FindGO<Player>("player");
}

Enemy_weapons::~Enemy_weapons() {
	//if (atack_state == true) {
		//if (enemy_attack->atack_state == true) {
			DeleteGO(enemy_attack);
		//}
	//}
}

void Enemy_weapons::Setup() {
	//敵の武器の種類の確定
	set_weapons = 2;//ここはいったん仮で定数設定してるだけで後々ランダムにしていく予定
	e_w_enemy = FindGO<Enemy>("enemy");
	if (set_weapons == 1) {
		Enemy_weapons_Render.Init("Assets/modelData/battleship_gun_enemy.tkm");
		Enemy_weapons_Render.Update();
	}
	else if (set_weapons == 2) {
		Enemy_weapons_Render.Init("Assets/modelData/machine_gun_enemy.tkm");
		Enemy_weapons_Render.Update();
	}
}

void Enemy_weapons::Update() {
	if (fast == 0) {//ここで一回セットアップをしないとエラーを吐くため仕方なくアップデートの中の一フレーム目でセットアップをしています。ご了承ください。
		Setup();
	}
	fast++;
	if (e_w_player->game_state == 0&&fast!=0) {
		Move();
		if (atack_ok == true) {
			firing_cound++;//攻撃タイミングの計算
			//武器によっての分岐
			switch (set_weapons)
			{
			case 1://戦艦砲
				if (firing_cound % 180 == 0) {
					enemy_attack = NewGO<Enemy_attack>(1, "enemy_attack");
					atack_state = true;
					enemy_attack->firing_position = e_w_position;
					enemy_attack->e_a_aiming = e_w_enemy->enemy_rotation;
					enemy_attack->e_a_Bullet_Fowrad = e_w_enemy->enemy_forward;
				}
				break;
			case 2://マシンガン
				if (firing_cound % 60 == 0) {
					enemy_attack = NewGO<Enemy_attack>(1, "enemy_attack");
					atack_state = true;
					enemy_attack->firing_position = e_w_position;
					enemy_attack->e_a_Bullet_Fowrad = e_w_enemy->enemy_forward;
				}
			default:
				break;
			}
			
		}
	}
	if (e_w_player->game_end_state == 1) {
		DeleteGO(this);
	}
	Enemy_weapons_Render.Update();
}

void Enemy_weapons::Move() {
	//ここは丸パクリでOK
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