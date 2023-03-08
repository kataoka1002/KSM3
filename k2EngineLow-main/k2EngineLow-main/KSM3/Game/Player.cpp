#include "stdafx.h"
#include "Player.h"
#include <math.h>
#include "Battleship_gun.h"

Player::Player() {
	player_modelRender.Init("Assets/modelData/test_player.tkm");
	pouse_spriteRender.Init("Assets/sprite/pouse.DDS", 1920.0f, 1080.0f);
	characterController.Init(70.0f, 150.0f, player_position);

	
	//��]�e�[�u��
	int i;
	for (i = 0; i < 360; i++) {
		fsin[i] = (float)sin(i * 3.1415926535 / 180);
		fcos[i] = (float)cos(i * 3.1415926535 / 180);
	}
	battleship_gun = NewGO<Battleship_gun>(1, "battleship_gun");
}

Player::~Player()
{
	DeleteGO(battleship_gun);
}

void Player::Update() {
	battleship_gun->game_state = game_state;
	battleship_gun->B_G_position = player_position;
	battleship_gun->B_G_rotation = player_rotation;
	if (game_state == 0) {
		player_modelRender.SetPosition(player_position);

		Move();//�ړ�����

		//ManageState();//�X�e�[�g�Ǘ�

		player_modelRender.Update();
		if (g_pad[0]->IsTrigger(enButtonStart)) {
			game_state = 1;
		}
	}
	else if (game_state == 1) {
		pause();
	}
}

void Player::Move()
{
	player_moveSpeed = { 0.0f,0.0f,0.0f };//�ړ����x�̏�����

	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	float cx, cy;

	forward.y = 0.0f;
	right.y = 0.0f;


	right *= stickL.x * 120.0f;
	forward *= stickL.y * 120.0f;

	playerFowrad.Normalize();

	//x��z�̈ړ����x����������(�X�e�B�b�N�̓��͂���������)�B
	//��]����
	if (stickL.x!=0.0f)
	{
		playerFowrad.x = playerFowrad.x * cos(stickL.x*-0.05) - playerFowrad.z * sin(stickL.x * -0.05);
		playerFowrad.z = playerFowrad.x * sin(stickL.x*-0.05) + playerFowrad.z * cos(stickL.x * -0.05);

		player_rotation.SetRotationY(atan2(playerFowrad.x, playerFowrad.z));
		player_modelRender.SetRotation(player_rotation);
		//��]���̈ړ�
		if (stickL.y != 0.0f) {
			player_moveSpeed += playerFowrad * forward.z * 9;

			player_position = characterController.Execute(player_moveSpeed, 1.0f / 60.0f);
		}
	}
	//��]���Ă��Ȃ��Ƃ��̈ړ�
	else if (stickL.y != 0.0f) {
		player_moveSpeed += playerFowrad * forward.z * 4;

		player_position = characterController.Execute(player_moveSpeed, 1.0f / 60.0f);

	}

	//���W��������B
	player_modelRender.SetPosition(player_position);
	player_modelRender.SetRotation(player_rotation);
}

void Player::pause() {
	
	if (g_pad[0]->IsTrigger(enButtonB)) {
		game_state = 0;
	}
	else if (g_pad[0]->IsTrigger(enButtonA)) {
		game_end_state = 1;
	}
}

void Player::Render(RenderContext& rc)
{
	
	player_modelRender.Draw(rc);
	if (game_state == 1)
		pouse_spriteRender.Draw(rc);
}