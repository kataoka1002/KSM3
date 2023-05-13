#include "stdafx.h"
#include "Player.h"
#include <math.h>
#include "Left_arm_weapons.h"
#include "Customize_UI_ver2.h"
#include "Game.h"
#include "Result.h"


Player::Player() 
{
	
	//�v���C���[�̃��f���ƃ|�[�Y��ʂ̃X�v���C�g�̏�����
	player_modelRender.Init("Assets/modelData/player.tkm");
	pouse_spriteRender.Init("Assets/sprite/pouse.DDS", 1920.0f, 1080.0f);
	//�L�����R���̐ݒ�
	characterController.Init(70.0f, 150.0f, player_position);
}

Player::~Player()
{
	DeleteGO(m_machineGunSE);
}

bool Player::Start()
{
	m_game = FindGO<Game>("game");

	//���ʉ��̍쐬(���������鉹���Ȃ̂ŃC���X�^���X��ێ�������)
	m_machineGunSE = NewGO<SoundSource>(0);
	m_runSE = NewGO<SoundSource>(0);
	m_walkSE = NewGO<SoundSource>(0);

	//���ʉ��̐ݒ�
	m_machineGunSE->Init(enMachineGun);	//������
	m_machineGunSE->SetVolume(0.5f * m_game->SEvol);	//���ʒ���
	m_runSE->Init(enPlayerRun);	//������
	m_runSE->SetVolume(0.5f * m_game->SEvol);	//���ʒ���
	m_walkSE->Init(enRunning);	//������
	m_walkSE->SetVolume(0.5f * m_game->SEvol);	//���ʒ���


	return true;
}

void Player::Update() 
{
	if (game_state == 0) //���C���Q�[��
	{
		Move();			//�ړ�����
		MachineGunSE();	//�}�V���K���̌��ʉ��Đ�
		RunSE();		//�����̍Đ�

		//�X�^�[�g�{�^��������ƃ|�[�Y��ʂɈړ�
		if (g_pad[0]->IsTrigger(enButtonStart)) 
		{
			game_state = 1;
		}
		if (g_pad[0]->IsTrigger(enButtonA)) 
		{
			p_customize_ui_ver2 = NewGO<Customize_UI_ver2>(1, "customize_ui_ver2");
		}

		//���f���̍X�V
		player_modelRender.Update(true);
	}
	else if (game_state == 1) //�|�[�Y���
	{
		pause();
	}

	//HP��0�ȉ��ɂȂ�Ȃ�Ǝ��S
	if (m_playerHP <= 0)
	{
		//���S�̉��o

		//���U���g��
		m_result = NewGO<Result>(1, "result");
	}
}

void Player::Move()
{
	player_moveSpeed = { 0.0f,0.0f,0.0f };//�ړ����x�̏�����

	Vector3 stickL;
	throttle = 0;
	stickL.x = g_pad[0]->GetLStickXF();
	//�X�e�B�b�N��|�����ʂ̎擾
	throttle = g_pad[0]->GetRTrigger();

	Vector3 right = g_camera3D->GetRight();
	right.y = 0.0f;
	right *= stickL.x * 120.0f;

	//�X�s�[�h��0����Ȃ��Ȃ�G�t�F�N�g��o��
	if (throttle != 0)
	{
		MakeEfe();	
	}
		
	playerFowrad.Normalize();

	//x��z�̈ړ����x����������(�X�e�B�b�N�̓��͂���������)�B
	//��]����
	if (stickL.x!=0.0f)
	{
		playerFowrad.x = playerFowrad.x * cos(stickL.x * -0.05) - playerFowrad.z * sin(stickL.x * -0.05);
		playerFowrad.z = playerFowrad.x * sin(stickL.x * -0.05) + playerFowrad.z * cos(stickL.x * -0.05);

		player_rotation.SetRotationY(atan2(playerFowrad.x, playerFowrad.z));
	}
	//��]���Ă��Ȃ��Ƃ��̈ړ�
	if (throttle != 0.0f) 
	{
		//���񂾂񑬂�����
		accelerator += 0.05;
		if (accelerator >= 2) 
		{
			accelerator = 2;	//�ő�l��2
		}
	}
	else 
	{
		//���񂾂�x������
		accelerator -= 0.05;
		if (accelerator <= 0) 
		{
			accelerator = 0;	//�ŏ��l��0
		}
	}

	move_s = 4.0f * accelerator;
	player_moveSpeed += playerFowrad  * move_s * (throttle / 2.0f);

	player_position = characterController.Execute(player_moveSpeed, 1.0f / 60.0f);

	//���W�������B
	player_modelRender.SetPosition(player_position);
	player_modelRender.SetRotation(player_rotation);
}

void Player::MakeEfe()
{
	//�v���C���[�̃{�^��������Ă���ʂɂ���č��ڂ���̗ʂ�ς���
	if (throttle < 126.0f)
	{
		//�����Ă����7�t���[�����Ƃɍ��ڂ���𔭐�������
		if (effectCount > 20)
		{
			//���ڂ���G�t�F�N�g�̏������ƍĐ�
			sunabokoriEffect = NewGO<EffectEmitter>(0);
			sunabokoriEffect->Init(enSunabokori);
			sunabokoriEffect->SetScale({ 4.0f,4.0f,4.0f });
			sunabokoriEffect->SetRotation(player_rotation);
			sunabokoriEffect->SetPosition(player_position);
			sunabokoriEffect->Play();

			effectCount = 0;	//�J�E���g���Z�b�g
		}
	}
	else if (throttle > 127.0f)
	{
		//�����Ă����3�t���[�����Ƃɍ��ڂ���𔭐�������
		if (effectCount > 3)
		{
			//���ڂ���G�t�F�N�g�̏������ƍĐ�
			sunabokoriEffect = NewGO<EffectEmitter>(0);
			sunabokoriEffect->Init(enSunabokori);
			sunabokoriEffect->SetScale({ 4.0f,4.0f,4.0f });
			sunabokoriEffect->SetRotation(player_rotation);
			sunabokoriEffect->SetPosition(player_position);
			sunabokoriEffect->Play();

			effectCount = 0;	//�J�E���g���Z�b�g
		}
	}
	effectCount++;
}

void Player::pause() 
{
	if (g_pad[0]->IsTrigger(enButtonB)) 
	{
		game_state = 0;	//���C���Q�[���ɖ߂�
	}
	else if (g_pad[0]->IsTrigger(enButtonA)) 
	{
		game_end_state = 1;	//�Q�[���I��
	}
}

void Player::RunSE()
{
	if (throttle <= 0)	//�����ĂȂ���
	{
		//���ʉ���~
		m_walkSE->Stop();
		m_runSE->Stop();

		return;
	}

	if (throttle > 0 && throttle <= 127 && m_runSE->IsPlaying() != true)	//������蓮���Ă��鎞
	{
		//������Đ�
		m_walkSE->Play(true);
	}
	else if (throttle > 127 && m_walkSE->IsPlaying() != true)	//���������Ă��鎞
	{
		//���鉹�Đ�
		m_runSE->Play(true);
	}


	//�����Ă���Ƃ�����̉��͎~�߂�
	if (throttle > 127)
	{
		m_walkSE->Stop();
	}
	//����Ă���Ƃ�����̉��͎~�߂�
	if (throttle > 0 && throttle <= 127)
	{
		m_runSE->Stop();
	}
}

void Player::MachineGunSE()
{
	if (g_pad[0]->IsPress(enButtonRB1) && m_machineGunSE->IsPlaying() != true)
	{
		m_machineGunSE->Play(true);	//�����čĐ�
	}
	else if(g_pad[0]->IsPress(enButtonRB1) == false)
	{
		m_machineGunSE->Stop();		//�U������Ȃ��Ȃ��~
	}
}

void Player::Render(RenderContext& rc)
{
	player_modelRender.Draw(rc);

	//�|�[�Y���Ȃ�|�[�Y��ʂ�\��
	if (game_state == 1)
	{
		pouse_spriteRender.Draw(rc);
	}
}