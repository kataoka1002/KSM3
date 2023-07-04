#include "stdafx.h"
#include "Enemy_HP_UI.h"
#include "Enemy_Near.h"
#include "Enemy.h"
#include "Enemy_Far.h"
#include "Player.h"
#include "Game.h"
#include "GameCamera.h"

namespace
{
	//スプライトのサイズ
	const Vector3 HP_BER_SIZE = { 186.0f,13.0f,1.0f };		
	const Vector3 HP_FRAME_SIZE = { 195.0f,22.0f,1.0f };	

	//HPバーのローカルポジション
	const float ENEMY_NEAR_HP_BER_POS_Y = 160.0f;
	const float ENEMY_HP_BER_POS_Y = 130.0f;
	const float ENEMY_FAR_HP_BER_POS_Y = 250.0f;
}

Enemy_HP_UI::Enemy_HP_UI()
{

	//HPバーの初期化
	m_HPSprite.Init("Assets/sprite/enemy/enemyHP3.dds", HP_BER_SIZE.x, HP_BER_SIZE.y);
	m_HPSprite.SetScale(m_scale);


	//HPフレームの初期化
	m_HPFrameSprite.Init("Assets/sprite/enemy/enemyHPFrame.dds", HP_FRAME_SIZE.x, HP_FRAME_SIZE.y);
	m_HPFrameSprite.SetScale(m_scale);

}

Enemy_HP_UI::~Enemy_HP_UI()
{
	
}

bool Enemy_HP_UI::Start()
{

	//クラスを見つける
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");
	m_camera = FindGO<GameCamera>("gamecamera");


	return true;
}

void Enemy_HP_UI::Update()
{	

	//大きさの計算処理
	CalcScale();


	//ポジションの処理
	CalcPosition();

}

void Enemy_HP_UI::CalcPosition()
{
	Vector3 pos;

	//親によってポジションを変える
	if (m_enemyNear != nullptr)
	{

		//ポジションの取得
		pos = m_enemyNear->GetPos();


		//エネミーの上の方に画像を表示したいので,y座標を少し大きくする。
		pos.y += ENEMY_NEAR_HP_BER_POS_Y;

	}
	else if (m_enemy != nullptr)
	{

		//ポジションの取得
		pos = m_enemy->GetPos();


		//エネミーの上の方に画像を表示したいので,y座標を少し大きくする。
		pos.y += ENEMY_HP_BER_POS_Y;

	}
	else if (m_enemyFar != nullptr)
	{

		//ポジションの取得
		pos = m_enemyFar->GetPos();


		//エネミーの上の方に画像を表示したいので,y座標を少し大きくする。
		pos.y += ENEMY_FAR_HP_BER_POS_Y;

	}

	
	//ワールド座標からスクリーン座標を計算(計算結果がm_positionに代入される)
	g_camera3D->CalcScreenPositionFromWorldPosition(m_position, pos);


	//フレームをセットする
	m_HPFrameSprite.SetPosition(Vector3(m_position.x, m_position.y, 0.0f));
	m_HPFrameSprite.Update();


	//画像を左に寄せる
	Vector3 BerSizeSubtraction = SendHPBer(HP_BER_SIZE, m_scale);
	m_position.x -= BerSizeSubtraction.x;


	//HPバーをセットする
	m_HPSprite.SetPosition(Vector3(m_position.x, m_position.y, 0.0f));
	m_HPSprite.Update();	

}

void Enemy_HP_UI::CalcScale()
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

Vector3 Enemy_HP_UI::SendHPBer(Vector3 size, Vector3 scale)
{
	Vector3 BerSize = size;									//画像の元の大きさ
	Vector3 changedBerSize = Vector3::Zero;					//画像をスケール変換したあとの大きさ
	Vector3 BerSizeSubtraction = Vector3::Zero;				//元画像と変換後画像のスケール差

	changedBerSize.x = BerSize.x * scale.x;
	BerSizeSubtraction.x = BerSize.x - changedBerSize.x;
	BerSizeSubtraction.x *= 0.5f;	//サイズ減少量を２で割ることで,移動させる距離を求める

	return BerSizeSubtraction;
}

template <class T>
bool Enemy_HP_UI::CalcAngle(T enemy)
{

	//カメラからエネミーの位置へのベクトルを求める
	Vector3 toEnemy = enemy->GetPos() - m_camera->GetCameraPos();
	toEnemy.Normalize();


	//カメラの前向きとカメラからエネミーへのベクトルの内積を求める
	float angle = m_camera->GetCameraForward().Dot(toEnemy);
	

	//内積の結果から角度を求める
	angle = acos(angle);	


	//カメラから見てエネミーが一定角度以内のとき
	if (fabsf(angle) <= Math::DegToRad(50.0f))
	{

		//プレイヤーとエネミーの距離を求める
		Vector3 diff = enemy->GetPos() - m_player->GetPlayerPosition();


		//一定距離以内なら
		if (diff.Length() <= 2000.0f)
		{
			//描画する
			return true;
		}

	}

	//描画しない
	return false;
}

void Enemy_HP_UI::Render(RenderContext& rc)
{

	//メインゲーム中かつプレイヤーが生きている間のみ表示
	if (m_player->GetGameState() != MAIN_GAME_NUM || m_player->GetPlayerDead() != false)
	{
		return;
	}

	
	if (m_enemyNear != nullptr)
	{
		//描画するかしないかの処理
		bool canDraw = CalcAngle(m_enemyNear);

		if (canDraw == false)
		{
			return;
		}
	}

	if (m_enemy != nullptr)
	{
		//描画するかしないかの処理
		bool canDraw = CalcAngle(m_enemy);

		if (canDraw == false)
		{
			return;
		}
	}

	if (m_enemyFar != nullptr)
	{
		//描画するかしないかの処理
		bool canDraw = CalcAngle(m_enemyFar);

		if (canDraw == false)
		{
			return;
		}
	}
	
	//描画
	m_HPFrameSprite.Draw(rc);
	m_HPSprite.Draw(rc);
}