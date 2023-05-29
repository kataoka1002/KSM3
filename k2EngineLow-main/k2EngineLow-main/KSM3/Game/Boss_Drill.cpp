//�h�����̃p�[�c�B

#include "stdafx.h"
#include "Boss_Drill.h"
#include "Player.h"
#include "Boss.h"
#include "Boss_Drill_attack.h"
#include "Drop_item.h"
#include "Boss_Shovel.h"
#include "Game.h"
#include "Left_arm_weapons.h"
#include "Left_leg_weapons.h"
#include "Right_arm_weapons.h"
#include "Right_leg_weapons.h"
#include "Shoulder_weapons.h"

Boss_Drill::Boss_Drill()
{
	m_game = FindGO<Game>("game");
	b_a_player = FindGO<Player>("player");

	m_animationClip[enAnimationClip_Idle].Load("Assets/animData/Boss_Drill_idol.tka");
	m_animationClip[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClip[enAnimationClip_attack].Load("Assets/animData/Boss_Drill_attack.tka");
	m_animationClip[enAnimationClip_attack].SetLoopFlag(true);
}

Boss_Drill::~Boss_Drill()
{
	if (b_boss_weapons != nullptr) {
		DeleteGO(b_boss_weapons);
	}
	DeleteGO(b_boss_weapons);
	/*if (defeatState == true)
	{
		drop_item->drop_kinds = set_weapons;
	}*/
}

void Boss_Drill::Setup()
{
	set_weapons = 1;
	b_w_boss = FindGO<Boss>("boss");
	if (set_weapons == 1)
	{
		boss_Drill_Render.Init("Assets/modelData/Boss_Drill.tkm", true, false, m_animationClip, enAnimationClip_Num, enModelUpAxisZ);
		boss_Drill_Render.Update();
	}

	
}

void Boss_Drill::Update()
{
	if (fast == 0)
	{
		Setup();
	}
	fast++;
	if (b_a_player->game_state == 0 && fast != 0)
	{
		Move();

		if (fast >= 20 && fast < 140) {
			boss_Drill_Render.PlayAnimation(enAnimationClip_attack, 0.5f);
		}
		else {
			boss_Drill_Render.PlayAnimation(enAnimationClip_Idle, 0.5f);
		}
		if (fast == 20)
		{
			b_boss_weapons = NewGO<Boss_Drill_attack>(1, "boss_Drill_attack");
			attack_state = true;
			b_boss_weapons->firing_position = b_w_position;
			b_boss_weapons->b_a_aiming = b_w_boss->boss_rotation;
			b_boss_weapons->b_a_Bullet_Fowrad = b_w_boss->boss_forward;
		}
		//�U���I�������Z�b�g
		if (fast >=21) {
			if (b_boss_weapons == nullptr) {
				fast = 1;
			}
		}

		



		

		//if (attack_ok == true)
		//{
		//	firing_cound++;//�U���̃^�C�~���O�̌v�Z�B
		//	if (firing_cound % 108 == 0)
		//	{
		//		b_boss_weapons = NewGO<Boss_Drill_attack>(1, "boss_Drill_attack");
		//		attack_state = true;
		//		b_boss_weapons->firing_position = b_w_position;
		//		b_boss_weapons->b_a_aiming = b_w_boss->boss_rotation;
		//		b_boss_weapons->b_a_Bullet_Fowrad = b_w_boss->boss_forward;
		//	}
		//}
	}
	if (b_a_player->game_end_state == 1)
	{
		DeleteGO(this);
	}
	boss_Drill_Render.Update();

	//b_w_rotation.SetRotationY(atan2(b_w_Fowrad.x, b_w_Fowrad.z));
	//boss_Riser_Render.SetPosition(b_w_position);
	//boss_Riser_Render.SetRotation(b_w_rotation);
	//boss_Riser_Render.Update();
	//PlayerSearch();

	boss_Drill_Render.SetScale(Drill_scale);
	boss_Drill_Render.Update();
	if (drill_HP<=0.0f)
	{
		//drop_item = NewGO<Drop_item>(1, "drop_item");
		//drop_item->Drop_position.y += 50.0f;
		//defeatState = true;
		
		//���������ʂƓ����ɃV���x��������
		if (Death_count == 0){
			Explosion_Another = NewGO<EffectEmitter>(0);
			Explosion_Another->Init(enBoss_Explosion_Another);
			Explosion_Another->SetScale({ 25.0f,25.0f,25.0f });
			Explosion_Another->Coercion_destruction = false;	// ����ɏ����Ȃ�
			//efeLP += b_w_position;
			Explosion_Another->SetPosition(efeLP + b_w_position);
			Explosion_Another->SetRotation(b_w_rotation);
			Explosion_Another->Play();
		}
		if (Death_count == 140) {
			Damage();
		}
		if (Death_count>=320&&Death_count<340) {
			Drill_scale -= 1.0f;
			boss_Drill_Render.SetScale(Drill_scale);
		}
		if (Death_count == 320) {
			Explosion_efe = NewGO<EffectEmitter>(0);
			Explosion_efe->Init(enBoss_Explosion);
			Explosion_efe->SetScale({ 70.0f,70.0f,70.0f });
			Explosion_efe->Coercion_destruction = false;	// ����ɏ����Ȃ�
			//efeLP += b_w_position;
			Explosion_efe->SetPosition(efeLP + b_w_position);
			Explosion_efe->SetRotation(b_w_rotation);
			Explosion_efe->Play();
		}
		if (Death_count == 340) {
			DeleteGO(b_w_boss->b_boss_shovel);
			DeleteGO(this);
		}
		

		Death_count++;
	}
}

void Boss_Drill::Move()
{
	//�����͊ۃp�N����OK
	Quaternion originRotation = b_w_boss->boss_rotation;
	b_w_position = b_w_boss->boss_position;
	Vector3 lp = b_w_localposition;
	originRotation.Multiply(lp);
	b_w_position += lp;
	b_w_rotation = originRotation;
	boss_Drill_Render.SetPosition(b_w_position);
	boss_Drill_Render.SetRotation(b_w_rotation);
}

void Boss_Drill::PlayerSearch()
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
void Boss_Drill::Damage()
{
	efePosi = b_w_position;
		//---------------------------------------------------------------------------------------------------
		if (b_a_player != nullptr)	//�v���C���[�̏�񂪓����Ă���Ȃ�
		{
			//�e�ƃv���C���[�̋����𑪂�
			Vector3 diffPlayer = efePosi - Vector3{ b_a_player->player_position.x, b_a_player->player_position.y + 50.0f, b_a_player->player_position.z };

			//����ɂ���ă_���[�W��ς���
			float a = diffPlayer.Length();
				//�����𑪂���ȉ��Ȃ�̗͌���
			if (diffPlayer.Length() <= 2000.0f) //�_���[�W������͈�
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
			if (diffLeftArm.Length() <= 2000.0f) //�_���[�W������͈�
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
			if (diffLeftLeg.Length() <= 2000.0f) //�_���[�W������͈�
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
			if (diffRightArm.Length() <= 2000.0f) //�_���[�W������͈�
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
			if (diffRightLeg.Length() <= 2000.0f) //�_���[�W������͈�
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
			if (diffShoulder.Length() <= 2000.0f) //�_���[�W������͈�
			{
				m_shoulder->S_w_HP -= 200.0f;

			}

		}
		//---------------------------------------------------------------------------------------------------
	
	
}

void Boss_Drill::Render(RenderContext& rc)
{
	boss_Drill_Render.Draw(rc);
}