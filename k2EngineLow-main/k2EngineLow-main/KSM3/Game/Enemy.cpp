#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include"Game.h"

#include <time.h>
#include <stdlib.h>
#include "Battle_ship_attack.h"
#include "Drop_item.h"


Enemy::Enemy() {
	e_player = FindGO<Player>("player");
	
}

Enemy::~Enemy() {
	if (defeat_state == true) {
		for (int i = 0; i < 12; i++) {
			if (enemy_weapons == i) {
				drop_item->drop_weapons[i] = 1;
			}
			else {
				drop_item->drop_weapons[i] = 0;
			}
		}
	}
}

bool Enemy::Start() {
	
	//enemy_rotation.SetRotationY(Math::PI);

	enemy_modelRender.Init("Assets/modelData/enemy_model.tkm");
	enemy_modelRender.SetRotation(enemy_rotation);
	enemy_modelRender.SetPosition(enemy_position);
	//�L�����N�^�[�R���g���[���[���������B
	enemy_characterController.Init(
		50.0f,			//���a�B
		-40.0f,			//�����B
		enemy_position		//���W�B
	);
	return true;
}

void Enemy::Update()
{
	if (e_player->game_state == 0) {
		Move();
		PlayerSearch();
		enemy_modelRender.Update();
		if (e_player->attack_state_la == true) {
			e_battle_ship_attack = FindGO< Battle_ship_attack>("battle_ship_attack");
			Vector3 diff = e_battle_ship_attack->firing_position - enemy_position;
			if (diff.Length() <= 120.0f)
			{
				drop_item = NewGO<Drop_item>(1, "drop_item");
				drop_item->Drop_position = enemy_position;
				drop_item->Drop_position.y += 50.0f;
				defeat_state = true;
				DeleteGO(this);
			}
		}
	}
}

void Enemy::PlayerSearch() {
	//�G�l�~�[����v���C���[�������Ă�����ǂ�������
	Vector3 toPlayer = e_player->player_position - enemy_position;

	//�v���C���[�Ƃ̋������v�Z����
	float distToPlayer = toPlayer.Length();
	//�v���C���[�Ɍ������ĐL�т�x�N�g���𐳋K������
	Vector3 toPlayerDir = toPlayer;
	toPlayerDir.Normalize();
	//�G�l�~�[�̑O��������toPlayerDir�Ƃ̓��ς��v�Z����
	float t = toPlayerDir.Dot(enemy_forward);
	//���ς̌��ʂ�acos�֐��ɓn���āAm_enemyFowrad��toPlayerDir�̂Ȃ��p�x�����߂�B
	float angle = acos(t);

	//�G�L�����̑O���������X�V����
	enemy_forward = toPlayerDir;
	// �G�̑O���������g���āA��]�N�H�[�^�j�I�����v�Z����B
	enemy_rotation.SetRotationY(atan2(enemy_forward.x, enemy_forward.z));
	enemy_modelRender.SetPosition(enemy_position);
	enemy_modelRender.SetRotation(enemy_rotation);
	enemy_modelRender.Update();
}

void Enemy::Move() {
	//�G�l�~�[����v���C���[�Ɍ������x�N�g�����v�Z����
	Vector3 toPlayer = e_player->player_position - enemy_position;
	//�x�N�g���𐳋K������B
	toPlayer.Normalize();
	//�ړ����x��ݒ肷��B
	enemy_moveSpeed = toPlayer * 100.0f;
	//�G�l�~�[���ړ�������
	enemy_position = enemy_characterController.Execute(enemy_moveSpeed, g_gameTime->GetFrameDeltaTime());
	Vector3 modelPosition = enemy_position;
}

void Enemy::Render(RenderContext& rc)
{
	//���f���̕`��B
	enemy_modelRender.Draw(rc);
}
