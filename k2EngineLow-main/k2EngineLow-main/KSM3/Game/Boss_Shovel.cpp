//�V���x���̃p�[�c�B

#include "stdafx.h"
#include "Boss_Shovel.h"
#include "Player.h"
#include "Boss.h"
#include "Boss_Shovel_attack.h"

Boss_Shovel::Boss_Shovel()
{
	b_w_player = FindGO<Player>("player");
}

Boss_Shovel::~Boss_Shovel()
{
	DeleteGO(b_boss_weapons);
}

bool Boss_Shovel::Start()
{
	m_animationClip[enAnimationClip_Idle].Load("Assets/animData/Boss_shovel_idol01.tka");
	m_animationClip[enAnimationClip_Idle].SetLoopFlag(true);
	//������
	boss_Shovel_Render.Init("Assets/modelData/Boss_shovel.tkm");//, 0, 0, m_animationClip, enAnimationClip_Num, enModelUpAxisY);

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
		Move();
		if (attack_ok == true)
		{
			firing_cound++;//�U���̃^�C�~���O�̌v�Z�B
			if (firing_cound % 108 == 0)
			{
				b_boss_weapons = NewGO<Boss_Shovel_attack>(1, "boss_Shovel_attack");
				attack_state = true;
				b_boss_weapons->firing_position = b_w_position;
				b_boss_weapons->b_a_aiming = b_w_boss->boss_rotation;
				b_boss_weapons->b_a_Bullet_Fowrad = b_w_boss->boss_forward;
			}
		}
	}
	if (b_w_player->game_end_state == 1)
	{
		DeleteGO(this);
	}
	boss_Shovel_Render.Update();

	switch (shovelState)
	{
	case 0:
		boss_Shovel_Render.PlayAnimation(enAnimationClip_Idle);
		break;
	}

	boss_Shovel_Render.SetScale(15.0f);
	boss_Shovel_Render.Update();
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