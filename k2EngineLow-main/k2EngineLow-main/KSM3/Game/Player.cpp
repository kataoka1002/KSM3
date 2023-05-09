#include "stdafx.h"
#include "Player.h"
#include <math.h>
#include "Left_arm_weapons.h"
#include "Customize_UI_ver2.h"
#include "Game.h"


Player::Player() 
{
	//プレイヤーのモデルとポーズ画面のスプライトの初期化
	player_modelRender.Init("Assets/modelData/player.tkm");
	pouse_spriteRender.Init("Assets/sprite/pouse.DDS", 1920.0f, 1080.0f);
	//キャラコンの設定
	characterController.Init(70.0f, 150.0f, player_position);
}

Player::~Player()
{
	//DeleteGO(p_left_arm_weapons);
}

void Player::Update() 
{
	if (game_state == 0) //メインゲーム
	{
		Move();	//移動処理

		//スタートボタンを押すとポーズ画面に移動
		if (g_pad[0]->IsTrigger(enButtonStart)) 
		{
			game_state = 1;
		}
		if (g_pad[0]->IsTrigger(enButtonA)) 
		{
			p_customize_ui_ver2 = NewGO<Customize_UI_ver2>(1, "customize_ui_ver2");
		}

		//モデルの更新
		player_modelRender.Update(true);
	}
	else if (game_state == 1) //ポーズ画面
	{
		pause();
	}
}

void Player::Move()
{
	player_moveSpeed = { 0.0f,0.0f,0.0f };//移動速度の初期化

	Vector3 stickL;
	float throttle = 0;
	stickL.x = g_pad[0]->GetLStickXF();
	//スティックを倒した量の取得
	throttle = g_pad[0]->GetRTrigger();

	Vector3 right = g_camera3D->GetRight();
	right.y = 0.0f;
	right *= stickL.x * 120.0f;

	//スピードが0じゃないならエフェクトを出す
	if (throttle != 0)
	{
		MakeEfe();
	}

	playerFowrad.Normalize();

	//xかzの移動速度があったら(スティックの入力があったら)。
	//回転処理
	if (stickL.x!=0.0f)
	{
		playerFowrad.x = playerFowrad.x * cos(stickL.x * -0.05) - playerFowrad.z * sin(stickL.x * -0.05);
		playerFowrad.z = playerFowrad.x * sin(stickL.x * -0.05) + playerFowrad.z * cos(stickL.x * -0.05);

		player_rotation.SetRotationY(atan2(playerFowrad.x, playerFowrad.z));
	}
	//回転していないときの移動
	if (throttle != 0.0f) 
	{
		//だんだん速くする
		accelerator += 0.05;
		if (accelerator >= 2) 
		{
			accelerator = 2;	//最大値は2
		}
	}
	else 
	{
		//だんだん遅くする
		accelerator -= 0.05;
		if (accelerator <= 0) 
		{
			accelerator = 0;	//最小値は0
		}
	}

	move_s = 4.0f * accelerator;
	player_moveSpeed += playerFowrad  * move_s * (throttle / 2.0f);

	player_position = characterController.Execute(player_moveSpeed, 1.0f / 60.0f);

	//座標を教える。
	player_modelRender.SetPosition(player_position);
	player_modelRender.SetRotation(player_rotation);
}

void Player::MakeEfe()
{
	//動いている間3フレームごとに砂ぼこりを発生させる
	if (effectCount > 3) 
	{
		//砂ぼこりエフェクトの初期化と再生
		sunabokoriEffect = NewGO<EffectEmitter>(0);
		sunabokoriEffect->Init(enSunabokori);
		sunabokoriEffect->SetScale({ 4.0f,4.0f,4.0f });
		sunabokoriEffect->SetRotation(player_rotation);
		sunabokoriEffect->SetPosition(player_position);
		sunabokoriEffect->Play();

		effectCount = 0;	//カウントリセット
	}
	effectCount++;
}

void Player::pause() 
{
	if (g_pad[0]->IsTrigger(enButtonB)) 
	{
		game_state = 0;	//メインゲームに戻る
	}
	else if (g_pad[0]->IsTrigger(enButtonA)) 
	{
		game_end_state = 1;	//ゲーム終了
	}
}

void Player::Render(RenderContext& rc)
{
	player_modelRender.Draw(rc);

	//ポーズ中ならポーズ画面を表示
	if (game_state == 1)
	{
		pouse_spriteRender.Draw(rc);
	}
}