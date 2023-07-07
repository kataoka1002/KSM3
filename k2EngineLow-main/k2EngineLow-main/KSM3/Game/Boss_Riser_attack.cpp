#include "stdafx.h"
#include "Boss_Riser_attack.h"
#include "Boss_Riser.h"
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

Boss_Riser_attack::Boss_Riser_attack()
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

Boss_Riser_attack::~Boss_Riser_attack()
{
	//m_weapon->m_attackState = false;
}

bool Boss_Riser_attack::Start() {
	m_game = FindGO<Game>("game");
	m_boss = FindGO<Boss>("boss");
	m_player = FindGO<Player>("player");
	m_weapon = FindGO<Boss_Riser>("boss_riser");
	m_coreWeapon = FindGO<Core_weapons>("core_weapons");




	//��(��)
	g_soundEngine->ResistWaveFileBank(2, "Assets/audio/Taihou_kouho1.wav");

	SetUp();

	return true;
}

void Boss_Riser_attack::DestroyWithImpactEffect() {
		m_weaponEffect = NewGO<EffectEmitter>(0);
		m_weaponEffect->Init(enBoss_Dozar_Landing);
		m_weaponEffect->SetScale({ 50.0f,50.0f,50.0f });
		m_weaponEffect->SetPosition(m_firePosition);
		m_weaponEffect->Play();
		m_effectPosition = m_firePosition;
		
	
	m_loadingCount++;
	if (m_fastFlag == true) {
		//���e��������ʉ�����
		m_battleShipGunTyakutiSE = NewGO<SoundSource>(0);			//���Đ�����ƏI���Ȃ̂ŃC���X�^���X��ێ������Ȃ��ׂɂ�����NewGO����
		m_battleShipGunTyakutiSE->Init(en_Boss_Dozar_Langing_SE);		//������
		m_battleShipGunTyakutiSE->SetVolume(2.0f * m_game->GetSEVol());	//���ʒ���
		m_battleShipGunTyakutiSE->Play(false);

		//��ʂ�h�炷
		GameCamera* m_camera = FindGO<GameCamera>("gamecamera");
		m_camera->SetBigVibFlag(true);
		Damage(true);

		m_fastFlag = false;
	}
	if (m_loadingCount == 100) {
		// ���e�����玀��
		DeleteGO(this);
		m_BulletEffect->Stop();
		DeleteGO(m_BulletEffect);
	}

}

void Boss_Riser_attack::SetUp()
{
	GameCamera* m_camera = FindGO<GameCamera>("gamecamera");
	m_camera->SetVibFlag(true);
	m_bulletModel.Init("Assets/modelData/V_P_bullet.tkm");
	m_aim.Multiply(m_bulletLocalPosition);	//�|���Z
	m_rot = m_aim;
	m_firePosition += m_bulletLocalPosition;
	m_bulletModel.SetScale(30);
	m_bulletModel.SetPosition(m_firePosition);
	m_bulletModel.SetRotation(m_rot);
	m_bulletModel.Update();

	Effect();
}

void Boss_Riser_attack::Update()
{
	if (m_bulletEfeCount == 0) {
		m_BulletEffect = NewGO<EffectEmitter>(0);
		m_BulletEffect->Init(enBoss_Dozar_efe);
		m_BulletEffect->SetScale({ 35.0f,35.0f,35.0f });

		m_BulletEffect->Play();
	}
	if (m_bulletEfeCount == 600) {
		DeleteGO(m_BulletEffect);
		m_BulletEffect = nullptr;
		m_bulletEfeCount = -1;
	}
	if (m_BulletEffect != nullptr) {
		m_BulletEffect->SetPosition(m_firePosition);
	}
	m_bulletEfeCount++;

	if (m_player->GetGameState() == MAIN_GAME_NUM)
	{

		m_fallSpeed += 0.002;

		if (m_firePosition.y <= 0.0f)
		{
			if (farst == true) {
				DestroyWithImpactEffect();
				farst = false;
			}
		}
		m_bulletModel.Update();
		Damage(false);
		Move();

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

void Boss_Riser_attack::Effect() {
	//m_weaponEffect = NewGO<EffectEmitter>(0);
	//m_weaponEffect->Init(enMasinganHibana);
	//m_weaponEffect->SetScale({ 10.0f,10.0f,10.0f });
	//m_weaponEffect->SetPosition(firing_position);
	//m_weaponEffect->Play();
}

void Boss_Riser_attack::Move()
{
	//�e��O�ɔ�΂�����
	m_moveSpeed += m_bulletForward * 3.0f;
	m_moveSpeed.x -= 0.25;
	m_moveSpeed.y -= 0.5 + m_fallSpeed;
	m_firePosition += m_moveSpeed;

	//�o���b�g�̍X�V
	m_bulletModel.SetRotation(m_rot);
	m_bulletModel.SetPosition(m_firePosition);
	m_bulletModel.Update();
}

void Boss_Riser_attack::Damage(bool No_tyakudan)
{
	if (No_tyakudan == true) {
		//---------------------------------------------------------------------------------------------------
		if (m_player != nullptr)	//�v���C���[�̏�񂪓����Ă���Ȃ�
		{
			//�e�ƃv���C���[�̋����𑪂�
			Vector3 diffPlayer = m_effectPosition - Vector3{ m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y + 50.0f, m_player->GetPlayerPosition().z };

			//����ɂ���ă_���[�W��ς���

				//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffPlayer.Length() <= 50000.0f) //�_���[�W������͈�
			{
				m_player->ApplyDamage(5.0f);

			}

		}



		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_leftArm != nullptr)	//���r�ɏ�񂪓����Ă���Ȃ�
		{
			//�e�ƍ��r�̋����𑪂�
			Vector3 diffLeftArm = m_effectPosition - m_leftArm->GetPosition();

			//����ɂ���ă_���[�W��ς���

				//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffLeftArm.Length() <= 50000.0f) //�_���[�W������͈�
			{
				m_leftArm->ApplyDamage(5.0f);

			}
		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_leftLeg != nullptr)	//�����ɏ�񂪓����Ă���Ȃ�
		{
			//�e�ƍ��r�̋����𑪂�
			Vector3 diffLeftLeg = m_effectPosition - m_leftLeg->GetPosition();

			//����ɂ���ă_���[�W��ς���

				//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffLeftLeg.Length() <= 50000.0f) //�_���[�W������͈�
			{
				m_leftLeg->ApplyDamage(5.0f);

			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_rightArm != nullptr)	//�E��ɏ�񂪓����Ă���Ȃ�
		{
			//�e�ƍ��r�̋����𑪂�
			Vector3 diffRightArm = m_effectPosition - m_rightArm->GetPosition();

			//����ɂ���ă_���[�W��ς���

				//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffRightArm.Length() <= 50000.0f) //�_���[�W������͈�
			{
				m_rightArm->ApplyDamage(5.0f);

			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_rightLeg != nullptr)	//�E���ɏ�񂪓����Ă���Ȃ�
		{
			//�e�ƍ��r�̋����𑪂�
			Vector3 diffRightLeg = m_effectPosition - m_rightLeg->GetPosition();

			//����ɂ���ă_���[�W��ς���

				//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffRightLeg.Length() <= 50000.0f) //�_���[�W������͈�
			{
				m_rightLeg->ApplyDamage(5.0f);

			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_shoulder != nullptr)	//���ɏ�񂪓����Ă���Ȃ�
		{
			//�e�ƍ��r�̋����𑪂�
			Vector3 diffShoulder = m_effectPosition - m_shoulder->GetPosition();

			//����ɂ���ă_���[�W��ς���

				//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffShoulder.Length() <= 50000.0f) //�_���[�W������͈�
			{
				m_shoulder->ApplyDamage(5.0f);

			}

		}
		//---------------------------------------------------------------------------------------------------
	}
	else if (No_tyakudan == false) {


		//---------------------------------------------------------------------------------------------------
		if (m_player != nullptr)	//�v���C���[�̏�񂪓����Ă���Ȃ�
		{
			//�e�ƃv���C���[�̋����𑪂�
			Vector3 diffPlayer = m_firePosition - Vector3{ m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y + 50.0f, m_player->GetPlayerPosition().z };

			//����ɂ���ă_���[�W��ς���

				//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffPlayer.Length() <= 200.0f) //�_���[�W������͈�
			{
				m_player->ApplyDamage(200.0f);
				if (farst == true) {
					DestroyWithImpactEffect();
					farst = false;
				}
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
			if (diffLeftArm.Length() <= 200.0f) //�_���[�W������͈�
			{
				m_leftArm->ApplyDamage(200.0f);
				if (farst == true) {
					DestroyWithImpactEffect();
					farst = false;
				}
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
			if (diffLeftLeg.Length() <= 200.0f) //�_���[�W������͈�
			{
				m_leftLeg->ApplyDamage(200.0f);
				if (farst == true) {
					DestroyWithImpactEffect();
					farst = false;
				}
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
			if (diffRightArm.Length() <= 200.0f) //�_���[�W������͈�
			{
				m_rightArm->ApplyDamage(200.0f);
				if (farst == true) {
					DestroyWithImpactEffect();
					farst = false;
				}
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
			if (diffRightLeg.Length() <= 200.0f) //�_���[�W������͈�
			{
				m_rightLeg->ApplyDamage(200.0f);
				if (farst == true) {
					DestroyWithImpactEffect();
					farst = false;
				}
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
			if (diffShoulder.Length() <= 200.0f) //�_���[�W������͈�
			{
				m_shoulder->ApplyDamage(200.0f);
				if (farst == true) {
					DestroyWithImpactEffect();
					farst = false;
				}
			}

		}
		//---------------------------------------------------------------------------------------------------
	}
}

void Boss_Riser_attack::Render(RenderContext& rc)
{
	
}