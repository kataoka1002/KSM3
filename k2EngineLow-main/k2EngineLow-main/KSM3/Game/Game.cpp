#include "stdafx.h"
#include "Game.h"
#include "BoxMove.h"
#include "Player.h"
#include "Title.h"
#include "Result.h"
#include "Lighting.h"
#include "Enemy.h"
#include "Left_arm_weapons.h"
#include "Drop_item.h"
#include "BackGround.h"
#include"GameCamera.h"

bool Game::Start()
{
	m_spriteRender.Init("Assets/modelData/utc_nomal.DDS", 100.0f, 100.0f);
	m_spriteRender.SetPosition({ -600.0f,300.0f,0.0f });

	
	//m_modelRender.Init("Assets/modelData/test_player.tkm");

	//m_modelRender.SetPosition(0.0f, 0.0f, 0.0f);

	/*m_levelRender.Init("Assets/level/sample.tkl",
		[&](LevelObjectData2& objData)
		{
			//名前がBox_Moveだったら。
			if (objData.EqualObjectName(L"Box_Move") == true) {

				auto box = NewGO<BoxMove>(0);
				//配置座標、スケール、回転を取得する。
				box->m_position = objData.position;
				box->m_scale = objData.scale;
				box->m_rotation = objData.rotation;
				//後で削除するために、ボックスをプッシュしておく。
				m_boxmoves.push_back(box);

				//trueにすると、レベルの方でモデルが読み込まれない。
				return true;
			}
		});
		*/


	
	//m_modelRender.SetRotation(rot);
	//m_modelRender.SetScale(1.0f);
	//m_modelRender.Update();



	return true;


}

Game::Game()
{
	lighting = NewGO<Lighting>(1, "lighting");
	player = NewGO<Player>(1, "player");
	enemy = NewGO<Enemy>(1, "enemy");
	enemy->enemy_position = { 0.0f,0.0f,2000.0f };
	drop_item = NewGO< Drop_item>(1, "drop_item");
	background = NewGO< BackGround>(1, "background");
	gameCamera = NewGO<GameCamera>(1, "gameCamera");
}

Game::~Game()
{
	//プッシュしたボックスを削除していく。
	for (auto box : m_boxmoves)
	{
		DeleteGO(box);
	}

	DeleteGO(player);
	DeleteGO(enemy);
	if (drop_item->GetState == false) {
		DeleteGO(drop_item);
	}
	DeleteGO(background);
	DeleteGO(gameCamera);
}

void Game::Update()
{
	//wchar_t wcsbuf[256];
	//swprintf_s(wcsbuf, 256, L"%d秒経過!!", int(m_timer));
	//表示するテキストを設定。
	m_fontRender.SetText(L"あいうえお\n");
	//フォントの位置を設定。
	m_fontRender.SetPosition(Vector3(-800.0f, 0.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender.SetScale(2.0f);
	//フォントの色を設定。
	m_fontRender.SetColor({ 1.0f,0.0f,0.0f,1.0f });
	m_timer += g_gameTime->GetFrameDeltaTime();

	//m_modelRender.PlayAnimation(enAnimClip_Idle);


	//m_modelRender.Update();
	m_spriteRender.Update();

	//enemy->enemy_game_state = player->game_state;
	//enemy->enemy_position = player->player_position;

	//pause画面からタイトルへの遷移
	if (player->game_end_state == 1) {
		title = NewGO<Title>(1, "title");
		DeleteGO(this);
	}

	//リザルトへの遷移
	if (g_pad[0]->IsTrigger(enButtonSelect)) {
		result = NewGO<Result>(1, "result");
		DeleteGO(this);
	}

}

void Game::Render(RenderContext& rc)
{
	//m_modelRender.Draw(rc);
	m_spriteRender.Draw(rc);

	//m_fontRender.Draw(rc);
}