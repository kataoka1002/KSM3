//ストライカーのパーツ。

#include "stdafx.h"
#include "Boss.h"
#include "Player.h"
#include "Game.h"
#include <time.h>
#include <stdlib.h>
#include "Customize_UI_ver2.h"
#include "Battle_ship_attack.h"
#include "Drop_item.h"
#include "Boss_Riser.h"
#include "Boss_Shovel.h"
#include "Boss_Drill.h"
#include "Boss_Cannon.h"
#include "Boss_Turbo.h"
#include "Result.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Boss_Saber.h"
#include"GameCamera.h"
#include "Left_arm_weapons.h"
#include "Left_leg_weapons.h"
#include "Right_arm_weapons.h"
#include "Right_leg_weapons.h"
#include "Shoulder_weapons.h"


Boss::Boss() 
{

	m_customizeUI = FindGO<Customize_UI_ver2>("customize_ui_ver2");
	//左腕
	if (m_customizeUI->m_leftArmWeapon != nullptr)
	{
		m_leftArm = m_customizeUI->m_leftArmWeapon;	//カスタマイズUIにあるポインタを渡してやる
	}
	//左足
	if (m_customizeUI->m_leftLegWeapon != nullptr)
	{
		m_leftLeg = m_customizeUI->m_leftLegWeapon;	//カスタマイズUIにあるポインタを渡してやる
	}
	//右腕
	if (m_customizeUI->m_rightArmWeapon != nullptr)
	{
		m_rightArm = m_customizeUI->m_rightArmWeapon;	//カスタマイズUIにあるポインタを渡してやる
	}
	//右足
	if (m_customizeUI->m_rightLegWeapon != nullptr)
	{
		m_rightLeg = m_customizeUI->m_rightLegWeapon;	//カスタマイズUIにあるポインタを渡してやる
	}
	//肩
	if (m_customizeUI->m_shoulderWeapon != nullptr)
	{
		m_shoulder = m_customizeUI->m_shoulderWeapon;	//カスタマイズUIにあるポインタを渡してやる
	}

	boss_game = FindGO<Game>("game");
	b_player = FindGO<Player>("player");
	//b_boss_riser = FindGO<Boss_Riser>("boss_riser");
	b_boss_riser = NewGO<Boss_Riser>(2, "boss_riser");
	b_boss_shovel = NewGO<Boss_Shovel>(2, "boss_shovel");
	b_boss_drill = NewGO<Boss_Drill>(2, "boss_drill");
	b_boss_cannon = NewGO<Boss_Cannon>(2, "boss_cannon");
	b_boss_turbo = NewGO<Boss_Turbo>(2, "boss_turbo");
	b_boss_saber = NewGO<Boss_Saber>(2, "boss_saber");
}

Boss::~Boss() 
{
	DeleteGO(boss_game);
	DeleteGO(b_boss_riser);//ライザーの武器削除。
	DeleteGO(b_boss_shovel);//ショベルの武器削除。
	DeleteGO(b_boss_drill);//ドリルの武器削除。
	DeleteGO(b_boss_cannon);//キャノンの武器削除。
	DeleteGO(b_boss_turbo);//ターボの武器削除。
	if (b_boss_saber != nullptr) {
		DeleteGO(b_boss_saber);
	}
}

bool Boss::Start()
{	
	m_bossHPSprite.Init("Assets/sprite/boss/bossGageNakami.dds",565.0f,48.0f);
	m_bossHPSprite.SetPosition({ -290.0f,360.0f,0.0f });
	m_bossHPSprite.SetPivot({ 0.0f,0.5f });
	m_bossHPSprite.Update();

	m_bossHPWakuSprite.Init("Assets/sprite/boss/bossGageWaku1.dds", 800.0f, 400.0f);
	m_bossHPWakuSprite.SetPosition({ -20.0f,360.0f,0.0f });
	m_bossHPWakuSprite.Update();

	m_bossHPWakuSprite2.Init("Assets/sprite/boss/bossGageWaku2.dds", 800.0f, 400.0f);
	m_bossHPWakuSprite2.SetPosition({ -20.0f,360.0f,0.0f });
	m_bossHPWakuSprite2.Update();


	boss_modelRender.Init("Assets/modelData/Boss_core.tkm");
	boss_rotation.SetRotationDegY(180.0f);
	boss_modelRender.SetRotation(boss_rotation);
	boss_modelRender.SetPosition(boss_position);
	//キャラクターコントローラーを初期化。
	boss_characterController.Init(
		750.0f,			//半径。
		40.0f,			//高さ。
		boss_position	//座標。
	);
	boss_modelRender.SetScale(Scale);
	boss_modelRender.Update();
	return true;
}

void Boss::Update()
{
	Damage();
	SetHPScale();
	if (Boss_efecount % 1000 == 0) {
		m_BossEffect = NewGO<EffectEmitter>(0);
		m_BossEffect->Init(enBoss_Magic_Circle);
		m_BossEffect->SetScale({ Efect_scale,Efect_scale,Efect_scale });
		Vector3 efeLP = { 0.0f,680.0f,2000.0f };
		efeLP += boss_position;
		m_BossEffect->SetPosition(efeLP);
		m_BossEffect->Play();
	}
	if (boss_attack_count == 500) {
		switch (Boss_attack_kind)
		{
		case 1:
			Boss_attack_efe = NewGO<EffectEmitter>(0);
			Boss_attack_efe->Init(en_Boss_attack);
			Boss_attack_efe->SetScale({ 35.0f, 35.0f, 35.0f });
			attack_efe_LP += boss_position;
			Boss_attack_efe->SetPosition(attack_efe_LP);
			Boss_attack_efe->Play();
			break;
		default:
			break;
		}
			
		
	}
	if (boss_attack_count >= 500 && boss_attack_count < 520) {
		switch (Boss_attack_kind)
		{
		case 1:
			attack_efe_LP.y -= 200.0f;
			Boss_attack_efe->SetPosition(attack_efe_LP);
			Player_Damage(1, false);
			break;
		default:
			break;
		}
	}
	switch (Boss_attack_kind)
	{
	case 1:
		if (boss_attack_count == 520) {
			Player_Damage(1, true);
			attack_efe_LP = { 0.0f,1000.0f,0.0f };
			boss_attack_count = 0;
		}
	default:
		break;
	}
	if (boss_attack_count == 400&&Boss_attack_kind==1) {
		Boss_attack_Explosion_efe = NewGO<EffectEmitter>(0);
		Boss_attack_Explosion_efe->Init(en_Boss_attack_Explosion);
		Boss_attack_Explosion_efe->SetScale({ 50.0f, 50.0f, 50.0f });
		Boss_attack_Explosion_efe->SetPosition(boss_position);
		Boss_attack_Explosion_efe->Play();
		m_battleShipGunTyakutiSE = NewGO<SoundSource>(0);			//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
		m_battleShipGunTyakutiSE->Init(enButtleShipTyakudan);		//初期化
		m_battleShipGunTyakutiSE->SetVolume(2.0f * boss_game->GetSEVol());	//音量調整
		m_battleShipGunTyakutiSE->Play(false);
	}



	Boss_efecount++;
	boss_attack_count++;
	boss_time += g_gameTime->GetFrameDeltaTime();
	boss_time_score += g_gameTime->GetFrameDeltaTime();
	if (boss_time_score >= 1.0f)
	{
		time_score -= 150;
		boss_time_score = 0.0f;
	}

	
	boss_modelRender.Update();
}

void Boss::Player_Damage(int boss_damage_kind, bool Landing_state) {
	if (Landing_state == false) {
		switch (boss_damage_kind)
		{
			case 1:
				//---------------------------------------------------------------------------------------------------
				if (b_player != nullptr)	//プレイヤーの情報が入っているなら
				{
					//弾とプレイヤーの距離を測る
					Vector3 diffPlayer = attack_efe_LP - Vector3{ b_player->GetPlayerPosition().x, b_player->GetPlayerPosition().y + 50.0f, b_player->GetPlayerPosition().z };

					//武器によってダメージを変える

						//距離を測り一定以下なら体力減少
					if (diffPlayer.Length() <= 2000.0f) //ダメージが入る範囲
					{
						b_player->ApplyDamage(1.0f);

					}

				}



				//---------------------------------------------------------------------------------------------------

				//---------------------------------------------------------------------------------------------------
				if (m_leftArm != nullptr)	//左腕に情報が入っているなら
				{
					//弾と左腕の距離を測る
					Vector3 diffLeftArm = attack_efe_LP - m_leftArm->GetPosition();

					//武器によってダメージを変える

						//距離を測り一定以下なら体力減少
					if (diffLeftArm.Length() <= 2000.0f) //ダメージが入る範囲
					{
						m_leftArm->ApplyDamage(1.0f);

					}
				}
				//---------------------------------------------------------------------------------------------------

				//---------------------------------------------------------------------------------------------------
				if (m_leftLeg != nullptr)	//左足に情報が入っているなら
				{
					//弾と左腕の距離を測る
					Vector3 diffLeftLeg = attack_efe_LP - m_leftLeg->GetPosition();

					//武器によってダメージを変える

						//距離を測り一定以下なら体力減少
					if (diffLeftLeg.Length() <= 2000.0f) //ダメージが入る範囲
					{
						m_leftLeg->ApplyDamage(1.0f);

					}

				}
				//---------------------------------------------------------------------------------------------------

				//---------------------------------------------------------------------------------------------------
				if (m_rightArm != nullptr)	//右手に情報が入っているなら
				{
					//弾と左腕の距離を測る
					Vector3 diffRightArm = attack_efe_LP - m_rightArm->GetPosition();

					//武器によってダメージを変える

						//距離を測り一定以下なら体力減少
					if (diffRightArm.Length() <= 2000.0f) //ダメージが入る範囲
					{
						m_rightArm->ApplyDamage(1.0f);

					}

				}
				//---------------------------------------------------------------------------------------------------

				//---------------------------------------------------------------------------------------------------
				if (m_rightLeg != nullptr)	//右足に情報が入っているなら
				{
					//弾と左腕の距離を測る
					Vector3 diffRightLeg = attack_efe_LP - m_rightLeg->GetPosition();

					//武器によってダメージを変える

						//距離を測り一定以下なら体力減少
					if (diffRightLeg.Length() <= 2000.0f) //ダメージが入る範囲
					{
						m_rightLeg->ApplyDamage(1.0f);

					}

				}
				//---------------------------------------------------------------------------------------------------

				//---------------------------------------------------------------------------------------------------
				if (m_shoulder != nullptr)	//肩に情報が入っているなら
				{
					//弾と左腕の距離を測る
					Vector3 diffShoulder = attack_efe_LP - m_shoulder->GetPosition();

					//武器によってダメージを変える

						//距離を測り一定以下なら体力減少
					if (diffShoulder.Length() <= 2000.0f) //ダメージが入る範囲
					{
						m_shoulder->ApplyDamage(1.0f);

					}

				}
				//---------------------------------------------------------------------------------------------------
				break;
		default:
			break;
		}
	}
	else {
		switch (boss_damage_kind)
		{
		case 1:
			//---------------------------------------------------------------------------------------------------
			if (b_player != nullptr)	//プレイヤーの情報が入っているなら
			{
				//弾とプレイヤーの距離を測る
				Vector3 diffPlayer = attack_efe_LP - Vector3{ b_player->GetPlayerPosition().x, b_player->GetPlayerPosition().y + 50.0f, b_player->GetPlayerPosition().z };

				//武器によってダメージを変える

					//距離を測り一定以下なら体力減少
				if (diffPlayer.Length() <= 2500.0f) //ダメージが入る範囲
				{
					b_player->ApplyDamage(100.0f);

				}

			}



			//---------------------------------------------------------------------------------------------------

			//---------------------------------------------------------------------------------------------------
			if (m_leftArm != nullptr)	//左腕に情報が入っているなら
			{
				//弾と左腕の距離を測る
				Vector3 diffLeftArm = attack_efe_LP - m_leftArm->GetPosition();

				//武器によってダメージを変える

					//距離を測り一定以下なら体力減少
				if (diffLeftArm.Length() <= 2500.0f) //ダメージが入る範囲
				{
					m_leftArm->ApplyDamage(100.0f);

				}
			}
			//---------------------------------------------------------------------------------------------------

			//---------------------------------------------------------------------------------------------------
			if (m_leftLeg != nullptr)	//左足に情報が入っているなら
			{
				//弾と左腕の距離を測る
				Vector3 diffLeftLeg = attack_efe_LP - m_leftLeg->GetPosition();

				//武器によってダメージを変える

					//距離を測り一定以下なら体力減少
				if (diffLeftLeg.Length() <= 2500.0f) //ダメージが入る範囲
				{
					m_leftLeg->ApplyDamage(100.0f);

				}

			}
			//---------------------------------------------------------------------------------------------------

			//---------------------------------------------------------------------------------------------------
			if (m_rightArm != nullptr)	//右手に情報が入っているなら
			{
				//弾と左腕の距離を測る
				Vector3 diffRightArm = attack_efe_LP - m_rightArm->GetPosition();

				//武器によってダメージを変える

					//距離を測り一定以下なら体力減少
				if (diffRightArm.Length() <= 2500.0f) //ダメージが入る範囲
				{
					m_rightArm->ApplyDamage(100.0f);

				}

			}
			//---------------------------------------------------------------------------------------------------

			//---------------------------------------------------------------------------------------------------
			if (m_rightLeg != nullptr)	//右足に情報が入っているなら
			{
				//弾と左腕の距離を測る
				Vector3 diffRightLeg = attack_efe_LP - m_rightLeg->GetPosition();

				//武器によってダメージを変える

					//距離を測り一定以下なら体力減少
				if (diffRightLeg.Length() <= 2500.0f) //ダメージが入る範囲
				{
					m_rightLeg->ApplyDamage(100.0f);

				}

			}
			//---------------------------------------------------------------------------------------------------

			//---------------------------------------------------------------------------------------------------
			if (m_shoulder != nullptr)	//肩に情報が入っているなら
			{
				//弾と左腕の距離を測る
				Vector3 diffShoulder = attack_efe_LP - m_shoulder->GetPosition();

				//武器によってダメージを変える

					//距離を測り一定以下なら体力減少
				if (diffShoulder.Length() <= 2500.0f) //ダメージが入る範囲
				{
					m_shoulder->ApplyDamage(100.0f);

				}

			}
			//---------------------------------------------------------------------------------------------------
			break;
		default:
			break;
		}
	}
}

void Boss::PlayerSearch()
{
	//エネミーからプレイヤーが入ってきたら追いかける
	Vector3 toPlayer = b_player->GetPlayerPosition() - boss_position;

	//プレイヤーとの距離を計算する
	float distToPlayer = toPlayer.Length();
	//プレイヤーに向かって伸びるベクトルを正規化する
	Vector3 toPlayerDir = toPlayer;
	toPlayerDir.Normalize();
	//エネミーの前方方向とtoPlayerDirとの内積を計算する
	float t = toPlayerDir.Dot(boss_forward);
	//内積の結果をacos関数に渡して、m_enemyFowradとtoPlayerDirのなす角度を求める。
	float angle = acos(t);

	if (fabsf(angle) > Math::DegToRad(45.0f))
	{
		boss_rotation.SetRotationY(atan2(boss_forward.x, boss_forward.z));
		boss_modelRender.SetPosition(boss_position);
		boss_modelRender.SetRotation(boss_rotation);
		boss_modelRender.Update();
	}
	if (g_pad[0]->IsTrigger(enButtonA)) {
		Boss_attack = true;
	}


	if (Boss_attack == true) {

		if (Boss_Rotation_count < 10) {
			boss_rotation.AddRotationDegY((angle * M_PI / 180.0)/10);
		}
		if (Boss_Rotation_count >= 10 && Boss_Rotation_count < 15) {
			movespeed += toPlayerDir *100.0f;

			boss_position = boss_characterController.Execute(movespeed, 1.0f / 60.0f);
		}
		if (Boss_Rotation_count == 15) {
			Boss_attack = false;
		}
		Boss_Rotation_count++;
	}

	if (fabsf(angle) < Math::DegToRad(45.0f)) {
		b_boss_riser->attack_ok = true;
		b_boss_cannon->attack_ok = true;
		b_boss_drill->attack_ok = true;
		b_boss_shovel->attack_ok = true;
		b_boss_turbo->attack_ok = true;
	}
	else {
		b_boss_riser->attack_ok = false;
		b_boss_cannon->attack_ok = false;
		b_boss_drill->attack_ok = false;
		b_boss_shovel->attack_ok = false;
		b_boss_turbo->attack_ok = false;
	}

	//敵キャラの前方方向を更新する
	boss_forward = toPlayerDir;
	// 敵の前方方向を使って、回転クォータニオンを計算する。
	boss_rotation.SetRotationY(atan2(boss_forward.x, boss_forward.z));
	boss_modelRender.SetPosition(boss_position);
	boss_modelRender.SetRotation(boss_rotation);
	boss_modelRender.Update();
}

void Boss::Move()
 {
	//エネミーからプレイヤーに向かうベクトルを計算する
	Vector3 toPlayer = b_player->GetPlayerPosition() - boss_position;
	//ベクトルを正規化する。
	toPlayer.Normalize();
	//移動速度を設定する。
	boss_moveSpeed = toPlayer * 200.0f;
	//エネミーを移動させる
	boss_position = boss_characterController.Execute(boss_moveSpeed, g_gameTime->GetFrameDeltaTime());
	Vector3 modelPosition = boss_position;
}

void Boss::Damage()
{
	//ボス即死コード。
	if (g_pad[0]->IsPress(enButtonY))
	{
		boss_HP = 0.0f;
	}
	
	//やっつけたらリザルト画面へGO!!
	if (boss_HP <= 0.0f)
	{
		
		b_player->SetGameState(7);
		boss_HP = 0.0f;
		if (Death_count >= 0 && Death_count < 20) {
			if (b_boss_riser != nullptr) {
				b_boss_riser->scale -= 0.6f;
				b_boss_riser->boss_Riser_Render.SetScale(b_boss_riser->scale);
			}
			if (b_boss_drill != nullptr) {
				b_boss_drill->Drill_scale -= 1.02f;
				b_boss_drill->boss_Drill_Render.SetScale(b_boss_drill->Drill_scale);
			}
			if (b_boss_cannon != nullptr) {
				b_boss_cannon->scale -= 0.75f;
				b_boss_cannon->boss_Cannon_Render.SetScale(b_boss_cannon->scale);
			}
			if (b_boss_saber != nullptr) {
				b_boss_saber->scale -= 0.75f;
				b_boss_saber->boss_Cannon_Render.SetScale(b_boss_saber->scale);
			}
			if (b_boss_shovel != nullptr) {
				b_boss_shovel->scale -= 0.75f;
				b_boss_shovel->boss_Shovel_Render.SetScale(b_boss_shovel->scale);
			}
			if (b_boss_turbo != nullptr) {
				b_boss_turbo->scale -= 0.651f;
				b_boss_turbo->boss_Turbo_Render.SetScale(b_boss_riser->scale);
			}
		}
		if (Death_count == 0) {
			GameCamera* m_camera = FindGO<GameCamera>("gamecamera");
			m_camera->VibFinalFlag = true;
			if (b_boss_riser != nullptr) {
				
				Explosion_Another = NewGO<EffectEmitter>(0);
				Explosion_Another->Init(enBoss_Explosion);
				Explosion_Another->SetScale({ 70.0f,70.0f,70.0f });
				
				//efeLP += b_w_position;
				Explosion_Another->SetPosition(b_boss_riser->b_w_position);
				Explosion_Another->SetRotation(b_boss_riser->b_w_rotation);
				Explosion_Another->Play();
			}
			if (b_boss_drill != nullptr) {
				Explosion_Another = NewGO<EffectEmitter>(0);
				Explosion_Another->Init(enBoss_Explosion);
				Explosion_Another->SetScale({ 70.0f,70.0f,70.0f });
				
				//efeLP += b_w_position;
				Explosion_Another->SetPosition(b_boss_drill->b_w_position);
				Explosion_Another->SetRotation(b_boss_drill->b_w_rotation);
				Explosion_Another->Play();
			}
			if (b_boss_saber != nullptr) {
				Explosion_Another = NewGO<EffectEmitter>(0);
				Explosion_Another->Init(enBoss_Explosion);
				Explosion_Another->SetScale({ 70.0f,70.0f,70.0f });
				
				//efeLP += b_w_position;
				Explosion_Another->SetPosition(b_boss_saber->b_w_position);
				Explosion_Another->SetRotation(b_boss_saber->b_w_rotation);
				Explosion_Another->Play();
			}
			if (b_boss_shovel != nullptr) {
				Explosion_Another = NewGO<EffectEmitter>(0);
				Explosion_Another->Init(enBoss_Explosion);
				Explosion_Another->SetScale({ 70.0f,70.0f,70.0f });
				
				//efeLP += b_w_position;
				Explosion_Another->SetPosition(b_boss_shovel->b_w_position);
				Explosion_Another->SetRotation(b_boss_shovel->b_w_rotation);
				Explosion_Another->Play();
			}
			if (b_boss_turbo != nullptr) {
				Explosion_Another = NewGO<EffectEmitter>(0);
				Explosion_Another->Init(enBoss_Explosion);
				Explosion_Another->SetScale({ 70.0f,70.0f,70.0f });
				
				//efeLP += b_w_position;
				Explosion_Another->SetPosition(b_boss_turbo->b_w_position);
				Explosion_Another->SetRotation(b_boss_turbo->b_w_rotation);
				Explosion_Another->Play();
			}
			
		}
		if (Death_count == 60) {
			Boss_Explosion = NewGO<EffectEmitter>(0);
			Boss_Explosion->Init(enBoss_Death);
			Boss_Explosion->SetScale({ 70.0f,70.0f,70.0f });
			
			//efeLP += b_w_position;
			Boss_Explosion->SetPosition(boss_position);
			Boss_Explosion->SetRotation(boss_rotation);
			Boss_Explosion->Play();
		}
		if (Death_count >= 60 && Death_count < 120) {
			
			Scale -= 0.25f;
			boss_modelRender.SetScale(Scale);
			
		}
		if (Death_count == 120) {
			GameCamera* m_camera = FindGO<GameCamera>("gamecamera");
			m_camera->VibBigFlag = true;
			Boss_Explosion = NewGO<EffectEmitter>(0);
			Boss_Explosion->Init(enBoss_Death2);
			Boss_Explosion->SetScale({ 70.0f,70.0f,70.0f });
			
			//efeLP += b_w_position;
			Boss_Explosion->SetPosition(boss_position);
			Boss_Explosion->SetRotation(boss_rotation);
			Boss_Explosion->Play();
		}
		if (Death_count==440) {
			b_player->SetGameState(2);
			result = NewGO<Result>(1, "result");
			result->SE_volume = boss_game->GetSEVol();
			result->BGM_volume = boss_game->GetBGMVol();

			result->minute = (int)boss_time / 60;
			result->sec = (int)boss_time % 60;
			//b_player->m_bossSurvival = false;	//ボスが生きているかをプレーヤーに教える
			//エネミーがどの武器を持っていたか取得し、ドロップするアイテムを決める
			//ココもいらない?
			if (defeat_state == true)
			{
				drop_item->drop_kinds = b_boss_riser->set_weapons;
				drop_item->drop_kinds = b_boss_shovel->set_weapons;
				drop_item->drop_kinds = b_boss_drill->set_weapons;
				drop_item->drop_kinds = b_boss_cannon->set_weapons;
				drop_item->drop_kinds = b_boss_turbo->set_weapons;
			}


			DeleteGO(this);

		}
		Death_count++;
		
	}
}

void Boss::SetHPScale()
{
	float m_scaleX = boss_HP * (1.0f / BOSS_HP_MAX);	//時間が減るほどゲージが減っていく

	max(0, m_scaleX);	//スケールは0以下にならない

	m_bossHPSprite.SetScale({ m_scaleX,1.0f,1.0f });
	m_bossHPSprite.Update();
}

void Boss::Render(RenderContext& rc)
{
	//モデルの描画。
	boss_modelRender.Draw(rc);
	if (b_player->GetPlayerHP() > 0) {
		m_bossHPSprite.Draw(rc);
		m_bossHPWakuSprite.Draw(rc);
		m_bossHPWakuSprite2.Draw(rc);
	}
}
