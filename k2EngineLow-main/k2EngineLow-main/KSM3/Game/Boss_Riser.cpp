//���C�U�[�p�[�c�B

#include "stdafx.h"
#include "Boss_Riser.h"
#include "Player.h"
#include "Boss.h"
#include "Boss_Riser_attack.h"
#include "Drop_item.h"
#include "Game.h"

Boss_Riser::Boss_Riser()
{
	m_game = FindGO<Game>("game");
	b_w_player = FindGO<Player>("player");
}

Boss_Riser::~Boss_Riser()
{
	DeleteGO(b_boss_weapons);	
	if (defeatState == true)
	{
		drop_item->drop_kinds = set_weapons;
	}
}

void Boss_Riser::Setup()
{
	m_animationClip[enAnimationClip_Idle].Load("Assets/animData/dozar_idol.tka");
	m_animationClip[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClip[enAnimationClip_attack].Load("Assets/animData/dozar_attack.tka");
	m_animationClip[enAnimationClip_attack].SetLoopFlag(true);


	set_weapons = 1;
	b_w_boss = FindGO<Boss>("boss");
	if (set_weapons == 1)
	{
		boss_Riser_Render.Init("Assets/modelData/Boss_do-ze-1.tkm", true, false, m_animationClip, enAnimationClip_Num, enModelUpAxisZ);
		boss_Riser_Render.Update();
	}
	
	//�L�����R���B
	//boss_riser_characterContller.Init(
	//	450.0f,			//���a�B
	//	40.0f,			//�����B
	//	b_w_position	//���W�B
	//);
	//boss_Riser_Render.SetRotation(b_w_rotation);
	//boss_Riser_Render.SetPosition(b_w_position);
}

void Boss_Riser::Update()
{
	if (fast == 0)
	{
		Setup();
	}
	fast++;
	
	if (b_w_player->game_state == 0 && fast != 0)
	{
		if (fast >= 540 && fast < 810) {
			boss_Riser_Render.PlayAnimation(enAnimationClip_attack,0.5f);
		}
		else {
			boss_Riser_Render.PlayAnimation(enAnimationClip_Idle,0.5f);
		}
		if (fast == 809) {
			DeleteGO(m_weaponEffect);
			m_weaponEffect = nullptr;
			fast = 1;
		}
		
		if (attack_state == 0) {

		}

		if (fast == 640) {
			m_weaponEffect = NewGO<EffectEmitter>(0);
			m_weaponEffect->Init(enBoss_Dozar_Charge);
			m_weaponEffect->SetScale({ 30.0f,30.0f,30.0f });
			
			//efeLP += b_w_position;
			m_weaponEffect->SetPosition(efeLP + b_w_position);
			m_weaponEffect->SetRotation(b_w_rotation);
			m_weaponEffect->Play();
		}

		if (fast == 665)
		{
			b_boss_weapons = NewGO<Boss_Riser_attack>(1, "boss_Riser_attack");
			attack_state = true;
			b_boss_weapons->firing_position = b_w_position;
			b_boss_weapons->b_a_aiming = b_w_boss->boss_rotation;
			b_boss_weapons->b_a_Bullet_Fowrad = b_w_boss->boss_forward;
		}
		Move();
	}
	if (b_w_player->game_end_state == 1)
	{
		DeleteGO(this);
	}
	boss_Riser_Render.Update();

	//b_w_rotation.SetRotationY(atan2(b_w_Fowrad.x, b_w_Fowrad.z));
	//boss_Riser_Render.SetPosition(b_w_position);
	//boss_Riser_Render.SetRotation(b_w_rotation);
	//boss_Riser_Render.Update();
	//PlayerSearch();

	boss_Riser_Render.SetScale(scale);
	if (riser_HP<=0.0f)
	{
		//drop_item = NewGO<Drop_item>(1, "drop_item");
		//drop_item->Drop_position.y += 50.0f;
		defeatState = true;
		DeleteGO(this);
	}
}

void Boss_Riser::Move()
{
	//�����͊ۃp�N����OK
	Quaternion originRotation = b_w_boss->boss_rotation;
	b_w_position = b_w_boss->boss_position;
	Vector3 lp = b_w_localposition;
	originRotation.Multiply(lp);
	b_w_position += lp;
	b_w_rotation = originRotation;
	boss_Riser_Render.SetPosition(b_w_position);
	boss_Riser_Render.SetRotation(b_w_rotation);
}

void Boss_Riser::PlayerSearch()
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

void Boss_Riser::Render(RenderContext& rc)
{
	boss_Riser_Render.Draw(rc);
}