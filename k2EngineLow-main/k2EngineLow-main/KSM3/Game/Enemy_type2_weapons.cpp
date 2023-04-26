#include "stdafx.h"
#include "Enemy_type2_weapons.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy_attack.h"

Enemy_type2_weapons::Enemy_type2_weapons() {
	e_w_player = FindGO<Player>("player");
}

Enemy_type2_weapons::~Enemy_type2_weapons() {
	//if (atack_state == true) {
		//if (enemy_attack->atack_state == true) {
	DeleteGO(enemy_attack);
	//}
//}
}

void Enemy_type2_weapons::Setup() {
	//�G�̕���̎�ނ̊m��
	set_weapons = 1;//�����͂������񉼂Œ萔�ݒ肵�Ă邾���Ō�X�����_���ɂ��Ă����\��
	e_w_enemy = FindGO<Enemy>("enemy");
	if (set_weapons == 1) {
		Enemy_weapons_Render.Init("Assets/modelData/battleship_gun_Drop.tkm");
		Enemy_weapons_Render.Update();
	}
	else if (set_weapons == 2) {
		Enemy_weapons_Render.Init("Assets/modelData/machine_gun_enemy.tkm");
		Enemy_weapons_Render.Update();
	}
}

void Enemy_type2_weapons::Update() {
	if (fast == 0) {//�����ň��Z�b�g�A�b�v�����Ȃ��ƃG���[��f�����ߎd���Ȃ��A�b�v�f�[�g�̒��̈�t���[���ڂŃZ�b�g�A�b�v�����Ă��܂��B���������������B
		Setup();
	}
	fast++;
	if (game_state == 0 && fast != 0) {
		Move();
		if (atack_ok == true) {
			firing_cound++;//�U���^�C�~���O�̌v�Z
			//����ɂ���Ă̕���
			switch (set_weapons)
			{
			case 1://��͖C
				if (firing_cound % 180 == 0) {
					enemy_attack = NewGO<Enemy_attack>(1, "enemy_attack");
					atack_state = true;
					enemy_attack->firing_position = e_w_position;
					enemy_attack->e_a_aiming = e_w_enemy->enemy_rotation;
					enemy_attack->e_a_Bullet_Fowrad = e_w_enemy->enemy_forward;
				}
				break;
			case 2://�}�V���K��
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

void Enemy_type2_weapons::Move() {
	//�����͊ۃp�N����OK
	Quaternion originRotation = e_w_enemy->enemy_rotation;
	e_w_position = e_w_enemy->enemy_position;
	Vector3 lp = e_w_localposition;
	originRotation.Multiply(lp);
	e_w_position += lp;
	e_w_Rotation = originRotation;
	Enemy_weapons_Render.SetPosition(e_w_position);
	Enemy_weapons_Render.SetRotation(e_w_Rotation);
}

void Enemy_type2_weapons::Render(RenderContext& rc) {
	Enemy_weapons_Render.Draw(rc);
}