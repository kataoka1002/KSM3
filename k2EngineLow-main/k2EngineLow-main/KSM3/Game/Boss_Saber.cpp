#include "stdafx.h"
#include "Boss_Saber.h"
#include "Player.h"
#include "Boss.h"
#include "Boss_Cannon_attack.h"
#include "Drop_item.h"
#include "Game.h"

Boss_Saber::Boss_Saber() {
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");
}

Boss_Saber::~Boss_Saber() {

}

void Boss_Saber::Setup() {
	m_boss = FindGO<Boss>("boss");
	boss_Cannon_Render.Init("Assets/modelData/Boss_Saber.tkm");
	boss_Cannon_Render.Update();
	m_enemyCharacterController.Init(
		200.0f,			//半径。
		70.0f,			//高さ。
		m_position	//座標。
	);
	boss_Cannon_Render.SetScale(scale);
	boss_Cannon_Render.Update();
	
}

void Boss_Saber::Update() {
	if (m_fastFlag == 0)
	{
		Setup();
	}
	m_fastFlag++;
	if (m_player->GetGameState() == MAIN_GAME_NUM && m_fastFlag != 0)
	{
		Move();
	}
	if (m_player->GetGameEndState() == 1)
	{
		DeleteGO(this);
	}
	boss_Cannon_Render.Update();
	

	if (connon_HP <= 0.0f)
	{
		/*m_dropItem = NewGO<Drop_item>(1, "drop_item");
		m_dropItem->m_position = b_w_position;
		m_dropItem->m_position.y += 50.0f;*/
		notHituyou = true;
		DeleteGO(this);
	}
}

void Boss_Saber::Move() {
	//ここは丸パクリでOK
	Quaternion originRotation = m_boss->GetRotation();
	m_position = m_boss->GetPosition();
	Vector3 lp = m_localPosition;
	originRotation.Multiply(lp);
	m_position += lp;
	m_rotation = originRotation;
	boss_Cannon_Render.SetPosition(m_position);
	boss_Cannon_Render.SetRotation(m_rotation);
}

void Boss_Saber::Render(RenderContext& rc)
{
	boss_Cannon_Render.Draw(rc);
}