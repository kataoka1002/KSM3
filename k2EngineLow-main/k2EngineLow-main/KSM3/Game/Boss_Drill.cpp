//ドリルのパーツ。

#include "stdafx.h"
#include "Boss_Drill.h"
#include "Player.h"
#include "Boss.h"
#include "Boss_Drill_attack.h"

Boss_Drill::Boss_Drill()
{
	b_w_player = FindGO<Player>("player");
}

Boss_Drill::~Boss_Drill()
{
	DeleteGO(b_boss_weapons);
}

void Boss_Drill::Setup()
{
	set_weapons = 1;
	b_w_boss = FindGO<Boss>("boss");
	if (set_weapons == 1)
	{
		boss_Drill_Render.Init("Assets/modelData/Boss_Drill.tkm");
		boss_Drill_Render.Update();
	}

	//キャラコンいらんのん?
	//キャラコン。
	//boss_riser_characterContller.Init(
	//	450.0f,			//半径。
	//	40.0f,			//高さ。
	//	b_w_position	//座標。
	//);
	//boss_Riser_Render.SetRotation(b_w_rotation);
	//boss_Riser_Render.SetPosition(b_w_position);
}

void Boss_Drill::Update()
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
			firing_cound++;//攻撃のタイミングの計算。
			if (firing_cound % 108 == 0)
			{
				b_boss_weapons = NewGO<Boss_Drill_attack>(1, "boss_Drill_attack");
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
	boss_Drill_Render.Update();

	//b_w_rotation.SetRotationY(atan2(b_w_Fowrad.x, b_w_Fowrad.z));
	//boss_Riser_Render.SetPosition(b_w_position);
	//boss_Riser_Render.SetRotation(b_w_rotation);
	//boss_Riser_Render.Update();
	//PlayerSearch();

	boss_Drill_Render.SetScale(20.0f);
	boss_Drill_Render.Update();
}

void Boss_Drill::Move()
{
	//ここは丸パクリでOK
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

void Boss_Drill::Render(RenderContext& rc)
{
	boss_Drill_Render.Draw(rc);
}