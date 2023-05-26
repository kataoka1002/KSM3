//キャノンのパーツ。

#include "stdafx.h"
#include "Boss_Cannon.h"
#include "Player.h"
#include "Boss.h"
#include "Boss_Cannon_attack.h"
#include "Drop_item.h"
#include "Game.h"

Boss_Cannon::Boss_Cannon()
{
	m_game = FindGO<Game>("game");
	b_w_player = FindGO<Player>("player");
}

Boss_Cannon::~Boss_Cannon()
{

}

void Boss_Cannon::Setup()
{
	b_w_boss = FindGO<Boss>("boss");
	boss_Cannon_Render.Init("Assets/modelData/Boss_cannon.tkm");
	boss_Cannon_Render.Update();
	m_enemyCharacterController.Init(
		200.0f,			//半径。
		70.0f,			//高さ。
		b_w_position	//座標。
	);
	//キャラコン。
	//boss_riser_characterContller.Init(
	//	450.0f,			//半径。
	//	40.0f,			//高さ。
	//	b_w_position	//座標。
	//);
	//boss_Riser_Render.SetRotation(b_w_rotation);
	//boss_Riser_Render.SetPosition(b_w_position);
}

void Boss_Cannon::Update()
{

	if (fast == 0)
	{
		Setup();
	}
	fast++;
	if (b_w_player->game_state == 0 && fast != 0)
	{
		Move();
		if (firing_cound == 600) {
			m_weaponEffect = NewGO<EffectEmitter>(0);
			m_weaponEffect->Init(enBoss_Cannon_Charge);
			m_weaponEffect->SetScale({ 70.0f,70.0f,70.0f });
			Vector3 efeLP= { 0.0f,680.0f,-200.0f };
			efeLP += b_w_position;
			m_weaponEffect->SetPosition(efeLP);
			m_weaponEffect->Play();
		}
		if (firing_cound == 735)
		{
			b_boss_weapons = NewGO<Boss_Cannon_attack>(1, "boss_Connon_attack");
			attack_state = true;
			b_boss_weapons->firing_position = b_w_position;
			b_boss_weapons->b_a_aiming = b_w_boss->boss_rotation;
			b_boss_weapons->b_a_Bullet_Fowrad = b_w_boss->boss_forward;
			firing_cound = 0;
		}
		firing_cound++;//攻撃のタイミングの計算。
		if (attack_ok == true)
		{
			
			
		}
	}
	if (b_w_player->game_end_state == 1)
	{
		DeleteGO(this);
	}
	boss_Cannon_Render.Update();

	//b_w_rotation.SetRotationY(atan2(b_w_Fowrad.x, b_w_Fowrad.z));
	//boss_Riser_Render.SetPosition(b_w_position);
	//boss_Riser_Render.SetRotation(b_w_rotation);
	//boss_Riser_Render.Update();
	//PlayerSearch();

	boss_Cannon_Render.SetScale(15.0f);

	if (connon_HP <= 0.0f)
	{
		drop_item = NewGO<Drop_item>(1, "drop_item");
		drop_item->Drop_position = b_w_position;
		drop_item->Drop_position.y += 50.0f;
		defeatState = true;
		DeleteGO(this);
	}
}

void Boss_Cannon::Move()
{
	//ここは丸パクリでOK
	Quaternion originRotation = b_w_boss->boss_rotation;
	b_w_position = b_w_boss->boss_position;
	Vector3 lp = b_w_localposition;
	originRotation.Multiply(lp);
	b_w_position += lp;
	b_w_rotation = originRotation;
	boss_Cannon_Render.SetPosition(b_w_position);
	boss_Cannon_Render.SetRotation(b_w_rotation);
}

void Boss_Cannon::PlayerSearch()
{
	////エネミーからプレイヤーが入ってきたら追いかける。
	//Vector3 toPlayer = b_w_player->player_position - b_w_position;

	////プレイヤーとの距離を計算する。
	//float distToPlayer = toPlayer.Length();
	////プレイヤーに向かって伸びるベクトルを正規化する。
	//Vector3 toPlayerDir = toPlayer;
	//toPlayerDir.Normalize();
	////エネミーの全方向とtoPlayerDirとの内積を計算する。
	//float t = toPlayerDir.Dot(b_w_Fowrad);
	////内積の結果をacos関数に渡して、m_enemyFowradとtoPlayerDirのなす角度を求める。
	//float angle = acos(t);

	//

	//b_w_Fowrad = toPlayerDir;

}

void Boss_Cannon::Render(RenderContext& rc)
{
	boss_Cannon_Render.Draw(rc);
}