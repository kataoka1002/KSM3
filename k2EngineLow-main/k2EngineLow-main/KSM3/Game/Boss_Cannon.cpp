#include "stdafx.h"
#include "Boss_Cannon.h"
#include "Player.h"
#include "Boss.h"
#include "Boss_Cannon_attack.h"
#include "Game.h"
#include "Boss_Saber.h"

Boss_Cannon::Boss_Cannon()
{
	
}

Boss_Cannon::~Boss_Cannon()
{

}

void Boss_Cannon::Setup()
{

	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");
	m_boss = FindGO<Boss>("boss");
	m_cannonModel.Init("Assets/modelData/Boss_cannon.tkm");
	m_cannonModel.Update();
	m_enemyCharacterController.Init(
		200.0f,			//���a�B
		70.0f,			//�����B
		m_position	//���W�B
	);
	m_cannonModel.SetScale(m_cannonScale);
	m_cannonModel.Update();
}

void Boss_Cannon::Update()
{

	if (m_fast == 0)
	{
		Setup();
	}
	m_fast++;
	if (m_player->GetGameState() == MAIN_GAME_NUM && m_fast != 0)
	{
		Move();
		Rotation();

		if (m_fireCount == 1800) {
			m_cannonChargeSE = NewGO<SoundSource>(0);			//���Đ�����ƏI���Ȃ̂ŃC���X�^���X��ێ������Ȃ��ׂɂ�����NewGO����
			m_cannonChargeSE->Init(enBoss_Cannon_Charge_SE);		//������
			m_cannonChargeSE->SetVolume(2.0f * m_game->GetSEVol());	//���ʒ���
			m_cannonChargeSE->Play(false);

			m_weaponEffect = NewGO<EffectEmitter>(0);
			m_weaponEffect->Init(enBoss_Cannon_Charge);
			m_weaponEffect->SetScale({ 70.0f,70.0f,70.0f });
			
			m_weaponEffect->SetPosition(m_effectLocalPos + m_position);
			m_weaponEffect->SetRotation(m_rotation);
			m_weaponEffect->Play();
		}

		if (m_weaponEffect != nullptr) {
			if (m_weaponEffect->IsPlay() == true) {
				m_weaponEffect->SetRotation(m_rotation);
				m_weaponEffect->SetPosition(m_effectLocalPos + m_position);
			}
			else {
				DeleteGO(m_weaponEffect);
				m_weaponEffect = nullptr;
			}
		}

		if (m_fireCount == 1935)
		{
			m_cannonAttack = NewGO<Boss_Cannon_attack>(1, "boss_Connon_attack");
			m_attackFlag = true;
			m_cannonAttack->firing_position = m_position;
			m_cannonAttack->b_a_aiming = m_rotation;
			m_cannonAttack->b_a_Bullet_Fowrad = m_forward;
			m_fireCount = 0;
		}
		m_fireCount++;//�U���̃^�C�~���O�̌v�Z�B
		if (m_attackOK == true)
		{
			
			
		}
	}
	if (m_player->GetGameEndState() == 1)
	{
		DeleteGO(this);
	}
	m_cannonModel.Update();


	if (m_HP <= 0.0f)
	{
		DeleteGO(this);
	}
}

void Boss_Cannon::Rotation() {
	//�G�l�~�[����v���C���[�������Ă�����ǂ�������B
	Vector3 toPlayer = m_player->GetPlayerPosition() - m_position;

	//�v���C���[�Ƃ̋������v�Z����B
	float distToPlayer = toPlayer.Length();
	//�v���C���[�Ɍ������ĐL�т�x�N�g���𐳋K������B
	Vector3 toPlayerDir = toPlayer;
	toPlayerDir.Normalize();
	m_forward = toPlayerDir;
	m_rotation.SetRotationY(atan2(m_forward.x, m_forward.z));
	m_cannonModel.SetRotation(m_rotation);
	
}

void Boss_Cannon::Move()
{
	//�����͊ۃp�N����OK
	Quaternion originRotation = m_boss->GetSaber()->m_rotation;
	m_position = m_boss->GetSaber()->m_position;
	Vector3 lp = m_localPosition;
	originRotation.Multiply(lp);
	m_position += lp;
	m_rotation = originRotation;
	m_cannonModel.SetPosition(m_position);
	m_cannonModel.SetRotation(m_rotation);
}

void Boss_Cannon::Render(RenderContext& rc)
{
	m_cannonModel.Draw(rc);
}