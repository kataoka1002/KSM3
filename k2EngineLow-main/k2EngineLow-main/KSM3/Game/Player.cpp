#include "stdafx.h"
#include "Player.h"
#include <math.h>
#include "Left_arm_weapons.h"



Player::Player() {
	player_modelRender.Init("Assets/modelData/test_player.tkm");
	pouse_spriteRender.Init("Assets/sprite/pouse.DDS", 1920.0f, 1080.0f);
	characterController.Init(70.0f, 150.0f, player_position);

	//回転テーブル
	int i;
	for (i = 0; i < 360; i++) {
		fsin[i] = (float)sin(i * 3.1415926535 / 180);
		fcos[i] = (float)cos(i * 3.1415926535 / 180);
	}
	
}

Player::~Player()
{
	//DeleteGO(p_left_arm_weapons);
}

void Player::Update() {
	
	if (game_state == 0) {
		player_modelRender.SetPosition(player_position);

		Move();//移動処理

		//ManageState();//ステート管理

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
	player_moveSpeed = { 0.0f,0.0f,0.0f };//移動速度の初期化

	Vector3 stickL;
	float throttle;
	stickL.x = g_pad[0]->GetLStickXF();
	throttle = g_pad[0]->GetRTrigger();
	brake = g_pad[0]->IsPress(enButtonLB2);

	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	float cx, cy;

	forward.y = 0.0f;
	right.y = 0.0f;


	right *= stickL.x * 120.0f;
	forward *= throttle * 120.0f;

	playerFowrad.Normalize();

	//xかzの移動速度があったら(スティックの入力があったら)。
	//回転処理
	if (stickL.x!=0.0f)
	{
		playerFowrad.x = playerFowrad.x * cos(stickL.x*-0.05) - playerFowrad.z * sin(stickL.x * -0.05);
		playerFowrad.z = playerFowrad.x * sin(stickL.x*-0.05) + playerFowrad.z * cos(stickL.x * -0.05);

		player_rotation.SetRotationY(atan2(playerFowrad.x, playerFowrad.z));
		player_modelRender.SetRotation(player_rotation);
		//回転時の移動
	}
	//回転していないときの移動
	if (throttle != 0.0f) {
		accelerator += 0.05;
		if (accelerator >= 2) {
			accelerator = 2;
		}

	}
	else {
		accelerator -= 0.05;
		if (accelerator <= 0) {
			accelerator = 0;
		}
	}

	player_moveSpeed += playerFowrad  * 4.0f * accelerator*(throttle/2.0f);

	player_position = characterController.Execute(player_moveSpeed, 1.0f / 60.0f);

	//座標を教える。
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