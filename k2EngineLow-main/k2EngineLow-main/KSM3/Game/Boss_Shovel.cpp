//�V���x���̃p�[�c�B

#include "stdafx.h"
#include "Boss_Shovel.h"
#include "Player.h"
#include "Boss.h"
#include "Boss_Shovel_attack.h"
#include "Drop_item.h"
#include "Game.h"
#include "Left_arm_weapons.h"
#include "Left_leg_weapons.h"
#include "Right_arm_weapons.h"
#include "Right_leg_weapons.h"
#include "Shoulder_weapons.h"

Boss_Shovel::Boss_Shovel()
{
	m_game = FindGO<Game>("game");
	b_w_player = FindGO<Player>("player");
}

Boss_Shovel::~Boss_Shovel()
{
	DeleteGO(b_boss_weapons);
	/*if (defeatState == true)
	{
		drop_item->drop_kinds = set_weapons;
	}*/
}

bool Boss_Shovel::Start()
{
	m_animationClip[enAnimationClip_Idle].Load("Assets/animData/Boss_shovel_idol01.tka");
	m_animationClip[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClip[enAnimationClip_Idle2].Load("Assets/animData/Boss_shovel_idol02.tka");
	m_animationClip[enAnimationClip_Idle2].SetLoopFlag(true);
	m_animationClip[enAnimationClip_Shock_Ground].Load("Assets/animData/Boss_shovel_crash.tka");
	m_animationClip[enAnimationClip_Shock_Ground].SetLoopFlag(true);
	//������
	boss_Shovel_Render.Init("Assets/modelData/Boss_shovel4.tkm", true, true , m_animationClip, enAnimationClip_Num, enModelUpAxisZ);
	//boss_Shovel_Render.Init("Assets/modelData/unityChan.tkm", true,true,m_animationClip, enAnimationClip_Num, enModelUpAxisY);
	if (defeatState == true)
	{
		drop_item->drop_kinds = set_weapons;
	}
	
	return true;
}

void Boss_Shovel::Setup()
{b_w_boss = FindGO<Boss>("boss");
	set_weapons = 1;
	
	if (set_weapons == 1)
	{
		//boss_Shovel_Render.Init("Assets/modelData/Boss_shovel.tkm");
		boss_Shovel_Render.Update();
	}

	//�L�����R���B
	//boss_riser_characterContller.Init(
	//	450.0f,			//���a�B
	//	40.0f,			//�����B
	//	b_w_position	//���W�B
	//);
	//boss_Riser_Render.SetRotation(b_w_rotation);
	//boss_Riser_Render.SetPosition(b_w_position);
	boss_Shovel_Render.SetScale(scale);
	boss_Shovel_Render.Update();
}

void Boss_Shovel::Update()
{
	
	
	if (fast == 0)
	{
		Setup();
		
	}
	fast++;
	if (b_w_player->game_state == 0 && fast != 0)
	{
		if (fast == 400) {
			m_Shovel_roar_SE = NewGO<SoundSource>(0);			//���Đ�����ƏI���Ȃ̂ŃC���X�^���X��ێ������Ȃ��ׂɂ�����NewGO����
			m_Shovel_roar_SE->Init(enBoss_Shovel_roar);		//������
			m_Shovel_roar_SE->SetVolume(2.0f * m_game->GetSEVol());	//���ʒ���
			m_Shovel_roar_SE->Play(false);
		}
		if (fast == 1300) {
			m_Shovel_roar_SE = NewGO<SoundSource>(0);			//���Đ�����ƏI���Ȃ̂ŃC���X�^���X��ێ������Ȃ��ׂɂ�����NewGO����
			m_Shovel_roar_SE->Init(enBoss_Shovel_roar);		//������
			m_Shovel_roar_SE->SetVolume(2.0f * m_game->GetSEVol());	//���ʒ���
			m_Shovel_roar_SE->Play(false);
		}
		if (fast >=270&&fast<630) {
			boss_Shovel_Render.PlayAnimation(enAnimationClip_Idle2,0.5f);
		}
		
		else if (fast >= 1170 && fast < 1500) {
			if (fast == 1400) {

				m_Shovel_shock_SE = NewGO<SoundSource>(0);			//���Đ�����ƏI���Ȃ̂ŃC���X�^���X��ێ������Ȃ��ׂɂ�����NewGO����
				m_Shovel_shock_SE->Init(en_Boss_Shovel_shock);		//������
				m_Shovel_shock_SE->SetVolume(2.0f * m_game->GetSEVol());	//���ʒ���
				m_Shovel_shock_SE->Play(false);

				shovel_shock = NewGO<EffectEmitter>(0);
				shovel_shock->Init(enBoss_Shovel_shock);
				shovel_shock->SetScale({ 70.0f,70.0f,70.0f });
				//efeLP += b_w_position;
				shovel_shock->SetPosition(b_w_position+ shock_efe_lpos);
				shovel_shock->SetRotation(b_w_rotation);
				shovel_shock->Play();
				Damage(0);
			}
			boss_Shovel_Render.PlayAnimation(enAnimationClip_Shock_Ground, 0.5f);
		}
		else if (fast == 1680) {
			
			DeleteGO(shovel_shock);
			shovel_shock = nullptr;
			fast = 0;
		}
		else {
			boss_Shovel_Render.PlayAnimation(enAnimationClip_Idle,0.5f);
		}
		
		Move();
		//if (attack_ok == true)
		//{
		//	firing_cound++;//�U���̃^�C�~���O�̌v�Z�B
		//	if (firing_cound % 108 == 0)
		//	{
		//		b_boss_weapons = NewGO<Boss_Shovel_attack>(1, "boss_Shovel_attack");
		//		attack_state = true;
		//		b_boss_weapons->firing_position = b_w_position;
		//		b_boss_weapons->b_a_aiming = b_w_boss->boss_rotation;
		//		b_boss_weapons->b_a_Bullet_Fowrad = b_w_boss->boss_forward;
		//	}
		//}
	}
	if (b_w_player->game_end_state == 1)
	{
		DeleteGO(this);
	}

	switch (shovelState)
	{
	case 0:
		
		break;
	}

	
	boss_Shovel_Render.Update();

	if (shovel_HP<=0.0f)
	{
		/*drop_item = NewGO<Drop_item>(1, "drop_item");
		drop_item->Drop_position.y += 50.0f;
		defeatState = true;*/
		DeleteGO(this);
	}
}

void Boss_Shovel::Move()
{
	//�����͊ۃp�N����OK
	Quaternion originRotation = b_w_boss->boss_rotation;
	b_w_position = b_w_boss->boss_position;
	Vector3 lp = b_w_localposition;
	originRotation.Multiply(lp);
	b_w_position += lp;
	b_w_rotation = originRotation;
	boss_Shovel_Render.SetPosition(b_w_position);
	boss_Shovel_Render.SetRotation(b_w_rotation);
}

void Boss_Shovel::Damage(int attack_Num) {
	if (attack_Num == 0) {
		//---------------------------------------------------------------------------------------------------
		if (b_w_player != nullptr)	//�v���C���[�̏�񂪓����Ă���Ȃ�
		{
			//�e�ƃv���C���[�̋����𑪂�
			Vector3 diffPlayer = b_w_position + shock_efe_lpos - Vector3{ b_w_player->player_position.x, b_w_player->player_position.y + 50.0f, b_w_player->player_position.z };

			//����ɂ���ă_���[�W��ς���

				//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffPlayer.Length() <= 2000.0f) //�_���[�W������͈�
			{
				b_w_player->m_playerHP -= 10.0f;
				

			}

		}



		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_leftArm != nullptr)	//���r�ɏ�񂪓����Ă���Ȃ�
		{
			//�e�ƍ��r�̋����𑪂�
			Vector3 diffLeftArm = b_w_position + shock_efe_lpos - m_leftArm->GetPosition();

			//����ɂ���ă_���[�W��ς���

				//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffLeftArm.Length() <= 2000.0f) //�_���[�W������͈�
			{
				m_leftArm->ApplyDamage(10.0f);
				

			}
		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_leftLeg != nullptr)	//�����ɏ�񂪓����Ă���Ȃ�
		{
			//�e�ƍ��r�̋����𑪂�
			Vector3 diffLeftLeg = b_w_position + shock_efe_lpos - m_leftLeg->GetPosition();

			//����ɂ���ă_���[�W��ς���

				//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffLeftLeg.Length() <= 2000.0f) //�_���[�W������͈�
			{
				m_leftLeg->ApplyDamage(10.0f);
				

			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_rightArm != nullptr)	//�E��ɏ�񂪓����Ă���Ȃ�
		{
			//�e�ƍ��r�̋����𑪂�
			Vector3 diffRightArm = b_w_position + shock_efe_lpos - m_rightArm->GetPosition();

			//����ɂ���ă_���[�W��ς���

				//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffRightArm.Length() <= 2000.0f) //�_���[�W������͈�
			{
				m_rightArm->ApplyDamage(10.0f);
				

			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_rightLeg != nullptr)	//�E���ɏ�񂪓����Ă���Ȃ�
		{
			//�e�ƍ��r�̋����𑪂�
			Vector3 diffRightLeg = b_w_position + shock_efe_lpos - m_rightLeg->GetPosition();

			//����ɂ���ă_���[�W��ς���

				//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffRightLeg.Length() <= 2000.0f) //�_���[�W������͈�
			{
				m_rightLeg->ApplyDamage(10.0f);
				

			}

		}
		//---------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------
		if (m_shoulder != nullptr)	//���ɏ�񂪓����Ă���Ȃ�
		{
			//�e�ƍ��r�̋����𑪂�
			Vector3 diffShoulder = b_w_position + shock_efe_lpos - m_shoulder->GetPosition();

			//����ɂ���ă_���[�W��ς���

				//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffShoulder.Length() <= 2000.0f) //�_���[�W������͈�
			{
				m_shoulder->ApplyDamage(10.0f);
				Effect();

			}

		}
		//---------------------------------------------------------------------------------------------------
	}
}

void Boss_Shovel::PlayerSearch()
{
	////�G�l�~�[����v���C���[�������Ă�����ǂ�������B
	//Vector3 toPlayer = b_w_player->player_position - b_w_position;

	////�v���C���[�Ƃ̋������v�Z����B
	//float distToPlayer = toPlayer.Length();
	////�v���C���[�Ɍ������ĐL�т�x�N�g���𐳋K������B
	//Vector3 toPlayerDir = toPlayer;
	//toPlayerDir.Normalize();
	////�G�l�~�[�̑S������toPlayerDir�Ƃ̓��ς��v�Z����B
	//float t = toPlayerDir.Dot(b_w_Fowrad);
	////���ς̌��ʂ�acos�֐��ɓn���āAm_enemyFowrad��toPlayerDir�̂Ȃ��p�x�����߂�B
	//float angle = acos(t);

	//

	//b_w_Fowrad = toPlayerDir;

}

void Boss_Shovel::Render(RenderContext& rc)
{
	boss_Shovel_Render.Draw(rc);
}