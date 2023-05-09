//�X�g���C�J�[�̃p�[�c�B

#include "stdafx.h"
#include "Boss.h"
#include "Player.h"
#include "Game.h"
#include <time.h>
#include <stdlib.h>
#include "Battle_ship_attack.h"
#include "Drop_item.h"
#include "Boss_Riser.h"
#include "Boss_Shovel.h"
#include "Boss_Drill.h"
#include "Boss_Cannon.h"
#include "Boss_Turbo.h"
#include "Result.h"


Boss::Boss() 
{
	b_player = FindGO<Player>("player");
	b_boss_riser = FindGO<Boss_Riser>("boss_riser");
	//b_boss_riser = NewGO<Boss_Riser>(2, "boss_riser");
	b_boss_shovel = NewGO<Boss_Shovel>(2, "boss_shovel");
	b_boss_drill = NewGO<Boss_Drill>(2, "boss_drill");
	b_boss_cannon = NewGO<Boss_Cannon>(2, "boss_cannon");
	b_boss_turbo = NewGO<Boss_Turbo>(2, "boss_turbo");
}

Boss::~Boss() 
{
	DeleteGO(b_boss_riser);//���C�U�[�̕���폜�B
	DeleteGO(b_boss_shovel);//�V���x���̕���폜�B
	DeleteGO(b_boss_drill);//�h�����̕���폜�B
	DeleteGO(b_boss_cannon);//�L���m���̕���폜�B
	DeleteGO(b_boss_turbo);//�^�[�{�̕���폜�B
	b_player->boss_survival = false;//�{�X�������Ă��邩���v���[���[�ɋ�����
	//�G�l�~�[���ǂ̕���������Ă������擾���A�h���b�v����A�C�e�������߂�
	//�R�R������Ȃ�?
	if (defeat_state == true) 
	{
		drop_item->drop_kinds = b_boss_riser->set_weapons;
		drop_item->drop_kinds = b_boss_shovel->set_weapons;
		drop_item->drop_kinds = b_boss_drill->set_weapons;
		drop_item->drop_kinds = b_boss_cannon->set_weapons;
		drop_item->drop_kinds = b_boss_turbo->set_weapons;
	}
}

bool Boss::Start()
{	
	//boss_rotation.SetRotationY(Math::PI);

	boss_modelRender.Init("Assets/modelData/Boss_core.tkm");
	boss_rotation.SetRotationDegY(180.0f);
	boss_modelRender.SetRotation(boss_rotation);
	boss_modelRender.SetPosition(boss_position);
	//�L�����N�^�[�R���g���[���[���������B
	boss_characterController.Init(
		750.0f,			//���a�B
		40.0f,			//�����B
		boss_position		//���W�B
	);
	return true;
}

void Boss::Update()
{
	boss_modelRender.SetScale(15.0f);
	Damage();

	if (b_player->game_state == 0) {
		
			//PlayerSearch();
		
		boss_modelRender.Update();
		/*if (b_player->attack_state_la == true) {
			
			if (boss_HP <= 0.0f) {
				drop_item = NewGO<Drop_item>(1, "drop_item");
				drop_item->Drop_position = boss_position;
				drop_item->Drop_position.y += 50.0f;
				defeat_state = true;
				DeleteGO(this);
			}
		}*/
	}
	boss_modelRender.Update();
}

void Boss::PlayerSearch()
{
	//�G�l�~�[����v���C���[�������Ă�����ǂ�������
	Vector3 toPlayer = b_player->player_position - boss_position;

	//�v���C���[�Ƃ̋������v�Z����
	float distToPlayer = toPlayer.Length();
	//�v���C���[�Ɍ������ĐL�т�x�N�g���𐳋K������
	Vector3 toPlayerDir = toPlayer;
	toPlayerDir.Normalize();
	//�G�l�~�[�̑O��������toPlayerDir�Ƃ̓��ς��v�Z����
	float t = toPlayerDir.Dot(boss_forward);
	//���ς̌��ʂ�acos�֐��ɓn���āAm_enemyFowrad��toPlayerDir�̂Ȃ��p�x�����߂�B
	float angle = acos(t);

	/*if (fabsf(angle) > Math::DegToRad(45.0f))
	{
		boss_rotation.SetRotationY(atan2(boss_forward.x, boss_forward.z));
		boss_modelRender.SetPosition(boss_position);
		boss_modelRender.SetRotation(boss_rotation);
		boss_modelRender.Update();
	}*/

	if (fabsf(angle) < Math::DegToRad(45.0f)) {
		b_boss_riser->attack_ok = true;
		b_boss_cannon->attack_ok = true;
		b_boss_drill->attack_ok = true;
		b_boss_shovel->attack_ok = true;
		b_boss_turbo->attack_ok = true;
	}
	else {
		b_boss_riser->attack_ok = false;
		b_boss_cannon->attack_ok = false;
		b_boss_drill->attack_ok = false;
		b_boss_shovel->attack_ok = false;
		b_boss_turbo->attack_ok = false;
	}

	//�G�L�����̑O���������X�V����
	boss_forward = toPlayerDir;
	// �G�̑O���������g���āA��]�N�H�[�^�j�I�����v�Z����B
	boss_rotation.SetRotationY(atan2(boss_forward.x, boss_forward.z));
	boss_modelRender.SetPosition(boss_position);
	boss_modelRender.SetRotation(boss_rotation);
	boss_modelRender.Update();
}

void Boss::Move()
 {
	//�G�l�~�[����v���C���[�Ɍ������x�N�g�����v�Z����
	Vector3 toPlayer = b_player->player_position - boss_position;
	//�x�N�g���𐳋K������B
	toPlayer.Normalize();
	//�ړ����x��ݒ肷��B
	boss_moveSpeed = toPlayer * 200.0f;
	//�G�l�~�[���ړ�������
	boss_position = boss_characterController.Execute(boss_moveSpeed, g_gameTime->GetFrameDeltaTime());
	Vector3 modelPosition = boss_position;
}

void Boss::Damage()
{
	//�{�X�����R�[�h�B
	//if (g_pad[0]->IsPress(enButtonY))
	//{
	//	boss_HP = 0.0f;
	//}
	
	//��������烊�U���g��ʂ�GO!!
	if (boss_HP <= 0.0f)
	{
		b_player->game_end_state == 1;
		result = NewGO<Result>(1, "result");

		DeleteGO(this);

	}
}

void Boss::Render(RenderContext& rc)
{
	//���f���̕`��B
	boss_modelRender.Draw(rc);
}
