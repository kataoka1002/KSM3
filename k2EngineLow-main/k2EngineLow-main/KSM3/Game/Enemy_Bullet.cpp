#include "stdafx.h"
#include "Customize_UI_ver2.h"
#include "Enemy_Bullet.h"
#include "Core_weapons.h"
#include "Enemy.h"
#include "Enemy_Near.h"
#include "Enemy_Far.h"
#include "Player.h"
#include "Game.h"
#include "GameCamera.h"
#include "sound/SoundEngine.h"
#include "Left_arm_weapons.h"
#include "Left_leg_weapons.h"
#include "Right_arm_weapons.h"
#include "Right_leg_weapons.h"
#include "Shoulder_weapons.h"


namespace
{
	//�Ώە��Ƃ̓����蔻�苗��
	const float RANGE_DISTANCE = 100.0f;

	//�_���[�W��
	const float ENEMY_MACHINEGUN_DAMAGE = 0.5f;
	const float ENEMY_GIGATONCANNON_DAMAGE = 50.0f;
	const float ENEMY_BATTLESHIPGUN_DAMAGE = 25.0f;

	//�X�s�[�h
	const float MACHINEGUN_BULLET_SPEED = 2.0f;
	const float GIGATONCANNON_BULLET_SPEED = 2.0f;
	const float BATTLESHIPGUN_BULLET_SPEED = 1.7f;

	//�e�̃��f���̑傫��
	const Vector3 MACHINEGUN_BULLET_SCALE = { 4.0f,4.0f,4.0f };
	const Vector3 GIGATONCANNON_BULLET_SCALE = { 15.0f,15.0f,10.0f };
	const Vector3 BATTLESHIPGUN_BULLET_SCALE = { 10.0f,10.0f,10.0f };

	//�G�t�F�N�g�̑傫��
	const Vector3 MACHINEGUNE_EFFECT_SCALE = { 10.0f,10.0f,10.0f };
	const Vector3 BATTLESHIPGUN_EFFECT_SCALE = { 5.7f, 5.7f, 5.7f };
}


Enemy_Bullet::Enemy_Bullet() 
{
	
}

Enemy_Bullet::~Enemy_Bullet() 
{
	
}

void Enemy_Bullet::DestroyWithImpactEffect()
{

	//�������G�l�~�[�̂Ƃ�
	if (m_enemyMama != nullptr)
	{

		//�}�V���K���̂Ƃ�
		if (m_enemyMama->GetWeponKind() == MACHINEGUN_NUM)
		{
			
			//�}�V���K���̒e�̉��G�t�F
			PlayEffect(enMasinganKemuri, m_position, m_rot, MACHINEGUNE_EFFECT_SCALE);

		}

	}
	//�ߋ����G�l�~�[�̂Ƃ�
	else if (m_enemyNearMama != nullptr)
	{

		//�M�K�g���L���m���̂Ƃ�
		if (m_enemyNearMama->GetWeponKind() == GIGATONCANNON_NUM)
		{

			//��ʂ�h�炷
			GameCamera* m_camera = FindGO<GameCamera>("gamecamera");
			m_camera->SetVibFlag(true);

		}

	}
	//�������G�l�~�[�̂Ƃ�
	else if (m_enemyFarMama != nullptr)
	{
		
		//��͖C�̂Ƃ�
		if (m_enemyFarMama->GetWeponKind() == BATTLESHIPGUN_NUM)	
		{

			//��͖C�G�t�F�N�g�̏������ƍĐ�
			PlayEffect(enTyakudan, m_position, m_rot, BATTLESHIPGUN_EFFECT_SCALE);


			//���e��������ʉ�����
			m_battleShipGunTyakutiSE = NewGO<SoundSource>(0);			//���Đ�����ƏI���Ȃ̂ŃC���X�^���X��ێ������Ȃ��ׂɂ�����NewGO����
			m_battleShipGunTyakutiSE->Init(enButtleShipTyakudan);		//������
			m_battleShipGunTyakutiSE->SetVolume(2.0f * m_game->GetSEVol());	//���ʒ���
			m_battleShipGunTyakutiSE->Play(false);


			//��ʂ�h�炷
			GameCamera* m_camera = FindGO<GameCamera>("gamecamera");
			m_camera->SetVibFlag(true);

		}
	}


	//�������g�̍폜
	DeleteGO(this);

}

bool Enemy_Bullet::Start()
{

	//�v���C���[��T��
	m_player = FindGO<Player>("player");


	//���U���g���Ȃ�
	if (m_player->GetGameState() == RESULT_NUM)
	{

		//�������g�̍폜
		DeleteGO(this);

	}


	//�J�X�^�}�C�YUI��T��
	m_customizeUI = FindGO<Customize_UI_ver2>("customize_ui_ver2");


	//�R�A�����T��
	m_coreWeapons = FindGO<Core_weapons>("core_weapons");


	//�Q�[����T��
	m_game = FindGO<Game>("game");


	//�v���C���[�̕������������
	FindWeapon();	
	
	
	//�����G�t�F�N�g�̐ݒ�
	Setup();		

		
	return true;

}

void Enemy_Bullet::FindWeapon()
{

	//�v���C���[������ł����烊�^�[��
	if (m_player->GetPlayerDead() == true)
	{
		return;
	}


	//���r�����݂�����
	if (m_customizeUI->GetLeftArmWeapon() != nullptr)
	{
		
		//�J�X�^�}�C�YUI�ɂ���|�C���^��n���Ă��
		m_leftArm = m_customizeUI->GetLeftArmWeapon();

	}

	//���������݂�����
	if (m_customizeUI->GetLeftLegWeapon() != nullptr)
	{
		
		//�J�X�^�}�C�YUI�ɂ���|�C���^��n���Ă��
		m_leftLeg = m_customizeUI->GetLeftLegWeapon();

	}

	//�E�r�����݂�����
	if (m_customizeUI->GetRightArmWeapon() != nullptr)
	{
		
		//�J�X�^�}�C�YUI�ɂ���|�C���^��n���Ă��
		m_rightArm = m_customizeUI->GetRightArmWeapon();

	}

	//�E�������݂�����
	if (m_customizeUI->GetRightLegWeapon() != nullptr)
	{
		
		//�J�X�^�}�C�YUI�ɂ���|�C���^��n���Ă��
		m_rightLeg = m_customizeUI->GetRightLegWeapon();

	}

	//�������݂�����
	if (m_customizeUI->GetShoulderWeapon() != nullptr)
	{
		
		//�J�X�^�}�C�YUI�ɂ���|�C���^��n���Ă��
		m_shoulder = m_customizeUI->GetShoulderWeapon();

	}

}

void Enemy_Bullet::Setup() 
{

	//�������̊m��(make_unique�֐�������new���Ă���)
	m_bulletModel = std::make_unique<ModelRender>();


	//�e���������G�l�~�[�̂Ƃ�
	if (m_enemyMama != nullptr)
	{

		switch (m_enemyMama->GetWeponKind())
		{
		case GIGAPLASMA_NUM:	//�M�K�v���Y�}

			break;

		case MACHINEGUN_NUM:	//�}�V���K��

			//���f���̏�����
			InitBullet("Assets/modelData/V_P_bullet.tkm", MACHINEGUN_BULLET_SCALE, m_enemyMama->GetForward(), m_enemyMama->GetRot());
			

			//�G�t�F�N�g�̍Đ�
			Effect(MACHINEGUN_NUM);
			
			//���̓G�l�~�[���Ŗ炵�Ă���

			break;

		case HELLFIRE_NUM:	//�w�C���t�@�C���[���C�t��

			break;

		default:

			break;

		}

	}
	//�e���ߋ����G�l�~�[�̂Ƃ�
	else if (m_enemyNearMama != nullptr)
	{

		switch (m_enemyNearMama->GetWeponKind())
		{
		case GIGATONCANNON_NUM:	//�M�K�g���L���m��

			//���f���̏�����
			InitBullet("Assets/modelData/V_P_bullet.tkm", GIGATONCANNON_BULLET_SCALE, m_enemyNearMama->GetForward(), m_enemyNearMama->GetRot());
			

			//�G�t�F�N�g�̍Đ�
			Effect(GIGATONCANNON_NUM);

			//�������̓G�l�~�[���Ŗ炵�Ă���

			break;

		default:

			break;

		}

	}
	//�e�����G�l�~�[�̂Ƃ�
	else if (m_enemyFarMama != nullptr)
	{

		switch (m_enemyFarMama->GetWeponKind())
		{
		case MISSILE_NUM:	//�~�T�C��

			break;

		case BATTLESHIPGUN_NUM:	//��͖C

			//���f���̏�����
			InitBullet("Assets/modelData/V_P_bullet.tkm", BATTLESHIPGUN_BULLET_SCALE, m_enemyFarMama->GetForward(), m_enemyFarMama->GetRot());


			//�G�t�F�N�g�̍Đ�
			Effect(BATTLESHIPGUN_NUM);

			break;

		default:

			break;

		}

	}

}

void Enemy_Bullet::InitBullet(const char* file, Vector3 scale, Vector3 forward, Quaternion rot)
{

	//���f���̏�����
	m_bulletModel->Init(file);


	//�傫���ݒ�
	m_bulletModel->SetScale(scale);


	//�G�l�~�[���猩�Đ������ʒu�ɒe��ݒ�
	originRotation.Multiply(m_bulletLocalPosition);	


	//��]�ʂ�������
	m_rot = originRotation;

	
	//����ɐe���猩���ʒu�𑫂��čŏI�I�ȕ���̈ʒu������
	m_position += m_bulletLocalPosition;	


	//�o���b�g�̑O�����̐ݒ�
	m_bulletFowrad = forward;


	//�X�V
	m_bulletModel->SetRotation(rot);
	m_bulletModel->SetPosition(m_position);

}

void Enemy_Bullet::Update() 
{

	//���C���Q�[����
	if (m_player->GetGameState() == MAIN_GAME_NUM)
	{

		//�ʒuY��0�ȉ��ɂȂ��
		if (m_position.y <= 0.0f)
		{

			//�폜���G�t�F�N�g���Đ�
			DestroyWithImpactEffect();

		}


		//�e�ɂ���Ċ֐���ς���
		if (m_enemyMama != nullptr)
		{

			//�ړ�����
			Move();	


			//�^�[�Q�b�g��T��
			MamaCheck(m_enemyMama->GetWeponKind());

		}
		else if (m_enemyNearMama != nullptr)
		{

			//�ړ�����
			MoveNear();


			//�^�[�Q�b�g��T��
			MamaCheck(m_enemyNearMama->GetWeponKind());

		}
		else if (m_enemyFarMama != nullptr)
		{

			//�ړ�����
			MoveFar();


			//�^�[�Q�b�g��T��
			MamaCheck(m_enemyFarMama->GetWeponKind());

		}

	}	
	//���U���g��
	else if (m_player->GetGameState() == RESULT_NUM)
	{

		//�������g�̍폜
		DeleteGO(this);

	}

	
	//�v���C���[���|�[�Y��ʂ���Q�[�����I���������
	if (m_player->GetGameEndState() == 1)
	{

		//�������g�̍폜
		DeleteGO(this);	

	}

}

void Enemy_Bullet::Move()
{
	
	//�M�K�v���Y�}
	if (m_enemyMama->GetWeponKind() == GIGAPLASMA_NUM)	
	{

	}
	//�}�V���K��
	else if (m_enemyMama->GetWeponKind() == MACHINEGUN_NUM)	
	{

		//�e��O�ɔ�΂�
		m_bulletSpeed += m_bulletFowrad * MACHINEGUN_BULLET_SPEED;
		m_position += m_bulletSpeed;


		//�e�ƃG�l�~�[(�e)�̋������v�Z
		Vector3 m_toEnemy = m_enemyMama->GetPos() - m_position;
		float m_dirToEnemy = m_toEnemy.Length();


		//��苗���ȏ�Ȃ�
		if (m_dirToEnemy >= 1800.0f)
		{

			//�e������
			DestroyWithImpactEffect();

		}


		//�o���b�g�̍X�V
		m_bulletModel->SetRotation(m_rot);
		m_bulletModel->SetPosition(m_position);
		m_bulletModel->Update();

	}
	//�w���t�@�C�����C�t��
	else if (m_enemyMama->GetWeponKind() == HELLFIRE_NUM)	
	{

	}

}

void Enemy_Bullet::MoveNear()
{
	
	//�M�K�g���L���m��
	if (m_enemyNearMama->GetWeponKind() == GIGATONCANNON_NUM)	
	{

		//�e��O�ɔ�΂�
		m_bulletSpeed += m_bulletFowrad * GIGATONCANNON_BULLET_SPEED;
		m_position += m_bulletSpeed;


		//�e�ƃG�l�~�[(�e)�̋������v�Z
		Vector3 m_toEnemy = m_enemyNearMama->GetPos() - m_position;
		float m_dirToEnemy = m_toEnemy.Length();
		
		
		//��苗���ȏ�Ȃ�
		if (m_dirToEnemy >= 100.0f)
		{
			
			//�e������
			DestroyWithImpactEffect();

		}


		//�o���b�g�̍X�V
		m_bulletModel->SetRotation(m_rot);
		m_bulletModel->SetPosition(m_position);
		m_bulletModel->Update();

	}

}

void Enemy_Bullet::MoveFar()
{
	
	//�~�T�C��
	if (m_enemyFarMama->GetWeponKind() == MISSILE_NUM)	
	{

	}
	//��͖C
	else if (m_enemyFarMama->GetWeponKind() == BATTLESHIPGUN_NUM)	
	{

		//�e��O�ɔ�΂�
		m_bulletSpeed += m_bulletFowrad * BATTLESHIPGUN_BULLET_SPEED;


		//�����Â��ɗ��Ƃ�
		m_bulletSpeed.y -= 0.1f;
		m_position += m_bulletSpeed;


		//�o���b�g�̍X�V
		m_bulletModel->SetRotation(m_rot);
		m_bulletModel->SetPosition(m_position);
		m_bulletModel->Update();

	}

}

void Enemy_Bullet::Effect(int num)
{

	if (num == GIGAPLASMA_NUM)
	{

	}
	else if (num == MACHINEGUN_NUM)
	{

		//�G�t�F�N�g�̏������ƍĐ�
		PlayEffect(enMasinganHibana, m_position, m_rot, { 0.7f,0.7f,0.7f });

	}
	else if (num == HELLFIRE_NUM)
	{

	}
	else if (num == GIGATONCANNON_NUM)
	{

		//�G�t�F�N�g�̏������ƍĐ�
		PlayEffect(enHidan, m_position, m_rot, { 1.5f,1.5f,1.5f });

	}
	else if (num == MISSILE_NUM)
	{

	}
	else if (num == BATTLESHIPGUN_NUM)
	{

		//�G�t�F�N�g�̏������ƍĐ�
		PlayEffect(enMasinganHibana, m_position, m_rot, { 0.7f,0.7f,0.7f });

	}

}

void Enemy_Bullet::MamaCheck(int weaponNum)
{
	
	//�v���C���[�̏�񂪓����Ă���Ȃ�
	if (m_player != nullptr)	
	{

		//�����𑪂�_���[�W��^����
		ApplyDamageWithDistanceCheck(m_player, Vector3{ m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y + 50.0f, m_player->GetPlayerPosition().z }, weaponNum);
	
	}

	
	//���r�ɏ�񂪓����Ă���Ȃ�
	if (m_leftArm != nullptr)	
	{

		//�����𑪂�_���[�W��^����
		ApplyDamageWithDistanceCheck(m_leftArm, m_leftArm->GetPosition(), weaponNum);
	
	}

	
	//�����ɏ�񂪓����Ă���Ȃ�
	if (m_leftLeg != nullptr)	
	{

		//�����𑪂�_���[�W��^����
		ApplyDamageWithDistanceCheck(m_leftLeg, m_leftLeg->GetPosition(), weaponNum);

	}

	
	//�E��ɏ�񂪓����Ă���Ȃ�
	if (m_rightArm != nullptr)	
	{

		//�����𑪂�_���[�W��^����
		ApplyDamageWithDistanceCheck(m_rightArm, m_rightArm->GetPosition(), weaponNum);

	}

	
	//�E���ɏ�񂪓����Ă���Ȃ�
	if (m_rightLeg != nullptr)	
	{

		//�����𑪂�_���[�W��^����
		ApplyDamageWithDistanceCheck(m_rightLeg, m_rightLeg->GetPosition(), weaponNum);

	}

	
	//���ɏ�񂪓����Ă���Ȃ�
	if (m_shoulder != nullptr)	
	{

		//�����𑪂�_���[�W��^����
		ApplyDamageWithDistanceCheck(m_shoulder, m_shoulder->GetPosition(), weaponNum);

	}

}

template<typename T>
void Enemy_Bullet::ApplyDamageWithDistanceCheck(T targetName, Vector3 targetPos, int weaponNum)
{

	//�Ώە��܂ł̃x�N�g�������߂�
	Vector3 targetToBullet = m_position - targetPos;


	//�}�V���K��
	if (weaponNum == MACHINEGUN_NUM)			
	{

		//���������ȉ��Ȃ�
		if (targetToBullet.Length() <= RANGE_DISTANCE) 
		{

			//�_���[�W��^����
			targetName->ApplyDamage(ENEMY_MACHINEGUN_DAMAGE);


			//���G�t�F�N�g���Đ�
			DestroyWithImpactEffect();

		}

	}
	//�M�K�g���L���m��
	else if (weaponNum == GIGATONCANNON_NUM)		
	{

		//���������ȉ��Ȃ�
		if (targetToBullet.Length() <= RANGE_DISTANCE) 
		{
			
			//�_���[�W��^����
			targetName->ApplyDamage(ENEMY_GIGATONCANNON_DAMAGE);
			
			
			//���G�t�F�N�g���Đ�
			DestroyWithImpactEffect();

		}

	}
	//��͖C
	else if (weaponNum == BATTLESHIPGUN_NUM)	
	{

		//���������ȉ��Ȃ�
		if (targetToBullet.Length() <= RANGE_DISTANCE) 
		{
			
			//�_���[�W��^����
			targetName->ApplyDamage(ENEMY_BATTLESHIPGUN_DAMAGE);
			
			
			//���G�t�F�N�g���Đ�
			DestroyWithImpactEffect();

		}

	}

}

void Enemy_Bullet::PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale)
{

	//�G�t�F�N�g�̍Đ�
	EffectEmitter* m_effect = NewGO<EffectEmitter>(0);
	m_effect->Init(name);
	m_effect->SetPosition(pos);
	m_effect->SetRotation(rot);
	m_effect->SetScale(scale);
	m_effect->Play();

}

void Enemy_Bullet::Render(RenderContext& rc)
{

	//�e��������
	if (m_enemyMama != nullptr)
	{
		
		//�M�K�v���Y�}
		if (m_enemyMama->GetWeponKind() == GIGAPLASMA_NUM)	
		{

		}
		//�}�V���K��
		else if (m_enemyMama->GetWeponKind() == MACHINEGUN_NUM)	
		{

			//�e�̕`��
			m_bulletModel->Draw(rc);

		}
		//�w�C���t�@�C���[���C�t��
		else if (m_enemyMama->GetWeponKind() == HELLFIRE_NUM)	
		{

		}

	}
	//�e���ߋ���
	else if (m_enemyNearMama != nullptr)
	{

		//�M�K�g���L���m��
		if (m_enemyNearMama->GetWeponKind() == GIGATONCANNON_NUM)	
		{
			
			//�e�̕`��
			m_bulletModel->Draw(rc);

		}

	}
	//�e��������
	else if (m_enemyFarMama != nullptr)
	{
		
		//�~�T�C��
		if (m_enemyFarMama->GetWeponKind() == MISSILE_NUM)	
		{

		}
		//��͖C
		else if (m_enemyFarMama->GetWeponKind() == BATTLESHIPGUN_NUM)	
		{
			
			//�e�̕`��
			m_bulletModel->Draw(rc);

		}

	}

}