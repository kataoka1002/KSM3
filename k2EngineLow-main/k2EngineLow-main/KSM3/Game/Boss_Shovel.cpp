//ショベルのパーツ。

#include "stdafx.h"
#include "Boss_Shovel.h"
#include "Player.h"
#include "Boss.h"
#include "Boss_Shovel_attack.h"
#include "Drop_item.h"
#include "Game.h"
#include "Left_arm_weapons.h"
#include "Left_leg_weapons.h"
#include "Right_arm_weapons.h"
#include "Right_leg_weapons.h"
#include "Shoulder_weapons.h"

Boss_Shovel::Boss_Shovel()
{
	m_game = FindGO<Game>("game");
	b_w_player = FindGO<Player>("player");
}

Boss_Shovel::~Boss_Shovel()
{
	DeleteGO(b_boss_weapons);
	/*if (defeatState == true)
	{
		drop_item->drop_kinds = set_weapons;
	}*/
}

bool Boss_Shovel::Start()
{
	m_animationClip[enAnimationClip_Idle].Load("Assets/animData/Boss_shovel_idol01.tka");
	m_animationClip[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClip[enAnimationClip_Idle2].Load("Assets/animData/Boss_shovel_idol02.tka");
	m_animationClip[enAnimationClip_Idle2].SetLoopFlag(true);
	m_animationClip[enAnimationClip_Shock_Ground].Load("Assets/animData/Boss_shovel_crash.tka");
	m_animationClip[enAnimationClip_Shock_Ground].SetLoopFlag(true);
	//初期化
	boss_Shovel_Render.Init("Assets/modelData/Boss_shovel4.tkm", true, true , m_animationClip, enAnimationClip_Num, enModelUpAxisZ);
	//boss_Shovel_Render.Init("Assets/modelData/unityChan.tkm", true,true,m_animationClip, enAnimationClip_Num, enModelUpAxisY);
	if (defeatState == true)
	{
		drop_item->drop_kinds = set_weapons;
	}
	
	return true;
}

void Boss_Shovel::Setup()
{b_w_boss = FindGO<Boss>("boss");
	set_weapons = 1;
	
	if (set_weapons == 1)
	{
		//boss_Shovel_Render.Init("Assets/modelData/Boss_shovel.tkm");
		boss_Shovel_Render.Update();
	}

	//キャラコン。
	//boss_riser_characterContller.Init(
	//	450.0f,			//半径。
	//	40.0f,			//高さ。
	//	b_w_position	//座標。
	//);
	//boss_Riser_Render.SetRotation(b_w_rotation);
	//boss_Riser_Render.SetPosition(b_w_position);
	boss_Shovel_Render.SetScale(scale);
	boss_Shovel_Render.Update();
}

void Boss_Shovel::Update()
{
	
	
	if (fast == 0)
	{
		Setup();
		
	}
	fast++;
	if (b_w_player->game_state == 0 && fast != 0)
	{
		if (fast == 400) {
			m_Shovel_roar_SE = NewGO<SoundSource>(0);			//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
			m_Shovel_roar_SE->Init(enBoss_Shovel_roar);		//初期化
			m_Shovel_roar_SE->SetVolume(2.0f * m_game->GetSEVol());	//音量調整
			m_Shovel_roar_SE->Play(false);
		}
		if (fast == 1300) {
			m_Shovel_roar_SE = NewGO<SoundSource>(0);			//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
			m_Shovel_roar_SE->Init(enBoss_Shovel_roar);		//初期化
			m_Shovel_roar_SE->SetVolume(2.0f * m_game->GetSEVol());	//音量調整
			m_Shovel_roar_SE->Play(false);
		}
		if (fast >=270&&fast<630) {
			boss_Shovel_Render.PlayAnimation(enAnimationClip_Idle2,0.5f);
		}
		
		else if (fast >= 1170 && fast < 1500) {
			if (fast == 1400) {

				m_Shovel_shock_SE = NewGO<SoundSource>(0);			//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
				m_Shovel_shock_SE->Init(en_Boss_Shovel_shock);		//初期化
				m_Shovel_shock_SE->SetVolume(2.0f * m_game->GetSEVol());	//音量調整
				m_Shovel_shock_SE->Play(false);

				shovel_shock = NewGO<EffectEmitter>(0);
				shovel_shock->Init(enBoss_Shovel_shock);
				shovel_shock->SetScale({ 70.0f,70.0f,70.0f });
				//efeLP += b_w_position;
				shovel_shock->SetPosition(b_w_position+ shock_efe_lpos);
				shovel_shock->SetRotation(b_w_rotation);
				shovel_shock->Play();
				Damage(0);
			}
			boss_Shovel_Render.PlayAnimation(enAnimationClip_Shock_Ground, 0.5f);
		}
		else if (fast == 1680) {
			
			DeleteGO(shovel_shock);
			shovel_shock = nullptr;
			fast = 0;
		}
		else {
			boss_Shovel_Render.PlayAnimation(enAnimationClip_Idle,0.5f);
		}
		
		Move();
		//if (attack_ok == true)
		//{
		//	firing_cound++;//攻撃のタイミングの計算。
		//	if (firing_cound % 108 == 0)
		//	{
		//		b_boss_weapons = NewGO<Boss_Shovel_attack>(1, "boss_Shovel_attack");
		//		attack_state = true;
		//		b_boss_weapons->firing_position = b_w_position;
		//		b_boss_weapons->b_a_aiming = b_w_boss->boss_rotation;
		//		b_boss_weapons->b_a_Bullet_Fowrad = b_w_boss->boss_forward;
		//	}
		//}
	}
	if (b_w_player->game_end_state == 1)
	{
		DeleteGO(this);
	}

	switch (shovelState)
	{
	case 0:
		
		break;
	}

	
	boss_Shovel_Render.Update();

	if (shovel_HP<=0.0f)
	{
		/*drop_item = NewGO<Drop_item>(1, "drop_item");
		drop_item->Drop_position.y += 50.0f;
		defeatState = true;*/
		DeleteGO(this);
	}
}

void Boss_Shovel::Move()
{
	//ここは丸パクリでOK
	Quaternion originRotation = b_w_boss->boss_rotation;
	b_w_position = b_w_boss->boss_position;
	Vector3 lp = b_w_localposition;
	originRotation.Multiply(lp);
	b_w_position += lp;
	b_w_rotation = originRotation;
	boss_Shovel_Render.SetPosition(b_w_position);
	boss_Shovel_Render.SetRotation(b_w_rotation);
}

void Boss_Shovel::Damage(int attack_Num) {
	if (attack_Num == 0) {
		//---------------------------------------------------------------------------------------------------
		if (b_w_player != nullptr)	//プレイヤーの情報が入っているなら
		{
			//弾とプレイヤーの距離を測る
			Vector3 diffPlayer = b_w_position + shock_efe_lpos - Vector3{ b_w_player->player_position.x, b_w_player->player_position.y + 50.0f, b_w_player->player_position.z };

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffPlayer.Length() <= 2000.0f) //ダメージが入る範囲
			{
				b_w_player->m_playerHP -= 10.0f;
				

			}

		}



		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_leftArm != nullptr)	//左腕に情報が入っているなら
		{
			//弾と左腕の距離を測る
			Vector3 diffLeftArm = b_w_position + shock_efe_lpos - m_leftArm->GetPosition();

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffLeftArm.Length() <= 2000.0f) //ダメージが入る範囲
			{
				m_leftArm->ApplyDamage(10.0f);
				

			}
		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_leftLeg != nullptr)	//左足に情報が入っているなら
		{
			//弾と左腕の距離を測る
			Vector3 diffLeftLeg = b_w_position + shock_efe_lpos - m_leftLeg->GetPosition();

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffLeftLeg.Length() <= 2000.0f) //ダメージが入る範囲
			{
				m_leftLeg->ApplyDamage(10.0f);
				

			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_rightArm != nullptr)	//右手に情報が入っているなら
		{
			//弾と左腕の距離を測る
			Vector3 diffRightArm = b_w_position + shock_efe_lpos - m_rightArm->GetPosition();

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffRightArm.Length() <= 2000.0f) //ダメージが入る範囲
			{
				m_rightArm->ApplyDamage(10.0f);
				

			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_rightLeg != nullptr)	//右足に情報が入っているなら
		{
			//弾と左腕の距離を測る
			Vector3 diffRightLeg = b_w_position + shock_efe_lpos - m_rightLeg->GetPosition();

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffRightLeg.Length() <= 2000.0f) //ダメージが入る範囲
			{
				m_rightLeg->ApplyDamage(10.0f);
				

			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_shoulder != nullptr)	//肩に情報が入っているなら
		{
			//弾と左腕の距離を測る
			Vector3 diffShoulder = b_w_position + shock_efe_lpos - m_shoulder->GetPosition();

			//武器によってダメージを変える

				//距離を測り一定以下なら体力減少
			if (diffShoulder.Length() <= 2000.0f) //ダメージが入る範囲
			{
				m_shoulder->ApplyDamage(10.0f);
				Effect();

			}

		}
		//---------------------------------------------------------------------------------------------------
	}
}

void Boss_Shovel::PlayerSearch()
{
	////エネミーからプレイヤーが入ってきたら追いかける。
	//Vector3 toPlayer = b_w_player->player_position - b_w_position;

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

void Boss_Shovel::Render(RenderContext& rc)
{
	boss_Shovel_Render.Draw(rc);
}