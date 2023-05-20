#include "stdafx.h"
#include "GigatonCannonAttack.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy_Far.h"
#include "Enemy_Near.h"
#include "Game.h"
#include "Boss.h"
#include "Boss_Drill.h"

GigatonCannonAttack::GigatonCannonAttack()
{

}

GigatonCannonAttack::~GigatonCannonAttack()
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

}

void GigatonCannonAttack::DestroyWithImpactEffect()
{
	//着弾したらエフェクト再生
	m_tyakudanEffect = NewGO<EffectEmitter>(0);
	m_tyakudanEffect->Init(enGigatonAttack);
	m_tyakudanEffect->SetScale({ 5.0f,5.0f,5.0f });
	m_tyakudanEffect->SetPosition({ m_position.x,m_position.y + 50.0f,m_position.z });
	m_tyakudanEffect->Play();

	//爆発音の設定と再生
	m_cannonSE = NewGO<SoundSource>(0);
	m_cannonSE->Init(enGigatonCannon);					//初期化
	m_cannonSE->SetVolume(2.0f * m_game->SEvol);		//音量調整
	m_cannonSE->Play(false);

	DeleteGO(this);
}

bool GigatonCannonAttack::Start()
{
	m_player = FindGO<Player>("player");
	m_game = FindGO<Game>("game");

	Setup();

	return true;
}

void GigatonCannonAttack::Setup()
{
	//弾のモデルの初期化
	m_bulletModel.Init("Assets/modelData/battleship_gun_bullet.tkm");
	m_bulletModel.SetScale(10.0f);

	//エネミーから見て正しい位置に弾を設定
	originRotation.Multiply(m_bulletLocalPosition);	//掛け算

	//最終的な弾の回転を決定
	m_rot = originRotation;
	m_position += m_bulletLocalPosition;				//それに親から見た位置を足して最終的な武器の位置を決定

	//前方向はプレイヤーと一緒
	m_bulletForward = m_player->playerForward;	

	//更新
	m_bulletModel.SetRotation(m_rot);
	m_bulletModel.SetPosition(m_position);
}

void GigatonCannonAttack::Update()
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

			DestroyWithImpactEffect();
		}
	}
	else if (m_player->game_state == 2)
	{
		DeleteGO(this);	//リザルト画面に行くと消す
	}

	if (m_player->game_end_state == 1)
	{
		DeleteGO(this);	//プレイヤーがポーズ画面からゲームを終了させると消す
	}
}

void GigatonCannonAttack::Move()
{
	//弾を前に飛ばす処理
	m_moveSpeed += m_bulletForward * 2.0f;
	m_position += m_moveSpeed;

	//弾とプレイヤー(親)の距離を計算して一定距離以上なら弾を消す
	Vector3 m_toPlayer = m_player->player_position - m_position;
	float m_dirToPlayer = m_toPlayer.Length();
	if (m_dirToPlayer >= 150.0f)
	{
		m_player->attack_state_la = false;
		m_player->attack_state_ra = false;
		m_player->attack_state_s = false;
		m_player->attack_state_ll = false;
		m_player->attack_state_rl = false;

		DestroyWithImpactEffect();
	}

	//バレットの更新
	m_bulletModel.SetPosition(m_position);
}

void GigatonCannonAttack::Damage()
{
	//エネミーの数だけ繰り返す
	for (auto enemy : m_game->m_enemyObject)
	{
		//弾とエネミーの距離を測り一定以下なら体力減少
		Vector3 diff = m_position - enemy->m_enemyPosition;
		if (diff.Length() <= 300.0f)
		{
			enemy->m_enemyHP -= m_bulletDamage;
			DestroyWithImpactEffect();
		}
	}
	//エネミーFarの数だけ繰り返す
	for (auto enemyFar : m_game->m_enemyFarObject)
	{
		//弾とエネミーの距離を測り一定以下なら体力減少
		Vector3 diff = m_position - enemyFar->m_enemyPosition;
		if (diff.Length() <= 300.0f)
		{
			enemyFar->m_enemyHP -= m_bulletDamage;
			DestroyWithImpactEffect();
		}
	}
	//エネミーNearの数だけ繰り返す
	for (auto enemyNear : m_game->m_enemyNearObject)
	{
		//弾とエネミーの距離を測り一定以下なら体力減少
		Vector3 diff = m_position - enemyNear->m_enemyPosition;
		if (diff.Length() <= 300.0f)
		{
			enemyNear->m_enemyHP -= m_bulletDamage;
			DestroyWithImpactEffect();
		}
	}
	//弾とボスの距離を測り一定以下なら体力減少
	if (m_game->boss != nullptr)
	{
		Vector3 diff = m_position - m_game->boss->boss_position;
		if (diff.Length() <= 300.0f)
		{
			m_game->boss->boss_HP -= m_bulletDamage;
			DestroyWithImpactEffect();
		}
	}
	//弾とドリルの距離を測り一定以下なら体力減少
	if (m_game->boss != nullptr)
	{
		if (m_game->boss->b_boss_drill != nullptr)
		{
			Vector3 diff = m_position - m_game->boss->b_boss_drill->b_w_position;
			if (diff.Length() <= 300.0f)
			{
				m_game->boss->b_boss_drill->drill_HP -= m_bulletDamage;
				DestroyWithImpactEffect();
			}
		}
	}
}

void GigatonCannonAttack::Render(RenderContext& rc)
{
	//ギガトンキャノンの弾は見せない
	//m_bulletModel.Draw(rc);
}