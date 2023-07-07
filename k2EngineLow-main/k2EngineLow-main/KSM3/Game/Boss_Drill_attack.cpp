#include "stdafx.h"
#include "Boss_Drill_attack.h"
#include "Boss_Drill.h"
#include "Customize_UI_ver2.h"
#include "Boss.h"
#include "Player.h"
#include "Core_weapons.h"
#include "sound/SoundEngine.h"
#include "Game.h"
#include "GameCamera.h"
#include "Left_arm_weapons.h"
#include "Left_leg_weapons.h"
#include "Right_arm_weapons.h"
#include "Right_leg_weapons.h"
#include "Shoulder_weapons.h"
#define _USE_MATH_DEFINES
#include <math.h>

Boss_Drill_attack::Boss_Drill_attack()
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
	if (m_customizeUI->GetRightLegWeapon() != nullptr)
	{
		m_rightLeg = m_customizeUI->GetRightLegWeapon();	//�J�X�^�}�C�YUI�ɂ���|�C���^��n���Ă��
	}
	//��
	if (m_customizeUI->GetShoulderWeapon() != nullptr)
	{
		m_shoulder = m_customizeUI->GetShoulderWeapon();	//�J�X�^�}�C�YUI�ɂ���|�C���^��n���Ă��
	}
}

Boss_Drill_attack::~Boss_Drill_attack()
{
	if (m_BulletEffect != nullptr) {
		m_BulletEffect->Stop();
		m_BulletEffect2->Stop();
		DeleteGO(m_BulletEffect);
		DeleteGO(m_BulletEffect2);
		m_BulletEffect = nullptr;
		m_BulletEffect2 = nullptr;
	}
	m_weapon->SetAttackOK(false);
}

bool Boss_Drill_attack::Start() {
	m_game = FindGO<Game>("game");
	m_boss = FindGO<Boss>("boss");
	m_player = FindGO<Player>("player");
	m_weapon = FindGO<Boss_Drill>("boss_drill");
	m_coreWeapon = FindGO<Core_weapons>("core_weapons");




	//��(��)
	g_soundEngine->ResistWaveFileBank(2, "Assets/audio/Taihou_kouho1.wav");

	
	SetUp();

	return true;
}

void Boss_Drill_attack::SetUp()
{
	m_bulletModel.Init("Assets/modelData/V_P_bullet.tkm");
	m_aim.Multiply(m_bulletLocalPosition);	//�|���Z
	m_rot = m_aim;
	m_firePosition += m_bulletLocalPosition;
	m_bulletModel.SetScale(30);
	m_bulletModel.SetPosition(m_firePosition);
	m_bulletModel.SetRotation(m_rot);
	m_bulletModel.Update();

	/*Effect();*/

}

void Boss_Drill_attack::Update()
{
	if (m_bulletEfeCount == 0) {
		//b_attack_SE = NewGO<SoundSource>(0);			//���Đ�����ƏI���Ȃ̂ŃC���X�^���X��ێ������Ȃ��ׂɂ�����NewGO����
		//b_attack_SE->Init(en_Boss_Drill);		//������
		//b_attack_SE->SetVolume(2.0f * m_game->SEvol);	//���ʒ���
		//b_attack_SE->Play(false);
	}
	if (m_bulletEfeCount % 510 == 0) {
		m_BulletEffect = NewGO<EffectEmitter>(0);
		m_BulletEffect->Init(enBoss_Drill);
		m_BulletEffect->SetScale({ 50.0f,50.0f,50.0f });


		m_BulletEffect->Play();
	}
	m_BulletEffect->SetRotation(m_effectRotation);
	m_BulletEffect->SetPosition(m_firePosition+m_effectLocalPos1);

	if (m_bulletEfeCount % 510 == 0) {
		m_BulletEffect2 = NewGO<EffectEmitter>(0);
		m_BulletEffect2->Init(enBoss_Drill);
		m_BulletEffect2->SetScale({ 50.0f,50.0f,50.0f });


		m_BulletEffect2->Play();
	}
	m_BulletEffect2->SetRotation(m_effectRotation);
	m_BulletEffect2->SetPosition(m_firePosition+m_effectLocalPos2);
	m_bulletEfeCount++;
	if (m_player->GetGameState() == MAIN_GAME_NUM)
	{
		Damage();
		Move();
		m_bulletModel.Update();
		
	}
	else if (m_player->GetGameState() == RESULT_NUM)
	{
		DeleteGO(this);	//���U���g��ʂɍs���Ə���
	}

	if (m_player->GetGameEndState() == 1)
	{
		DeleteGO(this);	//�v���C���[���|�[�Y��ʂ���Q�[�����I��������Ə���
	}
}

void Boss_Drill_attack::Move()
{

		if (m_drillCount>=120&&m_drillCount < 180) {
			m_moveSpeed += m_bulletForward * 10.0;
			m_firePosition += m_moveSpeed;
			m_bulletModel.SetPosition(m_moveSpeed);

			m_effectForward.x = m_bulletForward.x * cos(180 * (M_PI / 180)) - m_bulletForward.z * sin(180 * (M_PI / 180));
			m_effectForward.z = m_bulletForward.x * sin(180 * (M_PI / 180)) + m_bulletForward.z * cos(180 * (M_PI / 180));
			m_effectRotation.SetRotationY(atan2(m_effectForward.x, m_effectForward.z));
		}
		//if (drill_count == 9) {
		//	return_angle = Player_Search();
		//}
		if (m_drillCount == 209) {
			Vector3 toPlayer = m_player->GetPlayerPosition() - m_firePosition;

			//�v���C���[�Ƃ̋������v�Z����B
			float distToPlayer = toPlayer.Length();
			//�v���C���[�Ɍ������ĐL�т�x�N�g���𐳋K������B
			Vector3 toPlayerDir = toPlayer;
			toPlayerDir.Normalize();
			m_bulletForward = toPlayerDir;
			m_rot.SetRotationY(atan2(m_bulletForward.x, m_bulletForward.z));
			m_bulletModel.SetRotation(m_rot);
			m_lockPosition = m_player->GetPlayerPosition();
		}
		if (m_drillCount == 210) {
			Vector3 toPlayer = m_lockPosition - m_firePosition;

			//�v���C���[�Ƃ̋������v�Z����B
			float distToPlayer = toPlayer.Length();
			//�v���C���[�Ɍ������ĐL�т�x�N�g���𐳋K������B
			Vector3 toPlayerDir = toPlayer;
			toPlayerDir.Normalize();
			m_rot.SetRotationY(atan2(toPlayerDir.x, toPlayerDir.z));

			m_effectForward.x = toPlayerDir.x * cos(180 * (M_PI / 180)) - toPlayerDir.z * sin(180 * (M_PI / 180));
			m_effectForward.z = toPlayerDir.x * sin(180 * (M_PI / 180)) + toPlayerDir.z * cos(180 * (M_PI / 180));
			m_effectRotation.SetRotationY(atan2(m_effectForward.x, m_effectForward.z));

			m_bulletModel.SetRotation(m_rot);
			m_lockPosition = m_player->GetPlayerPosition();
			m_lastForward = toPlayerDir;
		}
		if (m_drillCount >= 210 && m_drillCount < 270) {
			Vector3 move_speed;

			move_speed += m_bulletForward * 400.0;
			m_firePosition += move_speed;
			m_bulletModel.SetPosition(m_firePosition);

			if (m_weapon != nullptr) {
				//�e�ƃ{�X�̋����𑪂�
				Vector3 diffShoulder = m_firePosition - m_weapon->GetPosirion();

				//����ɂ���ă_���[�W��ς���

					//�����𑪂���ȉ��Ȃ�̗͌���
				if (diffShoulder.Length() <= 500.0f) //�_���[�W������͈�
				{
					m_weapon->ApplyDamage(2.0f);
					Effect();

				}
			}
		}
		if (m_drillCount == 230) {
			GameCamera* m_camera = FindGO<GameCamera>("gamecamera");
			m_camera->SetVibFlag(true);
			m_attackSE=NewGO<SoundSource>(0);
			m_attackSE->Init(en_Boss_Drill_sonic);		//������
			m_attackSE->SetVolume(2.0f * m_game->GetSEVol());	//���ʒ���
			m_attackSE->Play(false);
		}
		if (m_drillCount >= 270 && m_drillCount < 300) {
			m_lastForward.y += 0.05;
			if (m_lastForward.y >= 1.0f) {
				m_lastForward.y = 1.0f;
			}
			m_effectRotation.x = -m_lastForward.x;
			m_effectRotation.y = m_lastForward.y;
			m_effectRotation.z = -m_lastForward.z;
			m_effectRotation.SetRotationX(atan2(m_effectRotation.y, m_effectRotation.z));

			m_rot.SetRotationX(atan2(m_lastForward.y, m_lastForward.z));
			m_bulletModel.SetRotation(m_rot);
			Vector3 move_speed;

			move_speed += m_lastForward * 40.0;
			m_firePosition += move_speed;
			m_bulletModel.SetPosition(m_firePosition);
		}
		if (m_drillCount >= 300 && m_drillCount < 400) {
			Vector3 move_speed;

			move_speed += m_lastForward * 400.0;
			m_firePosition += move_speed;
			m_bulletModel.SetPosition(m_firePosition);
		}
		if (m_drillCount == 400) {
			m_weapon->SetDrillAttack(nullptr);
			DeleteGO(m_attackSE);
			DeleteGO(this);
		}
		m_drillCount++;
		m_bulletModel.Update();
}

float Boss_Drill_attack::PlayerSearch() {
	Vector3 toPlayer = m_player->GetPlayerPosition() - m_firePosition;

	//�v���C���[�Ƃ̋������v�Z����B
	float distToPlayer = toPlayer.Length();
	//�v���C���[�Ɍ������ĐL�т�x�N�g���𐳋K������B
	Vector3 toPlayerDir = toPlayer;
	toPlayerDir.Normalize();
	float t = toPlayerDir.Dot(m_bulletForward);
	//���ς̌��ʂ�acos�֐��ɓn���āAm_enemyFowrad��toPlayerDir�̂Ȃ��p�x�����߂�B
	float angle = acos(t);
	float Amount_of_rotation = angle / 200;
	

	return Amount_of_rotation;
	
}

void Boss_Drill_attack::Damage() {
	//---------------------------------------------------------------------------------------------------
	if (m_player != nullptr)	//�v���C���[�̏�񂪓����Ă���Ȃ�
	{
		//�e�ƃv���C���[�̋����𑪂�
		Vector3 diffPlayer = m_firePosition - Vector3{ m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y + 50.0f, m_player->GetPlayerPosition().z };

		//����ɂ���ă_���[�W��ς���

			//�����𑪂���ȉ��Ȃ�̗͌���
		if (diffPlayer.Length() <= 500.0f) //�_���[�W������͈�
		{
			m_player->ApplyDamage(50.0f);
			Effect();

		}

	}



	//---------------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------------
	if (m_leftArm != nullptr)	//���r�ɏ�񂪓����Ă���Ȃ�
	{
		//�e�ƍ��r�̋����𑪂�
		Vector3 diffLeftArm = m_firePosition - m_leftArm->GetPosition();

		//����ɂ���ă_���[�W��ς���

			//�����𑪂���ȉ��Ȃ�̗͌���
		if (diffLeftArm.Length() <= 500.0f) //�_���[�W������͈�
		{
			m_leftArm->ApplyDamage(50.0f);
			Effect();

		}
	}
	//---------------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------------
	if (m_leftLeg != nullptr)	//�����ɏ�񂪓����Ă���Ȃ�
	{
		//�e�ƍ��r�̋����𑪂�
		Vector3 diffLeftLeg = m_firePosition - m_leftLeg->GetPosition();

		//����ɂ���ă_���[�W��ς���

			//�����𑪂���ȉ��Ȃ�̗͌���
		if (diffLeftLeg.Length() <= 500.0f) //�_���[�W������͈�
		{
			m_leftLeg->ApplyDamage(50.0f);
			Effect();

		}

	}
	//---------------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------------
	if (m_rightArm != nullptr)	//�E��ɏ�񂪓����Ă���Ȃ�
	{
		//�e�ƍ��r�̋����𑪂�
		Vector3 diffRightArm = m_firePosition - m_rightArm->GetPosition();

		//����ɂ���ă_���[�W��ς���

			//�����𑪂���ȉ��Ȃ�̗͌���
		if (diffRightArm.Length() <= 500.0f) //�_���[�W������͈�
		{
			m_rightArm->ApplyDamage(50.0f);
			Effect();

		}

	}
	//---------------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------------
	if (m_rightLeg != nullptr)	//�E���ɏ�񂪓����Ă���Ȃ�
	{
		//�e�ƍ��r�̋����𑪂�
		Vector3 diffRightLeg = m_firePosition - m_rightLeg->GetPosition();

		//����ɂ���ă_���[�W��ς���

			//�����𑪂���ȉ��Ȃ�̗͌���
		if (diffRightLeg.Length() <= 500.0f) //�_���[�W������͈�
		{
			m_rightLeg->ApplyDamage(50.0f);
			Effect();

		}

	}
	//---------------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------------
	if (m_shoulder != nullptr)	//���ɏ�񂪓����Ă���Ȃ�
	{
		//�e�ƍ��r�̋����𑪂�
		Vector3 diffShoulder = m_firePosition - m_shoulder->GetPosition();

		//����ɂ���ă_���[�W��ς���

			//�����𑪂���ȉ��Ȃ�̗͌���
		if (diffShoulder.Length() <= 500.0f) //�_���[�W������͈�
		{
			m_shoulder->ApplyDamage(50.0f);
			Effect();

		}

	}
	//---------------------------------------------------------------------------------------------------
	if (m_boss != nullptr) {
		//�e�ƃ{�X�̋����𑪂�
		Vector3 diffShoulder = m_firePosition - m_boss->GetPosition();

		//����ɂ���ă_���[�W��ς���

			//�����𑪂���ȉ��Ȃ�̗͌���
		if (diffShoulder.Length() <= 500.0f) //�_���[�W������͈�
		{
			m_boss->ApplyDamage(50.0f);
			Effect();

		}
	}

	
}

void Boss_Drill_attack::Effect() {
	m_tyakudanEffect = NewGO<EffectEmitter>(0);
	m_tyakudanEffect->Init(enBoss_Drill_Landing);
	m_tyakudanEffect->SetScale({ 20.0f,20.0f,20.0f });
	m_tyakudanEffect->SetPosition(m_firePosition);
	m_tyakudanEffect->Play();
}

void Boss_Drill_attack::Render(RenderContext& rc)
{
	/*b_a_Bullet.Draw(rc);*/
}