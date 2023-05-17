#include "stdafx.h"
#include "Enemy_HP_UI.h"
#include "Enemy_Near.h"
#include "Enemy.h"
#include "Enemy_Far.h"
#include "Player.h"
#include "Game.h"


Enemy_HP_UI::Enemy_HP_UI()
{
	
}

Enemy_HP_UI::~Enemy_HP_UI()
{
	
}

bool Enemy_HP_UI::Start()
{
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");

	m_HPSprite.Init("Assets/sprite/enemy/enemyHP.dds", HP_BER_SIZE.x, HP_BER_SIZE.y);
	m_HPSprite.SetScale(m_scale);
	m_HPFrameSprite.Init("Assets/sprite/enemy/enemyHPFrame.dds", HP_FRAME_SIZE.x, HP_FRAME_SIZE.y);
	m_HPFrameSprite.SetScale(m_scale);


	return true;
}

void Enemy_HP_UI::Update()
{	
	Damage();
	SetPosition();
}

void Enemy_HP_UI::SetPosition()
{
	Vector3 pos;

	//親によってポジションを変える
	if (m_enemyNear != nullptr)
	{
		pos = m_enemyNear->m_enemyPosition;
		//エネミーの上の方に画像を表示したいので,y座標を少し大きくする。
		pos.y += 130.0f;
	}
	else if (m_enemy != nullptr)
	{
		pos = m_enemy->m_enemyPosition;
		//エネミーの上の方に画像を表示したいので,y座標を少し大きくする。
		pos.y += 130.0f;
	}
	else if (m_enemyFar != nullptr)
	{
		pos = m_enemyFar->m_enemyPosition;
		//エネミーの上の方に画像を表示したいので,y座標を少し大きくする。
		pos.y += 250.0f;
	}

	
	//ワールド座標からスクリーン座標を計算。
	//計算結果がm_positionに代入される。
	g_camera3D->CalcScreenPositionFromWorldPosition(m_position, pos);

	m_HPFrameSprite.SetPosition(Vector3(m_position.x, m_position.y, 0.0f));
	m_HPFrameSprite.Update();

	//画像を左に寄せる
	Vector3 BerSizeSubtraction = HPBerSend(HP_BER_SIZE, m_scale);
	m_position.x -= BerSizeSubtraction.x;

	m_HPSprite.SetPosition(Vector3(m_position.x, m_position.y, 0.0f));
	m_HPSprite.Update();	
}

void Enemy_HP_UI::Damage()
{
	//親によってサイズを変える。
	//親の体力の割合からUIのサイズを計算している。
	if (m_enemyNear != nullptr)
	{
		m_scale.x = m_enemyNear->m_enemyHP * (1.0 / m_enemyNear->m_enemyHPMax);
	}
	else if (m_enemy != nullptr)
	{
		m_scale.x = m_enemy->m_enemyHP * (1.0 / m_enemy->m_enemyHPMax);
	}
	else if (m_enemyFar != nullptr)
	{
		m_scale.x = m_enemyFar->m_enemyHP * (1.0 / m_enemyFar->m_enemyHPMax);
	}

	//サイズは0より小さくならない
	if (m_scale.x <= 0.0f)
	{
		m_scale.x = 0.0f;
	}
	
	m_HPSprite.SetScale(m_scale);
	m_HPSprite.Update();
}

Vector3 Enemy_HP_UI::HPBerSend(Vector3 size, Vector3 scale)
{
	Vector3 BerSize = size;									//画像の元の大きさ
	Vector3 changeBerSize = Vector3::Zero;					//画像をスケール変換したあとの大きさ
	Vector3 BerSizeSubtraction = Vector3::Zero;				//元画像と変換後画像の差

	changeBerSize.x = BerSize.x * scale.x;
	BerSizeSubtraction.x = BerSize.x - changeBerSize.x;
	BerSizeSubtraction.x *= 0.5f;	//サイズ減少量を２で割ることで,移動させる距離を求める

	return BerSizeSubtraction;
}

void Enemy_HP_UI::Render(RenderContext& rc)
{
	if (m_player->game_state == 0) 
	{
		//一定距離以内で体力表示
		if (m_enemyNear != nullptr)
		{
			Vector3 diff = m_enemyNear->m_enemyPosition - m_player->player_position;

			if (diff.Length() <= 2000.0f)
			{
				m_HPFrameSprite.Draw(rc);
				m_HPSprite.Draw(rc);
			}
		}
		if (m_enemy != nullptr)
		{
			Vector3 diff = m_enemy->m_enemyPosition - m_player->player_position;

			if (diff.Length() <= 2000.0f)
			{
				m_HPFrameSprite.Draw(rc);
				m_HPSprite.Draw(rc);
			}
		}
		if (m_enemyFar != nullptr)
		{
			Vector3 diff = m_enemyFar->m_enemyPosition - m_player->player_position;
			
			if (diff.Length() <= 2000.0f)
			{
				m_HPFrameSprite.Draw(rc);
				m_HPSprite.Draw(rc);
			}
		}
	}
}