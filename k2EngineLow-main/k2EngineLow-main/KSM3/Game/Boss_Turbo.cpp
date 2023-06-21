//ターボのパーツ。

#include "stdafx.h"
#include "Boss_Turbo.h"
#include "Player.h"
#include "Boss.h"
#include "Boss_Turbo_attack.h"
#include "Drop_item.h"
#include "Game.h"

Boss_Turbo::Boss_Turbo()
{

	m_animationClip[enAnimationClip_Idle].Load("Assets/animData/Boss_turbo.tka");
	m_animationClip[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClip[enAnimationClip_Attack].Load("Assets/animData/Boss_turbo_attack.tka");
	m_animationClip[enAnimationClip_Attack].SetLoopFlag(true);
	b_w_player = FindGO<Player>("player");
}

Boss_Turbo::~Boss_Turbo()
{
	DeleteGO(b_boss_weapons);
	DeleteGO(TatumakiSE);
	if (defeatState == true)
	{
		drop_item->drop_kinds = set_weapons;
	}
}

void Boss_Turbo::Setup()
{
	set_weapons = 1;
	b_w_boss = FindGO<Boss>("boss");
	if (set_weapons == 1)
	{
		boss_Turbo_Render.Init("Assets/modelData/Boss_turbo2.tkm", true, true, m_animationClip, enAnimationClip_Num, enModelUpAxisZ);
		boss_Turbo_Render.Update();
	}

	//キャラコン。
	//boss_riser_characterContller.Init(
	//	450.0f,			//半径。
	//	40.0f,			//高さ。
	//	b_w_position	//座標。
	//);
	//boss_Turbo_Render.SetRotation(b_w_rotation);
	//boss_Turbo_Render.SetPosition(b_w_position);
	boss_Turbo_Render.SetScale(scale);
	boss_Turbo_Render.Update();
}

void Boss_Turbo::Update()
{
	if (fast == 0)
	{
		Setup();
	}
	fast++;
	if (b_w_player->GetGameState() == MAIN_GAME_NUM && fast != 0)
	{
		Move();
			Rotation();
		
		firing_cound++;//攻撃のタイミングの計算。
		


			if (firing_cound == 350)
			{
				/*m_weaponEffect = NewGO<EffectEmitter>(0);
				m_weaponEffect->Init(enTatumaki_charge);
				m_weaponEffect->SetScale({ 40.0f,40.0f,40.0f });
				m_weaponEffect->SetPosition(efeLP + b_w_position);
				m_weaponEffect->SetRotation(b_w_rotation);
				m_weaponEffect->Play();*/

			}
			if (firing_cound >= 500) {
				boss_Turbo_Render.PlayAnimation(enAnimationClip_Attack, 0.5f);
			}
			else {
				boss_Turbo_Render.PlayAnimation(enAnimationClip_Idle, 0.5f);
			}
			if (firing_cound == 500) {

				m_weaponEffect = NewGO<EffectEmitter>(0);
				m_weaponEffect->Init(enTatumaki_fire);
				m_weaponEffect->SetScale({ 40.0f,40.0f,30.0f });
				m_weaponEffect->SetPosition(efeLP + b_w_position);
				m_weaponEffect->SetRotation(b_w_rotation);
				m_weaponEffect->Play();
				
				TatumakiSE = NewGO<SoundSource>(0);
				TatumakiSE->Init(enTatumaki);
				TatumakiSE->Play(false);
				Rote = true;
			}
		
		/*if (m_weaponEffect != nullptr) {
			if (m_weaponEffect->IsPlay() == true) {
				m_weaponEffect->SetRotation(b_w_rotation);
				m_weaponEffect->SetPosition(efeLP + b_w_position);

			}
			else {
				DeleteGO(m_weaponEffect);
				m_weaponEffect = nullptr;
			}
		}*/

		if (firing_cound > 700) {
			b_boss_weapons = NewGO<Boss_Turbo_attack>(1, "boss_Turbo_attack");
			attack_state = true;
			b_boss_weapons->firing_position = b_w_position;
			b_boss_weapons->b_a_aiming = b_w_rotation;
			b_boss_weapons->b_a_Bullet_Fowrad = b_w_boss->boss_forward;
			if (firing_cound == 900) {
				firing_cound = 0;
				Rote = false;
				
			}
		}

		if (attack_ok == true)
		{

		}
	}
	if (b_w_player->GetGameEndState() == 1)
	{
		DeleteGO(this);
	}
	boss_Turbo_Render.Update();

	//b_w_rotation.SetRotationY(atan2(b_w_Fowrad.x, b_w_Fowrad.z));
	boss_Turbo_Render.SetPosition(b_w_position);
	/*boss_Turbo_Render.SetRotation(b_w_rotation);*/
	boss_Turbo_Render.Update();
	/*PlayerSearch();*/


	//if (turbo_HP <= 0.0f)
	//{
	//	drop_item = NewGO<Drop_item>(1, "drop_item");
	//	drop_item->Drop_position = b_w_position;
	//	drop_item->Drop_position.y += 50.0f;
	//	defeatState = true;
	//	DeleteGO(this);
	//}
}

void Boss_Turbo::Rotation() {
	
	if (Rote == false) {
		//エネミーからプレイヤーが入ってきたら追いかける。
		Vector3 toPlayer = b_w_player->GetPlayerPosition() - b_w_position;

		//プレイヤーとの距離を計算する。
		float distToPlayer = toPlayer.Length();
		//プレイヤーに向かって伸びるベクトルを正規化する。
		Vector3 toPlayerDir = toPlayer;
		toPlayerDir.Normalize();
		b_w_Fowrad = toPlayerDir;

		b_w_rotation.SetRotationY(atan2(b_w_Fowrad.x, b_w_Fowrad.z));
		boss_Turbo_Render.SetRotation(b_w_rotation);
	}
	else
	{
		
	}
	//firing_cound が 350のとき回転を止める

	
}

void Boss_Turbo::Move()
{
	//ここは丸パクリでOK
	Quaternion originRotation = b_w_boss->boss_rotation;
	b_w_position = b_w_boss->boss_position;
	Vector3 lp = b_w_localposition;
	originRotation.Multiply(lp);
	b_w_position += lp;
	b_w_rotation = originRotation;
	boss_Turbo_Render.SetPosition(b_w_position);
	//boss_Turbo_Render.SetRotation(b_w_rotation);
}

void Boss_Turbo::PlayerSearch()
{
	////エネミーからプレイヤーが入ってきたら追いかける。
	//Vector3 toPlayer = b_w_player->GetPlayerPosition() - b_w_position;

	////プレイヤーとの距離を計算する。
	//float distToPlayer = toPlayer.Length();
	////プレイヤーに向かって伸びるベクトルを正規化する。
	//Vector3 toPlayerDir = toPlayer;
	//toPlayerDir.Normalize();
	////エネミーの全方向とtoPlayerDirとの内積を計算する。
	//float t = toPlayerDir.Dot(b_w_Fowrad);
	////内積の結果をacos関数に渡して、m_enemyFowradとtoPlayerDirのなす角度を求める。
	//float angle = acos(t);

	//

	//b_w_Fowrad = toPlayerDir;

}

void Boss_Turbo::Render(RenderContext& rc)
{
	boss_Turbo_Render.Draw(rc);
}