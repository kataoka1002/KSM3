#include "stdafx.h"
#include "Enemy_HP_UI.h"
#include "Enemy_Near.h"
#include "Enemy.h"
#include "Enemy_Far.h"
#include "Player.h"
#include "Game.h"
#include "GameCamera.h"

namespace
{
	//�X�v���C�g�̃T�C�Y
	const Vector3 HP_BER_SIZE = { 186.0f,13.0f,1.0f };		
	const Vector3 HP_FRAME_SIZE = { 195.0f,22.0f,1.0f };	

	//HP�o�[�̃��[�J���|�W�V����
	const float ENEMY_NEAR_HP_BER_POS_Y = 160.0f;
	const float ENEMY_HP_BER_POS_Y = 130.0f;
	const float ENEMY_FAR_HP_BER_POS_Y = 250.0f;
}

Enemy_HP_UI::Enemy_HP_UI()
{

	//HP�o�[�̏�����
	m_HPSprite.Init("Assets/sprite/enemy/enemyHP3.dds", HP_BER_SIZE.x, HP_BER_SIZE.y);
	m_HPSprite.SetScale(m_scale);


	//HP�t���[���̏�����
	m_HPFrameSprite.Init("Assets/sprite/enemy/enemyHPFrame.dds", HP_FRAME_SIZE.x, HP_FRAME_SIZE.y);
	m_HPFrameSprite.SetScale(m_scale);

}

Enemy_HP_UI::~Enemy_HP_UI()
{
	
}

bool Enemy_HP_UI::Start()
{

	//�N���X��������
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");
	m_camera = FindGO<GameCamera>("gamecamera");


	return true;
}

void Enemy_HP_UI::Update()
{	

	//�傫���̌v�Z����
	CalcScale();


	//�|�W�V�����̏���
	CalcPosition();

}

void Enemy_HP_UI::CalcPosition()
{
	Vector3 pos;

	//�e�ɂ���ă|�W�V������ς���
	if (m_enemyNear != nullptr)
	{

		//�|�W�V�����̎擾
		pos = m_enemyNear->GetPos();


		//�G�l�~�[�̏�̕��ɉ摜��\���������̂�,y���W�������傫������B
		pos.y += ENEMY_NEAR_HP_BER_POS_Y;

	}
	else if (m_enemy != nullptr)
	{

		//�|�W�V�����̎擾
		pos = m_enemy->GetPos();


		//�G�l�~�[�̏�̕��ɉ摜��\���������̂�,y���W�������傫������B
		pos.y += ENEMY_HP_BER_POS_Y;

	}
	else if (m_enemyFar != nullptr)
	{

		//�|�W�V�����̎擾
		pos = m_enemyFar->GetPos();


		//�G�l�~�[�̏�̕��ɉ摜��\���������̂�,y���W�������傫������B
		pos.y += ENEMY_FAR_HP_BER_POS_Y;

	}

	
	//���[���h���W����X�N���[�����W���v�Z(�v�Z���ʂ�m_position�ɑ�������)
	g_camera3D->CalcScreenPositionFromWorldPosition(m_position, pos);


	//�t���[�����Z�b�g����
	m_HPFrameSprite.SetPosition(Vector3(m_position.x, m_position.y, 0.0f));
	m_HPFrameSprite.Update();


	//�摜�����Ɋ񂹂�
	Vector3 BerSizeSubtraction = SendHPBer(HP_BER_SIZE, m_scale);
	m_position.x -= BerSizeSubtraction.x;


	//HP�o�[���Z�b�g����
	m_HPSprite.SetPosition(Vector3(m_position.x, m_position.y, 0.0f));
	m_HPSprite.Update();	

}

void Enemy_HP_UI::CalcScale()
{
	//�e�ɂ���ăT�C�Y��ς���B
	//�e�̗̑͂̊�������UI�̃T�C�Y���v�Z���Ă���B
	if (m_enemyNear != nullptr)
	{
		m_scale.x = m_enemyNear->GetHP() * (1.0 / m_enemyNear->GetMaxHP());
	}
	else if (m_enemy != nullptr)
	{
		m_scale.x = m_enemy->GetHP() * (1.0 / m_enemy->GetMaxHP());
	}
	else if (m_enemyFar != nullptr)
	{
		m_scale.x = m_enemyFar->GetHP() * (1.0 / m_enemyFar->GetMaxHP());
	}

	//�T�C�Y��0��菬�����Ȃ�Ȃ�
	if (m_scale.x <= 0.0f)
	{
		m_scale.x = 0.0f;
	}
	
	m_HPSprite.SetScale(m_scale);
	m_HPSprite.Update();
}

Vector3 Enemy_HP_UI::SendHPBer(Vector3 size, Vector3 scale)
{
	Vector3 BerSize = size;									//�摜�̌��̑傫��
	Vector3 changedBerSize = Vector3::Zero;					//�摜���X�P�[���ϊ��������Ƃ̑傫��
	Vector3 BerSizeSubtraction = Vector3::Zero;				//���摜�ƕϊ���摜�̃X�P�[����

	changedBerSize.x = BerSize.x * scale.x;
	BerSizeSubtraction.x = BerSize.x - changedBerSize.x;
	BerSizeSubtraction.x *= 0.5f;	//�T�C�Y�����ʂ��Q�Ŋ��邱�Ƃ�,�ړ������鋗�������߂�

	return BerSizeSubtraction;
}

template <class T>
bool Enemy_HP_UI::CalcAngle(T enemy)
{

	//�J��������G�l�~�[�̈ʒu�ւ̃x�N�g�������߂�
	Vector3 toEnemy = enemy->GetPos() - m_camera->GetCameraPos();
	toEnemy.Normalize();


	//�J�����̑O�����ƃJ��������G�l�~�[�ւ̃x�N�g���̓��ς����߂�
	float angle = m_camera->GetCameraForward().Dot(toEnemy);
	

	//���ς̌��ʂ���p�x�����߂�
	angle = acos(angle);	


	//�J�������猩�ăG�l�~�[�����p�x�ȓ��̂Ƃ�
	if (fabsf(angle) <= Math::DegToRad(50.0f))
	{

		//�v���C���[�ƃG�l�~�[�̋��������߂�
		Vector3 diff = enemy->GetPos() - m_player->GetPlayerPosition();


		//��苗���ȓ��Ȃ�
		if (diff.Length() <= 2000.0f)
		{
			//�`�悷��
			return true;
		}

	}

	//�`�悵�Ȃ�
	return false;
}

void Enemy_HP_UI::Render(RenderContext& rc)
{

	//���C���Q�[�������v���C���[�������Ă���Ԃ̂ݕ\��
	if (m_player->GetGameState() != MAIN_GAME_NUM || m_player->GetPlayerDead() != false)
	{
		return;
	}

	
	if (m_enemyNear != nullptr)
	{
		//�`�悷�邩���Ȃ����̏���
		bool canDraw = CalcAngle(m_enemyNear);

		if (canDraw == false)
		{
			return;
		}
	}

	if (m_enemy != nullptr)
	{
		//�`�悷�邩���Ȃ����̏���
		bool canDraw = CalcAngle(m_enemy);

		if (canDraw == false)
		{
			return;
		}
	}

	if (m_enemyFar != nullptr)
	{
		//�`�悷�邩���Ȃ����̏���
		bool canDraw = CalcAngle(m_enemyFar);

		if (canDraw == false)
		{
			return;
		}
	}
	
	//�`��
	m_HPFrameSprite.Draw(rc);
	m_HPSprite.Draw(rc);
}