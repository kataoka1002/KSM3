#include "stdafx.h"
#include "MachineGunAttack.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy_Far.h"
#include "Enemy_Near.h"
#include "Game.h"
#include "Boss.h"
#include "Boss_Drill.h"

MachineGunAttack::MachineGunAttack()
{
	
}

MachineGunAttack::~MachineGunAttack()
{
	if (m_player->p_custom_point[0][2] != 0)
		m_player->attack_state_ra = false;
	if (m_player->p_custom_point[0][1] != 0)
		m_player->attack_state_s = false;
	if (m_player->p_custom_point[0][0] != 0)
		m_player->attack_state_la = false;
	if (m_player->p_custom_point[1][0] != 0)
		m_player->attack_state_ll = false;
	if (m_player->p_custom_point[1][2] != 0)
		m_player->attack_state_rl = false;

	//着弾したらエフェクト再生
	m_tyakudanEffect = NewGO<EffectEmitter>(0);
	m_tyakudanEffect->Init(enMasinganKemuri);
	m_tyakudanEffect->SetScale({ 10.0f,10.0f,10.0f });
	m_tyakudanEffect->SetPosition({ m_position.x,m_position.y,m_position.z });
	m_tyakudanEffect->Play();
}

bool MachineGunAttack::Start()
{
	m_player = FindGO<Player>("player");
	m_game = FindGO<Game>("game");

	Setup();
	
	return true;
}

void MachineGunAttack::Setup()
{
	//弾のモデルの初期化
	m_bulletModel.Init("Assets/modelData/battleship_gun_bullet.tkm");
	m_bulletModel.SetScale(2.0f);

	//エネミーから見て正しい位置に弾を設定
	originRotation.Multiply(m_bulletLocalPosition);	//掛け算

	//最終的な弾の回転を決定
	m_rot = originRotation;
	m_position += m_bulletLocalPosition;				//それに親から見た位置を足して最終的な武器の位置を決定

	//前方向はプレイヤーと一緒
	m_bulletForward = m_player->playerFowrad;

	//更新
	m_bulletModel.SetRotation(m_rot);
	m_bulletModel.SetPosition(m_position);
}

void MachineGunAttack::Update()
{
	if (m_player->game_state == 0)
	{
		Move();
		Damage();

		m_bulletModel.Update();

		if (m_position.y <= 0.0f)
		{
			m_player->attack_state_la = false;
			m_player->attack_state_ra = false;
			m_player->attack_state_s = false;
			m_player->attack_state_ll = false;
			m_player->attack_state_rl = false;

			DeleteGO(this);
		}
	}
}

void MachineGunAttack::Move()
{
	//弾を前に飛ばす処理
	m_moveSpeed += m_bulletForward * 2.0f;
	m_position += m_moveSpeed;

	//弾とプレイヤー(親)の距離を計算して一定距離以上なら弾を消す
	Vector3 m_toPlayer = m_player->player_position - m_position;
	float m_dirToPlayer = m_toPlayer.Length();
	if (m_dirToPlayer >= 1800.0f)
	{
		m_player->attack_state_la = false;
		m_player->attack_state_ra = false;
		m_player->attack_state_s = false;
		m_player->attack_state_ll = false;
		m_player->attack_state_rl = false;

		DeleteGO(this);
	}

	//バレットの更新
	m_bulletModel.SetPosition(m_position);
}

void MachineGunAttack::Damage()
{
	//エネミーの数だけ繰り返す
	for (auto enemy : m_game->m_enemyObject)
	{
		//弾とエネミーの距離を測り一定以下なら体力減少
		Vector3 diff = m_position - enemy->m_enemyPosition;
		if (diff.Length() <= 300.0f)
		{
			enemy->m_enemyHP -= 50.0f;
			DeleteGO(this);	//弾は消える
		}
	}
	//エネミーFarの数だけ繰り返す
	for (auto enemyFar : m_game->m_enemyFarObject)
	{
		//弾とエネミーの距離を測り一定以下なら体力減少
		Vector3 diff = m_position - enemyFar->m_enemyPosition;
		if (diff.Length() <= 400.0f)
		{
			enemyFar->m_enemyHP -= 50.0f;
			DeleteGO(this);	//弾は消える
		}
	}
	//エネミーNearの数だけ繰り返す
	for (auto enemyNear : m_game->m_enemyNearObject)
	{
		//弾とエネミーの距離を測り一定以下なら体力減少
		Vector3 diff = Vector3{ m_position.x,m_position.y + 20.0f,m_position.z } - enemyNear->m_enemyPosition;
		if (diff.Length() <= 400.0f)
		{
			enemyNear->m_enemyHP -= 50.0f;
			DeleteGO(this);	//弾は消える
		}
	}
	//弾とボスの距離を測り一定以下なら体力減少
	if (m_game->boss != nullptr)
	{
		Vector3 diff = m_position - m_game->boss->boss_position;
		if (diff.Length() <= 400.0f)
		{
			m_game->boss->boss_HP -= 50.0f;
			DeleteGO(this);	//弾は消える
		}
	}
	//弾とドリルの距離を測り一定以下なら体力減少
	if (m_game->boss != nullptr)
	{
		if (m_game->boss->b_boss_drill != nullptr)
		{
			Vector3 diff = m_position - m_game->boss->b_boss_drill->b_w_position;
			if (diff.Length() <= 400.0f)
			{
				m_game->boss->b_boss_drill->drill_HP -= 50.0f;
				DeleteGO(this);	//弾は消える
			}
		}
	}
}

void MachineGunAttack::Render(RenderContext& rc)
{
	m_bulletModel.Draw(rc);
}