#include "stdafx.h"
#include "Core_weapons_attack.h"
#include "Player.h"
#include "Core_weapons.h"
#include "Enemy.h"
#include "Enemy_Far.h"
#include "Enemy_Near.h"
#include "Game.h"
#include "Boss.h"
#include "Boss_Drill.h"

Core_weapons_attack::Core_weapons_attack() {
	C_W_A_player = FindGO<Player>("player");
	C_W_A_core_weapons = FindGO<Core_weapons>("core_weapons");
	m_game = FindGO<Game>("game");
	Setup();
}

void Core_weapons_attack::Setup() {
	switch (C_W_A_core_weapons->set_weapons)
	{
	case 1:
		break;
	case 2:
		C_W_Bullet.Init("Assets/modelData/V_P_bullet.tkm");
		C_W_Bullet.SetScale(4.0f);
		C_W_aiming = C_W_A_core_weapons->cw_Rotation;
		firing_position= C_W_A_core_weapons->cw_position;
		firing_position.y += 12.0f;
		move_speed = 200.0f;
		C_W_Bullet_Fowrad = C_W_A_player->playerForward;
		C_W_Bullet.SetPosition(firing_position);
		C_W_Bullet.SetRotation(C_W_aiming);
		damage_volume=10.0f;
		break;
	default:
		break;
	}
}

Core_weapons_attack::~Core_weapons_attack()
{
	C_W_A_core_weapons->atack_state = false;

	//着弾したらエフェクト再生
	m_tyakudanEffect = NewGO<EffectEmitter>(0);
	m_tyakudanEffect->Init(enMasinganKemuri);
	m_tyakudanEffect->SetScale({ 10.0f,10.0f,10.0f });
	m_tyakudanEffect->SetPosition({ firing_position.x,firing_position.y,firing_position.z });
	m_tyakudanEffect->Play();
}

void Core_weapons_attack::Update() {
	if (C_W_A_player->game_state == 0) {
		Move();
		Damage();
		C_W_Bullet.Update();
		if (firing_position.y <= 0.0f) {
			DeleteGO(this);
		}
	}
	else if (C_W_A_player->game_state == 2)
	{
		DeleteGO(this);	//リザルト画面に行くと消す
	}

	if (C_W_A_player->game_end_state == 1)
	{
		DeleteGO(this);	//プレイヤーがポーズ画面からゲームを終了させると消す
	}
}

void Core_weapons_attack::Damage()
{
	//エネミーの数だけ繰り返す
	for (auto enemy : m_game->m_enemyObject)
	{
		//弾とエネミーの距離を測り一定以下なら体力減少
		Vector3 diff = firing_position - enemy->GetPos();
		if (diff.Length() <= 200.0f)
		{
			enemy->ApplyDamage(m_bulletDamage);
			DeleteGO(this);	//弾は消える
		}
	}
	//エネミーFarの数だけ繰り返す
	for (auto enemyFar : m_game->m_enemyFarObject)
	{
		//弾とエネミーの距離を測り一定以下なら体力減少
		Vector3 diff = firing_position - enemyFar->GetPos();
		if (diff.Length() <= 200.0f)
		{
			enemyFar->ApplyDamage(m_bulletDamage);
			DeleteGO(this);	//弾は消える
		}
	}
	//エネミーNearの数だけ繰り返す
	for (auto enemyNear : m_game->m_enemyNearObject)
	{
		//弾とエネミーの距離を測り一定以下なら体力減少
		Vector3 diff = firing_position - enemyNear->GetPos();
		if (diff.Length() <= 200.0f)
		{
			enemyNear->ApplyDamage(m_bulletDamage);
			DeleteGO(this);	//弾は消える
		}
	}
	//弾とボスの距離を測り一定以下なら体力減少
	if (m_game->boss != nullptr)
	{
		Vector3 diff = firing_position - m_game->boss->boss_position;
		if (diff.Length() <= 200.0f)
		{
			m_game->boss->boss_HP -= m_bulletDamage;
			DeleteGO(this);	//弾は消える
		}
	}

	//弾とドリルの距離を測り一定以下なら体力減少
	if (m_game->boss != nullptr)
	{
		if (m_game->boss->b_boss_drill != nullptr)
		{
			Vector3 diff = firing_position - m_game->boss->b_boss_drill->b_w_position;
			if (diff.Length() <= 200.0f)
			{
				m_game->boss->b_boss_drill->drill_HP -= m_bulletDamage;
				DeleteGO(this);	//弾は消える
			}
		}
	}
}

void Core_weapons_attack::Move() {
	firing_position += C_W_Bullet_Fowrad * move_speed;
	firing_position.y -= fall_speed;
	move_speed -= 0.05f;
	fall_speed += 0.1f;
	C_W_Bullet.SetPosition(firing_position);

	//弾とプレイヤー(親)の距離を計算して一定距離以上なら弾を消す
	Vector3 m_toPlayer = C_W_A_player->player_position - firing_position;
	float m_dirToPlayer = m_toPlayer.Length();
	if (m_dirToPlayer >= 2000.0f)
	{
		DeleteGO(this);
	}

}

void Core_weapons_attack::Render(RenderContext& rc) {
	C_W_Bullet.Draw(rc);
}

