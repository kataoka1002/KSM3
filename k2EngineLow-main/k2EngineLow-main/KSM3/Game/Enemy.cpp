#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include"Game.h"

#include <time.h>
#include <stdlib.h>

Enemy::Enemy() {
	e_player = FindGO<Player>("player");
}

Enemy::~Enemy() {

}

bool Enemy::Start() {
	
	//enemy_rotation.SetRotationY(Math::PI);

	enemy_modelRender.Init("Assets/modelData/enemy_model.tkm");
	enemy_modelRender.SetRotation(enemy_rotation);
	enemy_modelRender.SetPosition(enemy_position);
	//キャラクターコントローラーを初期化。
	enemy_characterController.Init(
		50.0f,			//半径。
		-40.0f,			//高さ。
		enemy_position		//座標。
	);
	return true;
}

void Enemy::Update()
{
	if (e_player->game_state == 0) {
		Move();
		PlayerSearch();
		enemy_modelRender.Update();
	}
}

void Enemy::PlayerSearch() {
	//エネミーからプレイヤーが入ってきたら追いかける
	Vector3 toPlayer = e_player->player_position - enemy_position;

	//プレイヤーとの距離を計算する
	float distToPlayer = toPlayer.Length();
	//プレイヤーに向かって伸びるベクトルを正規化する
	Vector3 toPlayerDir = toPlayer;
	toPlayerDir.Normalize();
	//エネミーの前方方向とtoPlayerDirとの内積を計算する
	float t = toPlayerDir.Dot(enemy_forward);
	//内積の結果をacos関数に渡して、m_enemyFowradとtoPlayerDirのなす角度を求める。
	float angle = acos(t);

	//敵キャラの前方方向を更新する
	enemy_forward = toPlayerDir;
	// 敵の前方方向を使って、回転クォータニオンを計算する。
	enemy_rotation.SetRotationY(atan2(enemy_forward.x, enemy_forward.z));
	enemy_modelRender.SetPosition(enemy_position);
	enemy_modelRender.SetRotation(enemy_rotation);
	enemy_modelRender.Update();
}

void Enemy::Move() {
	//エネミーからプレイヤーに向かうベクトルを計算する
	Vector3 toPlayer = e_player->player_position - enemy_position;
	//ベクトルを正規化する。
	toPlayer.Normalize();
	//移動速度を設定する。
	enemy_moveSpeed = toPlayer * 100.0f;
	//エネミーを移動させる
	enemy_position = enemy_characterController.Execute(enemy_moveSpeed, g_gameTime->GetFrameDeltaTime());
	Vector3 modelPosition = enemy_position;
}

void Enemy::Render(RenderContext& rc)
{
	//モデルの描画。
	enemy_modelRender.Draw(rc);
}
