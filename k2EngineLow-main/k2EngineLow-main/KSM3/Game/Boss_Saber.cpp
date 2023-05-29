#include "stdafx.h"
#include "Boss_Saber.h"
#include "Player.h"
#include "Boss.h"
#include "Boss_Cannon_attack.h"
#include "Drop_item.h"
#include "Game.h"

Boss_Saber::Boss_Saber() {
	m_game = FindGO<Game>("game");
	b_w_player = FindGO<Player>("player");
}

Boss_Saber::~Boss_Saber() {

}

void Boss_Saber::Setup() {
	b_w_boss = FindGO<Boss>("boss");
	boss_Cannon_Render.Init("Assets/modelData/Boss_Saber.tkm");
	boss_Cannon_Render.Update();
	m_enemyCharacterController.Init(
		200.0f,			//半径。
		70.0f,			//高さ。
		b_w_position	//座標。
	);
	boss_Cannon_Render.SetScale(scale);
	boss_Cannon_Render.Update();
	
}

void Boss_Saber::Update() {
	if (fast == 0)
	{
		Setup();
	}
	fast++;
	if (b_w_player->game_state == 0 && fast != 0)
	{
		Move();
	}
	if (b_w_player->game_end_state == 1)
	{
		DeleteGO(this);
	}
	boss_Cannon_Render.Update();
	

	if (connon_HP <= 0.0f)
	{
		drop_item = NewGO<Drop_item>(1, "drop_item");
		drop_item->Drop_position = b_w_position;
		drop_item->Drop_position.y += 50.0f;
		defeatState = true;
		DeleteGO(this);
	}
}

void Boss_Saber::Move() {
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

void Boss_Saber::Render(RenderContext& rc)
{
	boss_Cannon_Render.Draw(rc);
}