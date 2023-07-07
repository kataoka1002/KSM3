#include "stdafx.h"
#include "Boss_Saber.h"
#include "Player.h"
#include "Boss.h"
#include "Boss_Cannon_attack.h"
#include "Drop_item.h"
#include "Game.h"

Boss_Saber::Boss_Saber() 
{
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");
}

Boss_Saber::~Boss_Saber() 
{

}

bool Boss_Saber::Start()
{
	Setup();

	return true;
}

void Boss_Saber::Setup() 
{
	m_boss = FindGO<Boss>("boss");
	m_saberModel.Init("Assets/modelData/Boss_Saber.tkm");
	m_saberModel.Update();
	m_enemyCharacterController.Init(
		200.0f,			//半径。
		70.0f,			//高さ。
		m_position	//座標。
	);
	m_saberModel.SetScale(m_scale);
	m_saberModel.Update();
	
}

void Boss_Saber::Update()
{
	if (m_player->GetGameState() == MAIN_GAME_NUM /*&& m_fastFlag != 0*/)
	{
		Move();
	}
	if (m_player->GetGameEndState() == 1)
	{
		DeleteGO(this);
	}
	m_saberModel.Update();
	

	if (m_HP <= 0.0f)
	{
		DeleteGO(this);
	}
}

void Boss_Saber::Move() 
{
	//ここは丸パクリでOK
	Quaternion originRotation = m_boss->GetRotation();
	m_position = m_boss->GetPosition();
	Vector3 lp = m_localPosition;
	originRotation.Multiply(lp);
	m_position += lp;
	m_rotation = originRotation;
	m_saberModel.SetPosition(m_position);
	m_saberModel.SetRotation(m_rotation);
}

void Boss_Saber::Render(RenderContext& rc)
{
	m_saberModel.Draw(rc);
}