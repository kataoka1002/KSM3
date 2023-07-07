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
	b_a_weapons->m_attackState = false;
}

bool Boss_Drill_attack::Start() {
	m_game = FindGO<Game>("game");
	b_a_boss = FindGO<Boss>("boss");
	b_a_player = FindGO<Player>("player");
	b_a_weapons = FindGO<Boss_Drill>("boss_drill");
	b_a_core_weapons = FindGO<Core_weapons>("core_weapons");




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
	m_BulletEffect->SetRotation(efe_rot);
	m_BulletEffect->SetPosition(m_firePosition+efe_l_pos1);

	if (m_bulletEfeCount % 510 == 0) {
		m_BulletEffect2 = NewGO<EffectEmitter>(0);
		m_BulletEffect2->Init(enBoss_Drill);
		m_BulletEffect2->SetScale({ 50.0f,50.0f,50.0f });


		m_BulletEffect2->Play();
	}
	m_BulletEffect2->SetRotation(efe_rot);
	m_BulletEffect2->SetPosition(m_firePosition+efe_l_pos2);
	m_bulletEfeCount++;
	if (b_a_player->GetGameState() == MAIN_GAME_NUM)
	{
		Damage();
		Move();
		m_bulletModel.Update();
		
	}
	else if (b_a_player->GetGameState() == RESULT_NUM)
	{
		DeleteGO(this);	//���U���g��ʂɍs���Ə���
	}

	if (b_a_player->GetGameEndState() == 1)
	{
		DeleteGO(this);	//�v���C���[���|�[�Y��ʂ���Q�[�����I��������Ə���
	}
}

void Boss_Drill_attack::Move()
{

		if (drill_count>=120&&drill_count < 180) {
			move_speed += m_bulletForward * 10.0;
			m_firePosition += move_speed;
			m_bulletModel.SetPosition(move_speed);

			efe_fowrad.x = m_bulletForward.x * cos(180 * (M_PI / 180)) - m_bulletForward.z * sin(180 * (M_PI / 180));
			efe_fowrad.z = m_bulletForward.x * sin(180 * (M_PI / 180)) + m_bulletForward.z * cos(180 * (M_PI / 180));
			efe_rot.SetRotationY(atan2(efe_fowrad.x, efe_fowrad.z));
		}
		//if (drill_count == 9) {
		//	return_angle = Player_Search();
		//}
		if (drill_count == 209) {
			Vector3 toPlayer = b_a_player->GetPlayerPosition() - m_firePosition;

			//�v���C���[�Ƃ̋������v�Z����B
			float distToPlayer = toPlayer.Length();
			//�v���C���[�Ɍ������ĐL�т�x�N�g���𐳋K������B
			Vector3 toPlayerDir = toPlayer;
			toPlayerDir.Normalize();
			m_bulletForward = toPlayerDir;
			m_rot.SetRotationY(atan2(m_bulletForward.x, m_bulletForward.z));
			m_bulletModel.SetRotation(m_rot);
			lock_p_position = b_a_player->GetPlayerPosition();
		}
		if (drill_count == 210) {
			Vector3 toPlayer = lock_p_position - m_firePosition;

			//�v���C���[�Ƃ̋������v�Z����B
			float distToPlayer = toPlayer.Length();
			//�v���C���[�Ɍ������ĐL�т�x�N�g���𐳋K������B
			Vector3 toPlayerDir = toPlayer;
			toPlayerDir.Normalize();
			m_rot.SetRotationY(atan2(toPlayerDir.x, toPlayerDir.z));

			efe_fowrad.x = toPlayerDir.x * cos(180 * (M_PI / 180)) - toPlayerDir.z * sin(180 * (M_PI / 180));
			efe_fowrad.z = toPlayerDir.x * sin(180 * (M_PI / 180)) + toPlayerDir.z * cos(180 * (M_PI / 180));
			efe_rot.SetRotationY(atan2(efe_fowrad.x, efe_fowrad.z));

			m_bulletModel.SetRotation(m_rot);
			lock_p_position = b_a_player->GetPlayerPosition();
			last_fowrad = toPlayerDir;
		}
		if (drill_count >= 210 && drill_count < 270) {
			Vector3 move_speed;

			move_speed += m_bulletForward * 400.0;
			m_firePosition += move_speed;
			m_bulletModel.SetPosition(m_firePosition);

			if (b_a_weapons != nullptr) {
				//�e�ƃ{�X�̋����𑪂�
				Vector3 diffShoulder = m_firePosition - Vector3{ b_a_weapons->m_position.x, b_a_weapons->m_position.y, b_a_weapons->m_position.z };

				//����ɂ���ă_���[�W��ς���

					//�����𑪂���ȉ��Ȃ�̗͌���
				if (diffShoulder.Length() <= 500.0f) //�_���[�W������͈�
				{
					b_a_weapons->drill_HP -= 2.0f;
					Effect();

				}
			}
		}
		if (drill_count == 230) {
			GameCamera* m_camera = FindGO<GameCamera>("gamecamera");
			m_camera->SetVibFlag(true);
			b_attack_SE=NewGO<SoundSource>(0);
			b_attack_SE->Init(en_Boss_Drill_sonic);		//������
			b_attack_SE->SetVolume(2.0f * m_game->GetSEVol());	//���ʒ���
			b_attack_SE->Play(false);
		}
		if (drill_count >= 270 && drill_count < 300) {
			last_fowrad.y += 0.05;
			if (last_fowrad.y >= 1.0f) {
				last_fowrad.y = 1.0f;
			}
			efe_rot.x = -last_fowrad.x;
			efe_rot.y = last_fowrad.y;
			efe_rot.z = -last_fowrad.z;
			efe_rot.SetRotationX(atan2(efe_rot.y, efe_rot.z));

			m_rot.SetRotationX(atan2(last_fowrad.y, last_fowrad.z));
			m_bulletModel.SetRotation(m_rot);
			Vector3 move_speed;

			move_speed += last_fowrad * 40.0;
			m_firePosition += move_speed;
			m_bulletModel.SetPosition(m_firePosition);
		}
		if (drill_count >= 300 && drill_count < 400) {
			Vector3 move_speed;

			move_speed += last_fowrad * 400.0;
			m_firePosition += move_speed;
			m_bulletModel.SetPosition(m_firePosition);
		}
		if (drill_count == 400) {
			b_a_weapons->b_boss_weapons = nullptr;
			DeleteGO(b_attack_SE);
			DeleteGO(this);
		}
		drill_count++;
		m_bulletModel.Update();
}

float Boss_Drill_attack::Player_Search() {
	Vector3 toPlayer = b_a_player->GetPlayerPosition() - m_firePosition;

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
	if (b_a_player != nullptr)	//�v���C���[�̏�񂪓����Ă���Ȃ�
	{
		//�e�ƃv���C���[�̋����𑪂�
		Vector3 diffPlayer = m_firePosition - Vector3{ b_a_player->GetPlayerPosition().x, b_a_player->GetPlayerPosition().y + 50.0f, b_a_player->GetPlayerPosition().z };

		//����ɂ���ă_���[�W��ς���

			//�����𑪂���ȉ��Ȃ�̗͌���
		if (diffPlayer.Length() <= 500.0f) //�_���[�W������͈�
		{
			b_a_player->ApplyDamage(50.0f);
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
	if (b_a_boss != nullptr) {
		//�e�ƃ{�X�̋����𑪂�
		Vector3 diffShoulder = m_firePosition - b_a_boss->GetPosition();

		//����ɂ���ă_���[�W��ς���

			//�����𑪂���ȉ��Ȃ�̗͌���
		if (diffShoulder.Length() <= 500.0f) //�_���[�W������͈�
		{
			b_a_boss->ApplyDamage(50.0f);
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