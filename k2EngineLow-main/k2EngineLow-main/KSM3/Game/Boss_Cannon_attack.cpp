#include "stdafx.h"
#include "Boss_Cannon_attack.h"
#include "Boss_Cannon.h"
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

Boss_Cannon_attack::Boss_Cannon_attack()
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

Boss_Cannon_attack::~Boss_Cannon_attack()
{
	m_cannon->SetAttackFlag(false);
}

bool Boss_Cannon_attack::Start() {
	m_game = FindGO<Game>("game");
	//b_a_boss = FindGO<Boss>("boss");
	m_player = FindGO<Player>("player");
	m_cannon = FindGO<Boss_Cannon>("boss_cannon");
	//b_a_core_weapons = FindGO<Core_weapons>("core_weapons");
	

	

	//��(��)
	g_soundEngine->ResistWaveFileBank(2, "Assets/audio/Taihou_kouho1.wav");

	
	SetUp();

	return true;
}

void Boss_Cannon_attack::DestroyWithImpactEffect() {
	if (m_loadingCount == 0){
		m_Cannon_LangingSE = NewGO<SoundSource>(0);			//���Đ�����ƏI���Ȃ̂ŃC���X�^���X��ێ������Ȃ��ׂɂ�����NewGO����
		m_Cannon_LangingSE->Init(en_Boss_cannon_Langing_SE);		//������
		m_Cannon_LangingSE->SetVolume(2.0f * m_game->GetSEVol());	//���ʒ���
		m_Cannon_LangingSE->Play(false);

		m_weaponEffect = NewGO<EffectEmitter>(0);
		m_weaponEffect->Init(enBoss_Cannon_Landing);
		m_weaponEffect->SetScale({ 70.0f,70.0f,70.0f });
		m_weaponEffect->SetPosition(m_firePosition);
		m_weaponEffect->Play();
		m_effectPosition = m_firePosition;
	}
	if (m_loadingCount == 126) {
		//��͖C�G�t�F�N�g�̏������ƍĐ�
		m_battleShipGunTyakutiSE = NewGO<SoundSource>(0);			//���Đ�����ƏI���Ȃ̂ŃC���X�^���X��ێ������Ȃ��ׂɂ�����NewGO����
		m_battleShipGunTyakutiSE->Init(enButtleShipTyakudan);		//������
		m_battleShipGunTyakutiSE->SetVolume(2.0f * m_game->GetSEVol());	//���ʒ���
		m_battleShipGunTyakutiSE->Play(false);

		m_weaponEffect = NewGO<EffectEmitter>(0);
		m_weaponEffect->Init(enTyakudan);
		m_weaponEffect->SetScale({ 70.0f,70.0f,70.0f });
		m_weaponEffect->SetPosition(m_effectPosition);
		m_weaponEffect->Play();
		Damage(true);
	}
	m_loadingCount++;
	if (m_fastFlag == true) {
		//���e��������ʉ�����
		
		
		//��ʂ�h�炷
		GameCamera* m_camera = FindGO<GameCamera>("gamecamera");
		//m_camera->SetBigVibFlag(true);
		m_camera->SetVibFlag(true);
		m_fastFlag = false;
	}
	if (m_loadingCount == 130) {
		// ���e�����玀��
		DeleteGO(m_weaponEffect);
		m_weaponEffect = nullptr;
		DeleteGO(m_BulletEffect);
		m_BulletEffect = nullptr;
		DeleteGO(this);
	}

}

void Boss_Cannon_attack::SetUp()
{
	
	//�e���f���B
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
	//b_a_Bullet_Fowrad = b_a_weapons->b_w_Fowrad;
	//firing_position.y += 100.0f;
	//firing_position.x -= 600.0f;
	//b_a_Bullet.SetRotation(b_a_boss->boss_rotation);
	//b_a_Bullet.SetPosition(firing_position);

	
}

void Boss_Cannon_attack::Update()
{
	
		if (m_bulletEfeCount % 32 == 0) {
			m_BulletEffect = NewGO<EffectEmitter>(0);
			m_BulletEffect->Init(enBoss_Cannon_Bullet);
			m_BulletEffect->SetScale({ 35.0f,35.0f,35.0f });
			
			m_BulletEffect->Play();
		}
		m_BulletEffect->SetPosition(m_firePosition);
		m_bulletEfeCount++;

	if (m_player->GetGameState() == MAIN_GAME_NUM)
	{
		m_fallSpeed += 0.002;

		if (m_firePosition.y <= 0.0f)
		{
			DestroyWithImpactEffect();
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

void Boss_Cannon_attack::Effect() {
	//m_weaponEffect = NewGO<EffectEmitter>(0);
	//m_weaponEffect->Init(enMasinganHibana);
	//m_weaponEffect->SetScale({ 10.0f,10.0f,10.0f });
	//m_weaponEffect->SetPosition(firing_position);
	//m_weaponEffect->Play();
}

void Boss_Cannon_attack::Move()
{

	//�e��O�ɔ�΂�����
	m_moveSpeed += m_bulletForward * 3.0f;
	m_moveSpeed.y -= 0.2+m_fallSpeed;
	m_firePosition += m_moveSpeed;

	//�o���b�g�̍X�V
	m_bulletModel.SetRotation(m_rot);
	m_bulletModel.SetPosition(m_firePosition);
	m_bulletModel.Update();


}

void Boss_Cannon_attack::Damage(bool No_tyakudan)
{
	if (No_tyakudan==true) {
		//---------------------------------------------------------------------------------------------------
		if (m_player != nullptr)	//�v���C���[�̏�񂪓����Ă���Ȃ�
		{
			//�e�ƃv���C���[�̋����𑪂�
			Vector3 diffPlayer = m_effectPosition - Vector3{ m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y + 50.0f, m_player->GetPlayerPosition().z };

			//����ɂ���ă_���[�W��ς���

				//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffPlayer.Length() <= 500.0f) //�_���[�W������͈�
			{
				m_player->ApplyDamage(200.0f);
				
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
			if (diffLeftArm.Length() <= 500.0f) //�_���[�W������͈�
			{
				m_leftArm->ApplyDamage(200.0f);
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
			if (diffLeftLeg.Length() <= 500.0f) //�_���[�W������͈�
			{
				m_leftLeg->ApplyDamage(200.0f);
				
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
			if (diffRightArm.Length() <= 500.0f) //�_���[�W������͈�
			{
				m_rightArm->ApplyDamage(200.0f);
				
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
			if (diffRightLeg.Length() <= 500.0f) //�_���[�W������͈�
			{
				m_rightLeg->ApplyDamage(200.0f);
				
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
			if (diffShoulder.Length() <= 500.0f) //�_���[�W������͈�
			{
				m_shoulder->ApplyDamage(200.0f);
				
			}

		}
		//---------------------------------------------------------------------------------------------------
	}
	else if(No_tyakudan==false){

	
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
				DestroyWithImpactEffect();
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
				DestroyWithImpactEffect();
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
				DestroyWithImpactEffect();
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
				DestroyWithImpactEffect();
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
				DestroyWithImpactEffect();
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
				DestroyWithImpactEffect();
			}
		
	}
	//---------------------------------------------------------------------------------------------------
}
}


void Boss_Cannon_attack::Render(RenderContext& rc)
{
	m_bulletModel.Draw(rc);
}