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
	if (m_customizeUI->GetLeftArmWeapon() != nullptr)
	{
		m_leftArm = m_customizeUI->GetLeftArmWeapon();	//カスタマイズUIにあるポインタを渡してやる
	}
	//左足
	if (m_customizeUI->GetLeftLegWeapon() != nullptr)
	{
		m_leftLeg = m_customizeUI->GetLeftLegWeapon();	//カスタマイズUIにあるポインタを渡してやる
	}
	//右腕
	if (m_customizeUI->GetRightArmWeapon() != nullptr)
	{
		m_rightArm = m_customizeUI->GetRightArmWeapon();	//カスタマイズUIにあるポインタを渡してやる
	}
	//右足
	if (m_customizeUI->GetLeftLegWeapon() != nullptr)
	{
		m_rightLeg = m_customizeUI->GetRightLegWeapon();	//カスタマイズUIにあるポインタを渡してやる
	}
	//肩
	if (m_customizeUI->GetShoulderWeapon() != nullptr)
	{
		m_shoulder = m_customizeUI->GetShoulderWeapon();	//カスタマイズUIにあるポインタを渡してやる
	}

	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");
	//b_boss_riser = FindGO<Boss_Riser>("boss_riser");
	m_bossRiser = NewGO<Boss_Riser>(2, "boss_riser");
	m_bossShovel = NewGO<Boss_Shovel>(2, "boss_shovel");
	m_bossDrill = NewGO<Boss_Drill>(2, "boss_drill");
	m_bossCannon = NewGO<Boss_Cannon>(2, "boss_cannon");
	m_bossTurbo = NewGO<Boss_Turbo>(2, "boss_turbo");
	m_bossSaber = NewGO<Boss_Saber>(2, "boss_saber");
}

Boss::~Boss() 
{
	DeleteGO(m_game);
	DeleteGO(m_bossRiser);//ライザーの武器削除。
	DeleteGO(m_bossShovel);//ショベルの武器削除。
	DeleteGO(m_bossDrill);//ドリルの武器削除。
	DeleteGO(m_bossCannon);//キャノンの武器削除。
	DeleteGO(m_bossTurbo);//ターボの武器削除。
	if (m_bossSaber != nullptr) {
		DeleteGO(m_bossSaber);
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


	m_modelRender.Init("Assets/modelData/Boss_core.tkm");
	m_rotation.SetRotationDegY(180.0f);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetPosition(m_position);
	//キャラクターコントローラーを初期化。
	m_characterController.Init(
		750.0f,			//半径。
		40.0f,			//高さ。
		m_position	//座標。
	);
	m_modelRender.SetScale(m_scale);
	m_modelRender.Update();
	return true;
}

void Boss::Update()
{
	Damage();
	SetHPScale();
	if (m_bossEfeCount % 1000 == 0) {
		m_BossEffect = NewGO<EffectEmitter>(0);
		m_BossEffect->Init(enBoss_Magic_Circle);
		m_BossEffect->SetScale({ m_efectScale,m_efectScale,m_efectScale });
		Vector3 m_effectLocalPos = { 0.0f,680.0f,2000.0f };
		m_effectLocalPos += m_position;
		m_BossEffect->SetPosition(m_effectLocalPos);
		m_BossEffect->Play();
	}
	if (m_bossAttackCount == 500) {
		switch (m_bossAttackKind)
		{
		case 1:
			m_bossAttackEfe = NewGO<EffectEmitter>(0);
			m_bossAttackEfe->Init(en_Boss_attack);
			m_bossAttackEfe->SetScale({ 35.0f, 35.0f, 35.0f });
			m_attackEfeLP += m_position;
			m_bossAttackEfe->SetPosition(m_attackEfeLP);
			m_bossAttackEfe->Play();
			break;
		default:
			break;
		}
			
		
	}
	if (m_bossAttackCount >= 500 && m_bossAttackCount < 520) {
		switch (m_bossAttackKind)
		{
		case 1:
			m_attackEfeLP.y -= 200.0f;
			m_bossAttackEfe->SetPosition(m_attackEfeLP);
			Player_Damage(1, false);
			break;
		default:
			break;
		}
	}
	switch (m_bossAttackKind)
	{
	case 1:
		if (m_bossAttackCount == 520) {
			Player_Damage(1, true);
			m_attackEfeLP = { 0.0f,1000.0f,0.0f };
			m_bossAttackCount = 0;
		}
	default:
		break;
	}
	if (m_bossAttackCount == 400&&m_bossAttackKind==1) {
		m_bossAttackExplosionEfe = NewGO<EffectEmitter>(0);
		m_bossAttackExplosionEfe->Init(en_Boss_attack_Explosion);
		m_bossAttackExplosionEfe->SetScale({ 50.0f, 50.0f, 50.0f });
		m_bossAttackExplosionEfe->SetPosition(m_position);
		m_bossAttackExplosionEfe->Play();
		m_battleShipGunTyakutiSE = NewGO<SoundSource>(0);			//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
		m_battleShipGunTyakutiSE->Init(enButtleShipTyakudan);		//初期化
		m_battleShipGunTyakutiSE->SetVolume(2.0f * m_game->GetSEVol());	//音量調整
		m_battleShipGunTyakutiSE->Play(false);
	}



	m_bossEfeCount++;
	m_bossAttackCount++;
	m_bossTime += g_gameTime->GetFrameDeltaTime();
	m_bossTimeScore += g_gameTime->GetFrameDeltaTime();
	if (m_bossTimeScore >= 1.0f)
	{
		m_timeScore -= 150;
		m_bossTimeScore = 0.0f;
	}

	
	m_modelRender.Update();
}

void Boss::Player_Damage(int boss_damage_kind, bool Landing_state) {
	if (Landing_state == false) {
		switch (boss_damage_kind)
		{
			case 1:
				//---------------------------------------------------------------------------------------------------
				if (m_player != nullptr)	//プレイヤーの情報が入っているなら
				{
					//弾とプレイヤーの距離を測る
					Vector3 diffPlayer = m_attackEfeLP - Vector3{ m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y + 50.0f, m_player->GetPlayerPosition().z };

					//武器によってダメージを変える

						//距離を測り一定以下なら体力減少
					if (diffPlayer.Length() <= 2000.0f) //ダメージが入る範囲
					{
						m_player->ApplyDamage(1.0f);

					}

				}



				//---------------------------------------------------------------------------------------------------

				//---------------------------------------------------------------------------------------------------
				if (m_leftArm != nullptr)	//左腕に情報が入っているなら
				{
					//弾と左腕の距離を測る
					Vector3 diffLeftArm = m_attackEfeLP - m_leftArm->GetPosition();

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
					Vector3 diffLeftLeg = m_attackEfeLP - m_leftLeg->GetPosition();

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
					Vector3 diffRightArm = m_attackEfeLP - m_rightArm->GetPosition();

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
					Vector3 diffRightLeg = m_attackEfeLP - m_rightLeg->GetPosition();

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
					Vector3 diffShoulder = m_attackEfeLP - m_shoulder->GetPosition();

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
			if (m_player != nullptr)	//プレイヤーの情報が入っているなら
			{
				//弾とプレイヤーの距離を測る
				Vector3 diffPlayer = m_attackEfeLP - Vector3{ m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y + 50.0f, m_player->GetPlayerPosition().z };

				//武器によってダメージを変える

					//距離を測り一定以下なら体力減少
				if (diffPlayer.Length() <= 2500.0f) //ダメージが入る範囲
				{
					m_player->ApplyDamage(100.0f);

				}

			}



			//---------------------------------------------------------------------------------------------------

			//---------------------------------------------------------------------------------------------------
			if (m_leftArm != nullptr)	//左腕に情報が入っているなら
			{
				//弾と左腕の距離を測る
				Vector3 diffLeftArm = m_attackEfeLP - m_leftArm->GetPosition();

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
				Vector3 diffLeftLeg = m_attackEfeLP - m_leftLeg->GetPosition();

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
				Vector3 diffRightArm = m_attackEfeLP - m_rightArm->GetPosition();

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
				Vector3 diffRightLeg = m_attackEfeLP - m_rightLeg->GetPosition();

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
				Vector3 diffShoulder = m_attackEfeLP - m_shoulder->GetPosition();

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
	Vector3 toPlayer = m_player->GetPlayerPosition() - m_position;

	//プレイヤーとの距離を計算する
	float distToPlayer = toPlayer.Length();
	//プレイヤーに向かって伸びるベクトルを正規化する
	Vector3 toPlayerDir = toPlayer;
	toPlayerDir.Normalize();
	//エネミーの前方方向とtoPlayerDirとの内積を計算する
	float t = toPlayerDir.Dot(m_forward);
	//内積の結果をacos関数に渡して、m_enemyFowradとtoPlayerDirのなす角度を求める。
	float angle = acos(t);

	if (fabsf(angle) > Math::DegToRad(45.0f))
	{
		m_rotation.SetRotationY(atan2(m_forward.x, m_forward.z));
		m_modelRender.SetPosition(m_position);
		m_modelRender.SetRotation(m_rotation);
		m_modelRender.Update();
	}
	if (g_pad[0]->IsTrigger(enButtonA)) {
		m_attack = true;
	}


	if (m_attack == true) {

		if (m_rotationCount < 10) {
			m_rotation.AddRotationDegY((angle * M_PI / 180.0)/10);
		}
		if (m_rotationCount >= 10 && m_rotationCount < 15) {
			m_moveSpeed += toPlayerDir *100.0f;

			m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);
		}
		if (m_rotationCount == 15) {
			m_attack = false;
		}
		m_rotationCount++;
	}

	if (fabsf(angle) < Math::DegToRad(45.0f)) {
		m_bossRiser->SetAttackOK(true);
		m_bossCannon->SetAttackOK(true);
		m_bossDrill->SetAttackOK(true);
		m_bossShovel->m_attackOK = true;
		m_bossTurbo->m_attackOK = true;
	}
	else {
		m_bossRiser->SetAttackOK(false);
		m_bossCannon->SetAttackOK(false);
		m_bossDrill->SetAttackOK(false);
		m_bossShovel->m_attackOK = false;
		m_bossTurbo->m_attackOK = false;
	}

	//敵キャラの前方方向を更新する
	m_forward = toPlayerDir;
	// 敵の前方方向を使って、回転クォータニオンを計算する。
	m_rotation.SetRotationY(atan2(m_forward.x, m_forward.z));
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();
}

void Boss::Damage()
{
	//ボス即死コード。
	if (g_pad[0]->IsPress(enButtonY))
	{
		m_HP = 0.0f;
	}
	
	//やっつけたらリザルト画面へGO!!
	if (m_HP <= 0.0f)
	{
		
		m_player->SetGameState(7);
		m_HP = 0.0f;
		if (m_deathCount >= 0 && m_deathCount < 20) {
			if (m_bossRiser != nullptr) {
				m_bossRiser->DecreaseScale(0.6f);
				m_bossRiser->SetRiserScale();
			}
			if (m_bossDrill != nullptr) {
				m_bossDrill->DecreaseScale(1.02f);
				m_bossDrill->SetDrillScale();
			}
			if (m_bossCannon != nullptr) {
				m_bossCannon->DecreaseScale(0.75f);
				m_bossCannon->SetCannonScale();
			}
			if (m_bossSaber != nullptr) {
				m_bossSaber->scale -= 0.75f;
				m_bossSaber->boss_Cannon_Render.SetScale(m_bossSaber->scale);
			}
			if (m_bossShovel != nullptr) {
				m_bossShovel->scale -= 0.75f;
				m_bossShovel->boss_Shovel_Render.SetScale(m_bossShovel->scale);
			}
			if (m_bossTurbo != nullptr) {
				m_bossTurbo->scale -= 0.651f;
				m_bossTurbo->boss_Turbo_Render.SetScale(m_bossRiser->GetScale());
			}
		}
		if (m_deathCount == 0) {
			GameCamera* m_camera = FindGO<GameCamera>("gamecamera");
			m_camera->SetFinalVibFlag(true);
			if (m_bossRiser != nullptr) {
				
				m_explosionAnother = NewGO<EffectEmitter>(0);
				m_explosionAnother->Init(enBoss_Explosion);
				m_explosionAnother->SetScale({ 70.0f,70.0f,70.0f });
				
				//efeLP += b_w_position;
				m_explosionAnother->SetPosition(m_bossRiser->GetPosirion());
				m_explosionAnother->SetRotation(m_bossRiser->GetRotation());
				m_explosionAnother->Play();
			}
			if (m_bossDrill != nullptr) {
				m_explosionAnother = NewGO<EffectEmitter>(0);
				m_explosionAnother->Init(enBoss_Explosion);
				m_explosionAnother->SetScale({ 70.0f,70.0f,70.0f });
				
				//efeLP += b_w_position;
				m_explosionAnother->SetPosition(m_bossDrill->GetPosirion());
				m_explosionAnother->SetRotation(m_bossDrill->GetRotation());
				m_explosionAnother->Play();
			}
			if (m_bossSaber != nullptr) {
				m_explosionAnother = NewGO<EffectEmitter>(0);
				m_explosionAnother->Init(enBoss_Explosion);
				m_explosionAnother->SetScale({ 70.0f,70.0f,70.0f });
				
				//efeLP += b_w_position;
				m_explosionAnother->SetPosition(m_bossSaber->m_position);
				m_explosionAnother->SetRotation(m_bossSaber->m_rotation);
				m_explosionAnother->Play();
			}
			if (m_bossShovel != nullptr) {
				m_explosionAnother = NewGO<EffectEmitter>(0);
				m_explosionAnother->Init(enBoss_Explosion);
				m_explosionAnother->SetScale({ 70.0f,70.0f,70.0f });
				
				//efeLP += b_w_position;
				m_explosionAnother->SetPosition(m_bossShovel->m_position);
				m_explosionAnother->SetRotation(m_bossShovel->m_rotation);
				m_explosionAnother->Play();
			}
			if (m_bossTurbo != nullptr) {
				m_explosionAnother = NewGO<EffectEmitter>(0);
				m_explosionAnother->Init(enBoss_Explosion);
				m_explosionAnother->SetScale({ 70.0f,70.0f,70.0f });
				
				//efeLP += b_w_position;
				m_explosionAnother->SetPosition(m_bossTurbo->m_position);
				m_explosionAnother->SetRotation(m_bossTurbo->m_rotation);
				m_explosionAnother->Play();
			}
			
		}
		if (m_deathCount == 60) {
			m_bossExplosion = NewGO<EffectEmitter>(0);
			m_bossExplosion->Init(enBoss_Death);
			m_bossExplosion->SetScale({ 70.0f,70.0f,70.0f });
			
			//efeLP += b_w_position;
			m_bossExplosion->SetPosition(m_position);
			m_bossExplosion->SetRotation(m_rotation);
			m_bossExplosion->Play();
		}
		if (m_deathCount >= 60 && m_deathCount < 120) {
			
			m_scale -= 0.25f;
			m_modelRender.SetScale(m_scale);
			
		}
		if (m_deathCount == 120) {
			GameCamera* m_camera = FindGO<GameCamera>("gamecamera");
			m_camera->SetBigVibFlag(true);
			m_bossExplosion = NewGO<EffectEmitter>(0);
			m_bossExplosion->Init(enBoss_Death2);
			m_bossExplosion->SetScale({ 70.0f,70.0f,70.0f });
			
			//efeLP += b_w_position;
			m_bossExplosion->SetPosition(m_position);
			m_bossExplosion->SetRotation(m_rotation);
			m_bossExplosion->Play();
		}
		if (m_deathCount==440) {
			m_player->SetGameState(2);
			m_result = NewGO<Result>(1, "result");
			m_result->SetVolume(m_game->GetBGMVol(), m_game->GetSEVol());

			m_result->SetTime((int)m_bossTime / 60, (int)m_bossTime % 60);


			DeleteGO(this);

		}
		m_deathCount++;
		
	}
}

void Boss::SetHPScale()
{
	float m_scaleX = m_HP * (1.0f / BOSS_HP_MAX);	//時間が減るほどゲージが減っていく

	max(0, m_scaleX);	//スケールは0以下にならない

	m_bossHPSprite.SetScale({ m_scaleX,1.0f,1.0f });
	m_bossHPSprite.Update();
}

void Boss::Render(RenderContext& rc)
{
	//モデルの描画。
	m_modelRender.Draw(rc);
	if (m_player->GetPlayerHP() > 0) {
		m_bossHPSprite.Draw(rc);
		m_bossHPWakuSprite.Draw(rc);
		m_bossHPWakuSprite2.Draw(rc);
	}
}
