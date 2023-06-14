#include "stdafx.h"
#include "EnemyBase.h"
#include "Game.h"
#include "Player.h"
#include "Drop_item.h"
#include "GameCamera.h"
#include "Combo.h"
#include "Enemy_HP_UI.h"


bool EnemyBase::Start()
{

	//�Q�[����T��
	m_game = FindGO<Game>("game");


	//�v���C���[��T��
	m_player = FindGO<Player>("player");


	//HP��UI�쐬
	m_HPUI = NewGO<Enemy_HP_UI>(1, "enemy_hp_ui");


	//�����̐���(���������鉹���Ȃ̂ŃC���X�^���X��ێ�������)
	m_asiotoSE = NewGO<SoundSource>(0);
	m_asiotoSE->Init(enRunning);					//������
	m_asiotoSE->SetVolume(0.8f * m_game->GetBGMVol());	//���ʒ���
	m_asiotoSE->Play(true);							//�Đ�
	m_asiotoSE->Stop();


	//�G�l�~�[�����G�t�F�N�g�̍Đ�
	PlayEffect(enEnemyHassei, m_enemyPosition, m_enemyRotation, { 10.0f,10.0f,10.0f });


	//�p�X�ړ��|�C���g�̍쐬
	MakePoint();


	//���퐶��
	WeaponSetUp();


	//�Q�[���S�ʂ̐ݒ�
	GameSetUp();


	//�G�l�~�[�̃��f���֌W�̏�����
	InitEnemyModel();


	return true;

}

void EnemyBase::WeaponSetUp()
{

	//���t���镐��̕ύX
	if (m_setWeapon == 1)		//�M�K�v���Y�}
	{

	}
	else if (m_setWeapon == 2)		//�}�V���K��
	{

		//���탂�f���ݒ�
		m_enemyWeaponModel.Init("Assets/modelData/machine_gun_enemy.tkm");
		m_enemyWeaponModel.SetScale(2.0f);
		m_enemyWeaponModel.SetPosition(m_weaponPosition);
		m_enemyWeaponModel.SetRotation(m_weaponRotation);
		m_enemyWeaponModel.Update();

	}
	else if (m_setWeapon == 3)		 //�w���t�@�C��
	{

	}
	else if (m_setWeapon == 4)		//�M�K�g���L���m��
	{

		//���탂�f���̐ݒ�
		m_enemyWeaponModel.Init("Assets/modelData/GIgaton_cannon.tkm");
		m_enemyWeaponModel.SetScale(1.3f);
		m_enemyWeaponModel.SetPosition(m_weaponPosition);
		m_enemyWeaponModel.SetRotation(m_weaponRotation);
		m_enemyWeaponModel.Update();

	}
	else if (m_setWeapon == 5)		//�~�T�C��
	{

	}
	else if (m_setWeapon == 6)		//��͖C
	{

		//���탂�f���̐ݒ�
		m_enemyWeaponModel.Init("Assets/modelData/battleship_gun_enemy.tkm");
		m_enemyWeaponModel.SetScale({ 3.0f ,5.0f,3.0f });
		m_enemyWeaponModel.SetPosition(m_weaponPosition);
		m_enemyWeaponModel.SetRotation(m_weaponRotation);
		m_enemyWeaponModel.Update();

	}

}

void EnemyBase::Update()
{

}

void EnemyBase::NormalAction(float dist)
{

	//�v���C���[�����S�����Ƃ��p
	m_asiotoSE->SetVolume(0.8f * m_game->GetSEVol());


	//�G�l�~�[�ƃv���C���[�̋����v�Z
	CalcDistance(dist);


	//����̈ړ���]
	WeaponMove();


	//�p�X�ړ��|�C���g�Ƀ��b�N�I�����Ă�Ȃ�
	if (m_lockOn == true)
	{

		//�p�X�ړ�
		PassMove();

	}
	//�p�X�ړ��|�C���g�Ƀ��b�N�I�����ĂȂ��Ȃ�
	else if (m_lockOn == false)
	{

		//���G
		PlayerSearch();


		//�ړ�
		Move();


		//�U��
		Attack();

	}


	//�G�l�~�[�X�V
	m_enemyModel.SetPosition(m_enemyPosition);
	m_enemyModel.SetRotation(m_enemyRotation);
	m_enemyModel.Update();

}

void EnemyBase::MakePoint()
{

	//�|�C���g�̍쐬
	m_pointList.push_back({ RandPos(),1 });		//��Ԗڂ̃|�C���g
	m_pointList.push_back({ RandPos(),2 });		//��Ԗڂ̃|�C���g
	m_pointList.push_back({ RandPos(),3 });		//�O�Ԗڂ̃|�C���g
	m_pointList.push_back({ RandPos(),4 });		//�l�Ԗڂ̃|�C���g


	//��Ԗڂ̃|�C���g������
	m_point = &m_pointList[0];

}

void EnemyBase::CalcDistance(float dist)
{

	//�G�l�~�[����v���C���[�ւ̃x�N�g��
	m_toPlayer = m_player->player_position - m_enemyPosition;


	//�v���C���[�Ƃ̋������v�Z����
	m_distToPlayer = m_toPlayer.Length();


	//�v���C���[�Ɍ������ĐL�т�x�N�g���𐳋K������
	m_toPlayerDir = m_toPlayer;
	m_toPlayerDir.Normalize();


	//�v���C���[�܂ł̋�������������Ƃ�
	if (m_distToPlayer > dist)
	{

		//�p�X�|�C���g�Ƀ��b�N�I��
		m_lockOn = true;

	}
	else
	{

		//�p�X�|�C���g���b�N�I������
		m_lockOn = false;

	}

}

void EnemyBase::CalcSpeed(float speed, int dirState)
{

	if (dirState == 0)	//�v���C���[����
	{

		//�O�����̐ݒ�
		m_enemyForward = m_toPlayerDir;


		//�ړ����x��ݒ�
		m_enemyMoveSpeed = m_enemyForward * speed;

	}
	else if (dirState == 1)	//�v���C���[�Ɣ��Ό���
	{

		//�O�����̐ݒ�
		m_enemyForward = m_toPlayerDir * -1.0;		

	}
	else if (dirState == 2)	//������1
	{

		//�O�ς���G�l�~�[�̉��������擾
		m_enemyForward = Cross(m_Up, m_toPlayerDir);	
		
		
		//�ړ����x�̐ݒ�
		m_enemyMoveSpeed = m_enemyForward * speed;

	}
	else if (dirState == 3)	//������2
	{

		//�O�ς���G�l�~�[�̉��������擾
		m_enemyForward = Cross(m_Up, m_toPlayerDir);	
		
		
		//�ړ����x�̐ݒ�
		m_enemyMoveSpeed = m_enemyForward * speed;

	}

}

void EnemyBase::PassMove()
{

	//�����̃|�W�V��������ڕW�Ƃ���|�C���g�̃x�N�g��
	Vector3 m_toPoint = m_point->m_position - m_enemyPosition;


	//�|�C���g�܂ł̋������v�Z
	float m_diffToPoint = m_toPoint.Length();


	//�|�C���g�܂ł̕����̌v�Z
	Vector3 m_toPointDir = m_toPoint;
	m_toPointDir.Normalize();


	//�O�����̐ݒ�
	m_enemyForward = m_toPointDir;


	//���������ȓ��Ȃ�
	if (m_diffToPoint < 20.0f)
	{

		//���ړI�n�Ƃ��Ă���|�C���g���z��̍Ō�̗v�f�Ȃ�
		if (m_point->m_num == m_pointList.size()) 
		{

			//��ԍŏ��̃|�C���g��ړI�n�Ƃ���
			m_point = &m_pointList[0];

		}
		else 
		{

			//�z��̎��̗v�f�̃|�C���g��ړI�n�Ƃ���
			m_point = &m_pointList[m_point->m_num];

		}

	}


	//�ړ�������B
	m_enemyMoveSpeed = m_enemyForward * 200.0f;
	m_enemyPosition = m_enemyCharacterController.Execute(m_enemyMoveSpeed, g_gameTime->GetFrameDeltaTime());


	//�G�l�~�[�̑O�������g���āA��]�N�H�[�^�j�I�����v�Z����B
	m_enemyRotation.SetRotationY(atan2(m_enemyForward.x, m_enemyForward.z));

}

void EnemyBase::Move()
{

}

void EnemyBase::PlayerSearch()
{
	
}

void EnemyBase::ExecuteOnEnemyDefeated()
{

	//���S���j�G�t�F
	EnemyDead();


	//�A�C�e���h���b�v�̏���
	ItemDrop();


	//���񂾃G�l�~�[�̐��𑝂₷
	m_game->AddDefeatedEnemyNumber();


	//�E�������𑝂₷
	m_player->killEnemy++;	


	//��ʂ�h�炷
	GameCamera* m_camera = FindGO<GameCamera>("gamecamera");
	m_camera->VibFlag = true;


	//�R���{�̏���
	Combo* m_combo = FindGO<Combo>("combo");
	m_combo->ComboUpdate();

}

void EnemyBase::ItemDrop()
{

	//�h���b�v�A�C�e���̐���
	m_dropItem = NewGO<Drop_item>(1, "drop_item");


	//�h���b�v�A�C�e���̏ꏊ�̌���
	m_dropItem->Drop_position = m_enemyPosition;
	m_dropItem->Drop_position.y += 50.0f;


	//�G�l�~�[���ǂ̕���������Ă������擾
	m_dropItem->drop_kinds = m_setWeapon;


	//�쐬�����A�C�e�����R���e�i�ɂ�������
	m_game->GetDropItemObject().push_back(m_dropItem);

}

void EnemyBase::WeaponMove()
{

	//���킪�G�l�~�[�Ɠ�������������悤�ɂ���(�e�q�֌W)
	Quaternion originRotation = m_enemyRotation;	//��]�̓G�l�~�[�Ɠ���
	Vector3 localPos = m_weaponLocalPos;			//�e���猩���ʒu�̒�`
	originRotation.Multiply(localPos);				//�|���Z


	//�ŏI�I�ȕ���̉�]������
	m_weaponRotation = originRotation;


	//����̈ʒu���G�l�~�[�Ɠ����ɐݒ�
	m_weaponPosition = m_enemyPosition;		
	
	
	//�e���猩���ʒu�𑫂��čŏI�I�ȕ���̈ʒu������
	m_weaponPosition += localPos;


	//�X�V
	m_enemyWeaponModel.SetPosition(m_weaponPosition);
	m_enemyWeaponModel.SetRotation(m_weaponRotation);
	m_enemyWeaponModel.Update();

}

void EnemyBase::Attack()
{

}

void EnemyBase::Fire(int m_weaponNum)
{

}

void EnemyBase::DustEffect()
{

	//���ڂ���̊Ԋu�J�E���g
	m_sunaHassei++;


	//�J�E���g�����ȏ�ɂȂ��
	if (m_sunaHassei >= 10)
	{

		//���ڂ���G�t�F�N�g�̍Đ�
		PlayEffect(enSunabokori, { m_enemyPosition.x,m_enemyPosition.y + 10.0f ,m_enemyPosition.z }, m_enemyRotation, { 4.0f,4.0f,4.0f });


		//�J�E���g���Z�b�g
		m_sunaHassei = 0;

	}

}

void EnemyBase::AsiotoSEManage(bool play)
{

	//������ϐ��ɑ��
	m_asiotoPlay = play;


	//�t���O�����������������Đ�����ĂȂ��Ƃ�
	if (m_asiotoPlay == true && m_asiotoSE->IsPlaying() != true)
	{

		//�����Đ�
		m_asiotoSE->Play(true);

	}
	//�t���O��������ꂽ��
	else if(m_asiotoPlay == false)
	{

		//������~
		m_asiotoSE->Stop();

	}

}

void EnemyBase::EnemyDead()
{

}

void EnemyBase::PlayEffect(EffectName name,Vector3 pos,Quaternion rot,Vector3 scale)
{

	//�G�t�F�N�g�̍Đ�
	EffectEmitter* m_effect = NewGO<EffectEmitter>(0);
	m_effect->Init(name);
	m_effect->SetPosition(pos);
	m_effect->SetRotation(rot);
	m_effect->SetScale(scale);
	m_effect->Play();

}

Vector3 EnemyBase::RandPos()
{

	Vector3 m_pos;

	//�����_���Ƀ|�W�V�����𓖂Ă͂߂�
	m_pos.x = rand() % 4800 - 2400;
	m_pos.y = 0.0f;
	m_pos.z = rand() % 9000;

	return m_pos;

}

void EnemyBase::Render(RenderContext& rc)
{

}

