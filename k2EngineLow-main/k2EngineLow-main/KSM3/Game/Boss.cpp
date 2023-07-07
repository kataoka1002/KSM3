//�X�g���C�J�[�̃p�[�c�B

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
	//���r
	if (m_customizeUI->GetLeftArmWeapon() != nullptr)
	{
		m_leftArm = m_customizeUI->GetLeftArmWeapon();	//�J�X�^�}�C�YUI�ɂ���|�C���^��n���Ă��
	}
	//����
	if (m_customizeUI->GetLeftLegWeapon() != nullptr)
	{
		m_leftLeg = m_customizeUI->GetLeftLegWeapon();	//�J�X�^�}�C�YUI�ɂ���|�C���^��n���Ă��
	}
	//�E�r
	if (m_customizeUI->GetRightArmWeapon() != nullptr)
	{
		m_rightArm = m_customizeUI->GetRightArmWeapon();	//�J�X�^�}�C�YUI�ɂ���|�C���^��n���Ă��
	}
	//�E��
	if (m_customizeUI->GetLeftLegWeapon() != nullptr)
	{
		m_rightLeg = m_customizeUI->GetRightLegWeapon();	//�J�X�^�}�C�YUI�ɂ���|�C���^��n���Ă��
	}
	//��
	if (m_customizeUI->GetShoulderWeapon() != nullptr)
	{
		m_shoulder = m_customizeUI->GetShoulderWeapon();	//�J�X�^�}�C�YUI�ɂ���|�C���^��n���Ă��
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
	DeleteGO(m_bossRiser);//���C�U�[�̕���폜�B
	DeleteGO(m_bossShovel);//�V���x���̕���폜�B
	DeleteGO(m_bossDrill);//�h�����̕���폜�B
	DeleteGO(m_bossCannon);//�L���m���̕���폜�B
	DeleteGO(m_bossTurbo);//�^�[�{�̕���폜�B
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
	//�L�����N�^�[�R���g���[���[���������B
	m_characterController.Init(
		750.0f,			//���a�B
		40.0f,			//�����B
		m_position	//���W�B
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
		m_battleShipGunTyakutiSE = NewGO<SoundSource>(0);			//���Đ�����ƏI���Ȃ̂ŃC���X�^���X��ێ������Ȃ��ׂɂ�����NewGO����
		m_battleShipGunTyakutiSE->Init(enButtleShipTyakudan);		//������
		m_battleShipGunTyakutiSE->SetVolume(2.0f * m_game->GetSEVol());	//���ʒ���
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
				if (m_player != nullptr)	//�v���C���[�̏�񂪓����Ă���Ȃ�
				{
					//�e�ƃv���C���[�̋����𑪂�
					Vector3 diffPlayer = m_attackEfeLP - Vector3{ m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y + 50.0f, m_player->GetPlayerPosition().z };

					//����ɂ���ă_���[�W��ς���

						//�����𑪂���ȉ��Ȃ�̗͌���
					if (diffPlayer.Length() <= 2000.0f) //�_���[�W������͈�
					{
						m_player->ApplyDamage(1.0f);

					}

				}



				//---------------------------------------------------------------------------------------------------

				//---------------------------------------------------------------------------------------------------
				if (m_leftArm != nullptr)	//���r�ɏ�񂪓����Ă���Ȃ�
				{
					//�e�ƍ��r�̋����𑪂�
					Vector3 diffLeftArm = m_attackEfeLP - m_leftArm->GetPosition();

					//����ɂ���ă_���[�W��ς���

						//�����𑪂���ȉ��Ȃ�̗͌���
					if (diffLeftArm.Length() <= 2000.0f) //�_���[�W������͈�
					{
						m_leftArm->ApplyDamage(1.0f);

					}
				}
				//---------------------------------------------------------------------------------------------------

				//---------------------------------------------------------------------------------------------------
				if (m_leftLeg != nullptr)	//�����ɏ�񂪓����Ă���Ȃ�
				{
					//�e�ƍ��r�̋����𑪂�
					Vector3 diffLeftLeg = m_attackEfeLP - m_leftLeg->GetPosition();

					//����ɂ���ă_���[�W��ς���

						//�����𑪂���ȉ��Ȃ�̗͌���
					if (diffLeftLeg.Length() <= 2000.0f) //�_���[�W������͈�
					{
						m_leftLeg->ApplyDamage(1.0f);

					}

				}
				//---------------------------------------------------------------------------------------------------

				//---------------------------------------------------------------------------------------------------
				if (m_rightArm != nullptr)	//�E��ɏ�񂪓����Ă���Ȃ�
				{
					//�e�ƍ��r�̋����𑪂�
					Vector3 diffRightArm = m_attackEfeLP - m_rightArm->GetPosition();

					//����ɂ���ă_���[�W��ς���

						//�����𑪂���ȉ��Ȃ�̗͌���
					if (diffRightArm.Length() <= 2000.0f) //�_���[�W������͈�
					{
						m_rightArm->ApplyDamage(1.0f);

					}

				}
				//---------------------------------------------------------------------------------------------------

				//---------------------------------------------------------------------------------------------------
				if (m_rightLeg != nullptr)	//�E���ɏ�񂪓����Ă���Ȃ�
				{
					//�e�ƍ��r�̋����𑪂�
					Vector3 diffRightLeg = m_attackEfeLP - m_rightLeg->GetPosition();

					//����ɂ���ă_���[�W��ς���

						//�����𑪂���ȉ��Ȃ�̗͌���
					if (diffRightLeg.Length() <= 2000.0f) //�_���[�W������͈�
					{
						m_rightLeg->ApplyDamage(1.0f);

					}

				}
				//---------------------------------------------------------------------------------------------------

				//---------------------------------------------------------------------------------------------------
				if (m_shoulder != nullptr)	//���ɏ�񂪓����Ă���Ȃ�
				{
					//�e�ƍ��r�̋����𑪂�
					Vector3 diffShoulder = m_attackEfeLP - m_shoulder->GetPosition();

					//����ɂ���ă_���[�W��ς���

						//�����𑪂���ȉ��Ȃ�̗͌���
					if (diffShoulder.Length() <= 2000.0f) //�_���[�W������͈�
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
			if (m_player != nullptr)	//�v���C���[�̏�񂪓����Ă���Ȃ�
			{
				//�e�ƃv���C���[�̋����𑪂�
				Vector3 diffPlayer = m_attackEfeLP - Vector3{ m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y + 50.0f, m_player->GetPlayerPosition().z };

				//����ɂ���ă_���[�W��ς���

					//�����𑪂���ȉ��Ȃ�̗͌���
				if (diffPlayer.Length() <= 2500.0f) //�_���[�W������͈�
				{
					m_player->ApplyDamage(100.0f);

				}

			}



			//---------------------------------------------------------------------------------------------------

			//---------------------------------------------------------------------------------------------------
			if (m_leftArm != nullptr)	//���r�ɏ�񂪓����Ă���Ȃ�
			{
				//�e�ƍ��r�̋����𑪂�
				Vector3 diffLeftArm = m_attackEfeLP - m_leftArm->GetPosition();

				//����ɂ���ă_���[�W��ς���

					//�����𑪂���ȉ��Ȃ�̗͌���
				if (diffLeftArm.Length() <= 2500.0f) //�_���[�W������͈�
				{
					m_leftArm->ApplyDamage(100.0f);

				}
			}
			//---------------------------------------------------------------------------------------------------

			//---------------------------------------------------------------------------------------------------
			if (m_leftLeg != nullptr)	//�����ɏ�񂪓����Ă���Ȃ�
			{
				//�e�ƍ��r�̋����𑪂�
				Vector3 diffLeftLeg = m_attackEfeLP - m_leftLeg->GetPosition();

				//����ɂ���ă_���[�W��ς���

					//�����𑪂���ȉ��Ȃ�̗͌���
				if (diffLeftLeg.Length() <= 2500.0f) //�_���[�W������͈�
				{
					m_leftLeg->ApplyDamage(100.0f);

				}

			}
			//---------------------------------------------------------------------------------------------------

			//---------------------------------------------------------------------------------------------------
			if (m_rightArm != nullptr)	//�E��ɏ�񂪓����Ă���Ȃ�
			{
				//�e�ƍ��r�̋����𑪂�
				Vector3 diffRightArm = m_attackEfeLP - m_rightArm->GetPosition();

				//����ɂ���ă_���[�W��ς���

					//�����𑪂���ȉ��Ȃ�̗͌���
				if (diffRightArm.Length() <= 2500.0f) //�_���[�W������͈�
				{
					m_rightArm->ApplyDamage(100.0f);

				}

			}
			//---------------------------------------------------------------------------------------------------

			//---------------------------------------------------------------------------------------------------
			if (m_rightLeg != nullptr)	//�E���ɏ�񂪓����Ă���Ȃ�
			{
				//�e�ƍ��r�̋����𑪂�
				Vector3 diffRightLeg = m_attackEfeLP - m_rightLeg->GetPosition();

				//����ɂ���ă_���[�W��ς���

					//�����𑪂���ȉ��Ȃ�̗͌���
				if (diffRightLeg.Length() <= 2500.0f) //�_���[�W������͈�
				{
					m_rightLeg->ApplyDamage(100.0f);

				}

			}
			//---------------------------------------------------------------------------------------------------

			//---------------------------------------------------------------------------------------------------
			if (m_shoulder != nullptr)	//���ɏ�񂪓����Ă���Ȃ�
			{
				//�e�ƍ��r�̋����𑪂�
				Vector3 diffShoulder = m_attackEfeLP - m_shoulder->GetPosition();

				//����ɂ���ă_���[�W��ς���

					//�����𑪂���ȉ��Ȃ�̗͌���
				if (diffShoulder.Length() <= 2500.0f) //�_���[�W������͈�
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
	//�G�l�~�[����v���C���[�������Ă�����ǂ�������
	Vector3 toPlayer = m_player->GetPlayerPosition() - m_position;

	//�v���C���[�Ƃ̋������v�Z����
	float distToPlayer = toPlayer.Length();
	//�v���C���[�Ɍ������ĐL�т�x�N�g���𐳋K������
	Vector3 toPlayerDir = toPlayer;
	toPlayerDir.Normalize();
	//�G�l�~�[�̑O��������toPlayerDir�Ƃ̓��ς��v�Z����
	float t = toPlayerDir.Dot(m_forward);
	//���ς̌��ʂ�acos�֐��ɓn���āAm_enemyFowrad��toPlayerDir�̂Ȃ��p�x�����߂�B
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

	//�G�L�����̑O���������X�V����
	m_forward = toPlayerDir;
	// �G�̑O���������g���āA��]�N�H�[�^�j�I�����v�Z����B
	m_rotation.SetRotationY(atan2(m_forward.x, m_forward.z));
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();
}

void Boss::Damage()
{
	//�{�X�����R�[�h�B
	if (g_pad[0]->IsPress(enButtonY))
	{
		m_HP = 0.0f;
	}
	
	//��������烊�U���g��ʂ�GO!!
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
	float m_scaleX = m_HP * (1.0f / BOSS_HP_MAX);	//���Ԃ�����قǃQ�[�W�������Ă���

	max(0, m_scaleX);	//�X�P�[����0�ȉ��ɂȂ�Ȃ�

	m_bossHPSprite.SetScale({ m_scaleX,1.0f,1.0f });
	m_bossHPSprite.Update();
}

void Boss::Render(RenderContext& rc)
{
	//���f���̕`��B
	m_modelRender.Draw(rc);
	if (m_player->GetPlayerHP() > 0) {
		m_bossHPSprite.Draw(rc);
		m_bossHPWakuSprite.Draw(rc);
		m_bossHPWakuSprite2.Draw(rc);
	}
}
