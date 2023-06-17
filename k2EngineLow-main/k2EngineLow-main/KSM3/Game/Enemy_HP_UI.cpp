#include "stdafx.h"
#include "Enemy_HP_UI.h"
#include "Enemy_Near.h"
#include "Enemy.h"
#include "Enemy_Far.h"
#include "Player.h"
#include "Game.h"
#include "GameCamera.h"


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
	m_camera = FindGO<GameCamera>("gamecamera");

	m_HPSprite.Init("Assets/sprite/enemy/enemyHP3.dds", HP_BER_SIZE.x, HP_BER_SIZE.y);
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
		pos = m_enemyNear->GetPos();
		//エネミーの上の方に画像を表示したいので,y座標を少し大きくする。
		pos.y += 160.0f;
	}
	else if (m_enemy != nullptr)
	{
		pos = m_enemy->GetPos();
		//エネミーの上の方に画像を表示したいので,y座標を少し大きくする。
		pos.y += 130.0f;
	}
	else if (m_enemyFar != nullptr)
	{
		pos = m_enemyFar->GetPos();
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
		m_scale.x = m_enemyNear->GetHP() * (1.0 / m_enemyNear->GetMaxHP());
	}
	else if (m_enemy != nullptr)
	{
		m_scale.x = m_enemy->GetHP() * (1.0 / m_enemy->GetMaxHP());
	}
	else if (m_enemyFar != nullptr)
	{
		m_scale.x = m_enemyFar->GetHP() * (1.0 / m_enemyFar->GetMaxHP());
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
	if (m_player->GetGameState() == 0 && m_player->GetPlayerDead() == false)
	{
		//一定距離以内&カメラの視野に入っているなら体力表示
		if (m_enemyNear != nullptr)
		{
			//カメラからエネミーの位置へのベクトルを求める
			Vector3 toEnemy = m_enemyNear->GetPos() - m_camera->pos;
			toEnemy.Normalize();
			//カメラの前向きとカメラからエネミーへのベクトルの内積を求める
			float angle = m_camera->m_cameraForward.Dot(toEnemy);
			angle = acos(angle);	//内積の結果から角度を求める

			//カメラから見てエネミーが一定角度以内のとき
			if (fabsf(angle) <= Math::DegToRad(50.0f))
			{			
				//プレイヤーとエネミーの距離を求める
				Vector3 diff = m_enemyNear->GetPos() - m_player->GetPlayerPosition();
				if (diff.Length() <= 2000.0f)
				{
					m_HPFrameSprite.Draw(rc);
					m_HPSprite.Draw(rc);
				}
			}
		}
		if (m_enemy != nullptr)
		{
			//計算の方法は上と一緒
			Vector3 toEnemy = m_enemy->GetPos() - m_camera->pos;
			toEnemy.Normalize();

			float angle = m_camera->m_cameraForward.Dot(toEnemy);
			angle = acos(angle);

			if (fabsf(angle) <= Math::DegToRad(50.0f))
			{
				Vector3 diff = m_enemy->GetPos() - m_player->GetPlayerPosition();

				if (diff.Length() <= 2000.0f)
				{
					m_HPFrameSprite.Draw(rc);
					m_HPSprite.Draw(rc);
				}
			}
		}
		if (m_enemyFar != nullptr)
		{
			//計算の方法は上と一緒
			Vector3 toEnemy = m_enemyFar->GetPos() - m_camera->pos;
			toEnemy.Normalize();

			float angle = m_camera->m_cameraForward.Dot(toEnemy);
			angle = acos(angle);

			if (fabsf(angle) <= Math::DegToRad(50.0f))
			{
				Vector3 diff = m_enemyFar->GetPos() - m_player->GetPlayerPosition();
				if (diff.Length() <= 2000.0f)
				{
					m_HPFrameSprite.Draw(rc);
					m_HPSprite.Draw(rc);
				}
			}
		}
	}
}