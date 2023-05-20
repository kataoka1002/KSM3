#include "stdafx.h"
#include "Battle_ship_attack.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy_Far.h"
#include "Enemy_Near.h"
#include "Game.h"
#include "Boss.h"
#include "Boss_Riser.h"
#include "Boss_Drill.h"

Battle_ship_attack::Battle_ship_attack() 
{
	
}

Battle_ship_attack::~Battle_ship_attack()
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

void Battle_ship_attack::DestroyWithImpactEffect()
{
	//着弾したらエフェクト発生
	m_tyakudanEffect = NewGO<EffectEmitter>(0);
	m_tyakudanEffect->Init(enTyakudan);
	m_tyakudanEffect->SetScale({ 5.7f,5.7f,5.7f });
	m_tyakudanEffect->SetPosition({ firing_position.x,firing_position.y + 50.0f,firing_position.z });
	m_tyakudanEffect->Play();

	//着弾したら効果音発生
	m_battleShipGunTyakudanSE = NewGO<SoundSource>(0);			//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
	m_battleShipGunTyakudanSE->Init(enButtleShipTyakudan);		//初期化
	m_battleShipGunTyakudanSE->SetVolume(2.0f * m_game->SEvol);	//音量調整
	m_battleShipGunTyakudanSE->Play(false);
	DeleteGO(this);	//弾は消える
}
bool Battle_ship_attack::Start()
{
	m_player = FindGO<Player>("player");
	m_game = FindGO<Game>("game");
	//m_boss = FindGO<Boss>("boss");

	//発射音の設定と再生
	m_battleShipGunSE = NewGO<SoundSource>(0);	//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
	m_battleShipGunSE->Init(enButtleShipGun);	//初期化
	m_battleShipGunSE->SetVolume(1.0f * m_game->SEvol);			//音量調整
	m_battleShipGunSE->Play(false);


	Setup();

	return true;
}

void Battle_ship_attack::Setup() 
{
	//モデルの初期化
	m_bulletModel.Init("Assets/modelData/battleship_gun_bullet.tkm");
	m_bulletModel.SetScale(5.0f);

	//エネミーから見て正しい位置に弾を設定
	originRotation.Multiply(m_bulletLocalPosition);	//掛け算

	//最終的な弾の回転を決定
	B_S_aiming = originRotation;
	firing_position += m_bulletLocalPosition;				//それに親から見た位置を足して最終的な武器の位置を決定

	//前方向はプレイヤーと一緒
	m_bulletForward = m_player->playerForward;
	
	//更新
	m_bulletModel.SetRotation(B_S_aiming);
	m_bulletModel.SetPosition(firing_position);
}

void Battle_ship_attack::Update()
{
	if (m_player->game_state == 0)
	{
		EfeEfe();
		Move();
		Damage();
		
		m_bulletModel.Update();
		if (firing_position.y <= 0.0f)
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
}

void Battle_ship_attack::Move() 
{
	firing_position += m_bulletForward * move_speed;
	firing_position.y -= fall_speed;
	move_speed -= 0.05f;
	fall_speed += 0.1f;
	m_bulletModel.SetPosition(firing_position);
}

void Battle_ship_attack::Damage()
{
	//エネミーの数だけ繰り返す
	for (auto enemy : m_game->m_enemyObject)
	{
		//弾とエネミーの距離を測り一定以下なら体力減少
		Vector3 diff = firing_position - enemy->m_enemyPosition;
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
		Vector3 diff = firing_position - enemyFar->m_enemyPosition;
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
		Vector3 diff = firing_position - enemyNear->m_enemyPosition;
		if (diff.Length() <= 300.0f)
		{
			enemyNear->m_enemyHP -= m_bulletDamage;
			DestroyWithImpactEffect();
		}
	}

	//弾とボスの距離を測り一定以下なら体力減少
	if (m_game->boss != nullptr)
	{
		Vector3 diff = firing_position - m_game->boss->boss_position;
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
			Vector3 diff = firing_position - m_game->boss->b_boss_drill->b_w_position;
			if (diff.Length() <= 300.0f)
			{
				m_game->boss->b_boss_drill->drill_HP -= m_bulletDamage;
				DestroyWithImpactEffect();
			}
		}
	}
}

void Battle_ship_attack::EfeEfe()
{
	m_kemuriCount++;
	if (m_kemuriCount >= 2)
	{
		//エフェクトの初期化と再生
		m_kemuriEffect = NewGO<EffectEmitter>(0);
		m_kemuriEffect->Init(enSenkanhouKemuri);
		m_kemuriEffect->SetScale({ 5.0f,5.0f,5.0f });
		m_kemuriEffect->SetRotation(B_S_aiming);
		m_kemuriEffect->SetPosition({ firing_position.x,firing_position.y + 50.0f,firing_position.z });
		m_kemuriEffect->Play();
		m_kemuriCount = 0;
	}
}

void Battle_ship_attack::Render(RenderContext& rc) 
{
	m_bulletModel.Draw(rc);
}