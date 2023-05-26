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
	if (m_customizeUI->m_leftArmWeapon != nullptr)
	{
		m_leftArm = m_customizeUI->m_leftArmWeapon;	//�J�X�^�}�C�YUI�ɂ���|�C���^��n���Ă��
	}
	//����
	if (m_customizeUI->m_leftLegWeapon != nullptr)
	{
		m_leftLeg = m_customizeUI->m_leftLegWeapon;	//�J�X�^�}�C�YUI�ɂ���|�C���^��n���Ă��
	}
	//�E�r
	if (m_customizeUI->m_rightArmWeapon != nullptr)
	{
		m_rightArm = m_customizeUI->m_rightArmWeapon;	//�J�X�^�}�C�YUI�ɂ���|�C���^��n���Ă��
	}
	//�E��
	if (m_customizeUI->m_rightLegWeapon != nullptr)
	{
		m_rightLeg = m_customizeUI->m_rightLegWeapon;	//�J�X�^�}�C�YUI�ɂ���|�C���^��n���Ă��
	}
	//��
	if (m_customizeUI->m_shoulderWeapon != nullptr)
	{
		m_shoulder = m_customizeUI->m_shoulderWeapon;	//�J�X�^�}�C�YUI�ɂ���|�C���^��n���Ă��
	}
}

Boss_Cannon_attack::~Boss_Cannon_attack()
{
	b_a_weapons->attack_state = false;
}

bool Boss_Cannon_attack::Start() {
	m_game = FindGO<Game>("game");
	b_a_boss = FindGO<Boss>("boss");
	b_a_player = FindGO<Player>("player");
	b_a_weapons = FindGO<Boss_Cannon>("boss_cannon");
	b_a_core_weapons = FindGO<Core_weapons>("core_weapons");
	

	

	//��(��)
	g_soundEngine->ResistWaveFileBank(2, "Assets/audio/Taihou_kouho1.wav");

	b_attack_SE = NewGO<SoundSource>(0);
	b_attack_SE->Init(2);
	b_attack_SE->SetVolume(0.2f);
	b_attack_SE->Play(false);
	SetUp();

	return true;
}

void Boss_Cannon_attack::DestroyWithImpactEffect() {
	if (Landing_count == 0){
		m_weaponEffect = NewGO<EffectEmitter>(0);
		m_weaponEffect->Init(enBoss_Cannon_Landing);
		m_weaponEffect->SetScale({ 70.0f,70.0f,70.0f });
		m_weaponEffect->SetPosition(firing_position);
		m_weaponEffect->Play();
		efePosi = firing_position;
	}
	if (Landing_count == 126) {
		//��͖C�G�t�F�N�g�̏������ƍĐ�
		m_weaponEffect = NewGO<EffectEmitter>(0);
		m_weaponEffect->Init(enTyakudan);
		m_weaponEffect->SetScale({ 70.0f,70.0f,70.0f });
		m_weaponEffect->SetPosition(efePosi);
		m_weaponEffect->Play();
		Damage(true);
	}
	Landing_count++;
	if (fast == true) {
		//���e��������ʉ�����
		m_battleShipGunTyakutiSE = NewGO<SoundSource>(0);			//���Đ�����ƏI���Ȃ̂ŃC���X�^���X��ێ������Ȃ��ׂɂ�����NewGO����
		m_battleShipGunTyakutiSE->Init(enButtleShipTyakudan);		//������
		m_battleShipGunTyakutiSE->SetVolume(2.0f * m_game->SEvol);	//���ʒ���
		m_battleShipGunTyakutiSE->Play(false);
		
		//��ʂ�h�炷
		GameCamera* m_camera = FindGO<GameCamera>("gamecamera");
		m_camera->VibBigFlag = true;
		
		fast = false;
	}
	if (Landing_count == 130) {
		// ���e�����玀��
		DeleteGO(this);
	}

}

void Boss_Cannon_attack::SetUp()
{
	
	//�e���f���B

	b_a_Bullet.Init("Assets/modelData/V_P_bullet.tkm");
	b_a_aiming.Multiply(m_bulletLocalPosition);	//�|���Z
	m_rot = b_a_aiming;
	firing_position += m_bulletLocalPosition;
	b_a_Bullet_Fowrad = b_a_boss->boss_forward;
	b_a_Bullet.SetScale(30);
	b_a_Bullet.SetPosition(firing_position);
	b_a_Bullet.SetRotation(m_rot);
	b_a_Bullet.Update();

	Effect();
	//b_a_Bullet_Fowrad = b_a_weapons->b_w_Fowrad;
	//firing_position.y += 100.0f;
	//firing_position.x -= 600.0f;
	//b_a_Bullet.SetRotation(b_a_boss->boss_rotation);
	//b_a_Bullet.SetPosition(firing_position);

	
}

void Boss_Cannon_attack::Update()
{
	
		if (Bullet_efe_count % 32 == 0) {
			m_BulletEffect = NewGO<EffectEmitter>(0);
			m_BulletEffect->Init(enBoss_Cannon_Bullet);
			m_BulletEffect->SetScale({ 35.0f,35.0f,35.0f });
			
			m_BulletEffect->Play();
		}
		m_BulletEffect->SetPosition(firing_position);
		Bullet_efe_count++;

	if (b_a_player->game_state == 0)
	{
		fall_speed += 0.002;

		if (firing_position.y <= 0.0f)
		{
			DestroyWithImpactEffect();
		}
		b_a_Bullet.Update();
		Damage(false);
		Move();
		
	}
	else if (b_a_player->game_state == 2)
	{
		DeleteGO(this);	//���U���g��ʂɍs���Ə���
	}

	if (b_a_player->game_end_state == 1)
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
	Move_speed += b_a_Bullet_Fowrad * 3.0f;
	Move_speed.y -= 0.2+fall_speed;
	firing_position += Move_speed;

	//�o���b�g�̍X�V
	b_a_Bullet.SetRotation(m_rot);
	b_a_Bullet.SetPosition(firing_position);
	b_a_Bullet.Update();


}

void Boss_Cannon_attack::Damage(bool No_tyakudan)
{
	if (No_tyakudan==true) {
		//---------------------------------------------------------------------------------------------------
		if (b_a_player != nullptr)	//�v���C���[�̏�񂪓����Ă���Ȃ�
		{
			//�e�ƃv���C���[�̋����𑪂�
			Vector3 diffPlayer = efePosi - Vector3{ b_a_player->player_position.x, b_a_player->player_position.y + 50.0f, b_a_player->player_position.z };

			//����ɂ���ă_���[�W��ς���

				//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffPlayer.Length() <= 500.0f) //�_���[�W������͈�
			{
				b_a_player->m_playerHP -= 200.0f;
				
			}

		}
		 
		 
		
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_leftArm != nullptr)	//���r�ɏ�񂪓����Ă���Ȃ�
		{
			//�e�ƍ��r�̋����𑪂�
			Vector3 diffLeftArm = efePosi - Vector3{ m_leftArm->l_a_w_position.x, m_leftArm->l_a_w_position.y, m_leftArm->l_a_w_position.z };

			//����ɂ���ă_���[�W��ς���

				//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffLeftArm.Length() <= 500.0f) //�_���[�W������͈�
			{
				m_leftArm->L_a_w_HP -= 200.0f;
				
			}
		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_leftLeg != nullptr)	//�����ɏ�񂪓����Ă���Ȃ�
		{
			//�e�ƍ��r�̋����𑪂�
			Vector3 diffLeftLeg = efePosi - Vector3{ m_leftLeg->l_l_w_position.x, m_leftLeg->l_l_w_position.y, m_leftLeg->l_l_w_position.z };

			//����ɂ���ă_���[�W��ς���

				//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffLeftLeg.Length() <= 500.0f) //�_���[�W������͈�
			{
				m_leftLeg->L_l_w_HP -= 200.0f;
				
			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_rightArm != nullptr)	//�E��ɏ�񂪓����Ă���Ȃ�
		{
			//�e�ƍ��r�̋����𑪂�
			Vector3 diffRightArm = efePosi - Vector3{ m_rightArm->r_a_w_position.x, m_rightArm->r_a_w_position.y, m_rightArm->r_a_w_position.z };

			//����ɂ���ă_���[�W��ς���

				//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffRightArm.Length() <= 500.0f) //�_���[�W������͈�
			{
				m_rightArm->m_rightArmHP -= 200.0f;
				
			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_rightLeg != nullptr)	//�E���ɏ�񂪓����Ă���Ȃ�
		{
			//�e�ƍ��r�̋����𑪂�
			Vector3 diffRightLeg = efePosi - Vector3{ m_rightLeg->r_l_w_position.x, m_rightLeg->r_l_w_position.y, m_rightLeg->r_l_w_position.z };

			//����ɂ���ă_���[�W��ς���

				//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffRightLeg.Length() <= 500.0f) //�_���[�W������͈�
			{
				m_rightLeg->R_l_w_HP -= 200.0f;
				
			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_shoulder != nullptr)	//���ɏ�񂪓����Ă���Ȃ�
		{
			//�e�ƍ��r�̋����𑪂�
			Vector3 diffShoulder = efePosi - Vector3{ m_shoulder->s_w_position.x, m_shoulder->s_w_position.y, m_shoulder->s_w_position.z };

			//����ɂ���ă_���[�W��ς���

				//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffShoulder.Length() <= 500.0f) //�_���[�W������͈�
			{
				m_shoulder->S_w_HP -= 200.0f;
				
			}

		}
		//---------------------------------------------------------------------------------------------------
	}
	else if(No_tyakudan==false){

	
	//---------------------------------------------------------------------------------------------------
	if (b_a_player != nullptr)	//�v���C���[�̏�񂪓����Ă���Ȃ�
	{
		//�e�ƃv���C���[�̋����𑪂�
		Vector3 diffPlayer = firing_position - Vector3{ b_a_player->player_position.x, b_a_player->player_position.y + 50.0f, b_a_player->player_position.z };

		//����ɂ���ă_���[�W��ς���
		
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffPlayer.Length() <= 200.0f) //�_���[�W������͈�
			{
				b_a_player->m_playerHP -= 200.0f;
				DestroyWithImpactEffect();
			}
		
	}
	//---------------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------------
	if (m_leftArm != nullptr)	//���r�ɏ�񂪓����Ă���Ȃ�
	{
		//�e�ƍ��r�̋����𑪂�
		Vector3 diffLeftArm = firing_position - Vector3{ m_leftArm->l_a_w_position.x, m_leftArm->l_a_w_position.y, m_leftArm->l_a_w_position.z };

		//����ɂ���ă_���[�W��ς���
		
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffLeftArm.Length() <= 200.0f) //�_���[�W������͈�
			{
				m_leftArm->L_a_w_HP -= 200.0f;
				DestroyWithImpactEffect();
			}
		}
	//---------------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------------
	if (m_leftLeg != nullptr)	//�����ɏ�񂪓����Ă���Ȃ�
	{
		//�e�ƍ��r�̋����𑪂�
		Vector3 diffLeftLeg = firing_position - Vector3{ m_leftLeg->l_l_w_position.x, m_leftLeg->l_l_w_position.y, m_leftLeg->l_l_w_position.z };

		//����ɂ���ă_���[�W��ς���
		
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffLeftLeg.Length() <= 200.0f) //�_���[�W������͈�
			{
				m_leftLeg->L_l_w_HP -= 200.0f;
				DestroyWithImpactEffect();
			}
		
	}
	//---------------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------------
	if (m_rightArm != nullptr)	//�E��ɏ�񂪓����Ă���Ȃ�
	{
		//�e�ƍ��r�̋����𑪂�
		Vector3 diffRightArm = firing_position - Vector3{ m_rightArm->r_a_w_position.x, m_rightArm->r_a_w_position.y, m_rightArm->r_a_w_position.z };

		//����ɂ���ă_���[�W��ς���
		
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffRightArm.Length() <= 200.0f) //�_���[�W������͈�
			{
				m_rightArm->m_rightArmHP -= 200.0f;
				DestroyWithImpactEffect();
			}
		
	}
	//---------------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------------
	if (m_rightLeg != nullptr)	//�E���ɏ�񂪓����Ă���Ȃ�
	{
		//�e�ƍ��r�̋����𑪂�
		Vector3 diffRightLeg = firing_position - Vector3{ m_rightLeg->r_l_w_position.x, m_rightLeg->r_l_w_position.y, m_rightLeg->r_l_w_position.z };

		//����ɂ���ă_���[�W��ς���
		
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffRightLeg.Length() <= 200.0f) //�_���[�W������͈�
			{
				m_rightLeg->R_l_w_HP -= 200.0f;
				DestroyWithImpactEffect();
			}
		
	}
	//---------------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------------
	if (m_shoulder != nullptr)	//���ɏ�񂪓����Ă���Ȃ�
	{
		//�e�ƍ��r�̋����𑪂�
		Vector3 diffShoulder = firing_position - Vector3{ m_shoulder->s_w_position.x, m_shoulder->s_w_position.y, m_shoulder->s_w_position.z };

		//����ɂ���ă_���[�W��ς���
		
			//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffShoulder.Length() <= 200.0f) //�_���[�W������͈�
			{
				m_shoulder->S_w_HP -= 200.0f;
				DestroyWithImpactEffect();
			}
		
	}
	//---------------------------------------------------------------------------------------------------
}
}


void Boss_Cannon_attack::Render(RenderContext& rc)
{
	b_a_Bullet.Draw(rc);
}